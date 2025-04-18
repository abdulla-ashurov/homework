#define _USE_MATH_DEFINES

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

/*
* Dataset: You are provided with a CSV file containing approximately 500,000 rows and 4 columns:
*   • f: A categorical column containing city names
*   • a: A numeric column
*   • b: A numeric column
*   • c: A categorical column with values 'p', 'q', 'r', or 's'
*
* Data Cleaning Instructions: Before answering any question, you should first clean the
* dataset by excluding all rows where either 'a' or 'b' contains non-numeric values. 
* All questions below should be answered using only this cleaned dataset.
*/

/*
* Questions: Answer the following questions, providing numerical answers with the specified precision:
*   1. Basic Function Application (10 points) Apply the function to all rows in the cleaned
*      dataset. Return the average value of 'g' rounded to 4 decimal places. 
*/

/*
* Data Format:
*  - Berlin,-0.5762802920519917,1.727867251915578,s 
*/

class Fields {
public:
    double m_a = 0.0;
    double m_b = 0.0;
    std::string m_city;
    std::string m_category;

    Fields() : m_a(0.0), m_b(0.0) {}
    Fields(const std::string &city, double a, double b, const std::string category)
        : m_city(city), m_a(a), m_b(b), m_category(category) {}
    
    void print() const {
        std::cout << m_city << ", " << m_a << ", " << m_b << ", " << m_category << std::endl;
    }
};

bool try_parse_to_double(const std::string &str, double &out) {
    std::istringstream iss(str);
    iss >> out;

    return !(iss.fail() || !iss.eof());
}

bool try_parse(const std::string &line, Fields &out) {
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

    out = Fields(city, a, b, category);

    return true;
}

void read(const std::string &file_name, std::vector<Fields> &out) {
    std::ifstream file(file_name);

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        Fields field;
        if (try_parse(line, field)) {
            out.emplace_back(field);
        }
    }
}

void print(const std::vector<Fields> &data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i].print();
    }
}

std::pair<double, double> func02(double a, double b, const std::string &c) {
    // Complex but deterministic transformations
    double phaseA = std::sin(M_PI * a / 4) * std::cos(M_PI * a / 6);
    double phaseB = std::sin(M_PI * b / 3) * std::cos(M_PI * b / 5);

    // Catagory-based multipliers with fixed rules
    double categoryMultiplier = 1.0;
    if (c == "p") categoryMultiplier = 1.2;
    else if (c == "q") categoryMultiplier = 0.8;
    else if (c == "r") categoryMultiplier = 1.5;
    else if (c == "s") categoryMultiplier = 0.9;

    // Complex quadratic form centered at (3,0)
    double baseG = 10.0 + 0.1 - 0.5 * std::pow(a - 3.0, 2);
    // Apply transformations with controlled precision
    double g = baseG * (1 + phaseA * 0.1) * categoryMultiplier;

    // Category-dependent output calculation
    double h;
    if (c == "p") {
        h = g * (a + std::abs(std::sin(a * 7)));
    } else if (c == "q") {
        h = g / (std::abs(b) + 0.001) * (1 + std::abs(std::cos(b
    * 5)));
    } else {
        h = g - std::log(1 + std::abs(a * b)) * (1 +
        std::abs(phaseA * phaseB));
    }

    // Round to prevent floating point discrepancies
    g = std::round(g * 1000000) / 1000000;
    h = std::round(h * 1000000) / 1000000;

    return std::make_pair(g, h);
}

void task1(const std::vector<Fields> &data) {
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); i++) {
        sum += func02(data[i].m_a, data[i].m_b, data[i].m_category).first;
    }

    std::cout << "Task1: " << std::fixed << std::setprecision(4) << sum / data.size() << std::endl;
}

void task2(const std::vector<Fields> &data) {
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].m_city == "Tokyo") {
            auto res = func02(data[i].m_a, data[i].m_b, data[i].m_category);
            double g = res.first;
            double h = res.second;

            if (g > 1.0) {
                sum += h;
            }
        }
    }

    std::cout << "Task2: " << std::fixed << std::setprecision(2) << sum << std::endl;
}

double get_median(std::vector<double> &nums) {
    std::sort(nums.begin(), nums.end());
    if (nums.size() % 2 == 0) {
        return (nums[nums.size() / 2 - 1] + nums[nums.size() / 2]) / 2.0;
    }

    return nums[nums.size()] / 2;
}

void task3(const std::vector<Fields> &data) {
    std::unordered_map<std::string, std::vector<double>> values;
    for (size_t i = 0; i < data.size(); i++) {
        values[data[i].m_category].push_back(func02(data[i].m_a, data[i].m_b, data[i].m_category).first);
    }

    double res = 0.0;
    for (const std::string &key : {"p", "q", "r", "s"}) {
        res += get_median(values[key]);
    }

    std::cout << "Task3: " << std::fixed << std::setprecision(3) << res << std::endl;
}

double compute_average_h_fixed_a(double fixed_a, const std::vector<Fields> &data) {
    double sum = 0.0;

    size_t count = 0;

    for (const auto &row : data) {
        if (row.m_city == "Paris") {
            double h = func02(fixed_a, row.m_b, row.m_category).second;
            sum += h;
            count++;
        }
    }

    return count > 0 ? sum / count : -1e9;
}

std::pair<double, double> optimize_a(const std::vector<Fields> &data, double low, double high) {
    const double eps = 1e-5;

    while (high - low > eps) {
        double mid1 = low + (high - low) / 3.0;
        double mid2 = high - (high - low) / 3.0;

        double h1 = compute_average_h_fixed_a(mid1, data);
        double h2 = compute_average_h_fixed_a(mid2, data);

        if (h1 < h2) {
            low = mid1;
        } else {
            high = mid2;
        }   
    }

    double best_a = (low + high) / 2;
    double best_avg_h = compute_average_h_fixed_a(best_a, data);

    return {
        std::round(best_a * 100.0) / 100.0,
        std::round(best_avg_h * 100.0) / 100.0
    };
}

// Ternary Search
void task4(const std::vector<Fields> &data) {
    double a_min = std::numeric_limits<double>::max();
    double a_max = std::numeric_limits<double>::lowest();

    for (const auto &row : data) {
        a_min = std::min(a_min, row.m_a);
        a_max = std::max(a_max, row.m_a);
    }

    auto res = optimize_a(data, a_min, a_max);

    std::cout << "Task4: " << std::fixed << std::setprecision(2) << res.first << " " << res.second << std::endl;
}

void task5(const std::vector<Fields> &data) {
    double delta = 0.0001;
    double sum_g_plus = 0.0;
    double sum_g_minus = 0.0;
    size_t count = 0;

    for (const auto &row : data) {
        if (row.m_city == "New York") {
            double g_plus = func02(1.0 + delta, row.m_b, row.m_category).first;
            double g_minus = func02(1.0 - delta, row.m_b, row.m_category).first;

            sum_g_plus += g_plus;
            sum_g_minus += g_minus;
            count++;
        }
    }

    double avg_g_plus = sum_g_plus / count;
    double avg_g_minus = sum_g_minus / count;

    double sensitivity = (avg_g_plus - avg_g_minus) / (2 * delta);

    std::cout << std::fixed << std::setprecision(6) << sensitivity << std::endl;
}

int main() {
    const std::string FILE_NAME("./interview_dataset.csv");

    std::vector<Fields> data;
    read(FILE_NAME, data);

    // print(data);

    task1(data);
    task2(data);
    task3(data);
    task4(data);
    task5(data);

    return 0;
}
