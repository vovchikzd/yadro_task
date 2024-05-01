#ifndef YADRO_TASK_INIT
#define YADRO_TASK_INIT

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using ull = unsigned long long int;

struct Conf {
  fs::path input_file, output_file, tmp_folder;
  ull write_delay, read_delay, rewind_delay, shift_delay, max_ram;
};

using args_iter = typename std::vector<std::string>::iterator;
Conf init(args_iter begin, args_iter end);

#endif  // YADRO_TASK_INIT
