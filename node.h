
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


    NODE_ID label;
    TOKEN_ID token;
    Node child1;
    Node child2;
    Node child3;
    Node child4;
public:
    Node(); //Default constructor

    //Constructor for the class.
    Node(NODE_ID, TOKEN_ID);

};



#endif //PROJECT_2_NODE_H
