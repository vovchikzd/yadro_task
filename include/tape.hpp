#ifndef YADRO_TASK_TAPE
#define YADRO_TASK_TAPE

#include <concepts>
#include <string>
#include <exception>

#include "init.hpp"
#include "itape.hpp"
#include "tape_head.hpp"

class tape final: itape {
  tape_head head;
  ull write_delay{};
  ull read_delay{};
  ull rewind_delay{};
  ull shift_delay{};

  int tape_convert(const std::string& str) const;
  void tape_sleep(ull duration) const;
public:
  tape() = default;

  template <std::convertible_to<fs::path> T>
  tape(T&& file, ull write_delay, ull read_delay, ull rewind_delay,
       ull shift_delay)
      : head(std::forward<T>(file))
      , write_delay(write_delay)
      , read_delay(read_delay)
      , rewind_delay(rewind_delay)
      , shift_delay(shift_delay) {}

  void write(int number) override;
  int read() const override;

  void shift_forward() const override;
  void shift_back() const override;

  void rewind_forward(size_t offset) const override;
  void rewind_back(size_t offset) const override;

  void set_path(const fs::path& path);   
};

class convert_error final: public std::exception {
  const char* message;
public:
  convert_error() = default;
  convert_error(const char* message);
  const char* what() const noexcept override;
};

#endif // YADRO_TASK_TAPE
