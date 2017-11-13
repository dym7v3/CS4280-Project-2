
#ifndef PROJECT_2_NODE_H
#define PROJECT_2_NODE_H

#include "token.h"
#include <vector>
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
    NULL_Node
};


class Node
{
private:


    NODE_ID Label;
    TOKEN_ID  token_id=NO_TOKEN;
    int line_number;
    string the_string;
    vector <Node> Children;
public:
    Node(); //Default constructor

    //Constructor for the class.
    Node(NODE_ID);

    void setChild1(Node);
    void setChild2(Node);
    void setChild3(Node);
    void setChild4(Node);
    void setToken(Token);
    NODE_ID getNODE_ID();
    unsigned int getSizeOfVector();
    vector<Node> getChild();
    TOKEN_ID getTokenID();
    string getTokenString();
    int getTokenLineNumber();

};

#endif //PROJECT_2_NODE_H
