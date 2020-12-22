#pragma once

#include <string>
#include <vector>
#include <set>
#include <stack>
#include <exception>
/*
class IRegexp {
public:
    IRegexp() {}
    virtual ~IRegexp() = 0;
};

class IParser {
public:
    IParser() = default;

    virtual const IRegexp& parse(std::string alfa) = 0;

    virtual const IRegexp& concatination(const IRegexp& one, const IRegexp& other) = 0; // *
    virtual const IRegexp& addition(const IRegexp& one, const IRegexp& other) = 0; // +
    virtual const IRegexp& star(const IRegexp& one, const IRegexp& other) = 0; // Klini's star

    virtual ~IParser() = 0;
};
*/
class State { //: public IRegexp {
public:
    std::vector<int> remainders = {};
    bool canSkip = 0;

    State() = default;
    State(const std::vector<int> rem, bool canSkip);

    ~State()  = default;
};

class MyParser { //; : public IParser {
    static void tryToSkip_(const State& one, const State& other, std::vector<int>& ans);
    static void deleteDuplicates_(State& state);
public:
    MyParser();
    static State concatination(const State& one, const State& other, int mod);// *
    static State addition(const State& one, const State& other, int nod); // +
    static State star(const State& one, int mod); // Klini's star

    static void tryMakeConcatination(std::stack<State>& stateStack, int mod);// *
    static void tryMakeAddition(std::stack<State>& stateStack, int mod); // +
    static void tryMakeStar(std::stack<State>& stateStack, int mod); // Klini's star

    static State parse(std::string alfa, char c, int mod);

    ~MyParser() = default;
};

class MySolver {
public:
    MySolver() = default;
    static bool getAnswer(std::string alfa, char c, int k);

    static void inputParse(std::string, std::string&, char&, int&);

    static void tryParseNumber(std::string& input, int& n);
    static void tryParseChar(std::string& input, char& targetChar);
};