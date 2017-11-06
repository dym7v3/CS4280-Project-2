//
// Created by Dennis Moyseyev on 10/23/2017.
//
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
const static int BUFFER_SIZE = 100;

const string File_Input(const string &file_name_without_ext) {

    string file_name=file_name_without_ext + ".fs17";
    ifstream inFile;
    inFile.open(file_name);//open the input file

    //Checks if the stream_variable is able to be open if not it will
    //throw an error.
    if (inFile)
    {
        stringstream strStream;
        strStream << inFile.rdbuf();//read the file
        string str = strStream.str();//str holds the content of the file
        return str;

    }
        //Only ends up here if the file was not able to be open.
    else
    {
        cout<<"ARGUMENT ERROR:  No File was found with the input name.\nThe program will be terminated.\n";
        exit(1);
    }
}
const string Input_From_Stdin()
{
    FILE* fp;
    char buffer [BUFFER_SIZE];
    string string_from_file;
    fp=stdin;
    /*keeps reading in the file until the end of the file is reached. Enter is required to be pressed for
    for it to take in all the input from the keyboard.
    */
    fseek(fp, 0, SEEK_END);
    auto len = (unsigned long)ftell(fp);
    if (len ==0)
    {
        cout<<"ARGUMENT ERROR: This is file is empty. The program will exit now. "<<endl;
        exit(1);
    }
    rewind(fp);

    while(! feof (fp))
    {
        //if it is equal to null then it will break the loop that is taking in the numbers from the file.
        if ( fgets (buffer , BUFFER_SIZE , fp) == nullptr )
            break;

        string_from_file+=buffer; //appends the buffer to a string which will be divided over whitespaces.
    }

    fclose (fp); //closes the stdin.
    return string_from_file;
}