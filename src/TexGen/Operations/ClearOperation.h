#pragma once

#include <TexGen/Operations/Operation.h>

class ClearOperation : public Operation
{
public:
    ClearOperation( void ) : Operation( kOperationType_Clear ) {}
    ~ClearOperation( void ) {}

    void Run( Texture* ioTexture, const std::vector<float> inArguments );
};
