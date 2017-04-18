//
// Created by DanonOfficial on 25.03.2017.
//

#ifndef HW_4_PRINTER_H
#define HW_4_PRINTER_H

#include <map>
#include <vector>
#include <string>

namespace asciiArt {
    struct Printer {
    private:
        std::string expr;
        int length, height, depth;
        std::map<char, std::vector<std::string> > alphabet;

        std::vector<std::string> escalateSymbol(int depth, char symbol);

        std::vector<std::string> escalateStringOfSymbol(std::string exp, int depth);

        std::vector<std::string> escalateComb(int depth, std::string comb);


        void findDepth();

    public:
        Printer();

        Printer(std::string a);

        void pushExpr(std::string exp);

        void Test(std::string a, int depth);

        void nonScalePrint(std::string a);

        void scalePrint(std::string a);
    };

}
#endif //HW_4_PRINTER_H
