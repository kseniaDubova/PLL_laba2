
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;


void create_file_matrix(string file_name, const vector<vector<int>>& matrix)
{
    ofstream out;
    out.open(file_name);
    if (out.is_open())
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                out << " " << matrix[i][j];
            }
            out << endl;
        }
    }
    out.close();
}

void create_matrix(string file_name, int size)
{
    vector<vector<int>> m(size, vector<int>(size));

    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m.size(); j++)
        {
            m[i][j] = rand() % 500;
        }
    }
    create_file_matrix(file_name, m);
}
void read_matrix(vector<vector<int>>& matrix, int size, string file_name)
{
    ifstream data;
    data.open(file_name);

    if (data.is_open())
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                data >> matrix[i][j];
            }
        }
    }
    data.close();

}

void mul_matrix(const vector<vector<int>>& matrix_1, const vector<vector<int>>& matrix_2, vector<vector<int>>& matrix_result)
{
    for (int i = 0; i < matrix_result.size(); i++)
    {
        for (int j = 0; j < matrix_result[i].size(); j++)
        {
            matrix_result[i][j] = 0;
            for (int k = 0; k < matrix_2.size(); k++)
            {
                matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }

        }
    }
}
void write_result(string str, vector<vector<int>>& matrix_result, int size, clock_t end, clock_t start)
{
    ofstream data(str);
    ofstream result("result.txt", ios::app);


    for (int i = 0; i < matrix_result.size(); i++)
    {
        for (int j = 0; j < matrix_result[i].size(); j++)
        {
            data << " " << matrix_result[i][j];
        }
        data << endl;
    }

    result << "Размер: " << size << " Время: " << (double(end - start)) / (double(CLOCKS_PER_SEC)) << endl;
    data.close();
    result.close();
}

int main()
{
    srand(time(NULL));
    int SIZE = 10;
    vector<vector<int>> matrix_1(SIZE, vector<int>(SIZE));
    vector<vector<int>> matrix_2(SIZE, vector<int>(SIZE));
    vector<vector<int>> matrix_result(SIZE, vector<int>(SIZE));
    create_matrix("Matrix_1.txt", SIZE);
    create_matrix("Matrix_2.txt", SIZE);
    read_matrix(matrix_1, SIZE, "Matrix_1.txt");
    read_matrix(matrix_2, SIZE, "Matrix_2.txt");

    clock_t start, end;
    start = clock();
    mul_matrix(matrix_1, matrix_2, matrix_result);
    end = clock();


    write_result("Matrix_res.txt", matrix_result, SIZE, end, start);

}
