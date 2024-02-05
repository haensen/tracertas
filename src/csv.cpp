#include "csv.hpp"

#include <sstream>

CSV::CSV(std::istream& is) {
    headers = readRow(is);
    while (!is.eof()) {
        std::vector<std::string> row = readRow(is);
        if (!row.empty()) cells.push_back(row);
    }
}

std::vector<std::string> CSV::readRow(std::istream& is) {
    // Read a line
    std::string line;
    std::getline(is, line);

    // Parse the cells from the line
    std::vector<std::string> row;
    std::string cell = "";
    bool insideQuotation = false;
    for (int i = 0; i < line.length(); i++) {
        char c = line[i];

        if (c == '"') {
            if (insideQuotation) {
                insideQuotation = false;
            } else {
                insideQuotation = true;
            }
        } else if (c == ',' && !insideQuotation) {
            row.push_back(cell);
            cell = "";
        } else {
            cell += c;
        }
    }
    if (!cell.empty()) row.push_back(cell);

    return row;
}

size_t CSV::columns() {
    return headers.size();
}

size_t CSV::rows() {
    return cells.size();
}

std::string CSV::columnHeader(size_t column) {
    return headers[column];
}

std::string CSV::cell(std::string column, size_t row) {
    size_t columnInd = 0;
    while (headers[columnInd] != column) { columnInd++; }
    return cell(columnInd, row);
}

std::string CSV::cell(size_t column, size_t row) {
    return cells[row][column];
}
