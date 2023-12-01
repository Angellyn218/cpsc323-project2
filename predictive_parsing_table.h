#include <stdexcept>
#include <map>
#include <vector>

#ifndef PREDICTIVE_PARSING_TABLE_H
#define PREDICTIVE_PARSING_TABLE_H

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
        : rows{rows}, cols{cols}
    {
        createMap();
        implementParseTable(stringList);
    }

    ~PredictiveParsingTable() {
        delete parse_map;
    }

    /**
     * Grab symbol of parse table at indicated position
     * 
     * @param col_key Column key string symbol
     * @param row_key Row key string symbol
     * @return String symbol at given column and row
    */
    VALUE_SYMBOL getSymbolAt(const std::string& col_key, const std::string& row_key) const {
        try {
            return parse_map->at(std::make_pair(col_key, row_key));
        } 
        catch (...) {
            throw KeyDoesNotExist();
        }
    }

private:
    size_t rows;
    size_t cols;
    std::map<std::pair<COLS_KEY,ROWS_KEY>,VALUE_SYMBOL>* parse_map;

    void createMap() {
        parse_map = new PARSE_MAP;
    }

    void implementParseTable(const std::vector<const std::string>& stringList) {
        if (stringList.size() > ((rows * cols)-1))
            throw TooManyStringObjectsError();

        if (stringList.size() < ((rows * cols)-1))
            throw TooLittleStringObjectsError();

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