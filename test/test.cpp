#include "catch_amalgamated.hpp"
#include "constants.hpp"

TEST_CASE("Test read function") {
    SECTION("It can parse valid input data from CSV file") {
        std::vector<Row> dataset;
        read(VALID_DATASET_FILE, dataset);

        REQUIRE(dataset == EXPECTED_VALID_DATASET);
    }

    SECTION("It should not parse not valid data from CSV file") {
        std::vector<Row> dataset;
        read(INVALID_DATASET_FILE, dataset);

        REQUIRE(dataset.empty());

        read(VALID_AND_INVALID_DATASET_FILE, dataset);
        REQUIRE(dataset == EXPECTED_VALID_DATASET);
    }
}

TEST_CASE("Test get_average_value_of_g") {
    SECTION("It can calculate average value of g from valid dataset") {
        std::vector<Row> dataset;
        read(VALID_DATASET_FILE, dataset);

        double expected_value = 5.1002;
        double value = get_average_value_of_g(dataset);

        REQUIRE(value == expected_value);
    }
}

TEST_CASE("Test filtered_calculation") {
    SECTION("It can calculate sum of all h where g is greater than 1 from valid dataset") {
        std::vector<Row> dataset;
        read(VALID_DATASET_FILE, dataset);

        double expected_value = 13.83;
        double value = filtered_calculation(dataset);

        REQUIRE(value == expected_value);
    }
}

TEST_CASE("Test grouped_analysis") {
    SECTION("It can calculate g median value for each unique values of c") {
        std::vector<Row> dataset;
        read(VALID_DATASET_FILE, dataset);

        double expected_value = 21.211;
        double value = grouped_analysis(dataset);

        REQUIRE(value == expected_value);
    }
}
