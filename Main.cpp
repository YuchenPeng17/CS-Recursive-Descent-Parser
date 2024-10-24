#include <iostream>
#include <vector>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "MyClass"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "}"));

    // // ##########################################################################################
    // // variable delcaration                         
    // tokens.push_back(new Token("keyword", "static"));       // static int a;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ";"));
    // //
    // tokens.push_back(new Token("keyword", "field"));        // field int b,c;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("identifier", "c"));
    // tokens.push_back(new Token("symbol", ";"));
    // // ##########################################################################################
    // // constructor 
    // // class Main { function void test ( ) { } }  
    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "test"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "x"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "var"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "testVarDec"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("symbol", "}"));
    // // ##########################################################################################
    // // // class Main { function void test ( ) { } }  
    // tokens.push_back(new Token("keyword", "class"));
    // tokens.push_back(new Token("identifier", "Main"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "test"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));

    // // var type varname, varname ;
    // tokens.push_back(new Token("keyword", "var"));     // var int a ;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ";"));

    // // let statements
    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));

    // // if statement
    // tokens.push_back(new Token("keyword", "if"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));
    // tokens.push_back(new Token("keyword", "else"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("symbol", "}"));
    // tokens.push_back(new Token("symbol", "}"));
    // // ##########################################################################################
    //class Main { static int test ; static int test2 ; function void test3 ( ) { } function void test4 ( ) { } }
    // tokens.push_back(new Token("keyword", "class"));
    // tokens.push_back(new Token("identifier", "Main"));
    // tokens.push_back(new Token("symbol", "{"));

    // tokens.push_back(new Token("keyword", "static"));       // static int test;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "test"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "static"));       // static int test2;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "test2"));
    // tokens.push_back(new Token("symbol", ";"));


    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "test3"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "test4"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("symbol", "}"));

    // int a , char b , boolean c
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "boolean"));
    // tokens.push_back(new Token("identifier", "c"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("identifier", "Test"));
    // tokens.push_back(new Token("identifier", "d"));
    // tokens.push_back(new Token("symbol", ";"));

    // { var int a ; var char b ; let a = skip ; let b = skip ; }
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "var"));     // var int a ;
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "var"));     // var int a ;
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));
    
    // tokens.push_back(new Token("keyword", "while"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("keyword", "do"));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));

    //     tokens.push_back(new Token("keyword", "return"));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));

    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("symbol", "}"));

    // if ( skip ) { }  
    // tokens.push_back(new Token("keyword", "if"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("keyword", "while"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));


    // keyword while
    // symbol (
    // keyword skip
    // symbol )
    // symbol {
    // symbol }



    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileIf();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}