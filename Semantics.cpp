#include "node.h"
#include "scanner.h"
#include <iostream>
#include <winnt.h>
#include <stack>
#include <set>

using namespace std;
const int NODE_IDS_SIZE=18;
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

deque<string> variables;
int varCounter=0;
int globals=0;
bool firstBlock=true;
bool inBlock=false;
int find(string );
bool verify(string);
void pop(int);
void push(string);

void printParseTree(Node rootP, int level, ostream &output)      /* for debugging */
{
    if (rootP.getNODE_ID()==NULL_Node)
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


void error(Node node)
{
    cout<<"SYNTAX ERROR: The variable "<<node.getTokenString()<<" already exists in the vector on line number: "<<node.getTokenLineNumber()<<endl;
    cout<<"You can't declare the a variable with the same name twice. The compiler will terminate."<<endl;
    exit(1);
}

//This checks the Syntax of the and semantics are good.
//This is will check if the variables are used properly or not.
void SyntaxLocal(Node rootP, int level)      /* for debugging */
{
    if (rootP.getNODE_ID()==VARS_Node || rootP.getNODE_ID()==MVARS_Node)
    {
        if(!find(rootP.getTokenString()) && !firstBlock)
        {
            push(rootP.getTokenString());
            if(firstBlock)
            {
                globals++;
            }
            else
            {
                varCounter++;
            }
        }
        else if(!verify(rootP.getTokenString()) && firstBlock)
        {
            push(rootP.getTokenString());
            globals++;
        }
        else {
            error(rootP);
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


/*This will be the function for R node Function:
R->EXPR (nothing gets generated bu rather calls it child node
Or when R->ID | Number
printf("LOAD %s", rootP.getTokenIdString());
No to check which case it is.
If it has a child then it is the first case.
If it has a token or number then it is the second case.

Now ASSIGN Function:
It this usually have a token that is an identifier.
Then there is a child. And we are not doing the child just the part for the assign function.
 First call the child node. When this returns that means that the value will be in the accumlater.
 How do we move it to the accumlater. All we would need to do is use the STORE function in the ambessly.
 pinrtf("STORE %s", rootP.getNodeTokeString); --> LOAD X


Now EXPR

 Remember that we are always do the only the top part. There is two case:
 EXRP-->M (Call the child)

 How do you determine cases is if there is a child or token. Child in the first case.

 The second case:
 EXPR-->M and EXPR-->EXRP
 You need to create the a temporary variable to be able to store the value so that you can get it out of the
 accumulater. You want to go with the right one first and then to the left node.
 First call the child 2. When it comes back it the value will be saved in a the accumlater. Then i need to create
 a temporary variable and then I save the value from the accumlater into the temp variable.
 Call node 2
 Create Temp
 printF("STORE %S", temp_varialbe) --> (STORE T1)
 In order to have these temporary variables we will just not allow for certian names to be used
 for variables in the program.

 Call Child 1 and then
 if(Token is + )
    print("ADD %s", temp_variable) -->(ADD T1)
 else
    print("SUB %s", temp_variable) -->(SUB T1)



 The OUT_NODE
 OUT-->EXPR (Remember that we are only making the code for the OUT node not EXPR)
 1) Call the child to evaluate the expression
 2) Then create a TEMP variable.
 3) Print (STORE to the temp variable)
 4) Print (WRITE to the temp variable)

 Two Cases for F
 F-->F (In this case you need to negate whatever comes back to you)
 F-->R

 You can figure out which case all you need to do is check the children on the node.

 case 2: Just call the child
 case 1: printf("Mult -1") (MULT -1)






 Traversal ()
 {
 counter=0;
 switch (Node){
    "Block":
        counter=0;
        call vars
        call stats
        pop the variables and do whatever you need to do when leaving the block.

        break
    }
}


IFF-->Expr
IFF-->RO
IFF-->Expr
IFF-->stat

{ This is one
    Call Child3
    Make TEMP_variable
    PrintF("STORE %S",TEMP_Variable)
    Call Child1
    Printf("SUB %S",TEMP_Variable)
}

 { Jump this is number one.
     create a Label = Label_created
     printF("BRZNEG %S", Label_created) //Ifs based on RO Token.
 }

 { This is number 3
    Call Child4
    printf("%S: NOOP", Label_created)

 }

 We save the labels locally.
 This is ^ what you implement when you get an iff node.
 If you use the labels and variables Globally then you won't have the ability to do nested variables.

 The only difference for loop is that you have two Labels and you jump out.

  */





