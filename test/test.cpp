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
