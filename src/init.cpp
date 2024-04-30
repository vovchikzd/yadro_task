#include "init.hpp"

#include <chrono>
#include <cstring>
#include <ctime>
#include <optional>
#include <sstream>
#include <string>
#include <iostream>
#include <tuple>
#include <filesystem>

namespace fs = std::filesystem;

init_except::init_except(const char* message): message(message) {}

const char* init_except::what() const noexcept {
  return message;
}

void print_error(const char* opt, const char* arg, const char* message) {
  std::cerr << "Error while processing '" << opt << "' option in " << arg << ": " << message << '\n';
  std::cerr << "Use default value\n";
}

fs::path get_date_time_folder() {
  std::stringstream result;
  auto t  = std::time(nullptr);
  auto tm = std::localtime(&t);
  result << "fsort_" << std::put_time(tm, "%d-%m-%Y_%H-%M-%S");
  return fs::path(result.str());
}

fs::path get_tmp_folder() {  // TODO
}

bool check_file(const char* file) {
  return fs::exists(file) && fs::is_regular_file(file);
}

int convert(char* str) {
  size_t pos = 0;
  int result;
  try {
    result = std::stoi(str, &pos);
  } catch (std::invalid_argument& exc) {
    throw init_except("Cannot convert to int");
  } catch (std::out_of_range& exc) {
    throw init_except("Value is too big");
  }

  if (pos != std::strlen(str)) {
    throw init_except("Typo in value");
  }
  return result;
}

Conf init(int argc, char** argv) {
  char** end = argv + argc;
  ++argv;
  std::optional<fs::path> output_file, input_file;
  std::optional<int> write_delay, read_delay, rewind_delay, shift_delay;

  for (; argv < end; ++argv) {
    if (std::strcmp(*(argv), "-o") == 0) {
      output_file = *(++argv);
    } else if (std::strcmp(*(argv), "-h") == 0
               || std::strcmp(*(argv), "--help") == 0) {
      std::cout << "Option '" << *argv << "' is ignored\n";
    } else if (std::strcmp(*(argv), "-m") == 0) {
      try {
        rewind_delay = convert(*(++argv));
      } catch (init_except& exc) {
        print_error("-m", *argv, exc.what());
        rewind_delay = 0;
      }  
    } else if (std::strcmp(*(argv), "-r") == 0) {
      try {
        read_delay = convert(*(++argv));
      } catch (init_except& exc) {
        print_error("-r", *argv, exc.what());
        read_delay = 0; 
      }
    } else if (std::strcmp(*(argv), "-w") == 0) {
      try {
        write_delay = convert(*(++argv));
      } catch (init_except& exc) {
        print_error("-w", *argv, exc.what());
        write_delay = 0;
      }
    } else if (std::strcmp(*(argv), "-s") == 0) {
      try {
        shift_delay = convert(*(++argv));
      } catch (init_except& exc) {
        print_error("-s", *argv, exc.what());
        shift_delay = 0;
      }
    } else if (*(argv)[0] == '-') {
      std::cout << "Unrecognized option: '" << *argv << "' is ignored\n";
    } else {
      if (!input_file.has_value() && check_file(*argv)) {
        input_file = *argv;
        continue;
      }

      std::cout << *argv << " argument is ignored\n";
    }
  }

  if (!input_file.has_value()) {
    throw init_except("No input file specified");
  }

  Conf result;
  fs::path tmp_folder = get_tmp_folder();  // TODO
  return result;
}
