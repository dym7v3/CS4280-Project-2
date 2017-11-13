
#include <iostream>
#include "./token.h"
#include "scanner.h"
#include "node.h"

using namespace std;

static const string ERROR="PARSING ERROR: ";
static Token tk;

/*
/accounts/classes/janikowc/cs4280
when you build a parse tree the tokens that you need to store are id, operators, numbers. Don't have to store the other ones.
Each node will have 4 children. input identifier won't have to store.
One node has one token.
Set all the pointers that you create to null before you start using them.
You can use a vector for the children.
main{
 ........
 .
 .
 .
 ..
 node *p=parser();
 preorder print(p);
 ...
 }
 This is why the print tree should be in a separate file. Because later on it will be removed.
 */



//prototypes for all the functions.
Node *PROGRAM();
Node BLOCK();
Node VARS();
Node MVARS();
Node EXPR();
Node M();
Node F();
Node R();
Node STATS();
Node MSTAT();
Node STAT();
Node IN();
Node OUT();
Node IFF();
Node LOOP();
Node ASSIGN();
Node RO();
void error(TOKEN_ID, Token);

void error(TOKEN_ID expected , Token got)
{
    cout<<"PARSING ERROR: The Expected Token was : "<<TOKEN_IDS_TO_STRING_ARRAY[expected]<<" but got : "<<TOKEN_IDS_TO_STRING_ARRAY[got.Get_Token_ID()]<<" on line number : "<<got.Get_Line_Number()<<endl;
    cout<<"The parsing was terminated. "<<endl;
    exit(1);
}

//<M> ->  <F> % <M> | <F> * <M> | <F>
Node M()
{
    Node t(M_Node);
    t.setChild1(F());
    if(tk.Get_Token_ID()==Operator_Modulo)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner();
        t.setChild2(M());
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Multiply)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner();
        t.setChild2(M());
        return t;
    }
    else
        return t;
}


//<F> ->  ( <F> ) | <R>
Node F()
{
    Node t(F_Node);
    if(tk.Get_Token_ID()==Delimiter_Left_Parenthesis)
    {
        tk=scanner(); //Consumes the (
        t.setChild1(F());
        if(tk.Get_Token_ID()==Delimiter_Right_Parenthesis)
        {
            tk=scanner(); //Consumes the )
            return t;
        } else
        {
            error(Delimiter_Right_Parenthesis,tk);
        }
    }
    else
    {
        t.setChild1(R());
        return t;
    }
}

//<IN> ->  Input Identifier ;
Node IN()
{
    if(tk.Get_Token_ID()==Keyword_Input)
    {
        tk=scanner(); //Consumes the input keyword
        if(tk.Get_Token_ID()==Identifiers)
        {
            Node t(IN_Node);
            t.setToken(tk); //First save the token then consume it.
            tk=scanner();
            if(tk.Get_Token_ID()==Delimiter_Semi_Colon)
            {
                tk=scanner();
                return t;
            }
            else
            {
                error(Delimiter_Semi_Colon,tk);
            }
        }
        else
        {
            error(Identifiers,tk);
        }
    }
    else
    {
        error(Keyword_Input,tk);
    }
}


//<EXPR>   ->  <M> + <EXPR> | <M> - <EXPR> | <M>
Node EXPR()
{
    Node t(EXPR_Node);
    t.setChild1(M());
    if(tk.Get_Token_ID()==Operator_Plus)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the plus.
        t.setChild2(EXPR());
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Minus)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the Minus.
        t.setChild2(EXPR());
        return t;
    }
    else
    {
       return t;
    }
}
//<STAT> ->  <IN> | <OUT> | <BLOCK> | <IFF> | <LOOP> | <ASSIGN>
Node STAT()
{
    Node t(STAT_Node);
    if(tk.Get_Token_ID()==Keyword_Input)
    {
        t.setChild1(IN());
        return t;
    }
    else if(tk.Get_Token_ID()==Keyword_Output)
    {
        t.setChild1(OUT());
        return t;
    }
    else if(tk.Get_Token_ID()==Keyword_Begin)
    {
        t.setChild1(BLOCK());
        return t;
    }
    else if(tk.Get_Token_ID()==Keyword_Check)
    {
        t.setChild1(IFF());
        return t;
    }
    else if (tk.Get_Token_ID()==Keyword_Loop)
    {
        t.setChild1(LOOP());
        return t;
    }
    else if(tk.Get_Token_ID()==Identifiers)
    {
        t.setChild1(ASSIGN());
        return t;
    }
    else
    {
        cout<<ERROR<<"Expected to get token to be loop, check, begin, ouput, input or Identifier but got : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" on line number : "<<tk.Get_Line_Number()<<endl;
    }
}

