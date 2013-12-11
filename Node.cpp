//
//  Node.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/6/13.
//
//

#include "Node.h"
GRT::UINT Node::numNodeInstances = 0;

StringNodeMap* Node::stringNodeMap = new StringNodeMap;



Node::Node(Node* Parent, const char* Name)
: m_Name(Name)
{
    m_Parent = Parent;
    numNodeInstances++;
} // Constructor

Node::~Node(void)
{
    clear();
    if( --numNodeInstances == 0 ){
        
        delete stringNodeMap;
        
        stringNodeMap = NULL;
     
    }
} // Destructor

bool Node::clear(){
    cout<<"node clear"<<endl;
    m_Parent = NULL;
    
    for(int i=0;i<m_Children.size();i++){
        cout<<"node clearing child at "<<endl;

        m_Children[i]->clear();
        delete  m_Children[i];
        m_Children[i] = NULL;
    }
    
    m_Children.clear();

    return true;
}



Node::Node(const Node &rhs){
    *this = rhs;
}

Node& Node:: operator = (const Node &rhs){
    if(this!= &rhs){
        copyBaseVariables( (Node*)&rhs );
    }
    return *this;
}


bool Node::deepCopyFrom(const Node *node) {
    cout<<"node deep copy attempt"<<endl;

    if( node == NULL ){
        return false;
    }
    
    copyBaseVariables(node);
    for(int i=0;i<node->m_Children.size();i++){    //Recursively deep copy the left child
        
        Node* c = node->m_Children[i]->createNewInstance();
        if(c ==NULL){
            cout<<"child not copied"<<endl;
            return false;
  
        }
        //Validate that the classifier was cloned correctly
        if( !c->deepCopyFrom( node->m_Children[i] ) ){
            delete c;
            c=NULL;
            cout<<"child not copied because of deep copy"<<endl;
            return false;
        }
        this->m_Children.push_back(c);
        c->m_Parent = this;
        cout<<"child copy success at "<<i<<endl;

        //this->leftChild->parent = node;
    }
    return true;
}

bool Node::copyBaseVariables(const Node *node){
    
    if( node == NULL ){
        // errorMessage = "copyBaseVariables(const Classifier *classifier) - Classifier is NULL!";
        //errorLog << errorMessage << endl;
        return false;
    }
    
    /*if( !this->copyBaseVariables( node ) ){
        return false;
    }*/
    //this->m_Children = node->m_Children;
        
    
    //this->m_Parent = node->m_Parent;
    this->m_Name = node->m_Name;
    std::cout<< "node copy base variables"<<std::endl;
    return true;
}

Node* Node::createInstanceFromString(string const &nodeType){
    
    cout<<"creating instance from string"<<endl;
    StringNodeMap* stringNodeMap = NULL;
    numNodeInstances=0;
    
    StringNodeMap::iterator iter = getMap()->find( nodeType );
    if( iter == getMap()->end() ){
        cout<<"returning null in create from string"<<endl;

        return NULL;
    }
    cout<<"returning second"<<endl;

    return iter->second();
}

Node* Node::createNewInstance() const{
    return createInstanceFromString( type );
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