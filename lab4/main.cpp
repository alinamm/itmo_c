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

    stack<LN> hui;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "+") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a + b);
        }
        if (cmd == "-") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(b - a);
        }
        if (cmd == "*") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a * b);
        }
        if (cmd == "+") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a + b);
        }
        if (cmd == ">") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a > b);
        }
        if (cmd == "<") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a < b);
        }
        if (cmd == ">=") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a >= b);
        }
        if (cmd == "<=") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a <= b);
        }
        if (cmd == "==") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a == b);
        }
        if (cmd == "!=") {
            LN a = hui.top();
            hui.pop();
            LN b = hui.top();
            hui.pop();
            hui.push(a != b);
        }

        hui.push(LN(cmd));
    }


    in.close();

    ofstream out;
    out.open(argv[2]);
    if (!out.is_open()) {
        fprintf(stderr, "can not open file");
        out.close();
        return 1;
    }

    while (!hui.empty()) {
        cout << (hui.top().sign_ ? "" : "-");
        for (int i = 0; i < hui.top().len_; i++) {
            cout << hui.top().a_[i];
        }
        hui.pop();
        cout << '\n';
    }

    out.close();

    return 0;
}
