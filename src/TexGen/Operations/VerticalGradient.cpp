#include <TexGen/Operations/VerticalGradient.h>
#include <algorithm>

void VerticalGradient::Run(Texture *ioTexture, const std::vector<float> inArguments)
{
	float startPos = inArguments[0];
	float endPos = inArguments[1];
    for( int y = 0; y < ioTexture->Height; ++y )
    {
        for( int x = 0; x < ioTexture->Width; ++x )
        {
			float fY = ((float)y / (float)ioTexture->Height);
			float interp = ( fY - startPos ) / ( endPos - startPos );
			interp = std::min( std::max( 0.0f, interp ), 1.0f );

            for( int i = 0; i < ioTexture->PixelDepth; ++i )
            {
                int index = ( (y*ioTexture->Width+x)*ioTexture->PixelDepth ) + i;
                float colorVal = interp * 255.0f;

                ioTexture->PixelData[index] = (unsigned char)( std::min( std::max( 0.0f, colorVal ), 255.0f ) );
            }
        }
    }
}
