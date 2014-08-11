#pragma once

#include <TexGen/Token.h>
#include <vector>
#include <TexGen/Node.h>

class Parser
{
public:
    static bool Parse(const std::vector<Token>& inTokens, Node** outParseTree);

private:
    Parser(void) {}
    ~Parser(void) {}

    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;
};
