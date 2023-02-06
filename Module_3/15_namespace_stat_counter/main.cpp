#include "libstat.h"

#include <iostream>

int main() {
    aggregator::tests::Sum();
    aggregator::tests::Max();
    aggregator::tests::Mean();
    aggregator::tests::StandardDeviation();
    aggregator::tests::Mode();
    aggregator::tests::Printer();

    std::cout << "Test passed!"sv << std::endl;
}