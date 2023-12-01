#include "stack.h"
#include "predictive_parsing_table.h"
#include <string>
#include <iostream>

#define given_parse_table = {"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", "ɛ", "ɛ", "T", "FR", "", "", "", "", "FR", "", "", "R", "", "ɛ", "ɛ", "*FR", "/FR", "", "ɛ", "ɛ", "F", "a", "", "", "", "", "(E)", "", ""}

int main()
{
    const std::vector<const std::string> parseList{"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", "ɛ", "ɛ", "T", "FR", "", "", "", "", "FR", "", "", "R", "", "ɛ", "ɛ", "*FR", "/FR", "", "ɛ", "ɛ", "F", "a", "", "", "", "", "(E)", "", ""};
    PredictiveParsingTable* table{new PredictiveParsingTable(6, 9, parseList)};

    std::cout << table->getSymbolAt("(", "F");


    delete table;

    return 0;
}
