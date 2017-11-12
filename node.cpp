


#include <iostream>
#include "node.h"

using namespace std;
//Default constructor.
Node::Node()
{
}

Node::Node(NODE_ID Label_ID)
{
    Label=Label_ID;
}

void Node::setChild1(Node child)
{
    Child1=child;
}

void Node::setChild2(Node child)
{
    Child2=child;
}
void Node::setChild3(Node child)
{
    Child3=child;
}

void Node::setChild4(Node child)
{
    Child4=child;
}

void Node::setToken(Token the_token) {
    token=the_token;
}

Token Node::getToken()
{
    return token;
}


