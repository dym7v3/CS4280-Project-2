//
// Created by Dennis Moyseyev on 12/5/2017.
//

#include "node.h"
#include <iostream>
#include <stack>

using namespace std;

//<program>  ->     <vars> <block> (Done)
//<block>    ->      Begin <vars> <stats> End (Done)
//<vars>     ->      empty | Var Identifier <mvars> (Done)
//<mvars>    ->     .  | , Identifier <mvars> (Done)
//<expr>     ->      <M> + <expr> | <M> - <expr> | <M> (Done)
//<M>        ->     <F> % <M> | <F> * <M> | <F> (Done)
//<F>        ->      ( <F> ) | <R> (Done)
//<R>        ->      [ <expr> ] | Identifier | Number (Done)
//<stats>    ->      <stat>  <mStat> (Done)
//<mStat>    ->      empty |  <stat>  <mStat> (Done)
//<stat>     ->      <in> | <out> | <block> | <if> | <loop> | <assign> (Done)
//<in>       ->      Input Identifier ; (Done)
//<out>      ->      Output <expr>  ; (Done)
//<if>       ->      Check [ <expr> <RO> <expr> ] <stat>
//<loop>     ->      Loop [ <expr> <RO> <expr> ] <stat>
//<assign>   ->      Identifier : <expr>   ; (Done)
//<RO>       ->      < | <= | >  | >= | ==  |  !=
int VarCounter=0;
vector<string> varaibles;

Node Child3;
Node Child4;
bool expr_exists=false;
bool m_node_exists=false;

void error()
{
    cout<<"CODE GENERATION ERROR: Could not go forward because didn't find the need children. "<<endl;
    exit(1);
}
string makeTempVariable()
{
    string variable="V";
    variable+=to_string(VarCounter);
    VarCounter++;
    varaibles.push_back(variable);
    return variable;
}

void codeGeneration(Node rootP, ostream &output )
{
    switch (rootP.getNODE_ID())
    {

        //<M> -> <F> % <M> | <F> * <M> | <F>
        case  M_Node:
        {
            Node Child1;
            Node Child2;
            vector<Node> kids = rootP.getChild();
            for (Node node : kids)
            {
                if (node.getNODE_ID() == M_Node)
                {
                    Child2=node;
                    m_node_exists=true;
                }
                if(node.getNODE_ID() == F_Node)
                {
                    Child1=node;
                }
            }
            if(m_node_exists)
            {
                m_node_exists=false;
                codeGeneration(Child2, output);
                string temp=makeTempVariable();
                output<<"STORE "<<temp<<endl;
                codeGeneration(Child1, output);
                if(rootP.getTokenID()==Operator_Multiply)
                {
                    output<<"MULT "<<temp<<endl;
                }
                else
                {
                    output<<"DIV "<<temp<<endl;
                }
            }
            else
            {
                codeGeneration(Child1, output);
            }
        }
        break;
        //<out> -> Output <expr>  ;
        case OUT_Node:
        {
            vector<Node> kids = rootP.getChild();
            for (const Node node : kids)
            {
                codeGeneration(node, output);
            }
            string temp=makeTempVariable();
            output<<"STORE "+temp<<endl;
            output<<"WRITE "+temp<<endl;
        }
        break;

        case IN_Node:
        {
            output<<"READ "<<rootP.getTokenString()<<endl;
        }
        break;

        case EXPR_Node:
        {
            Node Child1;
            Node Child2;
            //<expr> -> <M> + <expr> | <M> - <expr> | <M>
            vector<Node> kids = rootP.getChild();
            for (Node node : kids)
            {
                if (node.getNODE_ID() == EXPR_Node)
                {
                    Child2=node;
                    expr_exists=true;
                }
                if(node.getNODE_ID() == M_Node)
                {
                    Child1=node;
                }
            }
            if(expr_exists)
            {
                expr_exists=false;
                codeGeneration(Child2, output);
                string temp=makeTempVariable();
                output<<"STORE "<<temp<<endl;
                codeGeneration(Child1, output);
                if(rootP.getTokenID()==Operator_Plus)
                {
                    output<<"ADD "<<temp<<endl;
                }
                else
                {
                    output<<"SUB "<<temp<<endl;
                }
            }
            else
            {
                codeGeneration(Child1, output);
            }
        }
        break;
        case ASSIGN_Node:
        {
            vector<Node> kids = rootP.getChild();
            for (Node node : kids)
            {
                if(node.getNODE_ID()==EXPR_Node) {
                    codeGeneration(node, output);
                } else
                    error();
            }
            output<<"STORE "<<rootP.getTokenString()<<endl;
        }
        break;
        case R_Node :
        {
            if(rootP.getTokenID()==Identifiers || rootP.getTokenID()==Integer)
            {
                output<<"LOAD "<<rootP.getTokenString()<<endl;
            }
            else
            {
                vector<Node> kids = rootP.getChild();
                for (Node node : kids)
                {
                    if(node.getNODE_ID()==EXPR_Node){
                        codeGeneration(node, output);
                    } else {
                        error();
                    }
                }
            }

        }
        break;
        case F_Node:
        {
            vector<Node> kids = rootP.getChild();
            for (Node node : kids)
            {
                if(node.getNODE_ID()==F_Node)
                {
                    codeGeneration(node, output);
                    output<<"MULT -1"<<endl;
                } else{
                    codeGeneration(node, output);
                }
            }
        }
        break;
        default:
        {
            vector<Node> kids = rootP.getChild();
            for (const Node node : kids)
            {
                codeGeneration(node, output);
            }
        }
        break;
    }

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
 accumulater. You want to do with the right one first and then to the left node.
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





