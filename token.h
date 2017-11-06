//
// Created by Dennis Moyseyev on 10/18/2017.
//

#ifndef P1_TOKEN_H
#define P1_TOKEN_H
#include<string>


using namespace std;

enum TOKEN_ID
{
    End_Of_File=0,
    Keyword_Begin=1,
    Keyword_End=2,
    Keyword_Check=3,
    Keyword_Loop=4,
    Keyword_Void=5,
    Keyword_Var=6,
    Keyword_Return=7,
    Keyword_Input=8,
    Keyword_Output=9,
    Keyword_Program=10,
    Integer=11,
    Identifiers=12,
    Operator_Equal=13,
    Operator_Less_Than=14,
    Operator_Less_Than_Or_Equal_To=15,
    Operator_Greater_Than=16,
    Operator_Greater_Than_Or_Equal_To=17,
    Operator_Not_Equal_To=18,
    Operator_Equal_To=19,
    Operator_Plus=20,
    Operator_Minus=21,
    Operator_Divide=22,
    Operator_Multiply=23,
    Operator_Modulo=24,
    Operator_Ampersand=25,
    Delimiter_Colon=26,
    Delimiter_Period=27,
    Delimiter_Left_Parenthesis=28,
    Delimiter_Right_Parenthesis=29,
    Delimiter_Left_Curly_Brace=30,
    Delimiter_Right_Curly_Brace=31,
    Delimiter_Left_Bracket=32,
    Delimiter_Right_Bracket=33,
    Delimiter_Comma=34,
    Delimiter_Semi_Colon=35
};


class Token
{
//Private methods. This will be the line number, token id and the actual value of the string.
private:


    TOKEN_ID  token_id;
    int line_number;
    string the_string;
public:
    Token();
    //Constructor for the class.
    Token(TOKEN_ID , string, int);

    //Used to get the line number.
    int Get_Line_Number();

    //Used to get the string value of the Token.
    string Get_The_String();

    //Used to get the Token Id.
    TOKEN_ID Get_Token_ID();
};



#endif //P1_TOKEN_H
