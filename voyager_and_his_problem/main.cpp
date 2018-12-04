#include "functions.h"
#include <cmath>
#include <functional>
#include <stdlib.h>
#include <fstream>
#include <string>


int main() {
    ddvec cost_matrix{
            {INF, 10, 8, 19, 12},
            {10, INF, 20, 6, 3},
            {8, 20, INF, 4, 2},
            {19, 6, 4, INF, 7},
            {12, 3, 2, 7, INF}
    };

    ddvec test_matrix_5x5{
            {INF, 99, 98, 7, 3},
            {99, INF, 5, 6, 96},
            {98, 5, INF, 94, 4},
            {7, 6, 94, INF, 97},
            {3, 96, 4, 97, INF}
    };

    ddvec test_matrix_6x6{
            {INF, 99, 10,  4, 99, 99},
            { 99,INF, 99, 99,  5,  6},
            { 10, 99,INF, 99,  7, 99},
            {  4, 99, 99,INF, 95,  5},
            { 99,  5,  7, 95,INF, 99},
            { 99,  6, 99,  5, 99,INF}
    };

    print_matrix(cost_matrix);

    std::vector<int> best_path = tsp(cost_matrix);
    print_path(best_path);

}