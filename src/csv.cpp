#include "csv.hpp"

#include <sstream>

CSV::CSV(std::istream& is) {
    readRow(is, headers);
    while (!is.eof()) {
        cells.push_back(std::vector<std::string>());
        readRow(is, cells.back());
        if (cells.back().empty()) cells.pop_back();
    }
}

void CSV::readRow(std::istream& is, std::vector<std::string>& row) {
    // Read a line
    std::string line;
    std::getline(is, line);

    // Parse the cells from the line
    std::string cell = "";
    bool insideQuotation = false;
    for (uint32_t i = 0; i < line.length(); i++) {
        char c = line[i];

        if (c == '"') {
            if (insideQuotation) {
                insideQuotation = false;
            } else {
                insideQuotation = true;
            }
        } else if (c == ',' && !insideQuotation) {
            row.push_back(std::move(cell));
            cell = "";
        } else {
            cell += c;
        }
    }
    if (!cell.empty()) row.push_back(std::move(cell)); // The last cell did not get pushed in for-loop
}

size_t CSV::columns() {
    return headers.size();
}

size_t CSV::rows() {
    return cells.size();
}

std::string CSV::columnHeader(uint32_t column) {
    return headers[column];
}

int64_t CSV::columnIndex(const std::string& columnName) {
    int64_t columnInd = -1;
    for (int i = 0; i < columns(); i++) {
        if (headers[i] == columnName) {
            columnInd = i;
            break;
        }
    }
    return columnInd;
}

std::string CSV::cell(const std::string& column, uint32_t row) {
    return cell(columnIndex(column), row);
}

std::string CSV::cell(uint32_t column, uint32_t row) {
    return cells[row][column];
}
