#include <stdexcept>
#include <map>
#include <vector>

#ifndef PREDICTIVE_PARSING_TABLE_H
#define PREDICTIVE_PARSING_TABLE_H

#define COLS_KEY const std::string&
#define ROWS_KEY const std::string&
#define VALUE_SYMBOL const std::string&

struct KeyDoesNotExist : public std::runtime_error
{
    KeyDoesNotExist() : std::runtime_error("given key does not exist in parse table") {}
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
     * do not include element (0,0); for empty elements, use NULL
    */
    PredictiveParsingTable(
        const size_t rows, 
        const size_t cols,
        const std::vector<const std::string>& stringList) 
        : rows{rows}, cols{cols}
    {
        createMaps();
        implementParseTable(stringList);
    }

    ~PredictiveParsingTable() {
        delete keyRow_keyCol;
        delete keyCol_symbolVal;
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

        } 
        catch (...) {
            throw KeyDoesNotExist();
        }
    }

private:
    size_t rows;
    size_t cols;
    std::map<const std::string&, const std::string&>* keyRow_keyCol;
    std::map<const std::string&, const std::string&>* keyCol_symbolVal;

    void createMaps() {
        keyRow_keyCol = new std::map<COLS_KEY, ROWS_KEY>;
        keyCol_symbolVal = new std::map<ROWS_KEY, VALUE_SYMBOL>;
    }

    void implementParseTable(const std::vector<const std::string>& stringList) {
        if (stringList.size() > ((rows * cols)-1))
            throw TooManyStringObjectsError();

        if (stringList.size() < ((rows * cols)-1))
            throw TooLittleStringObjectsError();

        for (size_t c = 0; c < cols-1; ++c) {
            for (size_t r = 0; r < rows-1; ++r) {
                if (c == 0 && r == 0) continue;

                keyRow_keyCol->insert(std::pair<COLS_KEY,ROWS_KEY>(stringList[0],stringList[0]));
                keyCol_symbolVal->insert(std::pair<ROWS_KEY,VALUE_SYMBOL>(stringList[0],stringList[0]));
            }
        }
    }

};


#endif