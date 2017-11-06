
#include <iostream>
#include "./token.h"
#include "scanner.h"
#include <string>

using namespace std;

const string ERROR="PARSING ERORR: ";
Token tk;

/*
<program>  ->     <vars> <block>
<block>    ->      Begin <vars> <stats> End
<vars>     ->      empty | Var Identifier <mvars>
<mvars>    ->     .  | , Identifier <mvars>
<expr>     ->      <M> + <expr> | <M> - <expr> | <M>
<M>        ->     <F> % <M> | <F> * <M> | <F>
<F>        ->      ( <F> ) | <R>
<R>        ->      [ <expr> ] | Identifier | Number
<stats>    ->      <stat>  <mStat>
<mStat>    ->      empty |  <stat>  <mStat>
<stat>     ->      <in> | <out> | <block> | <if> | <loop> | <assign>
<in>       ->      Input Identifier ;
<out>      ->      Output <expr>  ;
<if>       ->      Check [ <expr> <RO> <expr> ] <stat>
<loop>     ->      Loop [ <expr> <RO> <expr> ] <stat>
<assign>   ->      Identifier : <expr>   ;
<RO>       ->      < | <= | >  | >= | ==  |  !=
*/

void mvars()
{

}



void block()
{

}

void vars()
{
    //if the token Id is a Keyword Var then it will consume the tk and call the mvar() function
    //it follows it automatically follows it in the BNF.
    if(tk.Get_Token_ID()==Keyword_Var)
    {
        tk=scanner(); //consumes the keyword Var
        mvars(); //calls mvars() right after Keyword Var.
        return;
    }
    else //This will be for the empty string.
        return;
}

void program()
{
    //program function can only go to two things. The vars() and block() functions which are non-terminals.
    vars();
    block();
    return;
}

void parser()
{
    tk=scanner(); //Grabs the first from the scanner.
    program(); //Runs program because it is the first production. It is obviously a none terminal.

    //Checks if the End of is the last token. If yes then the parsing is correct.
    if(tk.Get_Token_ID()==End_Of_File)
    {
        cout<<"Successful parsing."<<endl;
    }
    else
    { //Else it will display an error and terminate the program.
        cout<<ERROR<<" Last token was not 'End_of_File' token"<<endl;
        exit(1);
    }
    return; //This returns nothing. But later will be changed for the parse tree. It will return the whole parse tree.
}

