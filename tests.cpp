//
// Created by sofia on 22.12.2020.
//

#include "main.cpp"
#include <string>
#include <gtest/gtest.h>

TEST(ParserTest, SmallTest) {
    std::string alfa;
    char c;
    int k;
    MySolver::inputParse("ab+ a 1", alfa, c, k);

    ASSERT_EQ(1, k);
    ASSERT_EQ('a', c);
    ASSERT_EQ("ab+ ", alfa);
}

TEST(ParserTest, BigTest) {
    std::string alfa;
    char c;
    int k;
    MySolver::inputParse("ab + c.aba. * .bac. + . + * a 2  ", alfa, c, k);

    ASSERT_EQ(2, k);
    ASSERT_EQ('a', c);
    ASSERT_EQ("ab + c.aba. * .bac. + . + * ", alfa);
}



TEST(ParserTest, IncorrectRegexp) {
    std::string alfa;
    char c;
    int k;

    ASSERT_THROW(MyParser::parse("a++aaab+ ", 'a', 1), std::logic_error);
}

TEST(ParserTest, UnknownSymbolsInRegexp) {
    ASSERT_THROW(MyParser::parse("eg+ ", 'a', 1), std::logic_error);
}

TEST(ParserTest, IncorrectRegexp_ConcatinationFail) {
    ASSERT_THROW(MyParser::parse("a+b ", 'a', 1), std::logic_error);
}

TEST(ParserTest, IncorrectRegexp_tryMakeStarFail) {
    ASSERT_THROW(MyParser::parse("*ab+ ", 'a', 1), std::logic_error);
}

TEST(ParserTest, IncorrectRegexp_stateStackSizeFail) {
    ASSERT_THROW(MyParser::parse("aba+ ", 'a', 1), std::logic_error);
}


TEST(ParserTest, NoLastInteger) {
    std::string alfa;
    char c;
    int k;

    ASSERT_THROW(MySolver::inputParse("ab+ a", alfa, c, k), std::logic_error);
}

TEST(ParserTest, NoTargetSymbol) {
    std::string alfa;
    char c;
    int k;

    ASSERT_THROW(MySolver::inputParse("ab+ 1", alfa, c, k), std::logic_error);
}




TEST(AnswerTest, SmallTestTrue) {
    ASSERT_EQ(1, MySolver::getAnswer("ab.a+", 'b',  1));
}

TEST(AnswerTest, BigTestTrue) {
    ASSERT_EQ(1, MySolver::getAnswer("b ab.* c* + +", 'b',  5));
}



TEST(AnswerTest, SmallTestFalse) {
    ASSERT_EQ(0, MySolver::getAnswer("ab.a+", 'b', 7));
}

TEST(AnswerTest, BigTestFalse) {
    ASSERT_EQ(0, MySolver::getAnswer("1 ab. bb. + a*b.+ + ", 'b', 10));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
