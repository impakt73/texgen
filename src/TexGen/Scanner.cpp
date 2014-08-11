#include <TexGen/Scanner.h>
#include <regex>

void Scanner::Scan( const std::string& inText, std::vector<std::string>* outResults )
{
    std::regex option_regex( "\\S+?(?=[\\s\\n]|;|$)" );
    std::smatch match_object;
    std::string currentText = inText;
    while( std::regex_search( currentText, match_object, option_regex ) )
    {
        outResults->push_back(match_object[0]);

        currentText = match_object.suffix().str();
    }
}
