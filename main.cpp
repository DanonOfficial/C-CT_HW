#include <iostream>
#include "Printer.h"
#include <string>
#include <regex>
#include "Expression.h"
#include "Parser.h"

using namespace std;
int main() {
    asciiArt::Printer a;
    freopen("temporary.txt", "w", stdout);
    string b;
    cin >> b;
    a.pushExpr(b);
    prs::Parser kek(b.c_str());
    a.pushExpr(to_string(prs::eval(kek.parse())));
    a.Test("c(c(2,c(3,3)),c(1,1))", 4);
    regex_replace(b, regex("cC\\s+"), "");
    int depth = 0;
    int temp;

    cout << prs::eval(kek.parse()) << endl;
}