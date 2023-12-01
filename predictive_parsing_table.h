#include <stdexcept>
#include <map>
#include <vector>

#ifndef PREDICTIVE_PARSING_TABLE_H
#define PREDICTIVE_PARSING_TABLE_H

// definitions for easy reading of code
#define COLS_KEY const std::string
#define ROWS_KEY const std::string
#define VALUE_SYMBOL const std::string
#define PARSE_MAP std::map<std::pair<COLS_KEY,ROWS_KEY>,VALUE_SYMBOL>

struct KeyDoesNotExist : public std::runtime_error
{
    KeyDoesNotExist() : std::runtime_error("given key(s) does not exist in parse table") {}
    KeyDoesNotExist(const std::string& msg) : std::runtime_error(msg) {}
};

struct TooManyStringObjectsError : public std::runtime_error
{
    TooManyStringObjectsError() : std::runtime_error("too many string objects for given rows and cols") {}
    TooManyStringObjectsError(const std::string& msg) : std::runtime_error(msg) {}
};

struct TooLittleStringObjectsError : public std::runtime_error
{
    TooLittleStringObjectsError() : std::runtime_error("too little string objects for given rows and cols") {}
    TooLittleStringObjectsError(const std::string& msg) : std::runtime_error(msg) {}
};

class PredictiveParsingTable 
{
public:
    /**
     * Create instance of PredictiveParsingTable.
     * 
     * @param rows Number of rows of the parse table
     * @param cols Number of columns of the parse table
     * @param values Const std::vector of const std::string objects where 
     * these elements are ordered from left to right and top to bottom;
     * do not include element (0,0); for empty elements, use ""
    */
    PredictiveParsingTable(
        const size_t rows, 
        const size_t cols,
        const std::vector<const std::string>& stringList) 
        : rows{rows}, cols{cols}, startSymbol{stringList[cols-1]}
    {
        createMap();
        implementParseTable(stringList);
    }

    // destructor
    ~PredictiveParsingTable() {
        // free allocated space
        delete parse_map;
    }

    /**
     * Grab and return start symbol
     * assumed to be (0,1) of parse table
    */
    ROWS_KEY getStartSymbol() const {
        return startSymbol;
    }

    /**
     * Grab and return symbol of parse table at indicated position
     * 
     * @param col_key Column key string symbol
     * @param row_key Row key string symbol
     * @return String symbol at given column and row
    */
    VALUE_SYMBOL getSymbolAt(const std::string& col_key, const std::string& row_key) const {
        try {
            // from parse_map map, use the given strings to form a pair and use as key to return the symbol value
            return parse_map->at(std::make_pair(col_key, row_key));
        } 
        catch (...) {
            // if user tries to provide a col_key or row_key that does not exist, throw error
            throw KeyDoesNotExist();
        }
    }

private:
    const size_t rows; // number of rows for the parse table
    const size_t cols; // number of cols for the parse table
    std::map<std::pair<COLS_KEY,ROWS_KEY>,VALUE_SYMBOL>* parse_map;
    ROWS_KEY startSymbol;

    // create parse_map object for ptr
    void createMap() {
        parse_map = new PARSE_MAP;
    }

    // map the parse table to the parse_map object
    void implementParseTable(const std::vector<const std::string>& stringList) {
        // if given rows and cols does not match size of given parseList, throw error
        if (stringList.size() > ((rows * cols)-1))
            throw TooManyStringObjectsError();
        if (stringList.size() < ((rows * cols)-1))
            throw TooLittleStringObjectsError();

        // for each symbol, create a key pair of col and row for easy access
        for (size_t r = 1; r < rows; ++r) {
            for (size_t c = 1; c < cols; ++c) {
            parse_map->insert(std::make_pair(
                std::make_pair(
                    stringList[c - 1], 
                    stringList[r * cols - 1]), 
                stringList[r * cols - 1 + c])
            );
            }
        }
    }

};


#endif