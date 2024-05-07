#include "tape_sort.hpp"

void tape_sort::sort(fs::path& output_file) {
  input_tape.to_begin();
  buf.clear();

  while(!input_tape.eof()) {
    for (size_t counter = 0; counter < buf.capacity() && !input_tape.eof();
         ++counter) {
      buf.push_back(input_tape.read());
      input_tape.shift_forward();
    }
  }
}
