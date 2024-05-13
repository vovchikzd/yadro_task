#include "tape_sort.hpp"

#include <algorithm>

sort_error::sort_error(const char* message): message(message) {}
const char* sort_error::what() const noexcept { return message; }

tape_sort::tape_sort(tape& input_tape, fs::path& tmp_folder, ull max_ram)
    : input_tape(input_tape) {
  reserve_cap((max_ram / sizeof(int)) - 1);
  create_folders(tmp_folder);
}

fs::path tape_sort::get_new_folder() {
  std::stringstream result;
  auto t  = std::time(nullptr);
  auto tm = std::localtime(&t);
  result << "ext-sort_" << std::put_time(tm, "%d-%m-%Y_%H-%M-%S");
  return result.str();
}

void tape_sort::reserve_cap(size_t buf_size) {
  if (buf_size > buf.max_size()) buf_size = buf.max_size();

  while (true) {
    try {
      buf.reserve(buf_size);
      break;
    } catch (std::bad_alloc& exc) {
      buf_size /= 2;
      continue;
    } catch (std::exception& exc) { throw sort_error(exc.what()); }
  }

  if (buf.capacity() <= 1) throw sort_error("Cannot allocate memory");
}

void tape_sort::create_folders(fs::path& tmp_folder) {
  working_folder    = tmp_folder / get_new_folder();
  input_tmp_folder  = working_folder / "init_input";
  output_tmp_folder = working_folder / "init_output";

  try {
    fs::create_directory(working_folder);
    fs::create_directory(input_tmp_folder);
    fs::create_directory(output_tmp_folder);
  } catch (std::bad_alloc& exc) {
    throw sort_error("Cannot create temp directory");
  } catch (fs::filesystem_error& exc) { throw sort_error(exc.what()); }
}

void tape_sort::sort(fs::path& output_file) {
  input_tape.to_begin();
  buf.clear();

  while (!input_tape.eof()) {
    for (size_t counter = 0, buf_cap = buf.capacity();
         counter < buf_cap && !input_tape.eof(); ++counter) {
      buf.push_back(input_tape.read());
      input_tape.shift_forward();
    }
    std::sort(buf.begin(), buf.end());
    write_sorted(buf.begin(), buf.end());
    buf.clear();
  }

  merge_sorted(output_file);
}

void tape_sort::write_sorted(iter begin, iter end) {
  fs::path write_tmp_path(input_tmp_folder
                          / std::to_string(++file_name_counter));
  tape write_tmp_tape(write_tmp_path);
  std::for_each(begin, end, [&out_tape = write_tmp_tape](int value) {
    out_tape.write(value);
    out_tape.shift_forward();
  });
}

void tape_sort::merge_sorted(fs::path& output_file) {
  while (true) {
    fs::directory_iterator folder_iter(input_tmp_folder);
    auto begin         = fs::begin(folder_iter);
    auto end           = fs::end(folder_iter);
    size_t files_count = std::distance(begin, end);
    if (files_count <= 1) break;
    if (files_count % 2 != 0)
      fs::rename(begin->path(),
                 output_tmp_folder / (*begin++).path().filename());
    while (begin != end) { merge((*begin++).path(), (*begin++).path()); }
    swap_directories();
  }
  try {
    fs::rename(fs::begin(fs::directory_iterator(input_tmp_folder))->path(),
               output_file);
  } catch (...) {
    fs::copy(fs::begin(fs::directory_iterator(input_tmp_folder))->path(),
               output_file, fs::copy_options::overwrite_existing);
  }
}

void tape_sort::merge(const fs::path& first, const fs::path& second) {
  tape first_tape(first);
  tape second_tape(second);

  tape result(output_tmp_folder / std::to_string(++file_name_counter));

  while (!first_tape.eof() && !second_tape.eof()) {
    if (first_tape.read() < second_tape.read()) {
      result.write(first_tape.read());
      first_tape.shift_forward();
    } else {
      result.write(second_tape.read());
      second_tape.shift_forward();
    }
    result.shift_forward();
  }

  while (!first_tape.eof()) {
    result.write(first_tape.read());
    first_tape.shift_forward();
    result.shift_forward();
  }

  while (!second_tape.eof()) {
    result.write(second_tape.read());
    second_tape.shift_forward();
    result.shift_forward();
  }
}

void tape_sort::swap_directories() {
  fs::remove_all(input_tmp_folder);
  input_tmp_folder = output_tmp_folder;
  std::stringstream new_name;
  new_name << "new_output" << ++file_name_counter;
  output_tmp_folder = working_folder / new_name.str();

  try {
    fs::create_directory(output_tmp_folder);
  } catch (std::bad_alloc& exc) {
    throw sort_error("Cannot create temp directory");
  } catch (fs::filesystem_error& exc) { throw sort_error(exc.what()); }
}
