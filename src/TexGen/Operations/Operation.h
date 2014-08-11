#pragma once

#include <vector>
#include <TexGen/Texture.h>

class Operation
{
public:
    virtual ~Operation(void) {}

    virtual void Run( Texture* ioTexture, const std::vector<float> inArguments ) = 0;

protected:
    Operation(void) {}
    Operation(const Operation& other) = delete;
    Operation& operator=(const Operation& other) = delete;
};
