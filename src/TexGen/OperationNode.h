#pragma once

#include <TexGen/Node.h>

class OperationNode : public Node
{
public:
    OperationNode( const std::string& inOperationName ) : Node(kNodeType_Operation), mOperationName( inOperationName ) {}
    ~OperationNode(void) {}

    inline std::string GetName( void ) const { return mOperationName; }
    inline const std::vector<float>& GetArguments( void ) const { return mArguments; }

    inline void AddArgument( float inArgumentValue ) { mArguments.push_back( inArgumentValue ); }

    std::string GetDescription( void ) const { return "Operation Node: " + mOperationName + " " + std::to_string( mArguments.size() ) + " Arguments"; }

private:
    OperationNode(const OperationNode& other) = delete;
    OperationNode& operator=(const OperationNode& other) = delete;

    std::string mOperationName;
    std::vector<float> mArguments;
};
