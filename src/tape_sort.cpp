#include "tape_sort.hpp"
#include <algorithm>

sort_error::sort_error(const char* message): message(message) {}
const char* sort_error::what() const noexcept { return message; }

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

  merge_sorted();
}
