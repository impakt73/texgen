#pragma once

#include <TexGen/TokenData.h>
#include <string>

class NumberTokenData : public TokenData
{
public:
    NumberTokenData( float inValue )
        : mValue( inValue ) {}
    ~NumberTokenData( void ) {}

    inline float GetValue( void ) const { return mValue; }

private:
    float mValue;
};
