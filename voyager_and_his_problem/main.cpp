#include "functions.h"
#include <cmath>
#include <functional>
#include <stdlib.h>


int main() {
    ddvec cost_matrix{
            {INF, 10, 8, 19, 12},
            {10, INF, 20, 6, 3},
            {8, 20, INF, 4, 2},
            {19, 6, 4, INF, 7},
            {12, 3, 2, 7, INF}
    };

    ddvec test_matrix{
            {11, 11, 1, 11, 11},
            {12, 10, 14, 14, 14},
            {13, 12, 11, 16, 10},
            {12, 14, 12, 13, 23},
            {22, 12, 11, 11, 16}
    };

    ddvec test_matrix_2{
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1}
    };

    TSP_solver(cost_matrix);
}