#include "./token.h"

using namespace std;



//This is the constructor. It will take in the a TOKEn_ID, a string value and line number.
Token::Token()
{

}
//This is the constructor. It will take in the a TOKEn_ID, a string value and line number.
Token::Token(TOKEN_ID id, string the_string , int line_num)
{
    this->token_id=id;
    this->the_string=the_string;
    this->line_number=line_num;
}

//returns the line number very the token in found.
int Token::Get_Line_Number() {
    return this->line_number;
}

//returns the string value of the token.
string Token::Get_The_String() {
    return this->the_string;
}

//Returns the enumed type of the token id.
TOKEN_ID Token::Get_Token_ID() {
    return this->token_id;
}


