#ifndef _TSP_ALGORITHM_
#define _TSP_ALGORITHM_

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <sstream>

#define INF (NAN)

using dvec = std::vector<double>;
using ddvec = std::vector<std::vector<double>>;
using ivec = std::vector<int>;
using iivec = std::vector<std::vector<int>>;

// bool flags

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

// min max operations

double find_min_in_row(ddvec matrix, int row_index){
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

double find_min_in_column(ddvec matrix, int column_index){
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

double find_min_in_row(ddvec matrix, int row_index, int skip_col_index){
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

double find_min_in_column(ddvec matrix, int column_index, int skip_row_index){
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

double sum_of_min_in_row_and_column(ddvec &matrix, int row_index, int col_index){
    double min_in_row = find_min_in_row(matrix, row_index, col_index);
    double min_in_col = find_min_in_column(matrix, col_index, row_index);

    return min_in_col + min_in_row;
}

// row and column reduction

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

double reduce_all_columns_increase_LB(ddvec &matrix){
    double lower_bound = 0;
    for(int col_index = 0; col_index < matrix.size(); col_index++){
        auto min_in_column = find_min_in_column(matrix, col_index);
        reduce_column(matrix, col_index, min_in_column);
        lower_bound += min_in_column;
    }
    return lower_bound;
}

// filling forbidden routes with INF

void forbid_routes(ddvec &matrix, ivec row_col_index) {
    for (int index = 0; index < matrix.size(); index++) {
        matrix[(int)row_col_index[0]][index] = INF;
        matrix[index][(int)row_col_index[1]] = INF;
    }
    matrix[(int)row_col_index[1]][(int)row_col_index[0]] = INF;
}

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

void print_matrix(iivec matrix) {
    for (auto row: matrix) {
        for (auto elem: row) {
            std::cout.width(5);
            std::cout << std::internal << elem;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_path(ivec path) {
    std::cout << "{ ";
    for (auto elem: path)
        std::cout << elem << " ";
    std::cout << "}" << std::endl;
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

// choosing best routes

void last_two_routes(ddvec matrix, double &lower_bound, iivec &final_route) {
    iivec possible_routes;
    bool is_ok = false;
    lower_bound += reduce_all_rows_increase_LB(matrix);

    if(!is_0_in_each_col_and_row(matrix)){
        lower_bound += reduce_all_columns_increase_LB(matrix);
    }

    for(int row_index = 0; row_index < matrix.size(); row_index++) {
        for (int col_index = 0; col_index < matrix.size(); col_index++) {
            if(is_single_route_possible(matrix, row_index, col_index)){
                possible_routes.push_back({row_index,col_index});
            }
        }
    }

    for(int first_route = 0; first_route < possible_routes.size()-1; first_route++ ) {
        for(int second_route = first_route + 1; second_route < possible_routes.size(); second_route++) {
            if(possible_routes[first_route][0] != possible_routes[second_route][0] &&
               possible_routes[first_route][1] != possible_routes[second_route][1]) {
                final_route.push_back(possible_routes[first_route]);
                final_route.push_back(possible_routes[second_route]);
            }
        }
    }
}

ivec best_possible_single_route(ddvec &matrix) {
    ivec row_col_index{-1, -1};
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

/*
void last_two(ddvec &matrix, double &lower_bound, iivec &final_route) {
    int non_INF_neighbours;
    for (int row_index = 0; row_index < matrix.size(); row_index++) {
        non_INF_neighbours = 0;
        for (int col_index = 0; col_index < matrix.size(); col_index++) {
            if (isnan(matrix[row_index][col_index])) {
                if (row_index > 0 && row_index < 4) {
                    if (col_index > 0 && col_index < 4) {
                        (!isnan(matrix[row_index][col_index-1]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //left
                        (!isnan(matrix[row_index][col_index+1]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //right
                        (!isnan(matrix[row_index-1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //above
                        (!isnan(matrix[row_index+1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //under
                    }else if(col_index == 0){
                        (!isnan(matrix[row_index][col_index+1]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //right
                        (!isnan(matrix[row_index-1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //above
                        (!isnan(matrix[row_index+1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //under
                    }else(col_index == 4){
                        (!isnan(matrix[row_index][col_index-1]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //left
                        (!isnan(matrix[row_index-1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //above
                        (!isnan(matrix[row_index+1][col_index]) ? non_INF_neighbours++ : non_INF_neighbours+=0); //under
                    }
                }else if(row_index == 0){

                }
            }
        }
    }
}
*/

// TSP_solver and Wrapper

std::vector<int> sort_path(iivec &unsorted_path) {
    int first_node, current_node;
    std::vector<int> sorted_path;
    for(auto route: unsorted_path) {
        if(route[0] == 0){
            first_node = (int)route[0];
            current_node = (int)route[1];
            sorted_path.push_back(first_node +1);
            sorted_path.push_back(current_node +1);
            break;
        }
    }

    while(first_node != current_node) {
        for(auto route: unsorted_path){
            if((int)route[0] == current_node) {
                current_node = (int)route[1];
                sorted_path.push_back(current_node +1);
            }
        }
    }
    return sorted_path;
}

iivec TSP_solver(ddvec matrix, double &lower_bound) {
    ivec single_route;
    iivec final_route;
    lower_bound = 0;

    lower_bound += reduce_all_rows_increase_LB(matrix);

    if(!is_0_in_each_col_and_row(matrix)) {
        lower_bound += reduce_all_columns_increase_LB(matrix);
    }

    for(int step = 0; step < matrix.size()-2; step++){
        if(!is_0_in_each_col_and_row(matrix)){
            lower_bound += reduce_all_rows_increase_LB(matrix);
            lower_bound += reduce_all_columns_increase_LB(matrix);
        }
        single_route = best_possible_single_route(matrix);
        final_route.push_back(single_route);
        forbid_routes(matrix, single_route);
    }

    last_two_routes(matrix, lower_bound, final_route);
    return final_route;
}

std::vector<int> tsp(ddvec &matrix) {
    double lower_bound;
    iivec unsorted_path = TSP_solver(matrix, lower_bound);
    std::cout << "The lower bound is = " << lower_bound << std::endl;
    return sort_path(unsorted_path);
}


#endif
