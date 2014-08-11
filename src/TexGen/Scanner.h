#pragma once

#include <vector>
#include <string>

class Scanner
{
public:
    Scanner( void )
    {
    }
    ~Scanner( void )
    {
    }

    static void Scan( const std::string& inText, std::vector<std::string>* outResults );
};
