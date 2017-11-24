#include "node.h"
#include "scanner.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <winnt.h>

using namespace std;
const int NODE_IDS_SIZE=18;

string NodeIds[NODE_IDS_SIZE]={
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

void push(Token);
int find(string );
bool verify(string);
void insert(string);


void printParseTree(Node rootP, int level, ostream &output)      /* for debugging */
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
                cout<<" ";
                output<<" ";
            }
            level=level/2;
            cout<<level<<" : NODE --> "<<NodeIds[rootP.getNODE_ID()];
            output<<level<<" : NODE --> "<<NodeIds[rootP.getNODE_ID()];
            cout << " : TOKEN = '" << TOKEN_IDS_TO_STRING_ARRAY[rootP.getTokenID()] << "' ON LINE NUMBER = '" << rootP.getTokenLineNumber()<< "' WITH STRING VALUE : < " << rootP.getTokenString()<<" >"<<endl;
            output<< " : TOKEN = '" << TOKEN_IDS_TO_STRING_ARRAY[rootP.getTokenID()] << "' ON LINE NUMBER = '" << rootP.getTokenLineNumber()<< "' WITH STRING VALUE < "<< rootP.getTokenString()<<" >"<< endl;
        }
        else
        {
            level=level*2;
            for(auto i=0; i<level; i++)
            {
                cout<<" ";
                output<<" ";
            }
            level=level/2;
            cout<<level<<" : NODE --> "<<NodeIds[rootP.getNODE_ID()]<<endl;
            output<<level<<" : NODE --> "<<NodeIds[rootP.getNODE_ID()]<<endl;
        }
    }


    vector <Node> kids=rootP.getChild();
    for(const Node node : kids)
   {
       printParseTree(node, level + 1, output);
   }

}

//<program>  ->     <vars> <block>
//<block>    ->      Begin <vars> <stats> End
//<vars>     ->      empty | Var Identifier <mvars>
//<mvars>    ->     .  | , Identifier <mvars>
//<expr>     ->      <M> + <expr> | <M> - <expr> | <M>
//<M>        ->     <F> % <M> | <F> * <M> | <F>
//<F>        ->      ( <F> ) | <R>
//<R>        ->      [ <expr> ] | Identifier | Number
//<stats>    ->      <stat>  <mStat>
//<mStat>    ->      empty |  <stat>  <mStat>
//<stat>     ->      <in> | <out> | <block> | <if> | <loop> | <assign>
//<in>       ->      Input Identifier ;
//<out>      ->      Output <expr>  ;
//<if>       ->      Check [ <expr> <RO> <expr> ] <stat>
//<loop>     ->      Loop [ <expr> <RO> <expr> ] <stat>
//<assign>   ->      Identifier : <expr>   ;
//<RO>       ->      < | <= | >  | >= | ==  |  !=


void error(Node node)
{
    cout<<"SYNTAX ERROR: The variable "<<node.getTokenString()<<" already exists in the vector on line number: "<<node.getTokenLineNumber()<<endl;
    cout<<"You can't declare the a variable with the same name twice. The compiler will terminate."<<endl;
    exit(1);
}


vector<string> Globals;

//This checks the Syntax of the and semantics are good.
//This is will check if the variables are used properly or not.
void Syntax(Node rootP, int level)      /* for debugging */
{
    if (rootP.getNODE_ID()==VARS_Node || rootP.getNODE_ID()==MVARS_Node)
    {
        if(!verify(rootP.getTokenString()))
        {
            insert(rootP.getTokenString());
        }
        else
        {
           error(rootP);
        }
    }
    if(rootP.getNODE_ID()==STAT_Node)
    {
        vector <Node> kids=rootP.getChild();
        for(const Node node : kids)
        {
            Syntax(node, level + 1);
        }
    }





    vector <Node> kids=rootP.getChild();
    for(const Node node : kids)
    {
        Syntax(node, level + 1);
    }
}


void insert(string value)
{
    Globals.push_back(value);
}
void push(Token token)
{

}

int find(string value)
{

}
bool verify(string value)
{
    if(Globals.empty())
    {
        return false;
    }
    for (auto &Global : Globals)
    {
        if(Global == value)
        {
            return true;
        }
    }
    return false;
}