#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#define INF (NAN)

using dvec = std::vector<double>;
using ddvec = std::vector<std::vector<double>>;

// bool functions

bool is_0_in_each_col_and_row(const ddvec &matrix){
    double flag;

    for(auto row: matrix){
        flag = 1;
        for(auto i: row) {
            if (!isnan(i))
                flag *= i;
        }
        if(flag != 0)
            return false;
    }

    for(int j = 0; j < matrix.size(); j++){
        flag = 1;
        for(int i = 0; i < matrix.size(); ++i) {
            if(!isnan(matrix[i][j]))
                flag *= matrix[i][j];
        }
        if(flag != 0)
            return false;
    }
    return true;
}

bool is_single_route_possible(ddvec &matrix, int row_index, int col_index){
    if(matrix[row_index][col_index] == 0)
        return true;
    return false;
}

//

auto find_min_in_row(ddvec matrix, int row_index){
    bool is_first_INF = true;
    double min = 0;
    int i = 0;

    while(is_first_INF && i < matrix.size()){
        if(isnan(matrix[row_index][i]) == false) {
            min = matrix[row_index][i];
            is_first_INF = false;
        }
        i++;
    }

    for(i; i < matrix.size(); i++){
        if(isnan(matrix[row_index][i]) == false && matrix[row_index][i] < min)
            min = matrix[row_index][i];
    }
    return min;
}

auto find_min_in_column(ddvec matrix, int column_index){
    bool is_first_INF = true;
    double min = 0;
    int i = 0;

    while(is_first_INF && i < matrix.size()){
        if(isnan(matrix[i][column_index]) == false) {
            min = matrix[i][column_index];
            is_first_INF = false;
        }
        i++;
    }

    for(i; i < matrix.size(); i++){
        if(isnan(matrix[i][column_index]) == false && matrix[i][column_index] < min)
            min = matrix[i][column_index];
    }
    return min;
}

auto find_min_in_row(ddvec matrix, int row_index, int skip_col_index){
    bool is_first_INF = true;
    double min = 0;
    int i = 0;

    while(is_first_INF && i < matrix.size()){
        if(isnan(matrix[row_index][i]) == false && i != skip_col_index) {
            min = matrix[row_index][i];
            is_first_INF = false;
        }
        i++;
    }

    for(i; i < matrix.size(); i++){
        if(isnan(matrix[row_index][i]) == false && matrix[row_index][i] < min && i != skip_col_index)
            min = matrix[row_index][i];
    }
    return min;
}

auto find_min_in_column(ddvec matrix, int column_index, int skip_row_index){
    bool is_first_INF = true;
    double min = 0;
    int i = 0;

    while(is_first_INF && i < matrix.size()){
        if(isnan(matrix[i][column_index]) == false && i != skip_row_index) {
            min = matrix[i][column_index];
            is_first_INF = false;
        }
        i++;
    }

    for(i; i < matrix.size(); i++){
        if(isnan(matrix[i][column_index]) == false && matrix[i][column_index] < min && i != skip_row_index)
            min = matrix[i][column_index];
    }
    return min;
}

auto sum_of_min_in_row_and_column(ddvec &matrix, int row_index, int col_index){
    double min_in_row = find_min_in_row(matrix, row_index, col_index);
    double min_in_col = find_min_in_column(matrix, col_index, row_index);

    return min_in_col + min_in_row;
}

auto best_possible_single_route(ddvec &matrix) {
    static int row_col_index[2] = {-1, -1};
    double row_col_sum = -1;
    for (int row_index = 0; row_index < matrix.size(); row_index++) {
        for (int col_index = 0; col_index < matrix.size(); col_index++) {
            if (is_single_route_possible(matrix, row_index, col_index) && row_col_sum < sum_of_min_in_row_and_column(matrix, row_index, col_index)) {
                row_col_sum = sum_of_min_in_row_and_column(matrix, row_index, col_index);
                row_col_index[0] = row_index;
                row_col_index[1] = col_index;
            }
        }
    }

    for (int row_index = row_col_index[0]; row_index < matrix.size(); row_index++) {
        for (int col_index = row_col_index[1]; col_index < matrix[row_index].size(); col_index++) {
            if (is_single_route_possible(matrix, row_index, col_index) &&
                row_col_sum < sum_of_min_in_row_and_column(matrix, row_index, col_index)) {
                row_col_index[0] = row_index;
                row_col_index[1] = col_index;
                row_col_sum = sum_of_min_in_row_and_column(matrix, row_index, col_index);

            }
        }
    }
    return row_col_index;
}

// row and column reducing functions

void reduce_row(ddvec &matrix, int row_index, double reduction_val){
    for(int i = 0; i < matrix[row_index].size(); i++)
        matrix[row_index][i] -= reduction_val;
}

void reduce_column(ddvec &matrix, int col_index, double reduction_val){
    for(int i = 0; i < matrix.size(); i++)
        matrix[i][col_index] -= reduction_val;
}

