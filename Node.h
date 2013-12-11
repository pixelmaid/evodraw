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
    bool clear();
    Node(const Node &rhs);
    Node& operator = (const Node &rhs);
    bool copyBaseVariables(const Node *node);
    virtual void Update(void);
    
    Node* GetParentNode(void) const;
    void SetParentNode(Node* NewParent);
    
    void AddChildNode(Node* ChildNode);
    bool RemoveChildNode(Node* ChildNode);
    bool RecursiveRemoveChildNode(Node* ChildNode);
    const char* GetNodeName(void) const;
    
    string getType() const{
        return type;
    }
    
    const size_t CountChildNodes(const bool& RecursiveCount = false) const;
    //virtual const bool IsRootNode(void) const = 0;
    
    Node* GetChildNodeByName(const char* SearchName);
    
    static Node* createInstanceFromString(string const &nodeType);
    Node* createNewInstance() const;
    
    virtual bool deepCopyFrom(const Node *node);

    
    string type;
protected:
    //method to check if map has been intialized, and if not, creates a new instance
    static StringNodeMap *getMap(){
        if( !stringNodeMap ){ stringNodeMap = new StringNodeMap; }
        
        return stringNodeMap;
        
    }

        vector<Node*> m_Children;
    
private:
    Node* m_Parent;
    const char* m_Name;
    static StringNodeMap* stringNodeMap;
    static GRT::UINT numNodeInstances;
    
    
    
};

template< typename T >  Node* getNewNodeModuleInstance() { return new T; }

//subclass uses this class to "register" itself with the base class.
//inherits from node classifier to access map
template< typename T >
class RegisterNodeModule : Node {
public:
    RegisterNodeModule(string const &newNodeModuleName) {
        getMap()->insert( std::pair<string, Node*(*)()>(newNodeModuleName, &getNewNodeModuleInstance< T > ) );
        
    }
};

// class Node
#endif /* defined(__evodraw1__Node__) */
