#pragma once

#include <TexGen/Node.h>

class TextureNode : public Node
{
public:
    TextureNode( const std::string& inTextureName ) : Node(kNodeType_Texture), mTextureName( inTextureName ) {}
    ~TextureNode(void) {}

    inline std::string GetName( void ) const { return mTextureName; }
    inline void SetName( const std::string& inTextureName ) { mTextureName = inTextureName; }

    inline unsigned int GetWidth( void ) const { return mWidth; }
    inline void SetWidth( unsigned int inWidth ) { mWidth = inWidth; }

    inline unsigned int GetHeight( void ) const { return mHeight; }
    inline void SetHeight( unsigned int inHeight ) { mHeight = inHeight; }

    inline unsigned int GetPixelDepth( void ) const { return mPixelDepth; }
    inline void SetPixelDepth( unsigned int inPixelDepth ) { mPixelDepth = inPixelDepth; }

    std::string GetDescription( void ) const { return "Texture Node: " + mTextureName; }

private:
    TextureNode(const TextureNode& other);
    TextureNode& operator=(const TextureNode& other);

    std::string mTextureName;
    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mPixelDepth;
};
