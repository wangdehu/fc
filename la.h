#ifndef LA_H
#define LA_H
#include<bits/stdc++.h>
#define LAinFile "./ex01.in"
// #define outFile "./example.out"
typedef std::pair<char, char> tChar;
#define IntegerValue 100
#define FloatValue 101
#define VarVaule 111

#define reserveInt 5
#define reserveElse 15
#define reserveIf 17
#define reserveWhile 20

#define charAdd 41
#define charSub 42
#define charMul 43
#define charDev 44
#define charMod 45
#define charEqu 46
#define charBig 47
#define charSma 49
#define charNot 55

#define charLSB 81
#define charRSB 82
#define charLMB 88
#define charRMB 89
#define charLLB 86
#define charRLB 87
#define charSem 84
#define charCom 83

#define tcharBigEqu 48
#define tcharSmaEqu 50
#define tcharEquEqu 51
#define tcharNotEqu 52
#define tcharAndAnd 53
#define tcharOrOr   54
#define tcharAddAdd 56
#define tcharSubSub 57

struct LAOUT{
    int key;
    std::string token;
    LAOUT(int k,std::string s):key(k),token(s){}
};

#endif


