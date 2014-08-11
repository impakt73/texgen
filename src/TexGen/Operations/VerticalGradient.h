#pragma once

#include <TexGen/Operations/Operation.h>

class VerticalGradient : public Operation
{
public:
    VerticalGradient( void ) : Operation( kOperationType_VerticalGradient )  {}
    ~VerticalGradient( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
