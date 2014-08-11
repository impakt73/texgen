#pragma once

#include <vector>
#include <TexGen/Texture.h>
#include <TexGen/Operations/OperationType.h>

class Operation
{
public:
    virtual ~Operation(void) {}

    virtual void Run( Texture* ioTexture, const std::vector<float> inArguments ) = 0;

	inline eOperationType GetType( void ) const { return mType; }

protected:
	Operation(eOperationType inType) : mType( inType ) {}
    Operation(const Operation& other);
    Operation& operator=(const Operation& other);

	eOperationType mType;
};
