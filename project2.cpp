#include "stack.h"
#include "predictive_parsing_table.h"
#include <string> // string methods and manipulations
#include <iostream> // output to terminal
#include <algorithm>

// for purposes of this project and since regular symbol ɛ is not supported, use lowercase 'e'
#define EPSILON "e"

void stackImplementationParse(const PredictiveParsingTable*, std::string);
std::string reverseStr(std::string);

int main()
{
    // parse table in vector form and relative information
    const std::vector<const std::string> parseList{"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", EPSILON, EPSILON, "T", "FR", "", "", "", "", "FR", "", "", "R", "", EPSILON, EPSILON, "*FR", "/FR", "", EPSILON, EPSILON, "F", "a", "", "", "", "", "(E)", "", ""};
    const size_t ROWS{6};
    const size_t COLS{9};
    
    // parse table created using parseList
    const PredictiveParsingTable* parseTable{new PredictiveParsingTable(ROWS, COLS, parseList)};

    // input strings
    std::string inputStr1 = "(a+a)*a$";
    std::string inputStr2 = "a*(a/a)$";
    std::string inputStr3 = "a(a+a)$";
    
    std::cout << "==================== PROBLEM 1 ====================";
    stackImplementationParse(parseTable, inputStr1);

    std::cout << "\n==================== PROBLEM 2 ====================";
    stackImplementationParse(parseTable, inputStr2);
    
    std::cout << "\n==================== PROBLEM 3 ====================" ;
    stackImplementationParse(parseTable, inputStr3);

    // free allocated memory
    delete parseTable;

    return 0;
}

void stackImplementationParse(const PredictiveParsingTable* parseTable, std::string inputStr) {
    Stack<const char>* charStack{new Stack<const char>}; // stack object that holds char types

    const char startSymbol{parseTable->getStartSymbol()[0]}; // start symbol

    std::string topOfStack; // var for tracking top of stack
    std::string firstCharInput; // var for tracking first char of input
    std::string parseSymbol; // var for tracking parse table symbol of (topOfStack, firstCharInput)

    // required starting operations
    charStack->push('$'); // push $ to stack
    std::cout << "\nInput: " << inputStr << std::endl;
    std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;

    charStack->push(startSymbol); // push START SYMBOL to stack
    std::cout << "\nInput: " << inputStr << std::endl;
    std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;
    // end required starting operations

    // while top of stack does not equal $
    while (charStack->peek() != '$') {
        topOfStack = charStack->peek(); // update topOfStack
        firstCharInput = inputStr[0]; // update firstCharInput

        if (firstCharInput == topOfStack) { // top of stack DOES match first char of input
            charStack->pop();
            inputStr = inputStr.substr(1,inputStr.length()); // remove first char of inputStr
        }
        else { // top of stack DOES NOT match first char of input
            charStack->pop();
            parseSymbol = parseTable->getSymbolAt(firstCharInput, topOfStack); // refer to parse table to get relevant production rule

            // EPSILON means nothing, so if we get EPSILON production rule then do not push anything
            if (parseSymbol[0] != EPSILON[0]) {
                // push production rule onto stack in reverse order
                for (char c : reverseStr(parseSymbol)) {
                    charStack->push(c);
                }
            }
        }
        std::cout << "\nInput: " << inputStr << std::endl;
        std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;
    }

    // if both the stack and input str are reduced to both only having $ then the string is accepted, otherwise the string is invalid
    if (charStack->peek() == '$' && inputStr[0] == '$')
        std::cout << "Output: String is accepted/valid." << std::endl;
    else
        std::cout << "Output: String is not accepted/invalid." << std::endl;

    // free allocated memory
    delete charStack;
}

std::string reverseStr(std::string str) {
    return std::string(str.rbegin(), str.rend());
}