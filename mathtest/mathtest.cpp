#include "mathtest.hpp"
#include <random>

Task::Task() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 100);
  std::uniform_int_distribution<int> distrib2(1, 3); // remove divide
  num1 = distrib(gen);
  num2 = distrib(gen);
  int oper = distrib2(gen);
  if (oper == 1) {
    op = OP_ADD;
    answer = num1 + num2;
  } else if (oper == 2) {
    op = OP_SUBTRACT;
    answer = num1 - num2;
  } else if (oper == 3) {
    op = OP_MULTIPLICATE;
    answer = num1 * num2;
  } else if (oper == 4) {
    op = OP_DIVIDE;
    answer = num1 / num2;
  }
}

Task::Task(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max);
  std::uniform_int_distribution<int> distrib2(1, 3);
  num1 = distrib(gen);
  num2 = distrib(gen);
  int oper = distrib2(gen);
  if (oper == 1) {
    op = OP_ADD;
    answer = num1 + num2;
  } else if (oper == 2) {
    op = OP_SUBTRACT;
    answer = num1 - num2;
  } else if (oper == 3) {
    op = OP_MULTIPLICATE;
    answer = num1 * num2;
  } else if (oper == 4) {
    op = OP_DIVIDE;
    answer = num1 / num2;
  }
}

Task::Task(int min, int max, Operation operation) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max);
  num1 = distrib(gen);
  num2 = distrib(gen);
  if (operation == OP_ADD) {
    op = OP_ADD;
    answer = num1 + num2;
  } else if (operation == OP_SUBTRACT) {
    op = OP_SUBTRACT;
    answer = num1 - num2;
  } else if (operation == OP_MULTIPLICATE) {
    op = OP_MULTIPLICATE;
    answer = num1 * num2;
  } else if (operation == OP_DIVIDE) {
    op = OP_DIVIDE;
    answer = num1 / num2;
  }
}
