#include "catch_amalgamated.hpp"
#include "constants.hpp"

#include <iostream>

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
