#pragma once

#include <TexGen/Operations/Operation.h>

class RadialGradient : public Operation
{
public:
    RadialGradient( void ) : Operation( kOperationType_RadialGradient )  {}
    ~RadialGradient( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
