#pragma once

#include <TexGen/TokenData.h>

enum eToken
{
    kToken_Undefined = 0,
    kToken_Identifier,
    kToken_Number,
    kToken_Terminator,
    kToken_ScopeBegin,
    kToken_ScopeEnd,
    kToken_CommentBegin,
    kToken_CommentEnd
};

class Token
{
public:
    Token( eToken inTokenType, TokenData* inTokenData )
        : mType( inTokenType )
        , mData( inTokenData )
    {
    }

    ~Token( void )
    {
    }

    Token(const Token& other)
    {
        mType = other.mType;
        mData = other.mData;
    }
    Token& operator=(const Token& other)
    {
        mType = other.mType;
        mData = other.mData;

        return *this;
    }

    inline eToken GetType( void ) const { return mType; }
    inline TokenData* GetData( void ) const { return mData; }

    eToken mType;
    TokenData* mData; // This needs to be freed in the parser.
};
