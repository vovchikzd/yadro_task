#include "init.hpp"

#include <chrono>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>

fs::path get_tmp_folder() {
  fs::path result;
  try {
    result = fs::temp_directory_path();
  } catch (std::bad_alloc& exc) {
    result = "tmp";
  } catch (fs::filesystem_error& exc) { result = "tmp"; }

  if (!fs::exists(result) || !fs::is_directory(result))
    fs::create_directory(result);
  return result;
}

ull init_convert(const std::string& str) {
  if (str[0] == '-') {
    std::cout << "Cannot convert '" << str << "', use default value\n";
    return 0;
  }

  size_t pos{};
  ull result;

  try {
    result = std::stoull(str, &pos);
  } catch (std::invalid_argument& exc) {
    std::cout << "Cannot convert '" << str << "', use default value\n";
    return 0;
  } catch (std::out_of_range& exc) {
    std::cout << "Value '" << str << "' is too big, use default value\n";
    return 0;
  }

  if (pos != str.size()) {
    std::cout << "Typo in '" << str << "', use default value\n";
    return 0;
  }

  return result;
}

fs::path get_output_file(fs::path& input_file) {
  std::string filename = input_file.filename().string() + ".res";
  fs::path result(filename);
  return result;
}

std::tuple<ull, ull, ull, ull, std::optional<ull>> read_conf(
    fs::path& conf_file) {
  ull write_delay{}, read_delay{}, rewind_delay{}, shift_delay{};
  std::optional<ull> max_ram;

  std::ifstream conf_stream(conf_file);
  std::istream_iterator<std::string> conf_iter(conf_stream);

  for (int counter = 0; counter < 5 && !conf_stream.eof();
       ++counter, ++conf_iter) {
    switch (counter) {
      case 0: write_delay = init_convert(*conf_iter); break;
      case 1: read_delay = init_convert(*conf_iter); break;
      case 2: rewind_delay = init_convert(*conf_iter); break;
      case 3: shift_delay = init_convert(*conf_iter); break;
      case 4: max_ram = init_convert(*conf_iter); break;
    }
  }

  return std::make_tuple(write_delay, read_delay, rewind_delay, shift_delay,
                         max_ram);
}

Conf init(args_iter begin, args_iter end) {
  ++begin;

  std::optional<fs::path> input_file, output_file, config_file;
  ull max_ram = 0;

  for (; begin <= end; ++begin) {
    if ((*begin == "-h") || (*begin == "--help")) {
      std::cout << "'" << *begin << "' option is ignored\n";
    } else if (*begin == "-o") {
      if ((++begin) == end)
        throw std::invalid_argument("No output file specified");
      output_file = *begin;
    } else if (*begin == "-c") {
      if ((++begin) == end)
        throw std::invalid_argument("No config file specified");
      config_file = *begin;
    } else if (*begin == "-m") {
      if ((++begin) == end)
        throw std::invalid_argument("No RAM usage specified");
      max_ram = init_convert(*begin);
    } else if (*begin == "-M") {
      if ((++begin) == end)
        throw std::invalid_argument("No RAM usage specified");
      max_ram = init_convert(*begin);
      if (max_ram > (std::numeric_limits<ull>::max() / 1000000)) {
        std::cout << "Value '" << *begin << "' is too big, use default value\n";
        max_ram = 0;
        continue;
      }
      max_ram *= 1000000;
    } else if ((*begin)[0] == '-') {
      std::cout << "Unrecognized option '" << *begin << "' is ignored\n";
    } else {
      if (!input_file.has_value() && fs::exists(*begin)
          && fs::is_regular_file(*begin))
        input_file = *begin;
      else
        std::cout << "Argument '" << *begin << "' is ignored\n";
    }
  }

  if (!input_file.has_value())
    throw std::invalid_argument("No input file specified");

  if (!output_file.has_value())
    output_file = get_output_file(input_file.value());

  fs::path tmp_folder = get_tmp_folder();

  Conf result{.input_file   = input_file.value(),
              .output_file  = output_file.value(),
              .tmp_folder   = tmp_folder,
              .write_delay  = 0,
              .read_delay   = 0,
              .rewind_delay = 0,
              .shift_delay  = 0,
              .max_ram      = max_ram};

  // write, read, rewind, shift, ram
  if (config_file.has_value()) {
    auto sets           = read_conf(config_file.value());
    result.write_delay  = std::get<0>(sets);
    result.read_delay   = std::get<1>(sets);
    result.rewind_delay = std::get<2>(sets);
    result.shift_delay  = std::get<3>(sets);
    result.max_ram      = std::get<4>(sets).value_or(max_ram);
  }

  return result;
}
