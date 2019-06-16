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

struct Attr
{
    int val;
    std::string place;
    Attr()
    {
        val = 1;
        place.clear();
    }
    Attr(int v, std::string s) : val(v), place(s) {}
};

void init();
void addOut(std::string b, std::string s);
void Error(std::string name, int h, int type);
bool check(int key);
void checkAndErr(int k, std::string n, int h, int type);
void emit(std::string s);
void STMTS();
void STMT();
void REST0();
Attr LOC();
Attr RESTA(Attr inArrays);
void ELIST();
void REST1();
void REST4();
Attr REST5(Attr in);
Attr REST6(Attr in);
void REL();
void BOOL();
void EQUALITY();
void ROP_EXPR();
Attr EXPR();
Attr TERM();
Attr UNARY();
Attr FACTOR();
std::string newtemp();
#endif