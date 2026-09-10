#pragma once

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
