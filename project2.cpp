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
    
    std::cout << "==================== PROBLEM 1 ====================" << std::endl;
    stackImplementationParse(parseTable, inputStr1);
    std::cout << "==================== PROBLEM 2 ====================" << std::endl;
    stackImplementationParse(parseTable, inputStr2);
    std::cout << "==================== PROBLEM 3 ====================" << std::endl;
    stackImplementationParse(parseTable, inputStr3);

    // free allocated memory
    delete parseTable;

    return 0;
}

void stackImplementationParse(const PredictiveParsingTable* parseTable, std::string inputStr) {
    // stack object that holds char types
    Stack<const char>* charStack{new Stack<const char>};

    const char startSymbol{parseTable->getStartSymbol()[0]};

    std::string topOfStack;
    std::string firstLetterInput;
    std::string parseSymbol;

    // required starting operations
    charStack->push('$');
    std::cout << "\nInput: " << inputStr << std::endl;
    std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;

    std::cout << "\nInput: " << inputStr << std::endl;
    charStack->push(startSymbol);
    std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;
    // end required starting operations

    while (charStack->peek() != '$') {
        topOfStack = charStack->peek();
        firstLetterInput = inputStr[0];

        if (firstLetterInput == topOfStack) { // top of stack DOES match first char of input
            charStack->pop();

            inputStr = inputStr.substr(1,inputStr.length());
        }
        else { // top of stack DOES NOT match first char of input
            charStack->pop();

            parseSymbol = parseTable->getSymbolAt(firstLetterInput, topOfStack);
    
            if (parseSymbol[0] != EPSILON[0]) {
                for (char c : reverseStr(parseSymbol)) {
                    charStack->push(c);
                }
            }
        }
        std::cout << "\nInput: " << inputStr << std::endl;
        std::cout << "Stack: " << "[" << reverseStr(charStack->getString()) << " ]" << std::endl;
    }

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