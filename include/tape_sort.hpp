#ifndef YADRO_TASK_TAPE_SORT
#define YADRO_TASK_TAPE_SORT

#include <concepts>
#include <exception>
#include <vector>

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
  fs::path working_folder;
  fs::path input_folder;
  fs::path output_folder;
  std::vector<int> buf;
  size_t file_name_counter{};

  fs::path get_new_folder();
  void reserve_cap(size_t buf_size);

  using iter = typename std::vector<int>::iterator;
  void write_sorted(iter begin, iter end);
  void merge_sorted();

public:
  template <std::convertible_to<fs::path> T>
  tape_sort(tape& input_tape, T&& tmp_folder, ull max_ram = 0)
      : input_tape(input_tape) {
    reserve_cap((max_ram / sizeof(int)) - 1);
    working_folder = std::forward<T>(tmp_folder)/get_new_folder();

    try {
      fs::create_directory(working_folder);
    } catch (std::bad_alloc& exc) {
      throw sort_error("Cannot create temp directory");
    } catch (fs::filesystem_error& exc) {
      throw sort_error(exc.what());
    }
  }

  void sort(fs::path& output_file);
};

#endif  // YADRO_TASK_TAPE_SORT
