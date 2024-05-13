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
  fs::path input_tmp_folder;
  fs::path output_tmp_folder;
  std::vector<int> buf;
  size_t file_name_counter{};

  fs::path get_new_folder();
  void reserve_cap(size_t buf_size);

  using iter = typename std::vector<int>::iterator;
  void write_sorted(iter begin, iter end);
  void merge_sorted(fs::path& output_file);
  void create_folders(fs::path& tmp_folder);
  void swap_directories();
  void merge(const fs::path& first, const fs::path& second);

public:
  tape_sort(tape& input_tape, fs::path& tmp_folder, ull max_ram = 0);

  void sort(fs::path& output_file);
};

#endif  // YADRO_TASK_TAPE_SORT
