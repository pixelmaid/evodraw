//
//  Node.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/6/13.
//
//

#include "Node.h"

Node::Node(Node* Parent, const char* Name)
: m_Name(Name)
{
    m_Parent = Parent;
} // Constructor

Node::~Node(void)
{
    m_Parent = NULL;
    m_Children.clear();
} // Destructor


Node::Node(const Node &rhs){
    *this = rhs;
}

Node& Node:: operator = (const Node &rhs){
    if(this!= &rhs){
        copyBaseVariables( (Node*)&rhs );
    }
    return *this;
}


bool Node::copyBaseVariables(const Node *node){
    
    if( node == NULL ){
        // errorMessage = "copyBaseVariables(const Classifier *classifier) - Classifier is NULL!";
        //errorLog << errorMessage << endl;
        return false;
    }
    
    if( !this->copyBaseVariables( node ) ){
        return false;
    }
    this->m_Children = node->m_Children;
    
    this->m_Parent = node->m_Parent;
    this->m_Name = node->m_Name;
    std::cout<<"copy node base variables"<<std::endl;
    return true;
}


void Node::Update(void)
{
    if(!m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(NULL != m_Children[i])
            {
                m_Children[i]->Update();
                std::cout<<"child at "<<i<<" updating"<<std::endl;
            }
        }
    }
    std::cout<<"node is updating"<<std::endl;
} // Update()


Node* Node::GetParentNode(void) const
{
    return(m_Parent);
}; // GetParentNode()


void Node::SetParentNode(Node* NewParent)
{
    if(NULL != m_Parent)
    {
        m_Parent->RemoveChildNode(this);
    }
    m_Parent = NewParent;
}; // SetParentNode()

void Node::AddChildNode(Node* ChildNode)
{
    
    std::cout<<"add child node"<<std::endl;
    if(NULL != ChildNode)
    {
        //if(NULL != ChildNode->GetParentNode())
        //{
            ChildNode->SetParentNode(this);
            printf(" %p \n", this);
            printf(" %p \n", ChildNode);
        //}
        m_Children.push_back(ChildNode);
    }
}; // AddChildNode()

void Node::RemoveChildNode(Node* ChildNode)
{
    if(NULL != ChildNode && !m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(m_Children[i] == ChildNode)
            {
                m_Children.erase(m_Children.begin() + i);
                break; // break the for loop
            }
        }
    }
}; // RemoveChildNode()

const char* Node::GetNodeName(void) const
{
    return(m_Name);
}; // GetNodeName()


const size_t Node::CountChildNodes(const bool &RecursiveCount) const
{
    if(!RecursiveCount)
    {
        return(m_Children.size());
    }
    else
    {
        size_t Retval = m_Children.size();
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            Retval += m_Children[i]->CountChildNodes(true);
        }
        return(Retval);
    }
}; // CountChildNodes()

Node* Node::GetChildNodeByName(const char *SearchName)
{
    Node* Retval = NULL;
    if(!m_Children.empty())
    {
        for(size_t i = 0; i < m_Children.size(); ++i)
        {
            if(0 == strcmp(m_Children[i]->m_Name, SearchName))
            {
                Retval = m_Children[i];
                break; // break the for loop
            }
        }
    }
    return(Retval);
}; // GetChildNodeByName()