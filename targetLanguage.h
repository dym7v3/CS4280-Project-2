#ifndef PROJECT_2_TARGETLANGUAGE_H
#define PROJECT_2_TARGETLANGUAGE_H

#include <deque>
#include "node.h"

void printParseTree(Node, int, ostream &);
void SyntaxLocal(Node rootP, int level);
void printResults();
int find(string);
bool verify(string);
void pop(int);
void push(string);
void codeGeneration(Node, int , ostream &);

#endif //PROJECT_2_TARGETLANGUAGE_H
