#include "stack.h"
#include "predictive_parsing_table.h"
#include <string>
#include <iostream>

int main()
{
    // parse table in vector form and relative information
    const std::vector<const std::string> parseList{"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", "ɛ", "ɛ", "T", "FR", "", "", "", "", "FR", "", "", "R", "", "ɛ", "ɛ", "*FR", "/FR", "", "ɛ", "ɛ", "F", "a", "", "", "", "", "(E)", "", ""};
    const size_t ROWS{6};
    const size_t COLS{9};

    // parse table created using parseList
    PredictiveParsingTable* parseTable{new PredictiveParsingTable(ROWS, COLS, parseList)};

    // stack object that holds char types
    Stack<const char>* charStack{new Stack<const char>};

    // input string
    std::string inputStr1 = "(a+a)*a$";
    std::string inputStr2 = "a*(a/a)$";
    std::string inputStr3 = "a(a+a)$";
    
    // stack implementation
    /**
     * PUSH $ TO STACK ALWAYS
     * PUSH STARTING SYMBOL TO STACK
     * WHILE TOP OF STACK IS NOT EQUAL TO $
     *      IF FIRST CHAR OF INPUT MATCHES TOP OF STACK
     *          REMOVE FIRST CHAR FROM INPUT AND UPDATE INPUT
     *          POP TOP OF STACK
     *      ELSE
     *          POP TOP OF STACK
     *          USE POPPED ELEMENT AND FIRST CHAR OF INPUT AS KEYS TO FIND SYMBOL ON PARSE TABLE
     *          PUSH THE CHARS OF THE PARSE TABLE ***BACKWARDS*** ONTO THE STACK
     *      OUTPUT CURRENT STACK
     * 
     * note: i do not know the fail condition right now, pls msg me if you have any questions about 
     * the stack or parse table class, i also do not claim to have the comment implementation completely
     * correct, much love
    */

    // free allocated memory
    delete parseTable;
    delete charStack;

    return 0;
}
