//
// Created by DanonOfficial on 25.03.2017.
//
#include "Printer.h"
#include <iostream>
#include <cmath>
#include <ntdef.h>

namespace asciiArt {
    void getLeftAndRight(std::string &left, std::string &right, std::string comb);

    void formatting(std::vector<std::string> &a);

    Printer::Printer() {
        freopen("test.txt", "r", stdin);
        std::cin >> height >> length;
        std::cout << height << " " << length << std::endl;
        std::string in;
        char temp;
        while (getline(std::cin, in)) {
            if (in[0] == '>') {
                temp = in[1];
                std::vector<std::string> ch;
                for (int i = 0; i < height; i++) {
                    getline(std::cin, in);
                    while (in.length() < length) {
                        in.push_back(' ');
                    }
                    ch.push_back(in);
                }
                alphabet.insert(std::make_pair(temp, ch));
            }
        }
        depth = 0;
        expr = "";
        fclose(stdin);
    }

    Printer::Printer(std::string a) {
        Printer();
        std::cout << "new: " << height << " " << length << std::endl;
        expr = a;
        findDepth();
        std::cout << depth << std::endl;
    }

    void Printer::pushExpr(std::string exp) {
        expr += exp;
        findDepth();
    }

    void Printer::nonScalePrint(std::string exp) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < exp.length(); j++) {
                std::cout << alphabet[exp[j]][i];
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> Printer::escalateSymbol(int depth, char symbol) {
        std::vector<std::string> res;
        std::cout << height << " " << length << std::endl;
        std::cout << alphabet['c'].size() << std::endl;
        for (int i = 0; i < height; i++) {
            for (int k = 0; k < pow(2, depth - 1); k++) {
                std::string partOfRes;
                for (int j = 0; j < length; j++) {
                    for (int p = 0; p < pow(2, depth - 1); p++) {
                        partOfRes.push_back(alphabet[symbol][i][j]);
                    }
                }
                res.push_back(partOfRes);
            }
        }
        return res;
    }

    std::vector<std::string> Printer::escalateStringOfSymbol(std::string exp, int depth) {
        std::vector<std::string> res;
        for (int i = 0; i < exp.length(); i++) {
            std::vector<std::string> temp = escalateSymbol(depth, exp[i]);
            for (int j = 0; j < temp.size(); j++) {
                if (i == 0) {
                    res.push_back(temp[j]);
                } else {
                    res[j] += temp[j];
                }
            }
        }
        std::cout << "kek" << std::endl;
        return res;
    }

    std::vector<std::string> Printer::escalateComb(int depth, std::string comb) {
        //TODO: Рекурсивно вызвать для C, напрямую обработать для остального
        std::vector<std::string> res = escalateSymbol(depth, 'c');
        for (int i = 0; i < res.size(); i++) {
            std::cout << res[i] << "\n";
        }
        std::string left, right;
        getLeftAndRight(left, right, comb);
        std::vector<std::string> upPart;
        std::vector<std::string> downSide;
        std::cout << left << " loles " << right << "\n";
        if (left[0] != 'c') {
            upPart = escalateStringOfSymbol(left, depth - 1);
        } else {
            upPart = escalateComb(depth - 1, left);
        }

        int i = 0;
        for (; i < upPart.size(); i++) {
            res[i] += upPart[i];
        }
        if (right[0] != 'c') {
            downSide = escalateStringOfSymbol(right, depth - 1);
        } else {
            downSide = escalateComb(depth - 1, right);
        }
        for (int k = 0; k < downSide.size(); i++, k++) {
            res[i] += downSide[k];
        }
        if ((right[0] == 'c' && left[0] != 'c') || (right[0] == 'c' && left[0] != 'c')) {

        }
        formatting(res);
        return res;
    }

    void Printer::scalePrint(std::string a) {
        std::vector<std::string> res;
        std::string temp = "";
        for(int i = 0; i < a.length(); i++){
            if(a[i]!= 'c'){
                temp.push_back(a[i]);
            }
            else{
            }
        }
    }

    void Printer::Test(std::string a, int depth) {
        std::cout << "ke\n";
        std::vector<std::string> res = escalateComb(depth, a);
        for (int i = 0; i < res.size(); i++) {
            std::cout << res[i] << std::endl;
        }
    }

    void Printer::findDepth() {
        int res = 0;
        for (int i = 0; i < expr.length(); i++) {
            if (expr[i] == 'c' && expr[i + 1] == '(') {
                int max = 1;
                i += 2;
                while (max > 0 && i < expr.length()) {
                    if (expr[i] == '(') {
                        max++;
                        if (max > res) {
                            res = max;
                        }
                    }
                    if (expr[i] == ')') {
                        max--;
                    }
                    i++;
                }
            }
        }
        this->depth = res;
    }

    void getLeftAndRight(std::string &left, std::string &right, std::string comb) {
        int i = 2;
        if (comb[i] != 'c') {
            for (i = 2; comb[i] != ','; i++) {
                left += comb[i];
            }
        } else {
            left = "c(";
            i += 2;
            int st = 1;
            for (i; st > 0; i++) {
                left += comb[i];
                if (comb[i] == ')') {
                    st--;
                } else if (comb[i] == '(') {
                    st++;
                }
            }
        }
        i++;
        right = comb.substr(i);
        right.pop_back();
    }

    void formatting(std::vector<std::string> &a) {
        int normalizeValue = a[0].size() > a[a.size() - 1].size() ? a[0].size() : a[a.size() - 1].size();
        for (int i = 0; i < a.size(); i++) {
            if (a[i].size() < normalizeValue) {
                while (a[i].size() < normalizeValue) {
                    a[i].push_back(' ');
                }
            }
        }
    }
}
