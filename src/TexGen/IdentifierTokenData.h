#pragma once

#include <TexGen/TokenData.h>
#include <string>

class IdentifierTokenData : public TokenData
{
public:
    IdentifierTokenData( const std::string& inValue )
        : mValue( inValue ) {}
    ~IdentifierTokenData( void ) {}

    inline std::string GetValue( void ) const { return mValue; }

private:
    std::string mValue;
};
