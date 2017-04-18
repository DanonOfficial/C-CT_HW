//
// Created by DanonOfficial on 08.04.2017.
//

#ifndef HW_4_PARSER_H
#define HW_4_PARSER_H
#include "Expression.h"
namespace prs {
    struct Parser {
    public:
        explicit Parser(const char *input) : input(input) {} // Конструктор, принимает строку с выражением
        Expression parse(); // Основная функция парсинга
        double evaluate(const Expression &e);

    private:
        std::string parse_token(); // Парсит один токен
        Expression parse_simple_expression(); // Парсит простое выражение
        Expression parse_binary_expression(int min_priority); // Парсит бинарное выражение
        const char *input; // Кусок строки, который еще не распарсили
    };
    double eval(const Expression& e);
}
#endif //HW_4_PARSER_H
