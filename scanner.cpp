//
// Created by Dennis Moyseyev on 10/18/2017.
//
#include <string>
#include <iostream>
#include <map>
#include "./token.h"

using namespace std;
const int STRING_ARRAY_SIZE=10;
const int TABLE_ROWS=27;
const int TABLE_COLUMNS=24;
const int TOKENS_TO_STRING_ARRAY_SIZE=36;
int Character_Counter=0;
int Number_Line_Counter=1;
const char Get_Char(const string &, int );


enum STATE
{
    INITIAL=0, //S0 first state
    FINAL_STATE=2000,
    END_OF_FILE_COLUMN=0,
    DIGIT_COLUMN=1,
    LETTER_COLUMN=2,
    WHITESPACE_COLUMN=3,
    EQAULS_COLUMN=4,
    LESS_THAN_COLUMN=5,
    GREATER_THAN_COLUMN=6,
    NOT_COLUMN=7,
    COLON_COLUMN=8,
    PLUS_COLUMN=9,
    MINUS_COLUMN=10,
    MUlTIPLY_COLUMN=11,
    DIVIDE_COLUMN=12,
    AMPERSAND_COLUMN=13,
    PERCENT_COLUMN=14,
    PERIOD_COLUMN=15,
    LEFTBRACKET_COLUMN=16,
    RIGHTBRACKET_COLUMN=17,
    LEFTBRACE_COLUMN=18,
    RIGHTBRACE_COLUMN=19,
    COMMA_COLUMN=20,
    LEFT_PARENTHESIS_COLUMN=21,
    RIGHT_PARENTHESIS_COLUMN=22,
    SEMICOLON_COLUMN=23,

};

static map <char, STATE> Different_States= {
        {'=' , EQAULS_COLUMN},
        {'<' , LESS_THAN_COLUMN},
        {'>' , GREATER_THAN_COLUMN},
        {'!' , NOT_COLUMN},
        {':' , COLON_COLUMN},
        {'+' , PLUS_COLUMN},
        {'-' , MINUS_COLUMN},
        {'*' , MUlTIPLY_COLUMN},
        {'/' , DIVIDE_COLUMN},
        {'&' , AMPERSAND_COLUMN},
        {'%' , PERCENT_COLUMN},
        {'.' , PERIOD_COLUMN},
        {'[' , LEFTBRACKET_COLUMN},
        {']' , RIGHTBRACKET_COLUMN},
        {'{' , LEFTBRACE_COLUMN},
        {'}' , RIGHTBRACE_COLUMN},
        {',' , COMMA_COLUMN},
        {'(' , LEFT_PARENTHESIS_COLUMN},
        {')' , RIGHT_PARENTHESIS_COLUMN},
        {';' , SEMICOLON_COLUMN}
};

map <int, TOKEN_ID > Final_States_To_Token_Ids= {
        { 2000 , End_Of_File},
        { 2002 , Integer},
        { 2001 , Identifiers},
        { 2003 , Operator_Equal},
        { 2005 , Operator_Less_Than},
        { 2006 , Operator_Less_Than_Or_Equal_To},
        { 2007 , Operator_Greater_Than},
        { 2008 , Operator_Greater_Than_Or_Equal_To},
        { 2009 , Operator_Not_Equal_To},
        { 2004 , Operator_Equal_To},
        { 2011 , Operator_Plus},
        { 2012 , Operator_Minus},
        { 2014 , Operator_Divide},
        { 2013 , Operator_Multiply},
        { 2016 , Operator_Modulo},
        { 2015 , Operator_Ampersand},
        { 2010 , Delimiter_Colon},
        { 2017 , Delimiter_Period},
        { 2023 , Delimiter_Left_Parenthesis},
        { 2024 , Delimiter_Right_Parenthesis},
        { 2020 , Delimiter_Left_Curly_Brace},
        { 2021 , Delimiter_Right_Curly_Brace},
        { 2018 , Delimiter_Left_Bracket},
        { 2019 , Delimiter_Right_Bracket},
        { 2022 , Delimiter_Comma},
        { 2025 , Delimiter_Semi_Colon}
};

map <string, TOKEN_ID > Identifiers_To_Token_Ids= {
        {"Begin" , Keyword_Begin} ,
        {"End" , Keyword_End} ,
        {"Check" , Keyword_Check} ,
        {"Loop" , Keyword_Loop} ,
        {"Void" , Keyword_Void} ,
        {"Var" , Keyword_Var},
        {"Return" , Keyword_Return},
        {"Input" , Keyword_Input},
        {"Output" , Keyword_Output},
        {"Program" , Keyword_Program},
};


string TOKEN_IDS_TO_STRING_ARRAY [TOKENS_TO_STRING_ARRAY_SIZE]= {
        "End_Of_File",
        "Keyword_Begin",
        "Keyword_End",
        "Keyword_Check",
        "Keyword_Loop",
        "Keyword_Void",
        "Keyword_Var",
        "Keyword_Return",
        "Keyword_Input",
        "Keyword_Output",
        "Keyword_Program",
        "Integer",
        "Identifier",
        "Operator_Equal",
        "Operator_Less_Than",
        "Operator_Less_Than_Or_Equal_To",
        "Operator_Greater_Than",
        "Operator_Greater_Than_Or_Equal_To",
        "Operator_Not_Equal_To",
        "Operator_Equal_To",
        "Operator_Plus",
        "Operator_Minus",
        "Operator_Divide",
        "Operator_Multiply",
        "Operator_Modulo",
        "Operator_Ampersand",
        "Delimiter_Colon",
        "Delimiter_Period",
        "Delimiter_Left_Parenthesis",
        "Delimiter_Right_Parenthesis",
        "Delimiter_Left_Curly_Brace",
        "Delimiter_Right_Curly_Brace",
        "Delimiter_Left_Bracket",
        "Delimiter_Right_Bracket",
        "Delimiter_Comma",
        "Delimiter_Semi_Colon"};

