
#include <iostream>
#include "./token.h"
#include "scanner.h"
#include <string>

using namespace std;

static const string ERROR="PARSING ERROR: ";
static Token tk;

/*
<PROGRAM>  ->  <VARS> <BLOCK>
<BLOCK>    ->  Begin <VARS> <STATS> End
<VARS>     ->  empty | Var Identifier <MVARS>
<MVARS>    ->  .  | , Identifier <MVARS>
<EXPR>     ->  <M> + <EXPR> | <M> - <EXPR> | <M>
<M>        ->  <F> % <M> | <F> * <M> | <F>
<F>        ->  ( <F> ) | <R>
<R>        ->  [ <EXPR> ] | Identifier | Number
<STATS>    ->  <STAT>  <MSTAT>
<MSTAT>    ->  empty |  <STAT>  <MSTAT>
<STAT>     ->  <IN> | <OUT> | <BLOCK> | <IFF> | <LOOP> | <ASSIGN>
<IN>       ->  Input Identifier ;
<OUT>      ->  Output <EXPR>  ;
<IFF>       ->  Check [ <EXPR> <RO> <EXPR> ] <STAT>
<LOOP>     ->  Loop [ <EXPR> <RO> <EXPR> ] <STAT>
<ASSIGN>   ->  Identifier : <EXPR>   ;
<RO>       ->  < | <= | >  | >= | ==  |  !=

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
void PROGRAM();
void BLOCK();
void VARS();
void MVARS();
void EXPR();
void M();
void R();
void STATS();
void MSTAT();
void STAT();
void IN();
void OUT();
void IFF();
void LOOP();
void ASSIGN();
void RO();
void error();

void error(TOKEN_ID expected , Token got)
{
    cout<<"PARSING ERROR: The Expected Token was : "<<TOKEN_IDS_TO_STRING_ARRAY[expected]<<" but got : "<<TOKEN_IDS_TO_STRING_ARRAY[got.Get_Token_ID()]<<endl;
    cout<<"The parsing was terminated. "<<endl;
    exit(1);
}

//<RO> ->  < | <= | >  | >= | ==  |  !=
void RO()
{
    if(tk.Get_Token_ID()==Operator_Less_Than)
    {
        tk=scanner(); //Consumes the less than operator.
        return;
    }
    else if(tk.Get_Token_ID()==Operator_Less_Than_Or_Equal_To)
    {
        tk=scanner(); //Consumes the less than or equal to operator.
        return;
    }
    else if(tk.Get_Token_ID()==Operator_Greater_Than)
    {
        tk=scanner(); //Consumes the greater than operator.
        return;
    }
    else if(tk.Get_Token_ID()==Operator_Greater_Than_Or_Equal_To)
    {
        tk=scanner(); // Consumes the greater than or equal to operator.
        return;
    }
    else if(tk.Get_Token_ID()==Operator_Equal_To)
    {
        tk=scanner(); //Consumes the equal to operator.
        return;
    }
    else if(tk.Get_Token_ID()==Operator_Not_Equal_To)
    {
        tk=scanner(); //Consumes the not equal to operator.
        return;
    }
    else
    {
        cout<<ERROR<<"The token that was received  was : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" but expected to get < or <= or > or >+ or == or !=."
        exit(1);
    }
}

//<ASSIGN>   ->  Identifier : <EXPR>   ;
void ASSIGN()
{
    //ASSIGN can only begin with an Identifier else error. Then after the Identifier we need a colon else error and After colon
    //we will call EXPR and after that ; else it will be error.
    if(tk.Get_Token_ID()==Identifiers)
    {
        tk=scanner(); //Consumes the Identifier
        if(tk.Get_Token_ID()==Delimiter_Colon)
        {
            tk=scanner(); //Consumes the Colon Identifier
            EXPR();
            if(tk.Get_Token_ID()==Delimiter_Semi_Colon)
            {
                tk=scanner(); //Consumes the Semi-Colon Delimiter.
                return;
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
void OUT()
{
    //There is only one production that the production can be. If not it will throw an error.
    //If the first is Output Keyword then it will call the EXPR function and then check if the token is a Semi-colon else it will throw an error.
    if(tk.Get_Token_ID()==Keyword_Output)
    {
        tk=scanner(); //Output Token consumed
        EXPR();
        if(tk.Get_Token_ID()==Delimiter_Semi_Colon)
        {
            tk=scanner(); //Consumes the Semi-colon.
            return;
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
void R()
{
    //Checks if the first is a open bracket.
    if(tk.Get_Token_ID()==Delimiter_Left_Bracket)
    {
        tk=scanner(); //Consuming the Left Bracket.
        EXPR();
        if(tk.Get_Token_ID()==Delimiter_Right_Bracket)
        {
            tk=scanner(); //Consumes the Right Bracket.
            return;
        }
        else
        {
            error(Delimiter_Right_Bracket,tk);
        }
    }
    else if(tk.Get_Token_ID()==Integer)
    {
        tk=scanner(); //consumes the Number or Integer token.
        return;
    }
    else if(tk.Get_Token_ID()==Identifiers)
    {
        tk=scanner(); //consumes the Identifier token.
        return;
    }
    else
    {
        cout<<ERROR<<"Expect to get a Left Bracket or Identifier or Number but got : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<endl;
        exit(1);
    }
}


//<MSTAT> ->  empty |  <STAT>  <MSTAT>
void MSTAT()
{

}

//<STATS> ->  <STAT>  <MSTAT>
void STATS()
{
    //This non-terminal function will only have two options.
    STAT();
    MSTAT();
    return ; //Returns when both execute in order.
}

//<MVARS> ->  .  | , Identifier <MVARS>
void MVARS()
{
    //When called it will check if it got the period delimiter or the comma delimiter.
    //If it got the period delimiter then it will consume the period and return.
    //else it will check the comma delimiter and then it will can the mvars() function and when that returns it will be done and return.
    if(tk.Get_Token_ID()==Delimiter_Period)
    {
        tk=scanner(); //consumes the period.
        return;
    }
    else if(tk.Get_Token_ID()==Delimiter_Comma)
    {
        tk=scanner(); //consumes the Comma delimiter.
        MVARS();
        return;
    }
    else
    {
        cout<<ERROR<<"The parser got a : "<<TOKEN_IDS_TO_STRING_ARRAY[tk.Get_Token_ID()]<<" but expected to have a period or comma delimiter."<<endl;
        exit(1);
    }
}

//<vars> ->  empty | Var Identifier <MVARS>
void VARS()
{
    //if the token Id is a Keyword Var then it will consume the tk and call the mvar() function
    //it follows it automatically follows it in the BNF.
    if(tk.Get_Token_ID()==Keyword_Var)
    {
        tk=scanner(); //consumes the keyword Var
        MVARS(); //calls mvars() right after Keyword Var.
        return;
    }
    else //This will be for the empty string.
        return;
}
//<BLOCK> ->  Begin <VARS> <STATS> End
void BLOCK()
{
    //The first thing the block function checks is the keyword.
    //Once it finds that then it will call vars() and right after it will call stats. Then it will check
    //if the end keyword was found. If it was then it will return.
    if(tk.Get_Token_ID()==Keyword_Begin)
    {
        tk=scanner(); //Consumes the Begin token.
        VARS();
        STATS();
        if(tk.Get_Token_ID()==Keyword_End)
        {
            tk=scanner(); //Consumes the End token.
            return;
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
void PROGRAM()
{
    //program function can only go to two things. The vars() and block() functions which are non-terminals.
    VARS();
    BLOCK();
    return;
}

void parser()
{
    tk=scanner(); //Grabs the first from the scanner.
    PROGRAM(); //Runs program because it is the first production. It is obviously a none terminal.

    //Checks if the End of is the last token. If yes then the parsing is correct.
    if(tk.Get_Token_ID()==End_Of_File)
    {
        cout<<"Successful parsing."<<endl;
    }
    else
    { //Else it will display an error and terminate the program.
        error(End_Of_File,tk);
    }
    return; //This returns nothing. But later will be changed for the parse tree. It will return the whole parse tree.
}

