#include <TexGen/Operations/ClearOperation.h>
#include <algorithm>

void ClearOperation::Run(Texture *ioTexture, const std::vector<float> inArguments)
{
    float colorVals[4];
    colorVals[0] = inArguments[0];
    colorVals[1] = inArguments[1];
    colorVals[2] = inArguments[2];
    colorVals[3] = inArguments[3];

    for( int y = 0; y < ioTexture->Height; ++y )
    {
        for( int x = 0; x < ioTexture->Width; ++x )
        {
            for( int i = 0; i < ioTexture->PixelDepth; ++i )
            {
                int index = ( (y*ioTexture->Width+x)*ioTexture->PixelDepth ) + i;
                float colorVal = colorVals[i] * 255.0f;
                ioTexture->PixelData[index] = (unsigned char)( std::min( std::max( 0.0f, colorVal ), 255.0f ) );
            }
        }
    }
}
