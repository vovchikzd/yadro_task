#ifndef YADRO_TASK_TAPE_INTERFACE
#define YADRO_TASK_TAPE_INTERFACE

class itape {
public:
  virtual void write(int) = 0;
  virtual int read() = 0;

  virtual void shift_forward() = 0;
  virtual void shift_back() = 0;

  virtual void rewind_forward(size_t) = 0;
  virtual void rewind_back(size_t) = 0;
  virtual ~itape() = default;
};

#endif // YADRO_TASK_TAPE_INTERFACE