//<IFF> /->  Check [ <EXPR> <RO> <EXPR> ] <STAT>
Node IFF()
{
    //This starts the check and then goes to Left Bracket and then EXPR and Then RO and Then EXPR and then Right Bracket and Then STAT.
    //There is only one way that the tokens can go.
    if(tk.Get_Token_ID()==Keyword_Check)
    {
        tk=scanner(); //Consumes the Check Keyword
        if(tk.Get_Token_ID()==Delimiter_Left_Bracket)
        {
            Node t(IFF_Node);
            tk=scanner(); //Consumes the Left Bracket token.
            t.setChild1(EXPR());
            t.setChild2(RO());
            t.setChild3(EXPR());
            if(tk.Get_Token_ID()==Delimiter_Right_Bracket)
            {
                tk=scanner(); //Consumes the Right Bracket token.
                t.setChild4(STAT());
                return t;
            }
            else {
                error(Delimiter_Right_Bracket,tk);
            }
        }
        else {
            error(Delimiter_Left_Bracket,tk);
        }
    }
    else{
        error(Keyword_Check, tk);
    }
}

//<LOOP>   ->  Loop [ <EXPR> <RO> <EXPR> ] <STAT>
Node LOOP()
{
    //Only allows only the loop keyword then Left bracket and EXPR then RO and EXPR and Right Bracket and STAT
    if(tk.Get_Token_ID()==Keyword_Loop)
    {
        Node t(LOOP_Node);
        tk=scanner(); // Consumes the Keyword Loop token
        if(tk.Get_Token_ID()==Delimiter_Left_Bracket)
        {
            tk=scanner(); //Consumes the Left Bracket token.
            t.setChild1(EXPR());
            t.setChild2(RO());
            t.setChild3(EXPR());
            if(tk.Get_Token_ID()==Delimiter_Right_Bracket)
            {
                tk=scanner(); //Consumes the Right Bracket token.
                t.setChild4(STAT());
                return t;
            } else{
                error(Delimiter_Right_Bracket,tk);
            }
        } else{
            error(Delimiter_Left_Bracket, tk);
        }
    } else{
        error(Keyword_Loop, tk);
    }
}

//<RO> ->  < | <= | >  | >= | ==  |  !=
Node RO()
{
    Node t (RO_Node);
    if(tk.Get_Token_ID()==Operator_Less_Than)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the less than operator.
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Less_Than_Or_Equal_To)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the less than or equal to operator.
        return t ;
    }
    else if(tk.Get_Token_ID()==Operator_Greater_Than)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the greater than operator.
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Greater_Than_Or_Equal_To)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); // Consumes the greater than or equal to operator.
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Equal_To)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the equal to operator.
        return t;
    }
    else if(tk.Get_Token_ID()==Operator_Not_Equal_To)
    {
        t.setToken(tk); //First save the token then consume it.
        tk=scanner(); //Consumes the not equal to operator.
        return t;
    }
    else
    {
        cout<<ERROR<<"The token that was received  was : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" but expected to get < or <= or > or >+ or == or != on line number : "<<tk.Get_Line_Number()<<endl;
        exit(1);
    }
}

//<ASSIGN>   ->  Identifier : <EXPR>   ;
Node ASSIGN()
{
    //ASSIGN can only begin with an Identifier else error. Then after the Identifier we need a colon else error and After colon
    //we will call EXPR and after that ; else it will be error.
    if(tk.Get_Token_ID()==Identifiers)
    {
        Node t(ASSIGN_Node);
        t.setToken(tk); //Save the token before consuming it.
        tk=scanner(); //Consumes the Identifier
        if(tk.Get_Token_ID()==Delimiter_Colon)
        {
            tk=scanner(); //Consumes the Colon Identifier
            t.setChild1(EXPR());
            if(tk.Get_Token_ID()==Delimiter_Semi_Colon)
            {
                tk=scanner(); //Consumes the Semi-Colon Delimiter.
                return t;
            }
            else
            {
                error(Delimiter_Semi_Colon, tk);
            }
        }
        else{
            error(Delimiter_Colon,tk);
        }
    } else{
        error(Identifiers,tk);
    }
}
//<OUT> ->  Output <EXPR>  ;
Node OUT()
{
    //There is only one production that the production can be. If not it will throw an error.
    //If the first is Output Keyword then it will call the EXPR function and then check if the token is a Semi-colon else it will throw an error.
    if(tk.Get_Token_ID()==Keyword_Output)
    {
        Node t(OUT_Node);
        tk=scanner(); //Output Token consumed
        t.setChild1(EXPR());
        if(tk.Get_Token_ID()==Delimiter_Semi_Colon)
        {
            tk=scanner(); //Consumes the Semi-colon.
            return t;
        }
        else
        {
            error(Delimiter_Semi_Colon,tk);
        }
    }
    else
    {
        error(Keyword_Output,tk);
    }
}

