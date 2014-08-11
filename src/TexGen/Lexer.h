#pragma once

#include <TexGen/Token.h>
#include <vector>
#include <string>

class Lexer
{
public:
    static void Lex(const std::vector<std::string> inTextChunks, std::vector<Token>* outTokens);

private:
    Lexer(void) {}
    ~Lexer(void) {}

    Lexer(const Lexer& other) = delete;
    Lexer& operator=(const Lexer& other) = delete;
};
