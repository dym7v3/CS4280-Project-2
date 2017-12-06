//
// Created by Dennis Moyseyev on 11/26/2017.
//

#ifndef PROJECT_2_SEMANTICS_H
#define PROJECT_2_SEMANTICS_H

#include <deque>

void printParseTree(Node, int, ostream &);
void SyntaxLocal(Node rootP, int level);
void printResults();
int find(string);
bool verify(string);
void pop(int);
void push(string);

#endif //PROJECT_2_SEMANTICS_H
