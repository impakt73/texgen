#pragma once

#include <TexGen/Operations/Operation.h>

class MultiplyBlend : public Operation
{
public:
    MultiplyBlend( void ) : Operation( kOperationType_MultiplyBlend )  {}
    ~MultiplyBlend( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
