/*
 * Created by Dennis Moyseyev on 10/17/2017.
 * This Program is the scanner part of the program what it does is take in a file
 * Then it will take that file and remove all the comments from it.
 * Then it wll have it broken up into tokens with the line numbers and the value of the actually token string.
 * It will be used by the parser. There is a function which is called the test scanner which will call the driver
 * with the string of the program and wait to get a toke back. It will continue to do this until it reaches the EOF character.
*/

#include <iostream>
#include "./filterFunction.h"
#include "./FileInputFunction.h"
#include "./testscanner.h"

using namespace std;

int main ( int argc, char *argv[] )
{

    string file_name_string; //will be used to take in all the file content and save it to a string.
    string string_from_file;

    //If no arguments are given then the scanner will take input from standard input.
    if(argc==1)
    {
        //takes it to a function that will handle standard input.
        string_from_file=Input_From_Stdin();
    }
    //If more then 3 arguments are given in the command line than the program will throw an error and not execution.
    else if(argc>=3)
    {
        //This throws an error because not many arguments are given.
        cout << "ARGUMENTS ERROR: To many arguments. It will exit now. ";
        exit(1);
    }
    else
    {
        //Takes the input file and converts it into a string which will be scanned through
        //and the tokens will be taken out of it.
        file_name_string=argv[1];
        string_from_file=File_Input(file_name_string);
    }

    //This will be the string that will be used to get tokens from.
    string_from_file=Remove_Comments(string_from_file);

    //Calls the parser(Test_scanner) function which will continue to call the driver until the end of file is reached.
    Test_Scanner(string_from_file);

    return 0;
}

