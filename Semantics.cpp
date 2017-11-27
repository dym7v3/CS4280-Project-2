#include "node.h"
#include "scanner.h"
#include <iostream>
#include <winnt.h>
#include <stack>
#include <set>

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

int find(string );
bool verify(string);
void pop(int);
void push(string);


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



deque<string> variables;
vector<string> Globals;
int varCounter=0;
int globals=0;
bool firstBlock=true;
bool inBlock=false;
//This checks the Syntax of the and semantics are good.
//This is will check if the variables are used properly or not.
void SyntaxLocal(Node rootP, int level)      /* for debugging */
{
    if (rootP.getNODE_ID()==VARS_Node || rootP.getNODE_ID()==MVARS_Node)
    {
        if(!find(rootP.getTokenString()))
        {
            push(rootP.getTokenString());
        }
        else
        {
            error(rootP);
        }
        if(firstBlock)
        {
            globals++;
        }
        else
        {
            varCounter++;
        }
    }
    if(rootP.getTokenID()==Identifiers && rootP.getNODE_ID()!=VARS_Node && rootP.getNODE_ID()!=MVARS_Node)
    {
        if(!find(rootP.getTokenString()))
        {
            if (!verify(rootP.getTokenString()))
            {
                cout << "SYNTAX ERROR: The variable '" << rootP.getTokenString()
                     << "' is not declared in scope on line number: " << rootP.getTokenLineNumber() << endl;
                cout << "The compiler will terminate." << endl;
                exit(1);
            }
        }
    }
    if(rootP.getNODE_ID()==BLOCK_Node)
    {
        inBlock=true;
        if(varCounter>0 && inBlock)
        {
            pop(varCounter);
            inBlock=false;
        }
        varCounter=0;
        firstBlock=false;
    }

    vector <Node> kids=rootP.getChild();
    for(const Node node : kids)
    {
        SyntaxLocal(node, level + 1);
    }
}
void printResults()
{
    cout<<"The variables: ";
    deque<string>::iterator it;
    for(it=variables.begin(); it!=variables.end(); it++)
    {
        cout<<*it<<", ";
    }
    cout<<"\nThe amount of the Globals is: "<<globals<<endl;
    cout<<"The amount of Locals: "<<varCounter<<endl;
}

void insert(string value)
{
    Globals.push_back(value);
}
void push(string value )
{
    variables.push_back(value);
}

void pop(int count)
{
    for(int i=count; 0<i; i--)
    {
        variables.pop_back();
    }
}
int find(string value)
{
    if(variables.empty())
    {
        return false;
    }
    deque<string>::iterator it;
    it=variables.begin();
    for(int i=globals; i>0; i--)
    {
        it++;
    }
    for(; it!=variables.end(); it++)
    {
        if(*it==value)
        {
            return true;
        }
    }
    return false;
}
bool verify(string value)
{
    if(variables.empty())
    {
        return false;
    }
    deque<string>::iterator it;
    for(it=variables.begin(); it!=variables.end(); it++)
    {
        if(*it==value)
        {
            return true;
        }
    }
    return false;
}