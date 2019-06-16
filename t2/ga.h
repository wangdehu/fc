#ifndef GA_H
#define GA_H

#include "la.h"
const static std::string empteyString = "ε";

struct G
{
    std::string left;
    std::vector<std::string> right;
    G(std::string l) : left(l) { right.clear(); }
};

void init();
void addOut(std::string b, std::string s);
void Error(std::string name, int h, int type);
bool check(int key);
void checkAndErr(int k, std::string n, int h, int type);
void STMTS();
void STMT();
void REST0();
void LOC();
void RESTA();
void ELIST();
void REST1();
void REST4();
void REST5();
void REST6();
void REL();
void BOOL();
void EQUALITY();
void ROP_EXPR();
void EXPR();
void TERM();
void UNARY();
void FACTOR();;
#endif