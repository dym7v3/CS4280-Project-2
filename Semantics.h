//
// Created by Dennis Moyseyev on 11/26/2017.
//

#ifndef PROJECT_2_SEMANTICS_H
#define PROJECT_2_SEMANTICS_H

void printParseTree(Node, int, ostream &);
void Syntax(Node, int);
extern vector<string> Globals;
void SyntaxLocal(Node rootP, int level);
extern deque<string> variables;
void printResults();


#endif //PROJECT_2_SEMANTICS_H
