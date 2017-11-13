


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

    Children.push_back(child);
}

void Node::setChild2(Node child)
{
    Children.push_back(child);
}
void Node::setChild3(Node child)
{

    Children.push_back(child);
}

void Node::setChild4(Node child)
{

    Children.push_back(child);
}

void Node::setToken(Token the_token) {
    token_id=the_token.Get_Token_ID();
    the_string=the_token.Get_The_String();
    line_number=the_token.Get_Line_Number();
}

NODE_ID Node::getNODE_ID()
{
    return Label;
}

TOKEN_ID Node::getTokenID()
{
    return token_id;
}

string Node::getTokenString()
{
    return the_string;
}
int Node::getTokenLineNumber()
{
    return line_number;
}

unsigned int Node::getSizeOfVector()
{
    return Children.size();
}

vector <Node> Node::getChild()
{
    return Children;
}
