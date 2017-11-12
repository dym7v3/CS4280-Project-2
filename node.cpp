


#include <iostream>
#include "node.h"

using namespace std;


//This is the constructor. It will take in the a TOKEn_ID, a string value and line number.
Node::Node()
{
}
Node::Node(NODE_ID Label_ID, TOKEN_ID Token_ID)
{
    label=Label_ID;
    token=Token_ID;
}

void Node:: setChild1()

