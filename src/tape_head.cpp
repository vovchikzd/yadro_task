#include "tape_head.hpp"

#include <algorithm>
#include <cctype>

bool tape_head::eof() {
  char ch = file_stream.peek();
  return (ch == EOF || ch == '\n');
}

bool tape_head::bof() {
  return file_stream.tellg() == begin_pos;
}

tape_head& tape_head::operator++() {
  if (eof()) return *this;
  file_stream.seekg(12, std::ios::cur);
  readed = false;
  return *this;
}

tape_head& tape_head::operator--() {
  if (bof()) return *this;
  file_stream.seekg(-12, std::ios::cur);
  readed = false;
  return *this;
}

std::string tape_head::value() {
  if (readed) return str;
  if (eof()) return std::string();
  std::string result;
  for (size_t counter = 0; counter < 11; ++counter) {
    char ch = file_stream.get();
    result += ch;
  }
  file_stream.seekg(-11, std::ios::cur);
  readed = true;
  trim(result);
  str = result;
  return result;
}

void tape_head::write(int number) {
  std::string to_write = padding(number);
  auto cur_pos         = file_stream.tellg();
  file_stream << to_write << separator;
  file_stream.seekg(cur_pos);
}

void tape_head::ltrim(std::string& str) {
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(),
                         [](unsigned char ch) { return !std::isspace(ch); }));
}

void tape_head::rtrim(std::string& str) {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            str.end());
}

void tape_head::trim(std::string& str) {
  ltrim(str);
  rtrim(str);
}

std::string tape_head::padding(int number) {
  std::string result = std::to_string(number);
  if (result.size() == 11) return result;
  size_t space_num = 11 - result.size();
  return result + std::string(space_num, ' ');
}

fs::path tape_head::get_path() {
  return file_path;
}
