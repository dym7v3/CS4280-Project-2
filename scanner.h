//
// Created by Dennis Moyseyev on 10/18/2017.
//

#ifndef P1_SCANNER_H
#define P1_SCANNER_H

#include <string>
#include "token.h"
using namespace std;

Token scanner();
extern int Character_Counter;
extern int Number_Line_Counter;
extern string the_file_string;

#endif //P1_SCANNER_H
