#include "mathtest.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>

Task::Task() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 100);
  std::uniform_int_distribution<int> distrib2(1, 3); // remove divide
  num1 = distrib(gen);
  num2 = distrib(gen);
  int oper = distrib2(gen);
  switch (oper) {
  case 1: op = OP_ADD;          answer = num1 + num2; break;
  case 2: op = OP_SUBTRACT;     answer = num1 - num2; break;
  case 3: op = OP_MULTIPLICATE; answer = num1 * num2; break;
  default: op = OP_DIVIDE;      answer = num1 / num2; break;
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
  switch (oper) {
  case 1: op = OP_ADD;          answer = num1 + num2; break;
  case 2: op = OP_SUBTRACT;     answer = num1 - num2; break;
  case 3: op = OP_MULTIPLICATE; answer = num1 * num2; break;
  default: op = OP_DIVIDE;      answer = num1 / num2; break;
  }
}

Task::Task(int min, int max, Operation operation) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max);
  num1 = distrib(gen);
  num2 = distrib(gen);
  op = operation;
  if (op == OP_DIVIDE && num2 == 0) num2 = 1; // ! /0
  switch (op) {
  case OP_ADD:          answer = num1 + num2; break;
  case OP_SUBTRACT:     answer = num1 - num2; break;
  case OP_MULTIPLICATE: answer = num1 * num2; break;
  case OP_DIVIDE:       answer = num1 / num2; break;
  }
}

static const char *op_symbol(Operation op) {
  switch (op) {
  case OP_ADD:          return "+";
  case OP_SUBTRACT:     return "-";
  case OP_MULTIPLICATE: return "*";
  case OP_DIVIDE:       return "/";
  }
  return "?";
}

static void check_count(int count) {
  if (count <= 0)
    throw std::invalid_argument("MathTest: count must be > 0");
}

static void check_range(int min, int max) {
  if (max < min)
    throw std::invalid_argument("MathTest: max must be >= min");
}


MathTest::MathTest(int count) : count(count), correct_count(0) {
  check_count(count);
  tasks = new Task[count];
  user_answers = new int[count];
  answered = new bool[count];
  for (int i = 0; i < count; ++i) {
    user_answers[i] = 0;
    answered[i] = false;
  }
}

MathTest::MathTest(int count, int min, int max)
    : count(count), correct_count(0) {
  check_count(count);
  check_range(min, max);
  tasks = new Task[count];
  user_answers = new int[count];
  answered = new bool[count];
  for (int i = 0; i < count; ++i) {
    tasks[i] = Task(min, max);
    user_answers[i] = 0;
    answered[i] = false;
  }
}

MathTest::MathTest(int count, int min, int max, Operation op)
    : count(count), correct_count(0) {
  check_count(count);
  check_range(min, max);
  tasks = new Task[count];
  user_answers = new int[count];
  answered = new bool[count];
  for (int i = 0; i < count; ++i) {
    tasks[i] = Task(min, max, op);
    user_answers[i] = 0;
    answered[i] = false;
  }
}

MathTest::~MathTest() {
  delete[] tasks;
  delete[] user_answers;
  delete[] answered;
}

std::string MathTest::format_question(int index) const {
  if (index < 0 || index >= count)
    throw std::out_of_range("format_question: index out of range");
  std::ostringstream oss;
  oss << tasks[index].num1 << " " << op_symbol(tasks[index].op) << " "
      << tasks[index].num2;
  return oss.str();
}

bool MathTest::submit_answer(int index, int answer) {
  if (index < 0 || index >= count)
    throw std::out_of_range("submit_answer: index out of range");

  if (answered[index])
    return user_answers[index] == tasks[index].answer;

  answered[index] = true;
  user_answers[index] = answer;

  bool correct = (answer == tasks[index].answer);
  if (correct) ++correct_count;
  return correct;
}

void MathTest::reset_answers() {
  for (int i = 0; i < count; ++i) {
    user_answers[i] = 0;
    answered[i] = false;
  }
  correct_count = 0;
}

char MathTest::get_mark() const {
  if (count <= 0) return 'F';
  double ratio = static_cast<double>(correct_count) / count;
  if (ratio >= 0.9) return 'A';
  if (ratio >= 0.7) return 'B';
  if (ratio >= 0.4) return 'C';
  if (ratio >= 0.2) return 'D';
  return 'F';
}

void MathTest::run() {
  reset_answers();
  for (int i = 0; i < count; ++i) {
    std::cout << "Question " << (i + 1) << "/" << count << ": "
              << format_question(i) << " = ?\n";
    std::cout << "Your answer: ";
    int ans;
    if (!(std::cin >> ans)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input, skipping.\n";
      continue;
    }
    submit_answer(i, ans);
  }
}

void MathTest::show_statistics() const {
  const int label_w = 12;
  const int data_w = 8;

  std::cout << "|" << std::setw(label_w) << "No" << " |";
  for (int i = 0; i < count; ++i)
    std::cout << std::setw(data_w) << (i + 1) << " |";
  std::cout << "\n";

  std::cout << "+";
  for (int i = 0; i < label_w + 1; ++i) std::cout << "-";
  std::cout << "+";
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < data_w + 1; ++j) std::cout << "-";
    std::cout << "+";
  }
  std::cout << "\n";

  std::cout << "|" << std::setw(label_w) << "Question" << " |";
  for (int i = 0; i < count; ++i)
    std::cout << std::setw(data_w) << format_question(i) << " |";
  std::cout << "\n";

  std::cout << "|" << std::setw(label_w) << "True Answer" << " |";
  for (int i = 0; i < count; ++i)
    std::cout << std::setw(data_w) << tasks[i].answer << " |";
  std::cout << "\n";

  std::cout << "|" << std::setw(label_w) << "Your Answer" << " |";
  for (int i = 0; i < count; ++i)
    std::cout << std::setw(data_w) << user_answers[i] << " |";
  std::cout << "\n";

  std::cout << "|" << std::setw(label_w) << "Result" << " |";
  for (int i = 0; i < count; ++i) {
    const char *r =
        (answered[i] && user_answers[i] == tasks[i].answer) ? "+" : "-";
    std::cout << std::setw(data_w) << r << " |";
  }
  std::cout << "\n\n";

  std::cout << "Total Result: " << correct_count << " / " << count
            << " (mark: " << get_mark() << ")\n";
}