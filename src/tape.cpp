#include "tape.hpp"

#include <chrono>
#include <thread>
#include <iostream>

using std::chrono::seconds;
using std::this_thread::sleep_for;

void tape::write(int number) {
  if (write_delay != 0) tape_sleep(write_delay);
  head = number;
}

int tape::read() const {
  if (read_delay != 0) tape_sleep(read_delay);
  int result = tape_convert(head.value());
  return result
}

void tape::shift_forward() const {
  if (shift_delay != 0) tape_sleep(shift_delay);
  ++head;
}

void tape::shift_back() const {
  if (shift_delay != 0) tape_sleep(shift_delay);
  --head;
}

void tape::rewind_forward(size_t offset) const {
  if (rewind_delay != 0) tape_sleep(rewind_delay);
  for (size_t cur_offset = 0; cur_offset < offset; ++cur_offset) ++head;
}

void tape::rewind_back(size_t offset) const {
  if (rewind_delay != 0) tape_sleep(rewind_delay);
  for (size_t cur_offset = 0; cur_offset < offset; ++cur_offset) --head;
}

void tape::set_path(const fs::path& path) { head = tape_head(path); }

void tape::tape_sleep(ull duration) const { sleep_for(seconds(duration)); }

int tape::tape_convert(const std::string& str) const {
  int result;
  size_t pos{};

  try {
    result = std::stoi(str, &pos);
  } catch (std::invalid_argument& exc) {
    std::cerr << "ERROR: Cannot convert '" << str << "'\n";
    throw convert_error();
  } catch (std::out_of_range& exc) {
    std::cerr << "ERROR: Too big number '" << str << "'\n";
    throw convert_error();
  }

  if (pos != str.size()) {
    std::cerr << "ERROR: Invalid convert '" << str << "'\n";
    throw convert_error();
  }

  return resutl;
}


convert_error::convert_error(const char* message): message(message) {}

const char* what() const noexcept { return message; }
