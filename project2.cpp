#include "stack.h"
#include "predictive_parsing_table.h"
#include <string> // string methods and manipulations
#include <iostream> // output to terminal
#include <algorithm>

// for purposes of this project and since regular symbol ɛ is not supported, use lowercase 'e'
#define EPSILON "e"

int main()
{
    // parse table in vector form and relative information
    const std::vector<const std::string> parseList{"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", EPSILON, EPSILON, "T", "FR", "", "", "", "", "FR", "", "", "R", "", EPSILON, EPSILON, "*FR", "/FR", "", EPSILON, EPSILON, "F", "a", "", "", "", "", "(E)", "", ""};
    const size_t ROWS{6};
    const size_t COLS{9};
    const char startSymbol{'E'};
    
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

    std::string topOfStack;
    std::string firstLetterInput;
    std::string parseSymbol;

    charStack->push('$');
    charStack->push(startSymbol);

    std::cout << charStack->getString() << std::endl;

    while (charStack->peek() != '$') {
        topOfStack = charStack->peek();
        firstLetterInput = inputStr1[0];

        std::cout << "\nCOMPARING: " + topOfStack + " " + firstLetterInput << std::endl;
        if (firstLetterInput == topOfStack) { // top of stack DOES match first char of input
            std::cout << "MATCHES" << std::endl;
            charStack->pop();

            inputStr1 = inputStr1.substr(1,inputStr1.length());
        }
        else { // top of stack DOES NOT match first char of input
            std::cout << "DOES NOT MATCH" << std::endl;
            charStack->pop();

            parseSymbol = parseTable->getSymbolAt(firstLetterInput, topOfStack);
    
            if (parseSymbol[0] != EPSILON[0]) {
                std::string reversedParseSymbol(parseSymbol.rbegin(), parseSymbol.rend());

                for (char c : reversedParseSymbol) {
                    charStack->push(c);
                }
            }
        }
        std::string stackAsString = charStack->getString();
        std::cout << std::string(stackAsString.rbegin(), stackAsString.rend()) << std::endl;
        std::cout << inputStr1 << std::endl;
    }

    if (charStack->peek() == '$' && inputStr1[0] == '$') {
        std::cout << "string accepted" << std::endl;
    }
    else {
        std::cout << "string not accepted" << std::endl;
    }

    // free allocated memory
    delete parseTable;
    delete charStack;

    return 0;
}
