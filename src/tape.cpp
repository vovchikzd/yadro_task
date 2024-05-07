#include "tape.hpp"

#include <chrono>
#include <iostream>
#include <thread>

using std::chrono::seconds;
using std::this_thread::sleep_for;

void tape::write(int number) {
  if (write_delay != 0) tape_sleep(write_delay);
  head.write(number);
}

int tape::read() {
  if (read_delay != 0) tape_sleep(read_delay);
  int result = tape_convert(head.value());
  return result;
}

void tape::shift_forward() {
  if (shift_delay != 0) tape_sleep(shift_delay);
  if (!head.eof()) ++head;
}

void tape::shift_back() {
  if (shift_delay != 0) tape_sleep(shift_delay);
  if (!head.bof()) --head;
}

void tape::rewind_forward(size_t offset) {
  if (rewind_delay != 0) tape_sleep(rewind_delay);
  for (size_t cur_offset = 0; cur_offset < offset && !head.eof(); ++cur_offset)
    ++head;
}

void tape::rewind_back(size_t offset) {
  if (rewind_delay != 0) tape_sleep(rewind_delay);
  for (size_t cur_offset = 0; cur_offset < offset && !head.bof(); ++cur_offset)
    --head;
}

void tape::tape_sleep(const ull duration) { sleep_for(seconds(duration)); }

int tape::tape_convert(const std::string& str) {
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

  return result;
}

bool tape::eof() {
  return head.eof();
}

bool tape::bof() {
  return head.bof();
}

void tape::to_end() {
  while (!head.eof()) ++head;
}

void tape::to_begin() {
  while (!head.bof()) --head;
}

fs::path tape::path() {
  return head.get_path();
}

convert_error::convert_error(const char* message): message(message) {}

const char* convert_error::what() const noexcept { return message; }
