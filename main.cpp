#include <cstring>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

#include "init.hpp"
#include "tape.hpp"

//std::string get_date_time() {
//  std::stringstream result;
//  auto t  = std::time(nullptr);
//  auto tm = std::localtime(&t);
//  result << std::put_time(tm, "%d-%m-%Y_%H-%M-%S");
//  return result.str();
//}

void print_help(std::ostream& stream = std::cout) {
  stream
    << "Usage: ext-sort INPUT FILE [OPTION ARGUMENT]\n\n"
       "Tape file (input file) must has newline separated data, otherwise write\n"
       "  to this tape is ambiguous\n"
       "Be aware that all invalib options will be ignored (as well as all\n"
       "  unrecognized arguments)\n"
       "First argument being a file is considered as input file\n\n"
       "Options:\n"
       "     -h, --help    print this help message (in case this option "
       "will\n"
       "                   be pass with any others options it will be "
       "ignored)\n\n"
       "     -o,           specify name of outputs file (default is name of\n"
       "                   input file with .res format)\n\n"
       "     -c,           specify config file, all settings are written in\n"
       "                   in the order 'write read rewind shift' and must\n"
       "                   be space/tab/newline separated. All delays in seconds.\n"
       "                   Optionally as fifth setting can be specifed max\n"
       "                   availabe RAM in bytes\n\n"
       "     -m,           specify max available RAM for sort in bytes\n\n"
       "     -M,           specify max abailable RAM for sort in megabytes\n\n"
       "Default value for any setting is zero.\n"
       "To skip any setting in config file, its value must be zero.\n"
       "If max RAM not specified (or specified as zero) I assume that\n"
       "  there isn't restriction in RAM usage.\n"
       "In case max RAM usage is specified both through config file and argument,\n"
       "  the value from file is used\n"
       "All numbers are expected to be integer non-negative values, otherwise will\n"
       "  be used default (zero) value";
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cerr << "Should be specified at leas input file\n";
    print_help(std::cerr);
    return EXIT_FAILURE;
  }

  if (argc > 11) {
    std::cerr << "ERROR: Too many argument passed\n";
    print_help(std::cerr);
    return EXIT_FAILURE;
  }

  if (argc == 2
      && (std::strcmp(argv[1], "-h") == 0
          || std::strcmp(argv[1], "--help") == 0)) {
    print_help();
    return EXIT_SUCCESS;
  }

  Conf conf;
  try {
    std::vector<std::string> args(argv + 1, argv + argc);
    conf = init(args.begin(), args.end());
  } catch (std::invalid_argument& exc) {
    std::cerr << "ERROR: " << exc.what() << '\n';
    return EXIT_FAILURE;
  } catch (std::exception& exc) {
    std::cerr << "ERROR: " << exc.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
