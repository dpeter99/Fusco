/***********
 * GEMWIRE *
 *  FUSCO  *
 ***********/

#pragma once
#include <lexer/Lex.hpp>
#include <ast/Statement.hpp>
#include <Main.hpp>
#include <stdexcept>

class Parser : public Common {
public:
    Parser(std::vector<struct Token> pTokens)
        : tokens(pTokens), currentToken(0) {}

    std::vector<Statement*> parse();

private:
    std::vector<struct Token> tokens;
    size_t currentToken;

    /** Token Manipulation **/
    template <class... T>
    bool matchAny(T ... tokens);
    bool check(Lexeme type);
    struct Token advance();
    struct Token previous();
    struct Token peek();
    bool endOfStream();

    /** Statement Parsing **/
    Statement* statement();
    Statement* printStatement();
    Statement* expressionStatement();

    Expression<Object>* expression();
    Expression<Object>* equality();
    Expression<Object>* comparison();
    Expression<Object>* term();
    Expression<Object>* factor();
    Expression<Object>* unary();
    Expression<Object>* primary();

    /** Error management **/
    struct Token verify(Lexeme type, std::string error);
    std::runtime_error error(struct Token token, std::string message);

    void recover();
};