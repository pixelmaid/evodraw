//
//  Node.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/6/13.
//
//

#ifndef __evodraw1__Node__
#define __evodraw1__Node__
#include <vector>
#include <iostream>
#include <map>
#include "GRT.h"
using namespace std;


class Node;
typedef std::map< string, Node*(*)() > StringNodeMap;

class Node
{
public:
    Node(Node* Parent = NULL, const char* Name = NULL);
    virtual ~Node(void);
    Node(const Node &rhs);
    Node& operator = (const Node &rhs);
    bool copyBaseVariables(const Node *node);
    virtual void Update(void);
    
    Node* GetParentNode(void) const;
    void SetParentNode(Node* NewParent);
    
    void AddChildNode(Node* ChildNode);
    void RemoveChildNode(Node* ChildNode);
    
    const char* GetNodeName(void) const;
    const size_t CountChildNodes(const bool& RecursiveCount = false) const;
    //virtual const bool IsRootNode(void) const = 0;
    
    Node* GetChildNodeByName(const char* SearchName);
    
// all the stuff you had me create
    string type;
protected:
    static StringNodeMap *getMap();
        vector<Node*> m_Children;
    
private:
    Node* m_Parent;
    const char* m_Name;
    static StringNodeMap* stringNodeMap;
    static GRT::UINT numNodeInstances;
    
    
    
};

// class Node
#endif /* defined(__evodraw1__Node__) */
