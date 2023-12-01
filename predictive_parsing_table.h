#include <stdexcept>
#include <map>

#ifndef PREDICTIVE_PARSING_TABLE_H
#define PREDICTIVE_PARSING_TABLE_H

class PredictiveParsingTable 
{
public:
    /**
     * Create instance of PredictiveParsingTable.
     * 
     * @param rows Number of rows of the parse table
     * @param cols Number of columns of the parse table
     * @param values List of string objects where elements are listed from LEFT to RIGHT and TOP to BOTTOM
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