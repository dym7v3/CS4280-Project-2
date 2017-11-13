#include "node.h"
#include "scanner.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
const int NODE_IDS_SIZE=19;

string NodeIds[NODE_IDS_SIZE]={
        "PARSER_Node",
        "PROGRAM_Node",
        "BLOCK_Node",
        "VARS_Node",
        "MVARS_Node",
        "EXPR_Node",
        "M_Node",
        "F_Node",
        "R_Node",
        "STATS_Node",
        "MSTAT_Node",
        "STAT_Node",
        "IN_Node",
        "OUT_Node",
        "IFF_Node",
        "LOOP_Node",
        "ASSIGN_Node",
        "RO_Node",
        "NULL_Node"

};



void printParseTree(Node rootP, int level, ostream& output)      /* for debugging */
{
    if (rootP.getNODE_ID()==NULL_Node)
    {
         return;
    }

    if (rootP.getNODE_ID()!=NULL_Node)
    {
        if(rootP.getTokenID()!=NO_TOKEN)
        {
            level=level*2;
            for(auto i=0; i<level; i++)
            {
                cout<<"\t";
                output<<"\t";
            }
            level=level/2;
            cout<<level<<" : NODE : "<<NodeIds[rootP.getNODE_ID()];
            output<<level<<" : NODE : "<<NodeIds[rootP.getNODE_ID()];
            cout << " : TOKEN = " << TOKEN_IDS_TO_STRING_ARRAY[rootP.getTokenID()] << " ON LINE NUMBER : " << rootP.getTokenLineNumber()<< " WITH STRING VALUE : " << rootP.getTokenString()<< endl;
            output<< " : TOKEN = " << TOKEN_IDS_TO_STRING_ARRAY[rootP.getTokenID()] << " ON LINE NUMBER : " << rootP.getTokenLineNumber()<< " WITH STRING VALUE : "<< rootP.getTokenString()<< endl;
        }
        else
        {
            level=level*2;
            for(auto i=0; i<level; i++)
            {
                cout<<"\t";
                output<<"\t";
            }
            level=level/2;
            cout<<level<<" : NODE : "<<NodeIds[rootP.getNODE_ID()]<<endl;
            output<<level<<" : NODE : "<<NodeIds[rootP.getNODE_ID()]<<endl;
        }
    }


    vector <Node> kids=rootP.getChild();
    for(const Node node : kids)
   {
        printParseTree(node,level+1,output);
   }

}
