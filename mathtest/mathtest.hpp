#pragma once

#include <string>

enum Operation { OP_ADD, OP_SUBTRACT, OP_MULTIPLICATE, OP_DIVIDE };

struct Task {
  int num1;
  int num2;
  Operation op;
  int answer;

  Task();
  Task(int min, int max);
  Task(int min, int max, Operation op);
};

class MathTest {
private:
  Task* tasks;
  int count;
  int* user_answers;
  int correct_count;
  bool* answered;

public:
  explicit MathTest(int count);
  MathTest(int count, int min, int max);
  MathTest(int count, int min, int max, Operation op);
  ~MathTest();

  // no copy
  MathTest(const MathTest&) = delete;
  MathTest& operator=(const MathTest&) = delete;

  // for tests
  int get_count() const { return count; }
  const Task& get_task(int index) const { return tasks[index]; }
  int get_user_answer(int index) const { return user_answers[index]; }
  int get_correct_count() const { return correct_count; }

  std::string format_question(int index) const;
  bool submit_answer(int index, int answer);
  void reset_answers();
  char get_mark() const;

  void run();
  void show_statistics() const;
};