double reduce_all_rows_increase_LB(ddvec &matrix){
    double lower_bound = 0;
    for(int row_index = 0; row_index < matrix.size(); row_index++){
        auto min_in_row = find_min_in_row(matrix, row_index);
        reduce_row(matrix, row_index, min_in_row);
        lower_bound += min_in_row;
    }
    return lower_bound;
}

double reduce_all_colsumns_increase_LB(ddvec &matrix){
    double lower_bound = 0;
    for(int col_index = 0; col_index < matrix.size(); col_index++){
        auto min_in_column = find_min_in_column(matrix, col_index);
        reduce_column(matrix, col_index, min_in_column);
        lower_bound += min_in_column;
    }
    return lower_bound;
}

void forbid_routes(ddvec &matrix, int row_index, int col_index){
    for (int index = 0; index < matrix.size(); index++) {
        matrix[row_index][index] = INF;
        matrix[index][col_index] = INF;
    }
    matrix[col_index][row_index] = INF;
}   // to check

void forbid_routes(ddvec &matrix, int* row_col_index) {
    for (int index = 0; index < matrix.size(); index++) {
        matrix[row_col_index[0]][index] = INF;
        matrix[index][row_col_index[1]] = INF;
    }
    matrix[row_col_index[1]][row_col_index[0]] = INF;
}   // to check

// print functions

void print_matrix(ddvec matrix) {
    for (auto row: matrix) {
        for (auto elem: row) {
            std::cout.width(5);
            std::cout << std::internal << elem;
        }
    std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_minimums_of_matrix_rows(ddvec &matrix) {
    std::cout << "Minimums in rows" << std::endl;
    for (int row_index = 0; row_index < matrix.size(); row_index++) {
        std::cout.width(3);
        std::cout << row_index << " : " << find_min_in_row(matrix, row_index) << std::endl;
    }
    std::cout << std::endl;
}

void print_minimums_of_matrix_columns(ddvec &matrix) {
    std::cout << "Minimums in columns" << std::endl;
    for (int col_index = 0; col_index < matrix.size(); col_index++) {
        std::cout.width(3);
        std::cout << col_index << " : " << find_min_in_column(matrix, col_index) << std::endl;
    }
    std::cout << std::endl;
}

bool is_all_huj(ddvec &matrix) {
    for(int row_index = 0; row_index < matrix.size(); row_index++) {
        for (int col_index = 0; col_index < matrix.size(); col_index++) {
            if(!isnan(matrix[row_index][col_index]))
                return false;
        }
    }
    return true;
}

void last_two_routes(ddvec matrix, double &lower_bound) {
    ddvec possible_routes;
    bool is_ok = false;
    lower_bound += reduce_all_rows_increase_LB(matrix);

    if(!is_0_in_each_col_and_row(matrix)){
        lower_bound += reduce_all_colsumns_increase_LB(matrix);
    }

    for(int row_index = 0; row_index < matrix.size(); row_index++) {
        for (int col_index = 0; col_index < matrix.size(); col_index++) {
            if(is_single_route_possible(matrix, row_index, col_index)){
                possible_routes.push_back({(double)row_index,(double)col_index});
            }
        }
    }

    while(!is_ok){
        
    }


}

int** TSP_solver(ddvec matrix){
    int size = matrix.size();
    int* single_route;
    int final_route[size][2];
    double lower_bound = 0;

    lower_bound += reduce_all_rows_increase_LB(matrix);

    std::cout << "all rows reduction, lb = " << lower_bound << std::endl;
    print_matrix(matrix);

    if(!is_0_in_each_col_and_row(matrix)){
        lower_bound += reduce_all_colsumns_increase_LB(matrix);

        std::cout << "all cols reduction, lb = " << lower_bound << std::endl;
        print_matrix(matrix);
    }

    for(int step = 0; step < matrix.size()-2; step++){
        if(!is_0_in_each_col_and_row(matrix)){
            lower_bound += reduce_all_rows_increase_LB(matrix);

            std::cout << "all rows reduction in for loop step = " << step << ", lb = " << lower_bound << std::endl;
            print_matrix(matrix);

            lower_bound += reduce_all_colsumns_increase_LB(matrix);

            std::cout << "all cols reduction in for loop step = " << step << ", lb = " << lower_bound << std::endl;
            print_matrix(matrix);
        }

        single_route = best_possible_single_route(matrix);
        final_route[step][0] = single_route[0];
        final_route[step][1] = single_route[1];
        forbid_routes(matrix, single_route);

        std::cout << "route [" << single_route[0] << "][" << single_route[1] << "] forbidden in step = " << step << std::endl;
        print_matrix(matrix);

    }
    last_two_routes(matrix, lower_bound);
    print_matrix(matrix);

    for(auto i: final_route){
        std::cout << "(" << i[0] << ";" << i[1] << ")\n";
    }
    std::cout << lower_bound;

}

#endif
