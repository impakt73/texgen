#include <TexGen/Parser.h>
#include <iostream>
#include <cassert>
#include <TexGen/TextureNode.h>
#include <TexGen/OperationNode.h>

#include <TexGen/IdentifierTokenData.h>
#include <TexGen/NumberTokenData.h>

bool Parser::Parse(const std::vector<Token>& inTokens, Node **outParseTree)
{
    Node* rootNode = new Node(kNodeType_Root);
    unsigned int tokenCount = inTokens.size();

    int scopeLevel = 0;
    bool inComment = false;
    TextureNode* currentTextureNode = nullptr;
    OperationNode* currentOperationNode = nullptr;

    for(unsigned int index = 0; index < tokenCount; ++index)
    {
        const Token& currentToken = inTokens[index];
        switch(currentToken.GetType())
        {
            case kToken_ScopeBegin:
            {
                if( !inComment )
                {
                    // We're opening a new texture scope so it shouldn't be null
                    assert( currentTextureNode != nullptr );

                    scopeLevel++;
                }
                break;
            }
            case kToken_ScopeEnd:
            {
                if( !inComment )
                {
                    // We're closing a texture scope so it shouldn't be null
                    assert( currentTextureNode != nullptr );
                    scopeLevel--;

                    rootNode->InsertNode( currentTextureNode );
                    currentTextureNode = nullptr;
                }
                break;
            }
            case kToken_CommentBegin:
            {
                assert( !inComment );
                inComment = true;
                break;
            }
            case kToken_CommentEnd:
            {
                assert( inComment );
                inComment = false;
                break;
            }
            case kToken_Terminator:
            {
                if( !inComment )
                {
                    // Terminate the operation
                    assert( currentOperationNode != nullptr );
                    assert( currentTextureNode != nullptr );

                    currentTextureNode->InsertNode( currentOperationNode );
                    currentOperationNode = nullptr;
                }
                break;
            }
            case kToken_Identifier:
            {
                if( !inComment )
                {
                    // Start a new texture if we're not in one
                    if( currentTextureNode == nullptr )
                    {
                        IdentifierTokenData* tokenData = static_cast<IdentifierTokenData*>(currentToken.GetData());

                        assert( tokenData->GetValue().compare( "Texture" ) == 0 );

                        // Free the data here. This means the tokens are one time use
                        delete tokenData;

                        currentTextureNode = new TextureNode( "Undefined" );
                    }
                    else
                    {
                        // We're still looking for a name
                        if( currentTextureNode->GetName().compare( "Undefined") == 0 )
                        {
                            IdentifierTokenData* tokenData = static_cast<IdentifierTokenData*>(currentToken.GetData());

                            // Make sure no one tries to name it "Undefined"
                            assert( tokenData->GetValue().compare( "Undefined" ) != 0 );

                            currentTextureNode->SetName( tokenData->GetValue() );

                            // Free the data here. This means the tokens are one time use
                            delete tokenData;

                            // We also need width height and pixel depth
                            assert( index + 3 < tokenCount );
                            assert( inTokens[index+1].GetType() == kToken_Number );
                            assert( inTokens[index+2].GetType() == kToken_Number );
                            assert( inTokens[index+3].GetType() == kToken_Number );

                            NumberTokenData* widthData = static_cast<NumberTokenData*>(inTokens[index+1].GetData());
                            NumberTokenData* heightData = static_cast<NumberTokenData*>(inTokens[index+2].GetData());
                            NumberTokenData* pixelDepthData = static_cast<NumberTokenData*>(inTokens[index+3].GetData());

                            currentTextureNode->SetWidth( widthData->GetValue() );
                            currentTextureNode->SetHeight( heightData->GetValue() );
                            currentTextureNode->SetPixelDepth( pixelDepthData->GetValue() );

                            delete widthData;
                            delete heightData;
                            delete pixelDepthData;
                        }
                        else
                        {
                            // We're looking for operations now.
                            assert( currentOperationNode == nullptr );

                            IdentifierTokenData* tokenData = static_cast<IdentifierTokenData*>(currentToken.GetData());
                            currentOperationNode = new OperationNode( tokenData->GetValue() );

                            // Free the data here. This means the tokens are one time use
                            delete tokenData;
                        }
                    }
                }
                break;
            }
            case kToken_Number:
            {
                if( !inComment )
                {
                    // Add arguments to the operation
                    if( currentOperationNode != nullptr )
                    {
                        NumberTokenData* tokenData = static_cast<NumberTokenData*>(currentToken.GetData());
                        currentOperationNode->AddArgument( tokenData->GetValue() );

                        // Free the data here. This means the tokens are one time use
                        delete tokenData;
                    }
                }
                break;
            }

            case kToken_Undefined:
            default:
            {
                std::cout << "Error! Undefined token encountered!" << std::endl;
                delete rootNode;
                return false;
            }
        }
    }

    *outParseTree = rootNode;
    return true;
}
