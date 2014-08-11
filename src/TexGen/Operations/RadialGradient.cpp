#include <TexGen/Operations/RadialGradient.h>
#include <algorithm>

void RadialGradient::Run(Texture *ioTexture, const std::vector<float> inArguments)
{
	float startRadius = inArguments[0];
	float endRadius = inArguments[1];
    for( int y = 0; y < ioTexture->Height; ++y )
    {
        for( int x = 0; x < ioTexture->Width; ++x )
        {
			float fX = ((float)x / (float)ioTexture->Width) * 2.0f - 1.0f;
			float fY = ((float)y / (float)ioTexture->Height) * 2.0f - 1.0f;

			float length = sqrt(fX * fX  + fY * fY );
			float startInterp = sqrt( startRadius * startRadius );
			float endInterp = sqrt( endRadius * endRadius );
			float interp = ( length - startInterp ) / ( endInterp - startInterp );
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
