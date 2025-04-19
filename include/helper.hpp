// Abdulla Ashurov, RQD* Clearing

#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct Row {
    double m_a;
    double m_b;
    std::string m_city;
    std::string m_category;

    Row(const std::string &city = "", double a = 0.0, double b = 0.0, const std::string &category = "")
        : m_city(city), m_a(a), m_b(b), m_category(category) {}
};

bool operator==(const Row &first, const Row &second) {
    return first.m_a == second.m_a && first.m_b == second.m_b && 
           first.m_city == second.m_city && first.m_category == second.m_category;
}

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
    if (!in.is_open()) {
        return;
    }
    
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

double get_average_value_of_g(const std::vector<Row> &dataset) {
    double sum = 0.0;
    for (const auto &row : dataset) {
        sum += func02(row.m_a, row.m_b, row.m_category).first;
    }

    double average_value = sum / dataset.size();

    return std::round(average_value * 10000.0) / 10000.0;
}

double filtered_calculation(const std::vector<Row> &dataset) {
    double sum = 0.0;
    for (const auto &row : dataset) {
        if (row.m_city == "Tokyo") {
            std::pair<double, double> res = func02(row.m_a, row.m_b, row.m_category);
            double g = res.first;
            double h = res.second;

            if (g > 1.0) {
                sum += h;
            }
        }
    }

    return std::round(sum * 100.0) / 100.0;
}

double get_median(std::vector<double> &nums) {
    if (nums.empty()) {
        return 0.0;
    }

    std::sort(nums.begin(), nums.end());

    if (nums.size() % 2 == 0) {
        return (nums[nums.size() / 2 - 1] + nums[nums.size() / 2]) / 2.0;
    }

    return nums[nums.size() / 2];
}

double grouped_analysis(const std::vector<Row> &dataset) {
    std::unordered_map<std::string, std::vector<double>> category_to_g_values;
    for (const auto &row : dataset) {
        category_to_g_values[row.m_category].push_back(func02(row.m_a, row.m_b, row.m_category).first);
    }

    double sum = 0.0;
    for (const auto &key : {"p", "q", "r", "s"}) {
        sum += get_median(category_to_g_values[key]);
    }

    return std::round(sum * 1000.0) / 1000.0;
}

double compute_average_h_fixed_a(double a, const std::vector<Row> &dataset) {
    double sum = 0.0;
    size_t count = 0;

    for (const auto &row : dataset) {
        if (row.m_city == "Paris") {
            sum += func02(a, row.m_b, row.m_category).second;
            count++;
        }
    }

    return count > 0 ? sum / count : -1e9;
}

std::pair<double, double> optimization_problem(const std::vector<Row> &dataset) {
    double a_min = std::numeric_limits<double>::max();
    double a_max = std::numeric_limits<double>::lowest();

    for (const auto &row : dataset) {
        a_min = std::min(a_min, row.m_a);
        a_max = std::max(a_max, row.m_a);
    }

    const double precision = 1e-5;
    while (a_max - a_min > precision) {
        double mid1 = a_min + (a_max - a_min) / 3.0;
        double mid2 = a_max - (a_max - a_min) / 3.0;

        double h1 = compute_average_h_fixed_a(mid1, dataset);
        double h2 = compute_average_h_fixed_a(mid2, dataset);

        if (h1 < h2) {
            a_min = mid1;
        } else {
            a_max = mid2;
        }
    }

    double best_a = (a_min + a_max) / 2.0;
    double best_avg_h = compute_average_h_fixed_a(best_a, dataset);

    return std::make_pair(
        std::round(best_a * 100.0) / 100.0,
        std::round(best_avg_h * 100.0) / 100.0
    );
}

double parameter_sensitivity(const std::vector<Row> &dataset) {
    const double DELTA = 0.0001;

    double sum_g_plus = 0.0;
    double sum_g_minus = 0.0;
    size_t count = 0;

    for (const auto &row : dataset) {
        if (row.m_city == "New York") {
            double g_plus = func02(1.0 + DELTA, row.m_b, row.m_category).first;
            double g_minus = func02(1.0 - DELTA, row.m_b, row.m_category).first;

            sum_g_plus += g_plus;
            sum_g_minus += g_minus;
            
            count++;
        }
    }

    double avg_g_plus = sum_g_plus / count;
    double avg_g_minus = sum_g_minus / count;

    double sensitivity = (avg_g_plus - avg_g_minus) / (2 * DELTA);

    return std::round(sensitivity * 1000000.0) / 1000000.0;
}

#endif // __HELPER_HPP__
