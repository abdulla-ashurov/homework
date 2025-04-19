#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include "../include/helper.hpp"

const std::string VALID_DATASET_FILE = "test/payloads/valid_dataset.csv";
const std::string INVALID_DATASET_FILE = "test/payloads/invalid_dataset.csv";
const std::string VALID_AND_INVALID_DATASET_FILE = "test/payloads/valid_and_invalid_dataset.csv";

const std::vector<Row> EXPECTED_VALID_DATASET = {
    Row("Berlin", -0.5762802920519917, 1.727867251915578, "s"),
    Row("Paris", 0.09434184059329664, -1.7241799812127212, "r"),
    Row("Dubai", -1.8597462867666863, -3.1309108468083178, "q"),
    Row("Sydney", 1.1724092061144014, 0.3212112253865307, "p"),
    Row("New York", -1.9995629204837775, 1.3134565068889366, "q"),
    Row("Berlin", 0.16189451955197098, 0.264015505498147, "r"),
    Row("Mumbai", -2.1656413503718976, -0.16446399349512308, "q"),
    Row("Tokyo", 0.9254043505208468, -1.5381731186485093, "r"),
    Row("Berlin", -0.5831231746998783, 3.335504175081088, "s"),
    Row("Dubai", 0.9942878108049084, -1.9331579795035507, "r"),
    Row("Dubai", 1.8948368355857947, 3.231029564254973, "p"),
    Row("Sydney", 0.0951971110011599, 1.1764958578539653, "r"),
    Row("New York", 1.0015030958115114, -2.371818190794083, "p"),
    Row("Paris", -0.47243384469654814, 1.130195892138381, "s"),
    Row("Sydney", 0.3100801876700431, 1.5998471314182683, "r"),
    Row("Sydney", -0.9991014135643922, 0.555589568910973, "s"),
    Row("Tokyo", -0.4999865040677538, 3.36305086944545, "s"),
    Row("London", -2.928401313417387, -0.09738062652492552, "q"),
    Row("New York", 1.0247935157572992, -2.523815516907555, "p"),
    Row("Seoul", -1.304751287871226, -0.8338434477747203, "q"),
    Row("Sydney", -2.29360472984121, 3.8254992603750306, "q")
};

#endif // __CONSTANTS_HPP__
