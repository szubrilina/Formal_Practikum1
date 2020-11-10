#include "Source.cpp"
#include <gtest/gtest.h>

TEST(getAnswerTest, OnlyAdditingTestTrue) { 
    //ASSERT_EQ(6, squareRoot(36.0));
    //ASSERT_EQ(18.0, squareRoot(324.0));
    //ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(1, getAnswer("ab+ a 1"));
}

TEST(getAnswerTest, AdditingAndMultiplyingTestTrue) {
    ASSERT_EQ(1, getAnswer("ab.a+ b 1"));
}

TEST(getAnswerTest, AdditingAndMultiplyingAndKliniStarTestTrue_test1) {
    ASSERT_EQ(1, getAnswer("ab + c.aba. * .bac. + . + * a 2"));
}

TEST(getAnswerTest, AdditionAndMultiplyingAndKliniStarTestTrue_test2) {
    ASSERT_EQ(1, getAnswer("aba. * .a. * ab1 + .. a 2"));
}

TEST(getAnswerTest, AdditionalAndMultiplyingAndKliniStarTestFalse) {
    ASSERT_EQ(0, getAnswer("ab. bb. + a*b.+ b 10"));
}

TEST(getAnswerTest, IncorrectRegularExpression) {
    ASSERT_EQ(-1, getAnswer("ab.abcbas.+ b 10"));
}

TEST(getAnswerTest, IncorrectInputAndCorrectRegExpression_test1) {
    ASSERT_EQ(-1, getAnswer("ab. c"));
}

TEST(getAnswerTest, IncorrectInputAndCorrectRegEcpression_test2) {
    ASSERT_EQ(-1, getAnswer("ab. c"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
