#include "pch.h"
#include "mathtest.hpp"

TEST(MathTestTest, TestConstructorDefault) {

	Task t;
	int result;
	switch (t.op) {
		case OP_ADD:
			result = t.num1 + t.num2;
			break;
		case OP_SUBTRACT:
			result = t.num1 - t.num2;
			break;
		case OP_MULTIPLICATE:
			result = t.num1 * t.num2;
			break;
		case OP_DIVIDE:
			result = t.num1 / t.num2;
			break;
	}

	EXPECT_EQ(t.answer, result);
}
