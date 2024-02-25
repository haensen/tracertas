#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

/**
 * For reading CSV formatted text.
 * Assumes the text has a header record.
*/
class CSV {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> cells;

    std::vector<std::string> readRow(std::istream& is);

public:
    /**
     * @param is Input stream
    */
    CSV(std::istream& is);

    size_t columns();
    size_t rows();

    /**
     * @returns The name of the column header
    */
    std::string columnHeader(uint32_t column);

    std::string cell(const std::string& column, uint32_t row);
    std::string cell(uint32_t column, uint32_t row);
};

#endif
