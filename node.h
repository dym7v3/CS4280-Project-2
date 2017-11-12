
#ifndef PROJECT_2_NODE_H
#define PROJECT_2_NODE_H

#include "token.h"

enum NODE_ID {
    PROGRAM_Node,
    BLOCK_Node,
    VARS_Node,
    MVARS_Node,
    EXPR_Node,
    M_Node,
    F_Node,
    R_Node,
    STATS_Node,
    MSTAT_Node,
    STAT_Node,
    IN_Node,
    OUT_Node,
    IFF_Node,
    LOOP_Node,
    ASSIGN_Node,
    RO_Node,
};


class Node
{
private:


    NODE_ID Label;
    Token token;
    Node Child1;
    Node Child2;
    Node Child3;
    Node Child4;
public:
    Node(); //Default constructor

    //Constructor for the class.
    Node(NODE_ID);

    void setChild1(Node);
    void setChild2(Node);
    void setChild3(Node);
    void setChild4(Node);
    void setToken(Token);
    Token getToken();
};

#endif //PROJECT_2_NODE_H
