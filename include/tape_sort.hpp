#ifndef YADRO_TASK_TAPE_SORT
#define YADRO_TASK_TAPE_SORT

#include <concepts>
#include <vector>
#include <exception>

#include "tape.hpp"

class sort_error: public std::exception {
  const char* message = nullptr;

public:
  sort_error() = default;
  sort_error(const char* message);
  const char* what() const noexcept override;
};



class tape_sort {
  tape& input_tape;
  fs::path tmp_folder;
  std::vector<int> buf;

public:
  template <std::convertible_to<fs::path> T>
  tape_sort(tape& input_tape, T&& tmp_folder, ull max_ram = 0)
      : input_tape(input_tape), tmp_folder(std::forward<T>(tmp_folder)) {
    size_t buf_size = (max_ram / sizeof(int)) - 1;
    if (buf_size > buf.max_size()) buf_size = buf.max_size();

    try {
      buf.reserve(buf_size);
    } catch (std::bad_alloc& exc) {
      throw sort_error("Cannot allocate memory");
    } catch (std::exception& exc) { throw sort_error(exc.what()); }
  }

  void sort(fs::path& output_file);
};

#endif  // YADRO_TASK_TAPE_SORT
