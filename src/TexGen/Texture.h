#pragma once

#include <string>

struct Texture
{
    std::string Name;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelDepth;
    unsigned char* PixelData;
};
