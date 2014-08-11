#include <TexGen/Lexer.h>
#include <cassert>
#include <stdexcept>
#include <TexGen/NumberTokenData.h>
#include <TexGen/IdentifierTokenData.h>


void Lexer::Lex(const std::vector<std::string> inTextChunks, std::vector<Token>* outTokens)
{
    for( auto& text : inTextChunks )
    {
        assert( text.size() > 0 );
        if( text.compare( "{" ) == 0 ) outTokens->push_back( Token( kToken_ScopeBegin, nullptr ) );
        else if( text.compare( "}" ) == 0 ) outTokens->push_back( Token( kToken_ScopeEnd, nullptr ) );
        else if( text.compare( "/*" ) == 0 ) outTokens->push_back( Token( kToken_CommentBegin, nullptr ) );
        else if( text.compare( "*/" ) == 0 ) outTokens->push_back( Token( kToken_CommentEnd, nullptr ) );
        else if( text.compare( ";" ) == 0 ) outTokens->push_back( Token( kToken_Terminator, nullptr ) );
        else
        {
            // It's either an identifier or a number
            try // ( Eww gross. )
            {
                // It's a number if this doesn't throw.
                float numberVal = std::stof( text );

                NumberTokenData* tokenData = new NumberTokenData( numberVal );

                outTokens->push_back( Token( kToken_Number, tokenData ) );
            }
            catch( std::invalid_argument )
            {
                // Ok so it's an identifier

                IdentifierTokenData* tokenData = new IdentifierTokenData( text );

                outTokens->push_back( Token( kToken_Identifier, tokenData ) );
            }
        }

    }
}
