#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <string>
#include <vector>

/**
 * For reading CSV-files
*/
class CSV {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> cells;

    std::vector<std::string> readRow(std::istream& is);

public:
    CSV(std::istream& is);

    size_t columns();
    size_t rows();

    std::string columnHeader(size_t column);

    std::string cell(std::string column, size_t row);
    std::string cell(size_t column, size_t row);
};

#endif
