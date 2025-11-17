#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Subrect {
    int rows;
    int cols;
    int top;   // linha do canto superior esquerdo
    int left;  // coluna do canto superior esquerdo
    vector<vector<int>> cells;
    int sum; // soma real do nó
    int bound; // soma dos positivos (limite superior)

    Subrect() : rows(0), cols(0), top(0), left(0), sum(0), bound(0) {}

    Subrect(int rows, int cols, int top, int left)
        : rows(rows), cols(cols), top(top), left(left), sum(0), bound(0){}
};

Subrect BruteForce(const vector<vector<int>>& matriz) {
    int R = (int)matriz.size();
    int C = R ? (int)matriz[0].size() : 0;
    Subrect best;
    best.sum = std::numeric_limits<int>::min();

    for (int top = 0; top < R; ++top) {
        for (int left = 0; left < C; ++left) {
            for (int bottom = top; bottom < R; ++bottom) {
                for (int right = left; right < C; ++right) {

                    int rows = bottom - top + 1;
                    int cols = right - left + 1;

                    if (rows == cols) continue; // ignorar quadrados

                    int currentSum = 0;
                    int posSum = 0;

                    for (int i = top; i <= bottom; ++i) {
                        for (int j = left; j <= right; ++j) {
                            int v = matriz[i][j];
                            currentSum += v;
                            if (v > 0) posSum += v;
                        }
                    }

                    if (currentSum > best.sum) {
                        best.rows = rows;
                        best.cols = cols;
                        best.top = top;
                        best.left = left;
                        best.sum = currentSum;
                        best.bound = posSum;
                        best.cells.assign(rows, vector<int>(cols));
                        for (int i = 0; i < rows; ++i)
                            for (int j = 0; j < cols; ++j)
                                best.cells[i][j] = matriz[top + i][left + j];
                    }
                }
            }
        }
    }

    return best;
}

int main() {

    int R = 40, C = 40;
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-10, 10);

    vector<vector<int>> A(R, vector<int>(C));

    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            A[i][j] = dist(rng);

    cout << "Matriz (" << R << "x" << C << "):\n";
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) cout << setw(3) << A[i][j] << ' ';
        cout << '\n';
    }

    cout << '\n';

    Subrect best = BruteForce(A);

    if (best.rows == 0) {
        cout << "Nenhum sub-retangulo (após excluir quadrados).\n";
        return 0;
    }

    cout << "Melhor sub-retangulo (brute force):\n";
    cout << "sum=" << best.sum
         << " bound=" << best.bound
         << " rows=" << best.rows
         << " cols=" << best.cols
         << " top="  << best.top
         << " left=" << best.left << "\n";

    for (int i = 0; i < best.rows; ++i) {
        for (int j = 0; j < best.cols; ++j)
            cout << setw(3) << best.cells[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}