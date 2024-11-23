#include "iostream"
#include "vector"
#include "fstream"

#include "include/sorter.h"
#include "include/sort_tester.h"

void write(const Test &results, std::ofstream &results_file) {
    for (auto &[iterations, time]: results) {
        results_file << iterations << " " << time << ";";
    }
    results_file << '\n';
}

void write_tests(ISorter &sorter, std::ofstream &results_file) {
    SortTester tester(sorter);

    write(tester.run(ArrayGenerator()).mean(), results_file);

    write(tester.run(DescArrayGenerator()).mean(), results_file);

    write(tester.run(AlmostDescArrayGenerator()).mean(), results_file);
    std::cout << "***\n";
}

int main() {
    std::ofstream a2_file;
    a2_file.open("./data/a2_results.csv");


    auto tresholds = {0, 5, 10, 15, 25, 50};

    for(auto treshold: tresholds ){
        a2_file << treshold << ";";
    }
    a2_file << '\n';


    MergeSorter msorter;
    for (auto treshold: tresholds) {
        msorter.set_insertion_treshold(treshold);
        write_tests(msorter, a2_file);
    }

    a2_file.close();

    std::ofstream a3_file;
    a3_file.open("./data/a3_results.csv");
    QuickSorter qsorter;
    IntroSorter isorter;

    write_tests(qsorter, a3_file);
    write_tests(isorter, a3_file);


    a3_file.close();
}
