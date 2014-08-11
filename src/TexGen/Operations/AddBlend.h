#pragma once

#include <TexGen/Operations/Operation.h>

class AddBlend : public Operation
{
public:
    AddBlend( void ) : Operation( kOperationType_AddBlend )  {}
    ~AddBlend( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
