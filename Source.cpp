#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <exception>
#include <stack>
#include <set>
#include <exception>
#include "MyRegexp.h"

State::State(const std::vector<int> rem, bool canSkip) : canSkip(canSkip) {
    remainders = rem;
}

MyParser::MyParser() = default;


void MyParser::tryToSkip_(const State& one, const State& other, std::vector<int>& ans) {
    if (one.remainders.empty() || one.canSkip) {
        for (int a : other.remainders)
            ans.push_back(a);
    }
}

void MyParser::deleteDuplicates_(State& state) {

    std::set<int> uniqueIntegers;
    for (int element : state.remainders) {
        uniqueIntegers.insert(element);
    }

    state.remainders.clear();
    for (int element : uniqueIntegers) {
        state.remainders.push_back(element);
    }
}



State MyParser::concatination(const State& one, const State& other, int mod) {
    std::vector<int> newRemainders;

    for (int a : one.remainders) {
        for (int b : other.remainders) {
            newRemainders.push_back((a + b) % mod);
        }
    }
    tryToSkip_(one, other, newRemainders);
    tryToSkip_(other, one, newRemainders);

    State newState(newRemainders, 0);

    deleteDuplicates_(newState);
    return newState;
}

void MyParser::tryMakeConcatination(std::stack<State>& stateStack, int mod) {
    if (stateStack.size() < 2) {
        throw(std::logic_error(std::string("Regular expression is not correct!")));
    }
    State other = stateStack.top();
    stateStack.pop();
    State one = stateStack.top();
    stateStack.pop();
    stateStack.push(MyParser::concatination(one, other, mod));
}




State MyParser::addition(const State& one, const State& other, int mod) {

    std::vector<int> newRemainders;

    for (int elem : one.remainders)
        newRemainders.push_back(elem);

    for (int elem : other.remainders)
        newRemainders.push_back(elem);

    State newState = State(newRemainders, 0);

    if (one.canSkip && other.canSkip) {
        newState.canSkip = 1;
    }

    deleteDuplicates_(newState);

    return newState;
}

void MyParser::tryMakeAddition(std::stack<State>& stateStack, int mod) {
    if (stateStack.size() < 2) {
        throw(std::logic_error(std::string("Regular expression is not correct!")));
    }
    State other = stateStack.top();
    stateStack.pop();
    State one = stateStack.top();
    stateStack.pop();
    State result = MyParser::addition(one, other, mod);
    stateStack.push(result);
}

///home/sofia/CLionProjects/FormalProjectv2/main.cpp




State MyParser::star(const State& one, int mod) { // Klini's star

    std::vector<State> stateDegres;
    stateDegres.push_back(one);

    for (int i = 2; i < mod * mod; ++i) {
        stateDegres.push_back(MyParser::concatination(stateDegres.back(), one, mod));
    }

    while (stateDegres.size() > 1) {
        State one = stateDegres.back();
        stateDegres.pop_back();

        State other = stateDegres.back();
        stateDegres.pop_back();

        State res = MyParser::addition(one, other, mod);
        stateDegres.push_back(res);
    }

    stateDegres.back().canSkip = 1;
    return stateDegres.back();
}

void MyParser::tryMakeStar(std::stack<State>& stateStack, int mod) { // Klini's star

    if (stateStack.empty()) {
        throw(std::logic_error(std::string("Regular expression is not correct!")));
    }
    State newState = MyParser::star(stateStack.top(), mod);
    stateStack.pop();
    stateStack.push(newState);
}

State MyParser::parse(std::string alfa, char targetChar, int mod) {
    std::stack<State>stateStack;

    for (char c : alfa) {
        if (c == '1') {
            State newState;
            newState.canSkip = 1;
            stateStack.push(newState);

        }
        else if (c == 'a' || c == 'b' || c == 'c') { // yes
            State newState;
            if (c == targetChar) {
                newState.remainders.push_back(1);
            }
            stateStack.push(newState);
        }
        else if (c == '*') {
            tryMakeStar(stateStack, mod);
        }
        else if (c == '.') {
            tryMakeConcatination(stateStack, mod);
        }
        else if (c == '+') {
            tryMakeAddition(stateStack, mod);
        }
        else if (c == ' ') {
        }
        else {
            throw(std::logic_error(std::string("Unknown symbols in regular expression!")));
        }
    }

    if (stateStack.size() != 1) {
        throw(std::logic_error(std::string("Regular expression is nor correct!")));
    }

    return stateStack.top();
}


bool MySolver::getAnswer(std::string alfa, char c, int k) {
    State resultState = MyParser::parse(alfa, c, k);

    for (int item : resultState.remainders) {
        if (item % k == 0) {
            return true;
        }
    }
    return false;
}

void MySolver::tryParseNumber(std::string& input, int&n) {

    std::string number;

    while (input.size() > 0 && input.back() == ' ') {
        input.pop_back();
    }

    while(input.size() > 0) {
        if (input.back() >= '0' && input.back() <= '9') {
            number += input.back();
            input.pop_back();
        }
        else {
            break;
        }
    }

    reverse(number.begin(), number.end());

    n = 0;
    for (int i = 0; i < number.size(); ++i) {
        n *= 10;
        n += (number[i] - '0');
    }

    if (n == 0 || input.size() == 0) {
        throw(std::logic_error(std::string("Input is incorrect!")));
    }
}


void MySolver::tryParseChar(std::string& input, char& targetChar) {
    while (input.size() > 0 && input.back() == ' ') {
        input.pop_back();
    }
    if (input.size() == 0 || !(input.back() >= 'a' && input.back() <= 'z')) {
        throw(std::logic_error(std::string("Input is incorrect!")));
    }
    targetChar = input.back();
    input.pop_back();
}


void MySolver::inputParse(std::string input, std::string& alfa, char& targetChar, int& mod) {

    MySolver::tryParseNumber(input, mod);

    MySolver::tryParseChar(input, targetChar);

    alfa = input;
}


/*
int main() {

    std::string input;
    std::string alfa;
    char c;
    int k;

    getline(std::cin, input);

    MySolver::inputParse(input, alfa, c, k);

    std::cout << MySolver::getAnswer(alfa, c, k);
    return 0;
}
*/
