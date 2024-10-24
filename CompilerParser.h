#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <vector>
#include <exception>
#include <string>

#include "ParseTree.h"
#include "Token.h"

using namespace std;

class CompilerParser {
    public:
        CompilerParser(std::vector<Token*> tokens);

        ParseTree* compileProgram();
        ParseTree* compileClass();
        ParseTree* compileClassVarDec();
        ParseTree* compileSubroutine();
        ParseTree* compileParameterList();
        ParseTree* compileSubroutineBody();
        ParseTree* compileVarDec();

        ParseTree* compileStatements();
        ParseTree* compileLet();
        ParseTree* compileIf();
        ParseTree* compileWhile();
        ParseTree* compileDo();
        ParseTree* compileReturn();

        ParseTree* compileExpression();
        ParseTree* compileTerm();
        ParseTree* compileExpressionList();

        // helper
        vector<Token*> total_tokens;
        Token* current_token;
        int token_counter;
        int last_token;
        void get_current_token();
        bool is_valid_variableName(string str);
        void debug();


};

class ParseException : public std::exception {
    public:
        const char* what();
};

#endif /*COMPILERPARSER_H*/