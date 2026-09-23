#include "mathtest.hpp"
#include <gtest/gtest.h>

TEST(MathTestTest, TestConstructorDefault) {
	Task t;
	int result = 0;
	switch (t.op) {
		case OP_ADD:          result = t.num1 + t.num2; break;
		case OP_SUBTRACT:     result = t.num1 - t.num2; break;
		case OP_MULTIPLICATE: result = t.num1 * t.num2; break;
		case OP_DIVIDE:       result = t.num1 / t.num2; break;
	}
	EXPECT_EQ(t.answer, result);
}

TEST(MathTestClassTest, ConstructorBySize) {
	MathTest mt(5);
	EXPECT_EQ(mt.get_count(), 5);
	EXPECT_EQ(mt.get_correct_count(), 0);
	for (int i = 0; i < 5; ++i) {
		EXPECT_GE(mt.get_task(i).num1, 1);
		EXPECT_LE(mt.get_task(i).num1, 100);
		EXPECT_GE(mt.get_task(i).num2, 1);
		EXPECT_LE(mt.get_task(i).num2, 100);
		EXPECT_EQ(mt.get_user_answer(i), 0);
	}
}

TEST(MathTestClassTest, ConstructorByRange) {
	MathTest mt(10, 1, 5);
	EXPECT_EQ(mt.get_count(), 10);
	for (int i = 0; i < 10; ++i) {
		EXPECT_GE(mt.get_task(i).num1, 1);
		EXPECT_LE(mt.get_task(i).num1, 5);
		EXPECT_GE(mt.get_task(i).num2, 1);
		EXPECT_LE(mt.get_task(i).num2, 5);
	}
}

TEST(MathTestClassTest, ConstructorByOperation) {
	MathTest mt(10, 1, 20, OP_ADD);
	EXPECT_EQ(mt.get_count(), 10);
	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(mt.get_task(i).op, OP_ADD);
		EXPECT_EQ(mt.get_task(i).answer,
		          mt.get_task(i).num1 + mt.get_task(i).num2);
	}
}

TEST(MathTestClassTest, SubmitCorrectAnswer) {
	MathTest mt(3, 1, 10, OP_ADD);
	const Task& t0 = mt.get_task(0);
	EXPECT_TRUE(mt.submit_answer(0, t0.answer));
	EXPECT_EQ(mt.get_user_answer(0), t0.answer);
	EXPECT_EQ(mt.get_correct_count(), 1);
}

TEST(MathTestClassTest, SubmitIncorrectAnswer) {
	MathTest mt(3, 1, 10, OP_ADD);
	const Task& t0 = mt.get_task(0);
	EXPECT_FALSE(mt.submit_answer(0, t0.answer + 1));
	EXPECT_EQ(mt.get_user_answer(0), t0.answer + 1);
	EXPECT_EQ(mt.get_correct_count(), 0);
}

TEST(MathTestClassTest, SubmitTwiceDoesNotDoubleCount) {
	MathTest mt(3, 1, 10, OP_ADD);
	const Task& t0 = mt.get_task(0);
	mt.submit_answer(0, t0.answer);
	mt.submit_answer(0, t0.answer);
	EXPECT_EQ(mt.get_correct_count(), 1);
}

TEST(MathTestClassTest, ResetAnswers) {
	MathTest mt(3, 1, 10, OP_ADD);
	mt.submit_answer(0, mt.get_task(0).answer);
	mt.submit_answer(1, mt.get_task(1).answer);
	EXPECT_EQ(mt.get_correct_count(), 2);

	mt.reset_answers();
	EXPECT_EQ(mt.get_correct_count(), 0);
	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(mt.get_user_answer(i), 0);
}

TEST(MathTestClassTest, FormatQuestion) {
	MathTest mt(1, 5, 5, OP_MULTIPLICATE);
	EXPECT_EQ(mt.format_question(0), "5 * 5");

	MathTest mt2(1, 7, 7, OP_ADD);
	EXPECT_EQ(mt2.format_question(0), "7 + 7");

	MathTest mt3(1, 9, 9, OP_DIVIDE);
	EXPECT_EQ(mt3.format_question(0), "9 / 9");
}

TEST(MathTestClassTest, GetMarkHigh) {
	MathTest mt(10, 1, 10, OP_ADD);
	for (int i = 0; i < 10; ++i)
		mt.submit_answer(i, mt.get_task(i).answer);
	EXPECT_EQ(mt.get_mark(), 'A');   // 100%
}

TEST(MathTestClassTest, GetMarkMiddle) {
	MathTest mt(10, 1, 10, OP_ADD);
	for (int i = 0; i < 5; ++i)
		mt.submit_answer(i, mt.get_task(i).answer);
	EXPECT_EQ(mt.get_mark(), 'C');   // 50%
}

TEST(MathTestClassTest, GetMarkLow) {
	MathTest mt(10, 1, 10, OP_ADD);
	for (int i = 0; i < 2; ++i)
		mt.submit_answer(i, mt.get_task(i).answer);
	EXPECT_EQ(mt.get_mark(), 'D');   // 20%
}

TEST(MathTestClassTest, GetMarkZero) {
	MathTest mt(10, 1, 10, OP_ADD);
	EXPECT_EQ(mt.get_mark(), 'F');   // 0%
}
