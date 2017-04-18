//
// Created by DanonOfficial on 08.04.2017.
//

#include "Parser.h"

namespace prs {

    int combination(int a, int b) {
        int res = 1;
        for (int i = a; i > a - b; i--) {
            res *= i;
        }
        for (int i = 1; i <= b; i++) {
            res /= i;
        }
        return res;
    }

    std::string Parser::parse_token() {
        while (std::isspace(*input)) ++input;

        if (std::isdigit(*input)) {
            std::string number;
            while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
            return number;
        }

        static const std::string tokens[] =
                {"+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")", ","};
        for (auto &t : tokens) {
            if (std::strncmp(input, t.c_str(), t.size()) == 0) {
                input += t.size();
                return t;
            }
        }

        return "";
    }

    Expression Parser::parse_simple_expression() {
        auto token = parse_token();
        if (token.empty()) throw std::runtime_error("Invalid input");

        if (token == "(") {
            auto result = parse();
            if (parse_token() != ")") throw std::runtime_error("Expected ')'");
            return result;
        }

        if (std::isdigit(token[0]))
            return Expression(token);

        return Expression(token, parse_simple_expression());
    }

    int get_priority(const std::string &binary_op) {
        if (binary_op == "+") return 1;
        if (binary_op == "-") return 1;
        if (binary_op == "*") return 2;
        if (binary_op == "/") return 2;
        if (binary_op == "mod") return 2;
        if (binary_op == "**") return 3;
        if (binary_op == ",")return 3;
        return 0;
    }

    Expression Parser::parse_binary_expression(int min_priority) {
        auto left_expr = parse_simple_expression();

        for (;;) {
            auto op = parse_token();
            auto priority = get_priority(op);
            if (priority <= min_priority) {
                input -= op.size();
                return left_expr;
            }

            auto right_expr = parse_binary_expression(priority);
            left_expr = Expression(op, left_expr, right_expr);
        }
    }


    Expression Parser::parse() {
        return parse_binary_expression(0);
    }


    double Parser::evaluate(const Expression &e) {
        switch (e.args.size()) {
            case 2: { // Два аргумента - бинарные операции.
                auto a = evaluate(e.args[0]);
                auto b = evaluate(e.args[1]);
                if (e.token == "+") return a + b;
                if (e.token == "-") return a - b;
                if (e.token == "*") return a * b;
                if (e.token == "/") return a / b;
                if (e.token == "**") return pow(a, b);
                if (e.token == "mod") return (int) a % (int) b;
                if (e.token == ",") return (int) combination(a, b);
                throw std::runtime_error("Unknown binary operator");
            }

            case 1: { // Один аргумент.
                auto a = evaluate(e.args[0]);
                if (e.token == "+") return +a;
                if (e.token == "-") return -a;
                if (e.token == "abs") return abs(a);
                if (e.token == "sin") return sin(a);
                if (e.token == "cos") return cos(a);
                throw std::runtime_error("Unknown unary operator");
            }

            case 0: { // Числа (ноль аргументов).
                return strtod(e.token.c_str(), nullptr);
            }
        }

        throw std::runtime_error("Unknown expression type");
    }

    double eval(const Expression &e) {
        switch (e.args.size()) {
            case 2: {
                auto a = eval(e.args[0]);
                auto b = eval(e.args[1]);
                if (e.token == "+") return a + b;
                if (e.token == "-") return a - b;
                if (e.token == "*") return a * b;
                if (e.token == "/") return a / b;
                if (e.token == "**") return pow(a, b);
                if (e.token == "mod") return (int) a % (int) b;
                if (e.token == ",") return combination(a, b);
                throw std::runtime_error("Unknown binary operator");
            }

            case 1: {
                auto a = eval(e.args[0]);
                if (e.token == "+") return +a;
                if (e.token == "-") return -a;
                if (e.token == "abs") return abs(a);
                if (e.token == "sin") return sin(a);
                if (e.token == "cos") return cos(a);
                throw std::runtime_error("Unknown unary operator");
            }

            case 0:
                return strtod(e.token.c_str(), nullptr);
        }

        throw std::runtime_error("Unknown expression type");
    }
}