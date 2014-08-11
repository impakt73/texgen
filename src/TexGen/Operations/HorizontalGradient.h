#pragma once

#include <TexGen/Operations/Operation.h>

class HorizontalGradient : public Operation
{
public:
    HorizontalGradient( void ) : Operation( kOperationType_HorizontalGradient )  {}
    ~HorizontalGradient( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
