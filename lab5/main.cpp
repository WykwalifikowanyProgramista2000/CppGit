#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
/*
#define INF (NAN)

std::vector<int> tsp(std::vector<vector<double>> cost_matrix){

}

int main() {

    std::vector<std::vector<double>> cost_matrix{
            {INF, 10, 8, 19, 12},
            {10, INF, 20, 6, 3},
            {8, 20, INF, 4, 2},
            {19, 6, 4, INF, 7},
            {12, 3, 2, 7, INF}
    };


}
 */
int main() {
    std::vector<int> v{3, 10, 4, 10, 5, 9};

    std::vector<int>::iterator result = std::min_element(std::begin(v), std::end(v));
    std::cout << *result;

}