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

/**
 * Lista, dentro de uma região (top,left,h,w), todos os sub‑retângulos de maior área
 * excluindo quadrados e o retângulo inteiro da região.
 */
static vector<Subrect> listLargestSubrectanglesInRegion(int top, int left, int h, int w) {
    vector<Subrect> out;
    if (h <= 0 || w <= 0) return out;

    long long bestArea = -1;

    for (int r = 1; r <= h; ++r) {
        for (int c = 1; c <= w; ++c) {
            if (r == c) continue;            // exclui quadrados
            if (r == h && c == w) continue;  // exclui a região inteira
            long long area = 1LL * r * c;

            if (area > bestArea) {
                bestArea = area;
                out.clear();
                for (int ti = 0; ti + r <= h; ++ti)

                    for (int lj = 0; lj + c <= w; ++lj)

                        out.emplace_back(r, c, top + ti, left + lj);

            } else if (area == bestArea) {
                for (int ti = 0; ti + r <= h; ++ti)

                    for (int lj = 0; lj + c <= w; ++lj)

                        out.emplace_back(r, c, top + ti, left + lj);
            }
        }
    }
    return out;
}




int main() {


    
}