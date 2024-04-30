#ifndef YADRO_TASK_INIT
#define YADRO_TASK_INIT

#include <exception>

class init_except final: std::exception {
  const char* message;
public:
  init_except(const char* message);
  const char* what() const noexcept override;
};

struct Conf {};

Conf init(int argc, char** argv);

#endif  // YADRO_TASK_INIT
