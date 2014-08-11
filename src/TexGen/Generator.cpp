#include <TexGen/Generator.h>
#include <assert.h>
#include <TexGen/TextureNode.h>
#include <TexGen/OperationNode.h>
#include <iostream>
#include <TexGen/Operations/ClearOperation.h>
#include <TexGen/Operations/NoiseOperation.h>
#include <TexGen/stb_image_write.h>


Generator::Generator( void )
{

}

Generator::~Generator( void )
{

}

void Generator::Initialize( Node* inProgramNode )
{
    mProgramNode = inProgramNode;

    ClearOperation* clearOp = new ClearOperation();
    RegisterOperation( "Clear", clearOp );

    NoiseOperation* noiseOp = new NoiseOperation();
    RegisterOperation( "Noise", noiseOp );
}

void Generator::Run( void )
{
    // Create all the textures
    for( Node* textureNode : mProgramNode->GetChildren() )
    {
        assert( textureNode->GetType() == kNodeType_Texture );

        TextureNode* texNode = static_cast<TextureNode*>( textureNode );

        assert( texNode->GetWidth() > 0 );
        assert( texNode->GetHeight() > 0 );
        assert( texNode->GetPixelDepth() > 0 );

        Texture* texture = new Texture();
        texture->Name = texNode->GetName();
        texture->Width = texNode->GetWidth();
        texture->Height = texNode->GetHeight();
        texture->PixelDepth = texNode->GetPixelDepth();
        texture->PixelData = new unsigned char[ texture->Width * texture->Height * texture->PixelDepth ];

        // Run the operations to complete the texture
        for( Node* operationNode : textureNode->GetChildren() )
        {
            assert( operationNode->GetType() == kNodeType_Operation );

            OperationNode* opNode = static_cast<OperationNode*>( operationNode );
            std::map<std::string, Operation*>::iterator opIterator = mOperations.find( opNode->GetName() );

            if( opIterator == mOperations.end() )
            {
                // Unsupported operation :(
                std::cout << "Unsupported Operation: " << opNode->GetName() << std::endl;
            }
            else
            {
                // Run the operation
                std::cout << "Performing Operation: " << opNode->GetName() << " On Texture: " << texNode->GetName() << std::endl;
                (*opIterator).second->Run( texture, opNode->GetArguments() );
            }
        }

        // Write the image
        stbi_write_png("TestImage.png", texture->Width, texture->Height, texture->PixelDepth, texture->PixelData, texture->Width * texture->PixelDepth);

        mTextures[texture->Name] = texture;
    }
}

void Generator::Destroy( void )
{
    std::map<std::string, Texture*>::iterator texIterator = mTextures.begin();
    for( ; texIterator != mTextures.end(); ++texIterator )
    {
        if( (*texIterator).second->PixelData != nullptr )
        {
            delete [] (*texIterator).second->PixelData;
        }
        delete (*texIterator).second;
    }
    mTextures.clear();

    std::map<std::string, Operation*>::iterator opIterator = mOperations.begin();
    for( ; opIterator != mOperations.end(); ++opIterator )
    {
        delete (*opIterator).second;
    }
    mOperations.clear();
}

void Generator::RegisterOperation(const std::string &inOperationName, Operation* inOperation)
{
    // Make sure it's not already registered
    assert( mOperations.find( inOperationName ) == mOperations.end() );

    mOperations[inOperationName] = inOperation;
}
