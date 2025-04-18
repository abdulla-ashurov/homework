#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>

struct Row {
    double m_a;
    double m_b;
    std::string m_city;
    std::string m_category;

    Row(const std::string &city = "", double a = 0.0, double b = 0.0, const std::string &category = "")
        : m_city(city), m_a(a), m_b(b), m_category(category) {}
};

bool try_parse_to_double(const std::string &str, double &num) {
    std::istringstream iss(str);
    iss >> num;

    return iss.eof() && !iss.fail();
}

bool try_parse(const std::string &line, Row &row) {
    std::string city, a_str, b_str, category;
    
    std::stringstream ss(line);
    if (!std::getline(ss, city, ',') || !std::getline(ss, a_str, ',') || 
        !std::getline(ss, b_str, ',') || !std::getline(ss, category, ',')) {
        return false;
    }

    double a = 0.0, b = 0.0;
    if (!try_parse_to_double(a_str, a) || !try_parse_to_double(b_str, b)) {
        return false;
    }

    row = Row(city, a, b, category);

    return true;
}

void read(const std::string &FILE_NAME, std::vector<Row> &out) {
    std::ifstream in(FILE_NAME);
    
    // Ignore column names
    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) {
        Row row;
        if (try_parse(line, row)) {
            out.emplace_back(row);
        }
    }
}

std::pair<double, double> func02(double a, double b, const std::string &c) {
    // Complex but deterministic transformations
    double phaseA = std::sin(M_PI * a / 4) * std::cos(M_PI * a / 6);
    double phaseB = std::sin(M_PI * b / 3) * std::cos(M_PI * b / 5);

    // Category-based multipliers with fixed rules
    double categoryMultiplier = 1.0;
    if (c == "p")
        categoryMultiplier = 1.2;
    else if (c == "q")
        categoryMultiplier = 0.8;
    else if (c == "r")
        categoryMultiplier = 1.5;
    else if (c == "s")
        categoryMultiplier = 0.9;
    
    // Complex quadratic form centered at (3,0)
    double baseG = 10.0 + 0.1 - 0.5 * std::pow(a - 3.0, 2);
    
    // Apply transformations with controlled precision
    double g = baseG * (1 + phaseA * 0.1) * categoryMultiplier;
    
    // Category-dependent output calculation
    double h;
    if (c == "p") {
        h = g * (a + std::abs(std::sin(a * 7)));
    } else if (c == "q") {
        h = g / (std::abs(b) + 0.001) * (1 + std::abs(std::cos(b * 5)));
    } else {
        h = g - std::log(1 + std::abs(a * b)) * (1 + std::abs(phaseA * phaseB));
    }

    // Round to prevent floating point discrepancies
    g = std::round(g * 1000000) / 1000000;
    h = std::round(h * 1000000) / 1000000;
    
    return std::make_pair(g, h);
}

#endif // __HELPER_HPP__
