#pragma once

#include <TexGen/NodeType.h>
#include <vector>
#include <string>

class Node
{
public:
    Node(void) : mType(kNodeType_Undefined), mParent(nullptr) {}
    Node(eNodeType inNodeType) : mType(inNodeType), mParent(nullptr) {}
    virtual ~Node(void)
    {
        for(Node*& child : mChildren)
        {
            delete child;
        }
        mChildren.clear();
    }

    inline eNodeType GetType(void) const { return mType; }
    inline Node* GetParent(void) const { return mParent; }
    inline void SetParent(Node* inNode) { mParent = inNode; }
    std::vector<Node*>& GetChildren(void) { return mChildren; }
    void InsertNode(Node* inNode) { mChildren.push_back(inNode); inNode->SetParent(this); }

    virtual std::string GetDescription( void ) const { return "Root Node"; }

protected:
    Node(const Node& other);
    Node& operator=(const Node& other);

    eNodeType mType;

    std::vector<Node*> mChildren;
    Node* mParent;
};
