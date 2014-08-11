#include <iostream>
#include <TexGen/File.h>
#include <TexGen/Scanner.h>
#include <TexGen/Lexer.h>
#include <TexGen/Parser.h>
#include <TexGen/Generator.h>

void PrintNode( Node* inNode )
{
    std::cout << inNode->GetDescription() << std::endl;

    for( int i = 0; i < inNode->GetChildren().size(); ++i )
    {
        PrintNode( inNode->GetChildren()[i] );
    }
}

int main(int argc, char** argv)
{
    const char* fileData = File::ReadTextFile( "res/Test.tgs" );
    if( fileData != NULL )
    {
        std::vector<std::string> results;
        Scanner::Scan( std::string( fileData ), &results );

        delete [] fileData;

        std::vector<Token> tokens;
        Lexer::Lex( results, &tokens );

        Node* rootNodePtr = nullptr;
        if( Parser::Parse( tokens, &rootNodePtr ) )
        {
            PrintNode( rootNodePtr );
        }
        else
        {
            std::cout << "Failed to parse file!" << std::endl;
        }

        Generator generator;
        generator.Initialize( rootNodePtr );
        generator.Run();
        generator.Destroy();
    }
    return 0;
}
