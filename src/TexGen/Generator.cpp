#include <TexGen/Generator.h>
#include <assert.h>
#include <TexGen/TextureNode.h>
#include <TexGen/OperationNode.h>
#include <iostream>
#include <TexGen/Operations/ClearOperation.h>
#include <TexGen/Operations/NoiseOperation.h>
#include <TexGen/Operations/RadialGradient.h>
#include <TexGen/Operations/HorizontalGradient.h>
#include <TexGen/Operations/VerticalGradient.h>
#include <TexGen/Operations/AddBlend.h>
#include <TexGen/Operations/MultiplyBlend.h>
#include <TexGen/stb_image_write.h>
#include <algorithm>

void AddBlendFunc( Texture* inSource, Texture* inDestination )
{
	for( int y = 0; y < inDestination->Height; ++y )
    {
        for( int x = 0; x < inDestination->Width; ++x )
        {
            for( int i = 0; i < inDestination->PixelDepth; ++i )
            {
                int index = ( (y*inDestination->Width+x)*inDestination->PixelDepth ) + i;
				float src = inSource->PixelData[index] / 255.0f;
				float dest = inDestination->PixelData[index] / 255.0f;
				float val = src + dest;
				val = std::min( std::max( 0.0f, val ), 1.0f );
				inDestination->PixelData[index] = (unsigned char)( val * 255.0f );
            }
        }
    }
}

void MultiplyBlendFunc( Texture* inSource, Texture* inDestination )
{
	for( int y = 0; y < inDestination->Height; ++y )
    {
        for( int x = 0; x < inDestination->Width; ++x )
        {
            for( int i = 0; i < inDestination->PixelDepth; ++i )
            {
                int index = ( (y*inDestination->Width+x)*inDestination->PixelDepth ) + i;

				float src = inSource->PixelData[index] / 255.0f;
				float dest = inDestination->PixelData[index] / 255.0f;
				float val = src * dest;
				val = std::min( std::max( 0.0f, val ), 1.0f );
				inDestination->PixelData[index] = (unsigned char)( val * 255.0f );
            }
        }
    }
}

Generator::Generator( void )
	: mBlendMode( kBlendMode_Add )
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

	RadialGradient* radGradOp = new RadialGradient();
    RegisterOperation( "RadialGradient", radGradOp );

	HorizontalGradient*  horizGradOp = new HorizontalGradient();
    RegisterOperation( "HorizontalGradient", horizGradOp );

	VerticalGradient*  vertGradOp = new VerticalGradient();
    RegisterOperation( "VerticalGradient", vertGradOp );

	AddBlend* addBlendOp = new AddBlend();
    RegisterOperation( "AddBlend", addBlendOp );

	MultiplyBlend* multiplyBlendOp = new MultiplyBlend();
    RegisterOperation( "MultiplyBlend", multiplyBlendOp );
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

		// Texture Back Buffer
		Texture texBuf;
		texBuf.Name = texNode->GetName();
		texBuf.Width = texNode->GetWidth();
		texBuf.Height = texNode->GetHeight();
		texBuf.PixelDepth = texNode->GetPixelDepth();
		texBuf.PixelData = new unsigned char[ texBuf.Width * texBuf.Height * texBuf.PixelDepth ];	


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
				switch( (*opIterator).second->GetType() )
				{
					case kOperationType_AddBlend:
					{
						mBlendMode = kBlendMode_Add;
						break;
					}
					case kOperationType_MultiplyBlend:
					{
						mBlendMode = kBlendMode_Multiply;
						break;
					}
					default:
					{
						std::cout << "Performing Operation: " << opNode->GetName() << " On Texture: " << texNode->GetName() << std::endl;
						(*opIterator).second->Run( &texBuf, opNode->GetArguments() );

						// Blend the texbuf with the actual texture
						switch( mBlendMode )
						{
							case kBlendMode_Add:
							{
								AddBlendFunc( &texBuf, texture );
								break;
							}
							case kBlendMode_Multiply:
							{
								MultiplyBlendFunc( &texBuf, texture );
								break;
							}
						}
					}
				}
            }
        }

		delete [] texBuf.PixelData;

        // Write the image
		stbi_write_png((texture->Name + ".png").c_str(), texture->Width, texture->Height, texture->PixelDepth, texture->PixelData, texture->Width * texture->PixelDepth);

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
