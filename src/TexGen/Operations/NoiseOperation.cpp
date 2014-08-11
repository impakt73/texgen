#include <TexGen/Operations/NoiseOperation.h>
#include <algorithm>

void NoiseOperation::Run(Texture *ioTexture, const std::vector<float> inArguments)
{
    for( int y = 0; y < ioTexture->Height; ++y )
    {
        for( int x = 0; x < ioTexture->Width; ++x )
        {
            for( int i = 0; i < ioTexture->PixelDepth; ++i )
            {
                int index = ( (y*ioTexture->Width+x)*ioTexture->PixelDepth ) + i;
                float colorVal = ( ( rand() % 1001 ) / 1000.0f ) * 255.0f;
                ioTexture->PixelData[index] = (unsigned char)( std::min( std::max( 0.0f, colorVal ), 255.0f ) );
            }
        }
    }
}
