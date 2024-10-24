#include <iostream>
#include <cctype>
#include "CompilerParser.h"
using namespace std;

/* Return the current token */
void CompilerParser::get_current_token(){
    if(token_counter<=last_token){
        // get the current token we are working on
        current_token = total_tokens.at(token_counter); 
        return;     
    }
    current_token = total_tokens.at(last_token);        
    cout<<"get_current_token(): out of range. last_token: "<<last_token<<" token_counter: "<<token_counter<<endl;;
    // cout<<"current_token type: "<<current_token->getType()<<"  value: "<<current_token->getValue()<<endl;
}

/* Verify if the variable name passed in is a variable name or not */
bool CompilerParser::is_valid_variableName(std::string str){
    char first_char = str[0];
    if(isalpha(first_char) || first_char=='_'){
        return true;
    }
    return false;
}

/* print current token */
void CompilerParser::debug(){
    cout<<"token counter is : "<<token_counter<<"  current_token type: "<<current_token->getType()<<"  value: "<<current_token->getValue()<<endl;
}

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::vector<Token*> tokens) {
    int size = tokens.size();
    token_counter = 0;
    last_token = size -1 ;
    for(int i = 0; i < size; i++){
        this->total_tokens.push_back(tokens.at(i));
    }
}

/**
 * Generates a parse tree for a single program
 */
