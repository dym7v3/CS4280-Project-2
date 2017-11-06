//
// Created by Dennis Moyseyev on 10/18/2017.
//

#include <string>
#include <iostream>
#include "filterFunction.h"
using namespace std;

/*
 * This function will go through the whole string and remove the comments in the string.
 * and return a new string with the comments removed to the caller function.
 */


//Checks if the character that is begin passed in allowed in the program.
bool isInside(const string & str, char c)
{
    return str.find(c) != std::string::npos;
}

const string allowed_characters="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890=#<>!:+-*/&%.(),[]{};\t\n ";
const string Remove_Comments(const string to_remove_comments_string)
{

    string string_without_comments;
    bool comment_started=false; //Keeps track if a comment is started.
    int size_of_string=to_remove_comments_string.length();
    int number_of_lines=1; //keeps tack on the file length.
    int currently_in_string=0;
    int where_comment_was_started=0;
    for(const char & c : to_remove_comments_string)
    {
        //This checks if the there is an not allowed character in the program. If there are then it will terminate.
        if(!isInside(allowed_characters,c))
        {
            if(c==EOF)
                continue;
            else{

                cout<<"SCANNER ERROR: A not allowed character was found on line : "<<number_of_lines<<endl;
                cout<<"The program will Terminate."<<endl;
                exit(1);
            }
        }


            ++currently_in_string; //keeps track of the current place in the string.
        //Checks if a comment was started if yes it will enter the if statment.
        if(comment_started)
        {
            if(c=='#') //checks if the end of the comment was found.
            {
                comment_started=false;
            }
            if(c=='\n') //counts the amount of lines in the program string.
            {
                string_without_comments+=c;
                number_of_lines++;
            }
            //Checks if it reached the end of the string and a comment was opened but never closed it will throw an error.
            if(size_of_string==currently_in_string)
            {
                cout<<"SCANNER ERROR: The file has an open comment statement but not closed comment statement at line : "<<where_comment_was_started<<endl;
                cout<<"The scanner will terminate. "<<endl;
                exit(1);
            }
            continue; //it will continue going in the string if a comment was started and hasn't end.
        }
        if(c=='#')
        {
            comment_started=true;
            /*
             * Grabs where the line number where the comment was started. This will be used just in case
             * it gets to the end of the page and the comment wasn't closed it will tell the user where the
             * last comment was started.
            */
            where_comment_was_started=number_of_lines;
        }
        if(c=='\n')
        {
            number_of_lines++;
        }
        if(!comment_started)
        {
            string_without_comments+=c;
        }

    }
    //returns the new with the comments removed.
    return  string_without_comments;
}
