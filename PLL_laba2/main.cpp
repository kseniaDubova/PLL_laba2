#include <fstream>
#include <vector>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string>
using namespace std;

void create_file_matrix(string file_name, const vector<vector<int>>& matrix) {
    ofstream out(file_name);
    for (const auto& row : matrix) {
        for (int val : row) {
            out << " " << val;
        }
        out << endl;
    }
}

void create_matrix(string file_name, int size) {
    vector<vector<int>> m(size, vector<int>(size));
    for (auto& row : m) {
        for (int& val : row) {
            val = rand() % 500;
        }
    }
    create_file_matrix(file_name, m);
}

void read_matrix(vector<vector<int>>& matrix, string file_name) {
    ifstream data(file_name);
    for (auto& row : matrix) {
        for (int& val : row) {
            data >> val;
        }
    }
}

void mul_matrix(const vector<vector<int>>& matrix_1, const vector<vector<int>>& matrix_2, vector<vector<int>>& matrix_result) {
    omp_set_num_threads(8);
    int i, j, k;
#pragma omp parallel for shared(matrix_1, matrix_2, matrix_result) private(i,j,k)
    for (i = 0; i < matrix_result.size(); i++) {
        for (j = 0; j < matrix_result[i].size(); j++) {
            matrix_result[i][j] = 0;
            for (k = 0; k < matrix_2.size(); k++) {
                matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
}

void write_result(string str, const vector<vector<int>>& matrix_result, double duration, string arr) {
    ofstream data(str);
    for (const auto& row : matrix_result) {
        for (int val : row) {
            data << " " << val;
        }
        data << endl;
    }
    ofstream result("result_8.txt", ios::app);
    result << "Размер: " << matrix_result.size() << " Время: " << duration << " секунд" << endl << arr << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));
    int SIZE[9] = { 100, 300, 500, 800, 1000, 1300, 1500, 1800, 2000};

    for (int i = 0; i < 9; i++)
    {
        vector<vector<int>> matrix_1(SIZE[i], vector<int>(SIZE[i]));
        vector<vector<int>> matrix_2(SIZE[i], vector<int>(SIZE[i]));
        vector<vector<int>> matrix_result(SIZE[i], vector<int>(SIZE[i]));

        create_matrix("Matrix_1.txt", SIZE[i]);
        create_matrix("Matrix_2.txt", SIZE[i]);

        read_matrix(matrix_1, "Matrix_1.txt");
        read_matrix(matrix_2, "Matrix_2.txt");
        double result = 0;
        string arr;

        for (int i = 0; i < 10; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            mul_matrix(matrix_1, matrix_2, matrix_result);
            auto end = chrono::high_resolution_clock::now();
            double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
            result += duration;
            arr.append(to_string(duration) + "  ");
        }

        result /= 10;
        cout << "Количество ядер: " << omp_get_max_threads() << endl;
        write_result("Matrix_res.txt", matrix_result, result, arr);
    }
}