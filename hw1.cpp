#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
//
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Open failed!\n";
        return 1;
    }

    cin.rdbuf(fin.rdbuf());

    int r, c;
    char x;
    const double EPS = 1e-9;

    while (cin >> r >> x >> c) {
        double arr[10][10], brr[10][10];
        int ppr1[10], ppr2[10];
        for (int i = 0; i < 10; ++i) {
            ppr1[i] = -1;
            ppr2[i] = -1;
        }
        bool temp[10] = {};
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                cin >> arr[i][j];
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                cin >> brr[i][j];

        int i1 = 0;
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < r; ++k) {
                if (fabs(arr[k][j]) < EPS || temp[k]) 
                    continue;
                for (int l = j; l < c; ++l) 
                    arr[k][l] /= arr[k][j];
                for (int a = k - 1; a >= 0; --a) {
                    double t = -arr[a][j];
                    for (int b = j; b < c; ++b) 
                        arr[a][b] += arr[k][b] * t;
                }
                for (int a = k + 1; a < r; ++a) {
                    double t = -arr[a][j];
                    for (int b = j; b < c; ++b) 
                        arr[a][b] += arr[k][b] * t;
                }
                temp[k] = 1;
                ppr1[i1] = k;
                ++i1;
                break;
            }
        }

        for (int h = 0; h < 10; ++h) 
            temp[h] = 0;

        int i2 = 0;
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < r; ++k) {
                if (fabs(brr[k][j]) < EPS || temp[k]) 
                    continue;
                for (int l = j; l < c; ++l) 
                    brr[k][l] /= brr[k][j];
                for (int a = k - 1; a >= 0; --a) {
                    double t = -brr[a][j];
                    for (int b = j; b < c; ++b) 
                        brr[a][b] += brr[k][b] * t;
                }
                for (int a = k + 1; a < r; ++a) {
                    double t = -brr[a][j];
                    for (int b = j; b < c; ++b) 
                        brr[a][b] += brr[k][b] * t;
                }
                temp[k] = 1;
                ppr2[i2] = k;
                ++i2;
                break;
            }
        }

        ////////////////////

        int rankA = i1;
        int rankB = i2;

        bool equal = true;
        if (rankA != rankB) equal = false;
        else {
            for (int t = 0; t < rankA && equal; ++t) {
                int ra = ppr1[t];
                int rb = ppr2[t];
                for (int j = 0; j < c; ++j) {
                    double va = arr[ra][j];
                    double vb = brr[rb][j];
                    if (fabs(va - vb) > EPS) { 
                        equal = false; break; 
                    }
                }
            }
        }

        if (equal) cout << "Yes," << rankA << endl;
        else cout << "No," << rankA << "," << rankB << endl;
    }
    return 0;
}
