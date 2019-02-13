#include "K-SAT.h"
#include <iostream>
using namespace std;

int main()
{
    int k = 3;
    srand(time(nullptr));
    KSAT problem(240, 60, k);
    problem.printClauses();
    try {
        int f = problem.WalkSAT();
        cout << f << " fixes by WalkSAT\n";
    } catch (const char* e) {
        cout << e << endl;
    }
    try {
        int f = problem.Moser();
        cout << f << " fixes by Moser\n";
    } catch (const char* e) {
        cout << e << endl;
    }
}
