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
static vector<Subrect> listLargestSubrectanglesInRegion(int top, int left, int rows, int cols) {
    vector<Subrect> out;
    if (rows <= 0 || cols <= 0) return out;

    long bestArea = -1;

    for (int r = 1; r <= rows; ++r) {
        for (int c = 1; c <= cols; ++c) {
            if (r == c) 
                continue;

            if (r == rows && c == cols) 
                continue;

            long area = 1LL * r * c;

            if (area > bestArea) {
                bestArea = area;
                out.clear();

                for (int ti = 0; ti + r <= rows; ++ti)
                    for (int lj = 0; lj + c <= cols; ++lj)

                        out.emplace_back(r, c, top + ti, left + lj);

            } else if (area == bestArea) {

                for (int ti = 0; ti + r <= rows; ++ti)
                    for (int lj = 0; lj + c <= cols; ++lj)
                        out.emplace_back(r, c, top + ti, left + lj);
            }
        }
    }
    return out;
}

static Subrect makeSubrect(const vector<vector<int>>& matriz,
                           int top, int left, int rows, int cols,
                           bool copyCells = true) {

    Subrect s(rows, cols, top, left);

    int sum = 0;

    int bound = 0;

    if (copyCells) s.cells.assign(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            int v = matriz[top + i][left + j];
            sum += v;

            if (v > 0) bound += v;

            if (copyCells) s.cells[i][j] = v;
        }
    }

    s.sum = sum;

    s.bound = bound;

    return s;
}

static void exploreBnB(const vector<vector<int>> matriz, const Subrect& node, Subrect& best) {

    Subrect cur = makeSubrect(matriz, node.top, node.left, node.rows, node.cols, false);

    if (cur.bound <= best.sum) 
        return;

    // Melhor
    if (cur.sum > best.sum) {

        best = makeSubrect(matriz, node.top, node.left, node.rows, node.cols, true);
        
    }

    // Filhos
    auto children = listLargestSubrectanglesInRegion(node.top, node.left, node.rows, node.cols);
    
    for (auto& ch : children)
        exploreBnB(matriz, ch, best);
}

static Subrect branchAndBound(const vector<vector<int>>& A) {

    int Rows = (int)A.size();

    int Cols = Rows ? (int)A[0].size() : 0;

    Subrect best;

    best.sum = std::numeric_limits<int>::min();//menor valor possível

    if (Rows == 0 || Cols == 0) 
        return best;

    auto roots = listLargestSubrectanglesInRegion(0, 0, Rows, Cols);

    for (auto& r : roots)
        exploreBnB(A, r, best);

    return best;
}


int main() {
    int R = 15, C = 15;

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

    Subrect best = branchAndBound(A);

    if (best.rows == 0) {
        cout << "Nenhum sub-retangulo.\n";
        return 0;
    }

    cout << "Melhor:\n";
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