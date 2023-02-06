#include "libstat.h"

#include <iostream>

int main() {
    statistics::tests::AggregSum();
    statistics::tests::AggregMax();
    statistics::tests::AggregMean();
    statistics::tests::AggregStandardDeviation();
    statistics::tests::AggregMode();
    statistics::tests::AggregPrinter();

    std::cout << "Test passed!"sv << std::endl;
}