//<R> ->  [ <EXPR> ] | Identifier | Number
Node R()
{
    Node t(R_Node);
    //Checks if the first is a open bracket.
    if(tk.Get_Token_ID()==Delimiter_Left_Bracket)
    {
        tk=scanner(); //Consuming the Left Bracket.
        t.setChild1(EXPR());
        if(tk.Get_Token_ID()==Delimiter_Right_Bracket)
        {
            tk=scanner(); //Consumes the Right Bracket.
            return t;
        }
        else
        {
            error(Delimiter_Right_Bracket,tk);
        }
    }
    else if(tk.Get_Token_ID()==Integer)
    {
        t.setToken(tk); //First save the token before it consumes it.
        tk=scanner(); //consumes the Number or Integer token.
        return t;
    }
    else if(tk.Get_Token_ID()==Identifiers)
    {
        t.setToken(tk); //First store the token before consuming it.
        tk=scanner(); //consumes the Identifier token.
        return t;
    }
    else
    {
        cout<<ERROR<<"Expect to get a Left Bracket or Identifier or Number but got : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" on line number : "<<tk.Get_Line_Number()<<endl;
        exit(1);
    }
}


//<MSTAT> ->  empty |  <STAT>  <MSTAT>
Node MSTAT()
{
    if(tk.Get_Token_ID()==Keyword_Input || tk.Get_Token_ID()==Keyword_Output || tk.Get_Token_ID()==Keyword_Begin || tk.Get_Token_ID()==Keyword_Check || tk.Get_Token_ID()==Keyword_Loop || tk.Get_Token_ID()==Identifiers) {
        Node t(MSTAT_Node);
        t.setChild1(STAT());
        t.setChild2(MSTAT());
        return t;
    }
    else
    {
       return Node(NULL_Node);
    }
}

//<STATS> ->  <STAT>  <MSTAT>
Node STATS()
{
    Node t(STATS_Node);
    //This non-terminal function will only have two options.
    t.setChild1(STAT());
    t.setChild2(MSTAT());
    return t; //Returns when both execute in order.
}

//<MVARS> ->  .  | , Identifier <MVARS>
Node MVARS()
{
    //When called it will check if it got the period delimiter or the comma delimiter.
    //If it got the period delimiter then it will consume the period and return.
    //else it will check the comma delimiter and then it will can the mvars() function and when that returns it will be done and return.
    if(tk.Get_Token_ID()==Delimiter_Period)
    {
        tk=scanner(); //consumes the period.
        return Node(NULL_Node);
    }
    else if(tk.Get_Token_ID()==Delimiter_Comma)
    {
        Node t(MVARS_Node);
        tk=scanner(); //consumes the Comma delimiter.
        if(tk.Get_Token_ID()==Identifiers)
        {
            t.setToken(tk); //First save the token then consume it.
            tk=scanner(); // Consumes the Identifier.
            t.setChild1(MVARS());
            return t;
        }
        else
        {
            error(Identifiers,tk);
        }

    }
    else
    {
        cout<<ERROR<<"The parser got a : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" but expected to have a period or comma delimiter."<<" on line number : "<<tk.Get_Line_Number()<<endl;
        exit(1);
    }
}

//<VARS> ->  empty | Var Identifier <MVARS>
Node VARS()
{
    //if the token Id is a Keyword Var then it will consume the tk and call the mvar() function
    //it follows it automatically follows it in the BNF.
    if(tk.Get_Token_ID()==Keyword_Var)
    {
        Node t(VARS_Node);
        tk=scanner(); //consumes the keyword Var
        if(tk.Get_Token_ID()==Identifiers)
        {
            t.setToken(tk); //First save the token then consume it.
            tk=scanner(); //consumes the Identifiers.
            t.setChild1(MVARS()); //calls mvars() right after Keyword Var.
            return t;
        }
        else
        {
            error(Identifiers,tk);
        }
    }
    else //This will be for the empty string.
        return Node(NULL_Node);
}
//<BLOCK> ->  Begin <VARS> <STATS> End
Node BLOCK()
{

    //The first thing the block function checks is the keyword.
    //Once it finds that then it will call vars() and right after it will call stats. Then it will check
    //if the end keyword was found. If it was then it will return.
    if(tk.Get_Token_ID()==Keyword_Begin)
    {
        Node t(BLOCK_Node);
        tk=scanner(); //Consumes the Begin token.
        t.setChild1(VARS());
        t.setChild2(STATS());
        if(tk.Get_Token_ID()==Keyword_End)
        {
            tk=scanner(); //Consumes the End token.
            return t;
        }
        else
        {
           error(Keyword_End,tk);
        }
    }
    else
    {
       error(Keyword_Begin,tk);
    }
}
//<PROGRAM>  ->  <VARS> <BLOCK>
Node * PROGRAM()
{
    auto *t=new Node(PROGRAM_Node);
    //program function can only go to two things. The vars() and block() functions which are non-terminals.
    t->setChild1(VARS());
    t->setChild2(BLOCK());
    return t;
}

Node * parser()
{

    Node *root; //Made the node which will be the root.
    tk=scanner(); //Grabs the first from the scanner.
    root=PROGRAM();
    //Checks if the End of is the last token. If yes then the parsing is correct.
    if(tk.Get_Token_ID()==End_Of_File)
    {
        cout<<"Successful parsing."<<endl;
    }
    else
    { //Else it will display an error and terminate the program.
        error(End_Of_File,tk);
    }
    return root; //This returns nothing. But later will be changed for the parse tree. It will return the whole parse tree.
}

