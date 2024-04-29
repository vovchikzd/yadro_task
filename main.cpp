#include <chrono>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>

namespace fs = std::filesystem;

void print_help(std::ostream& stream = std::cout) {
  stream
      << "Usage: fsort INPUT FILE [OPTIONS]\n\n"
         "Be aware that all invalib options will be ignored (as well as all\n"
         "unrecognized files)\n\n"
         "Options:\n"
         "     -h, --help    print this help message (in case this option "
         "will\n"
         "                   be pass with any others options it will be "
         "ignored)\n\n"
         "     -o,           specify name of outputs file (default is name of\n"
         "                   input file with .res format)\n\n"
         "Setting options (in case any option is passed, it will\n"
         "overwrite option from configure file):\n"
         "     -m,           specify delay to rewind tape\n"
         "     -r,           specify delay to read from tape\n" 
         "     -w,           specify delay to write to tape\n"
         "     -s,           specify delay to shift tape\n\n"
         "     -M,           specify max RAM usage in bytes\n\n"
         "Rules to write configure file:\n"
         "  configure file will be searced in:\n"
         "    {$HOME}/.config/fsort.conf or {$HOME}/.config/fsort/config.conf\n"
         "  all settings are written in the order 'write read rewind shift'\n"
         "and must be space/tab/newline separated\n"
         "  optionally as fifth parameter can be written max RAM usage\n"
         "in bytes\n\n"
         "In case the maximum RAM usage is not specified, I assume\n"
         "the maximum is unlimited"
}

fs::path get_date_time() {
  std::stringstream result;
  auto t  = std::time(nullptr);
  auto tm = *std::localtime(&t);
  result << "fsort_" << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  return fs::path(result.str());
}

fs::path get_tmp_folder() { // TODO
  fs::path default_tmp = "/tmp";

  if (fs::exists(default_tmp) && fs::is_directory(default_tmp)
      && check_perms(default_tmp)) {
    return fs::path(default_tmp/get_date_time());
  }
}

struct Sets { // TODO
  fs::path tmp_folder;
  fs::path output_file;
};

template <std::input_iterator T>
Sets init(T begin, T end) {
  std::string temp_out_filename = *(begin++);
  std::optional<fs::path> output_file;

  std::optional<int> write_delay;
  std::optional<int> read_delay;
  std::optional<int> rewind_delay;
  std::optional<int> shift_delay;
  std::optional<int> max_ram;
  std::optional<fs::path> input_file;

  for (; begin < end; ++begin) {
    if (*(begin) == "-o") {
      output_file = *(++begin);
      continue;
    } else if (*(begin) == "-h" || *(begin) == "--help") {
      std::cout << "'" << *begin << "' ignored\n";
      continue;
    } else if (*(begin) == "-m") {
      try {
       rewind_delay = std::stoi(*(++begin));
      } catch () {} // TODO
    } else if (*(begin) == "-r") {
      try {
       read_delay = std::stoi(*(++begin));
      } catch () {} // TODO
    } else if (*(begin) == "-w") {
      try {
       write_delay = std::stoi(*(++begin));
      } catch () {} // TODO
    } else if (*(begin) == "-s") {
      try {
       shift_delay = std::stoi(*(++begin));
      } catch () {} // TODO
    } else if (*(begin) == "-M") {
      try {
       max_ram = std::stoi(*(++begin));
      } catch () {} // TODO
    } else if (*(begin)[0] == '-') {
       std::cout << "Ignored unrecognized option: '" << *begin << "'\n";
    } else { // TODO
    }
  }

  fs::path tmp_folder = get_tmp_folder(); // TODO
  return result;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cerr << "Should be specified at leas input file\n";
    print_help(std::cerr);
    return EXIT_FAILURE;
  }

  if (argc == 2
      && (std::strcmp(argv[1], "-h") == 0
          || std::strcmp(argv[1], "--help" == 0))) {
    print_help();
    return EXIT_SUCCESS;
  }

  std::vector<std::string> args(argv, argv + argc);

  Sets sets;
  try {
    sets = init(args.begin(), args.end());
  } catch (CustomException& exc) { // TODO
    std::cerr << "ERROR: " << exc.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
