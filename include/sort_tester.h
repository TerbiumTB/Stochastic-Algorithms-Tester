#include "vector"
#include "array_generator.h"
#include "sorter.h"

#ifndef SET_3_SORT_TESTER_H
#define SET_3_SORT_TESTER_H

typedef std::vector<std::pair<int, double>> Test;

struct TestResults {
    std::vector<Test> tests;

    Test mean();

    Test deviation(double);
};


class SortTester {
private:
    ISorter &sorter;

    int repetitions;

    int start_size;
    int step;
    int end_size;

public:
    explicit SortTester(ISorter &sorter, int repetitions = 50,
                        int start_size = 500, int step = 100, int end_size = 10000)
            : sorter(sorter), start_size(start_size), step(step), end_size(end_size), repetitions(repetitions) {};

    TestResults run(const ArrayGenerator &);
};


#endif //SET_3_SORT_TESTER_H
