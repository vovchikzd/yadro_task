#include <cstring>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

#include "init.hpp"


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
         "Rules to write configure file:\n"
         "  configure file will be searced in:\n"
         "    {$HOME}/.config/fsort.conf or {$HOME}/.config/fsort/config.conf\n"
         "  all settings are written in the order 'write read rewind shift'\n"
         "and must be space/tab/newline separated\n";
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cerr << "Should be specified at leas input file\n";
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
    conf = init(argc, argv);
  } catch (init_except& exc) { // TODO
    std::cerr << "ERROR: " << exc.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