ParseTree* CompilerParser::compileProgram() {
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* class_tree = NULL;
    // check keyword class
    get_current_token();
    if(current_token->getType()=="keyword" && current_token->getValue()=="class"){
        class_tree = new ParseTree("class", "");
    }else{
        throw ParseException();
    }
    class_tree->addChild(new ParseTree("keyword", "class"));
    token_counter++;


    // check identifier class name
    get_current_token();
    if(current_token->getType()=="identifier"){
        class_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;


    // check symbol {
    get_current_token();
    if(current_token->getType() == "symbol" && current_token->getValue() == "{"){
        class_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

        // class varDec 
        get_current_token();
        if(current_token->getType()=="keyword" && (current_token->getValue()=="static" || current_token->getValue()=="field")){
            class_tree->addChild(compileClassVarDec());
        }

        // class subroutine
        get_current_token();
        // if there is subroutine, should be keyword function, method, constructor 
        if(current_token->getType()=="keyword" && (current_token->getValue()=="constructor" || current_token->getValue()=="function" || current_token->getValue()=="method")){
            class_tree->addChild(compileSubroutine());
        }


    // check symbol }
    get_current_token();
    if(current_token->getType() == "symbol" && current_token->getValue() == "}"){
        class_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        cout<<"here10"<<endl;
        throw ParseException();
    }

    return class_tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* classVarDec_tree = new ParseTree("classVarDec", "");     // to return
    // now the token should be keyword : static or field

    do{

    // handling keyword : static or field
    classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // handling data type
    get_current_token();
    // keyword: int, char, boolean
    if(current_token->getType()=="keyword"){
        if(current_token->getValue()=="int" || current_token->getValue()=="char" || current_token->getValue()=="boolean"){
            classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
    }else if(current_token->getType()=="identifier"){
        // identifier
        classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling variable name 
    get_current_token();
    if(current_token->getType()=="identifier"){
        if(is_valid_variableName(current_token->getValue())){
            classVarDec_tree->addChild(new ParseTree("identifier", current_token->getValue()));
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling ; or ,
    get_current_token();
    while(current_token->getType()=="symbol" && current_token->getValue()==","){
        classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));     // ","
        token_counter++;            // update the token we are updating
        // appending follwoing variables
        get_current_token();
        if(current_token->getType()=="identifier" && is_valid_variableName(current_token->getValue())){
            classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
            token_counter++;            // update the token we are updating
        }else{
            throw ParseException();
        }
        get_current_token();
    }

    // handling ;
    // should be symbol : ;
    if(current_token->getType()=="symbol" && (current_token->getValue()==";")){
        classVarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;
    get_current_token();
    // finish one line 
    }while(current_token->getType()=="keyword" && (current_token->getValue()=="static" || current_token->getValue()=="field"));

    return classVarDec_tree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* Subroutine_tree = new ParseTree("subroutine", "");
    do{
        // enter, shoud have keyword : constructor, method, function for token
        Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        token_counter++;


        // handling return type
        get_current_token();
        // keyword: int, char, boolean or void
        // identifier: self defined class
        if(current_token->getType()=="keyword" && (current_token->getValue()=="int" || current_token->getValue()=="char" || current_token->getValue()=="boolean" || current_token->getValue()=="void")){
            Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else if(current_token->getType()=="identifier" && is_valid_variableName(current_token->getValue())){
            Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;


        // handling subroutine name
        get_current_token();
        if(current_token->getType()=="identifier"){
            Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;


        // handling '('
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()=="("){                                       // (
            Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;


        // handling parameter list
        get_current_token();
        if((current_token->getType()=="keyword"&& current_token->getValue()=="int" || current_token->getValue()=="char" || current_token->getValue()=="boolean") || current_token->getType()=="identifier"){
            Subroutine_tree->addChild(compileParameterList());
        }else{
            Subroutine_tree->addChild(new ParseTree("parameterList", ""));
        }

        // handling )
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()==")"){                                       // )
            Subroutine_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;

        // handling subroutine body
        Subroutine_tree->addChild(compileSubroutineBody());

        get_current_token();
    }while(current_token->getType()=="keyword" && (current_token->getValue()=="constructor" || current_token->getValue()=="function" || current_token->getValue()=="method"));
    return Subroutine_tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameterList_tree = new ParseTree("parameterList", "");
    // either type or )
    // type int, char, boolean, className 
    do{
        get_current_token();
        // handling parameter type
        if(current_token->getType()=="keyword"){
            // if keyword, int char boolean 
            if(current_token->getValue()=="int" || current_token->getValue()=="char" || current_token->getValue()=="boolean"){
                parameterList_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
                token_counter++;
            }else{
                throw ParseException();
            }
        }else if(current_token->getType()=="identifier"){
            // if identifier 
            if(is_valid_variableName(current_token->getValue())){
                parameterList_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
                token_counter++;
            }else{
                throw ParseException();
            }
        }

        // should be identifier : name 
        // handling parameter name
        get_current_token();
        if(current_token->getType()=="identifier"){
            if(is_valid_variableName(current_token->getValue())){
                parameterList_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
                token_counter++;
            }else{
                throw ParseException();
            }
        }else{
            throw ParseException();
        }

        // handling ,
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()==","){
            parameterList_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
            token_counter++;
        }


        if(token_counter>last_token){
            break;
        }
        get_current_token();

    }while(current_token->getType()=="keyword"||current_token->getType()=="identifier");

    return parameterList_tree;
}

/**
 * Generates a parse tree for a subroutine's body
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* subroutineBody_tree = new ParseTree("subroutineBody", "");
    // { varDec, statements }

    // handling {
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="{"){
        subroutineBody_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // varDec 
    get_current_token();
    if(current_token->getType()=="keyword" && current_token->getValue()=="var"){
        subroutineBody_tree->addChild(compileVarDec());
    }


    // statements
    get_current_token();
    if(current_token->getType()=="keyword"){
        if(current_token->getValue()=="let" || current_token->getValue()=="if" || current_token->getValue()=="while" || current_token->getValue()=="do" || current_token->getValue()=="return"){
            subroutineBody_tree->addChild(compileStatements());
        }else{
            throw ParseException();
        }
    }else{
        subroutineBody_tree->addChild(new ParseTree("statements", ""));
    }

    // handling }
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="}"){
        subroutineBody_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;
    
    return subroutineBody_tree;
}

/**
 * Generates a parse tree for a variable declaration
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* VarDec_tree = new ParseTree("varDec", "");
    // var type varname, varname ;

    do{

    // append keyword var 
    VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // type
    get_current_token();
    if(current_token->getType()=="keyword" && (current_token->getValue()=="int" || current_token->getValue()=="char" || current_token->getValue()=="boolean")){
        // keyword int, char, boolean
        VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else if(current_token->getType()=="identifier"){
        if(is_valid_variableName(current_token->getValue())){
            // identifier variable_name
            VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }
    token_counter++;

    // varName
    get_current_token();
    if(current_token->getType()=="identifier"){
        if(is_valid_variableName(current_token->getValue())){
            VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling ; or ,
    get_current_token();
    while(current_token->getType()=="symbol" && current_token->getValue()==","){
        VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));     // ","
        token_counter++;            // update the token we are updating
        // appending follwoing variables
        get_current_token();
        if(current_token->getType()=="identifier" && is_valid_variableName(current_token->getValue())){
            VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
            token_counter++;            // update the token we are updating
        }else{
            throw ParseException();
        }
        get_current_token();
    }
    
    // should be symbol : ;
    if(current_token->getType()=="symbol" && (current_token->getValue()==";")){
        VarDec_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;
    get_current_token();
    // finish one line 
    
    }while(current_token->getType()=="keyword" && current_token->getValue()=="var");

    return VarDec_tree;
}

/**
 * Generates a parse tree for a series of statements
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statement_tree = new ParseTree("statements", "");
    get_current_token();
    do{
    // check keyword, value: let, if, while, do, return
        if(current_token->getValue() == "let"){
            statement_tree->addChild(compileLet());
        }else if(current_token->getValue() == "if"){
            statement_tree->addChild(compileIf());
        }else if(current_token->getValue() == "while"){
            statement_tree->addChild(compileWhile());
        }else if(current_token->getValue() == "do"){
            statement_tree->addChild(compileDo());
        }else if(current_token->getValue() == "return"){
            statement_tree->addChild(compileReturn());
        }else{
            throw ParseException();
        }
        if(token_counter>last_token){
            break;
        }
        get_current_token();
    }while(current_token->getType()=="keyword");
    return statement_tree;
}

/**
 * Generates a parse tree for a let statement
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* let_tree = new ParseTree("letStatement", "");
    // let a = skip;
    // let varname ( [expression] ) = expression ;
    // handling let keyword
    let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;
    
    // handling varname
    get_current_token();
    if(current_token->getType()=="identifier"){
        if(is_valid_variableName(current_token->getValue())){
            let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }
    token_counter++;

    // evaluate [ ]
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="["){
        // [
        let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        token_counter++;
        // expression
        get_current_token();
        let_tree->addChild(compileExpression());
        // ]
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()=="]"){
            let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;
    }else if(current_token->getType()=="symbol" && current_token->getValue()=="="){
    }else{
        throw ParseException();
    }
    
    // =
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="="){
        let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // expression
    get_current_token();
    let_tree->addChild(compileExpression());

    // ;
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()==";"){
        let_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    return let_tree;
}

/**
 * Generates a parse tree for an if statement
 */
ParseTree* CompilerParser::compileIf() {
    // if ( expression ) { statements } else { statements }
    ParseTree* if_tree = new ParseTree("ifStatement", "");

    get_current_token();

    // handling if
    if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // handling (
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="("){
        if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling expression
    get_current_token();
    if_tree->addChild(compileExpression());

    // handling )
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()==")"){
        if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling {
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="{"){
        if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // handling statements
    get_current_token();
    if(token_counter<last_token && current_token->getType()=="keyword" && (current_token->getValue()=="let" || current_token->getValue()=="if" || current_token->getValue()=="while" || current_token->getValue()=="do" || current_token->getValue()=="return")){
        if_tree->addChild(compileStatements());
    }else{
        if_tree->addChild(new ParseTree("statements", ""));
    }

    // handling }
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="}"){
        if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        throw ParseException();
    }
    token_counter++;

    // if there is else 
    get_current_token();
    if(current_token->getType()=="keyword" && current_token->getValue()=="else"){
        if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        token_counter++;

        // {
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()=="{"){
            if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            throw ParseException();
        }
        token_counter++;

        // statements
        get_current_token();
        if(token_counter<last_token && current_token->getType()=="keyword" && (current_token->getValue()=="let" || current_token->getValue()=="if" || current_token->getValue()=="while" || current_token->getValue()=="do" || current_token->getValue()=="return")){
            if_tree->addChild(compileStatements());
        }else{
            if_tree->addChild(new ParseTree("statements", ""));
        }

        // }
        get_current_token();
        if(current_token->getType()=="symbol" && current_token->getValue()=="}"){
            if_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
        }else{
            // cout<<"here6"<<endl;
            throw ParseException();
        }
        token_counter++;
    }
    return if_tree;
}

/**
 * Generates a parse tree for a while statement
 */
ParseTree* CompilerParser::compileWhile() {
    // while ( expression ) { statements }
    ParseTree* while_tree = new ParseTree("whileStatement", "");
    get_current_token();
    while_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // (
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="("){
        while_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;

    // expression
    get_current_token();
    while_tree->addChild(compileExpression());

    // )
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()==")"){
        while_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;

    // {
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="{"){
        while_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;

    // handling statements
    get_current_token();
    if(token_counter<last_token && current_token->getType()=="keyword" && (current_token->getValue()=="let" || current_token->getValue()=="if" || current_token->getValue()=="while" || current_token->getValue()=="do" || current_token->getValue()=="return")){
        while_tree->addChild(compileStatements());
    }else{
        while_tree->addChild(new ParseTree("statements", ""));
    }

    // }
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()=="}"){
        while_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;
    return while_tree;
}

/**
 * Generates a parse tree for a do statement
 */
ParseTree* CompilerParser::compileDo() {
    // do expression ;
    ParseTree* do_tree = new ParseTree("doStatement", "");
    do_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // expression
    get_current_token();
    do_tree->addChild(compileExpression());

    // ;
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()==";"){
        do_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;

    return do_tree;
}

/**
 * Generates a parse tree for a return statement
 */
ParseTree* CompilerParser::compileReturn() {
    // return expression ;
    ParseTree* return_tree = new ParseTree("returnStatement", "");
    return_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    token_counter++;

    // expression
    get_current_token();
    return_tree->addChild(compileExpression());

    // ;
    get_current_token();
    if(current_token->getType()=="symbol" && current_token->getValue()==";"){
        return_tree->addChild(new ParseTree(current_token->getType(), current_token->getValue()));
    }else{
        //cout<<"here1"<<endl;
        throw ParseException();
    }
    token_counter++;

    return return_tree;  
}

/**
 * Generates a parse tree for an expression
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* expression_tree = new ParseTree("expression", "");
    get_current_token();
    if(current_token->getType()=="keyword" && current_token->getValue()=="skip"){
        expression_tree->addChild(new ParseTree("keyword", "skip"));
    }
    token_counter++;
    return expression_tree;
}

/**
 * Generates a parse tree for an expression term
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}


const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