static int table[TABLE_ROWS][TABLE_COLUMNS] = {
        { 2000 , 2 , 1 , 0 , 3 , 5 , 7 , 9 , 11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 20 , 21 , 22 , 23 , 24 , 25 , 26 } ,
        { 2001 , 1 , 1 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 , 2001 } ,
        { 2002 , 2 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 , 2002 } ,
        { 2003 , 2003 , 2003 , 2003 , 4 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 , 2003 } ,
        { 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004 , 2004, 2004 , 2004 , 2004 , 2004 , 2004 } ,
        { 2005 , 2005 , 2005 , 2005 , 6 , 2005 , 2005, 2005, 2005 , 2005 , 2005, 2005 , 2005 , 2005 , 2005, 2005 , 2005 , 2005 , 2005 , 2005 , 2005 , 2005 , 2005 , 2005 , } ,
        { 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 , 2006 } ,
        { 2007 , 2007 , 2007 , 2007 , 8 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 , 2007 } ,
        { 2008 , 2008 , 2008 , 2008, 2008 , 2008 , 2008 , 2008, 2008 , 2008 , 2008 , 2008, 2008 , 2008 , 2008 , 2008, 2008 , 2008 , 2008 , 2008, 2008 , 2008 , 2008 , 2008  } ,
        { -1 , -1 , -1 , -1 , 10 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 },
        { 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 , 2009 } ,
        { 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 , 2010 } ,
        { 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 , 2011 } ,
        { 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 , 2012 } ,
        { 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 , 2013 } ,
        { 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 , 2014 } ,
        { 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 , 2015 } ,
        { 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 , 2016 } ,
        { 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 , 2017 } ,
        { 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 , 2018 } ,
        { 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 , 2019 } ,
        { 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 , 2020 } ,
        { 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 , 2021 } ,
        { 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 , 2022 } ,
        { 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 , 2023 } ,
        { 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 , 2024 } ,
        { 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 , 2025 } ,

};



//Checks if the character is a letter a number or something else and returned the enum type.
STATE check(char the_char)
{

        if (isalpha(the_char)) {
            return LETTER_COLUMN;
        } else if (isdigit(the_char)) {
            return DIGIT_COLUMN;
        } else if (isspace(the_char)) {
            return WHITESPACE_COLUMN;
        } else return the_char == EOF ? END_OF_FILE_COLUMN : Different_States[the_char];

}

//Returns a character from the string at the number in the string.
const char Get_Char(const string &file_string, int char_number_in_string)
{
    if(file_string.length()<char_number_in_string || char_number_in_string<0)
    {
        cout<<"SCANNER ERROR: Can't return a character that is outside the string. Program will terminate."<<endl;
        exit(1);
    }
    Character_Counter++;
    return file_string[char_number_in_string];
}

TOKEN_ID Token_Id_A_Keyword(const string & the_value_string)
{
    string identifiers_to_keywords_array [STRING_ARRAY_SIZE] ={"Begin" , "End" , "Check" , "Loop" , "Void" , "Var" , "Return" , "Input" , "Output" , "Program" };
    TOKEN_ID token=Identifiers;
    for (const auto &i : identifiers_to_keywords_array) {
          if(the_value_string== i)
        {
            token=Identifiers_To_Token_Ids[the_value_string];
        }
    }

    return token;
}

//This gets called by the test scanner program.
Token  Driver (const string &the_file_string)
{
    STATE state=INITIAL;
    TOKEN_ID token_id;
    string value_string;
    STATE next_state;

    while(state!=FINAL_STATE)
   {
       char  character_in_token=Get_Char(the_file_string,Character_Counter);

       next_state= static_cast<STATE>(table[state][check(character_in_token)]);

       //Error state.
       if(next_state<0)
       {
           cout<<"SCANNER ERROR: Encountered an ERROR state in the driver. The Program will exit now! "<<endl;
           exit(1);
       }
       //A Final State.
       if(next_state>=2000)
       {
           //this Goes and finds the token ID and then it returns it from a map.
           token_id=Final_States_To_Token_Ids[next_state];

           Character_Counter--; //This will go back one character because the previous step grabbed a variable that need to be put back.
           //Checks if the token id is an identifier then it will go and check if it is a keyword.
           if(token_id==Identifiers)
           {
               token_id=Token_Id_A_Keyword(value_string);
           }

           //Makes the token and then prints results and returns the toke to the test scanner which will be the parser.
           Token *my_token=new Token(token_id,value_string, Number_Line_Counter);
           cout <<"Token : "<<TOKEN_IDS_TO_STRING_ARRAY[(*my_token).Get_Token_ID()]<< " ~~~ String value : \""
                <<(*my_token).Get_The_String()<<"\" ~~~ The Line Number is : "<<(*my_token).Get_Line_Number()<<endl;
           return *my_token;
       }
       else
       {
           if(WHITESPACE_COLUMN!=check(character_in_token))
               value_string+=character_in_token;

           //Keeps track of the line numbers in the file. So that we can later display the token value and the line number.
           if(character_in_token=='\n')
           {
               Number_Line_Counter++;
           }
           state=next_state; //switches to a new state.
       }
   }
}