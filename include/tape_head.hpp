#ifndef YADRO_TASK_TAPE_HEAD
#define YADRO_TASK_TAPE_HEAD

#include <concepts>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class tape_head final {
  const fs::path file_path;
  std::fstream file_stream;
  std::fpos<mbstate_t> begin_pos;
  char separator;
  bool readed = false;
  std::string str{};


  void ltrim(std::string& str);
  void rtrim(std::string& str);
  void trim(std::string& str);
  std::string padding(int number);

public:
  template <std::convertible_to<fs::path> T>
  tape_head(T&& path)
      : file_path(std::forward<T>(path))
      , file_stream(file_path, std::ios::in | std::ios::out) {

    if (!file_stream.is_open()) {
      file_stream.clear();
      file_stream.open(file_path, std::ios::out); // create folder
      file_stream.close();
      file_stream.open(file_path, std::ios::in | std::ios::out);
    }

    char peeked = file_stream.peek();
    if (peeked == EOF || peeked == '\n') { separator = '\n'; } 
    else {
      file_stream.seekg(11, std::ios::cur);
      separator = file_stream.peek();
      file_stream.seekg(begin_pos);
    }

    begin_pos = file_stream.tellg();
  }

  void write(int number);
  bool eof();
  bool bof();
  std::string value();

  tape_head& operator++();
  tape_head& operator--();
  fs::path get_path();
};

#endif  // YADRO_TASK_TAPE_HEAD
