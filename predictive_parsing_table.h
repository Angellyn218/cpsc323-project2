#include <stdexcept>
#include <map>

#ifndef PREDICTIVE_PARSING_TABLE_H
#define PREDICTIVE_PARSING_TABLE_H

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
     * @param values List of string objects where elements are ordered from LEFT to RIGHT and TOP to BOTTOM
    */
    PredictiveParsingTable(
        const int rows, 
        const int cols,
        const std::string& values) 
        : rows{rows}, cols{cols}
    {
        createMap();
        implementMap();
    }

    ~PredictiveParsingTable() {

    }

private:
    int rows;
    int cols;
    std::map<std::string&, std::string&>* parseTable;

    static void createMap() {

    }

    static void implementMap() {

    }

};


#endif