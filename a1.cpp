#include "iostream"
#include "vector"
#include "numeric"
#include "numbers"
#include "random"
#include "fstream"

#include "include/sort_tester.h"

//circle with center (x, y) and radius r
struct Circle {
    double x;
    double y;
    double r;

    //checks whether point (px, py) lies inside the circle
    bool is_in(double px, double py) const {
        return (px - x) * (px - x) + (py - y) * (py - y) <= r * r;
    }
};

Circle create() {
    double x, y, r;
    std::cin >> x >> y >> r;
    return {x, y, r};
}


//rectangle with lower left vertex (x0, y0) and upper right vertex (x1, y1)
struct Rect {
    double x0;
    double y0;
    double x1;
    double y1;
};


//minimal rectangle, that includes all 3 circles
Rect wide_circum(Circle S, Circle P, Circle Q) {
    double x0 = std::min({P.x - P.r, Q.x - Q.r, S.x - S.r});
    double x1 = std::max({P.x + P.r, Q.x + Q.r, S.x + S.r});
    double y0 = std::min({P.y - P.r, Q.y - Q.r, S.y - S.r});
    double y1 = std::max({P.y + P.r, Q.y + Q.r, S.y + S.r});

    return {x0, y0, x1, y1};
}

//minimal rectangle, that includes intersection of 3 circles
Rect narrow_circum(Circle S, Circle P, Circle Q) {
    double x0 = std::max({P.x - P.r, Q.x - Q.r, S.x - S.r});
    double x1 = std::min({P.x + P.r, Q.x + Q.r, S.x + S.r});
    double y0 = std::max({P.y - P.r, Q.y - Q.r, S.y - S.r});
    double y1 = std::min({P.y + P.r, Q.y + Q.r, S.y + S.r});

    return {x0, y0, x1, y1};
}


//class that computes approximate area of intersection of 3 circles
class AreaApproximator {
private:
    Circle S;
    Circle P;
    Circle Q;

public:
    AreaApproximator() = default;

    AreaApproximator(Circle S, Circle P, Circle Q) {
        this->S = S;
        this->P = P;
        this->Q = Q;
    }

    //n - number of iterations
    //R - circumscribed rectangle
    //rather computes area of intersection of S, P, Q and R, but we believe that R includes circles intersection
    double approximate(Rect R, int n) {
        double x, y;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<> x_distrib(R.x0, R.x1);
        std::uniform_real_distribution<> y_distrib(R.y0, R.y1);

        int k = 0;
        for (int i = 0; i < n; ++i) {
            x = x_distrib(mt);
            y = y_distrib(mt);
            if (P.is_in(x, y) && Q.is_in(x, y) && S.is_in(x, y)) {
                ++k;
            }
        }
        return k * (R.x1 - R.x0) * (R.y1 - R.y0) / n;
    }
};

class AreaTester {
private:
    AreaApproximator approximator;
    int repetitions;
    int start;
    int step;
    int end;



public:
    explicit AreaTester(AreaApproximator approximator, int repetitions = 50, int start = 100, int step = 500, int end = 100000)
            : approximator(approximator), repetitions(repetitions), start(start), step(step), end(end) {};


    TestResults run(Rect R) {
        std::vector<Test> tests;
        for (int i = 0; i < repetitions; ++i){
            Test approx;
            for (int n = start; n <= end; n += step) {
                approx.emplace_back(n, approximator.approximate(R, n));
            }
            tests.push_back(approx);
        }

        return {tests};
    }
};

void write(const Test &results, std::ofstream &results_file) {
    for (auto &[iterations, value]: results) {
        results_file << iterations << " " << value << ";";
    }
    results_file << '\n';
}

int main() {
    Circle S{1, 1, 1};
    Circle P{1.5, 2, std::sqrt(5) / 2};
    Circle Q{2, 1.5, std::sqrt(5) / 2};

    Rect R_wide = wide_circum(S, P, Q);
    Rect R_narrow = narrow_circum(S, P, Q);

    AreaApproximator approximator(S, P, Q);

    double precise_area = 0.25 * std::numbers::pi + 1.25 * std::asin(0.8) - 1;

    std::ofstream a1_file;
    a1_file.open("./data/a1_results.csv");

    AreaTester test_runner(approximator);
    auto wide_results = test_runner.run(R_wide);
    auto narrow_results = test_runner.run(R_narrow);

    write(wide_results.mean(), a1_file);
    write(narrow_results.mean(), a1_file);
    write(wide_results.deviation(precise_area), a1_file);
    write(narrow_results.deviation(precise_area), a1_file);

    a1_file.close();
}