#ifndef YADRO_TASK_TAPE_INTERFACE
#define YADRO_TASK_TAPE_INTERFACE

class itape {
public:
  virtual void write(int) = 0;
  virtual int read() const = 0;

  virtual void shift_forward() const = 0;
  virtual void shift_back() const = 0;

  virtual void rewind_forward(size_t) const = 0;
  virtual void rewind_back(size_t) const = 0;
  virtual ~itape() = default;
};

#endif // YADRO_TASK_TAPE_INTERFACE
