#include "stack.h"
#include "predictive_parsing_table.h"
#include <string>

#define given_parse_table = {"a", "+", "-", "*", "/", "(", ")", "$", "E", "TQ", "", "", "", "", "TQ", "", "", "Q", "", "+TQ", "-TQ", "", "", "", "ɛ", "ɛ", "T", "FR", "", "", "", "", "FR", "", "", "R", "", "ɛ", "ɛ", "*FR", "/FR", "", "ɛ", "ɛ", "F", "a", "", "", "", "", "(E)", "", ""}

int main(int argc, char const *argv[])
{
    const std::vector<const std::string&> parseList = given_parse_table;

    return 0;
}
