#ifndef YADRO_TASK_TAPE
#define YADRO_TASK_TAPE

#include <concepts>
#include <exception>
#include <string>

#include "init.hpp"
#include "itape.hpp"
#include "tape_head.hpp"

class tape final: itape {
  tape_head head;
  const ull write_delay{};
  const ull read_delay{};
  const ull rewind_delay{};
  const ull shift_delay{};

  int tape_convert(const std::string& str);
  void tape_sleep(const ull duration);

public:
  tape() = delete;

  template <std::convertible_to<fs::path> T>
  tape(T&& file, ull write_delay = 0, ull read_delay = 0, ull rewind_delay = 0,
       ull shift_delay = 0)
      : head(std::forward<T>(file))
      , write_delay(write_delay)
      , read_delay(read_delay)
      , rewind_delay(rewind_delay)
      , shift_delay(shift_delay) {}

  void write(int number) override;
  int read() override;

  void shift_forward() override;
  void shift_back() override;

  void rewind_forward(size_t offset) override;
  void rewind_back(size_t offset) override;

  void to_end();
  void to_begin();
};


class convert_error final: public std::exception {
  const char* message;

public:
  convert_error() = default;
  convert_error(const char* message);
  const char* what() const noexcept override;
};

#endif  // YADRO_TASK_TAPE
