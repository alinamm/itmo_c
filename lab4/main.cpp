#include "LN.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "you have to enter only the names of input and output files");
        return 1;
    }
    ifstream in;
    in.open(argv[1]);
    if (!in.is_open()) {
        fprintf(stderr, "can not open file");
        in.close();
        return 1;
    }

    stack<LN> stack;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "+") {
            LN a = stackt.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a + b);
        }
        if (cmd == "-") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(b - a);
        }
        if (cmd == "*") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a * b);
        }
        if (cmd == "+") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a + b);
        }
        if (cmd == ">") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a > b);
        }
        if (cmd == "<") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a < b);
        }
        if (cmd == ">=") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a >= b);
        }
        if (cmd == "<=") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a <= b);
        }
        if (cmd == "==") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a == b);
        }
        if (cmd == "!=") {
            LN a = stack.top();
            stack.pop();
            LN b = stack.top();
            stack.pop();
            stack.push(a != b);
        }

        stack.push(LN(cmd));
    }


    in.close();

    ofstream out;
    out.open(argv[2]);
    if (!out.is_open()) {
        fprintf(stderr, "can not open file");
        out.close();
        return 1;
    }

    while (!stack.empty()) {
        cout << (stack.top().sign_ ? "" : "-");
        for (int i = 0; i < stack.top().len_; i++) {
            cout << stack.top().a_[i];
        }
        stack.pop();
        cout << '\n';
    }

    out.close();

    return 0;
}
