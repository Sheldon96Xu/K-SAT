/* This file was intended for variable-controlling experiments */

#include "K-SAT.h"
#include <iostream>
using namespace std;

int main()
{
    int k = 3;
    srand(time(nullptr));
    vector<double> succeed;
    vector<double> avgFlip;
    int round = 80;
    
    // Different densities
    vector<double> density {4.26,4.27,4.28,4.29,4.3};
    for (double d : density) {
        for (int n = 50; n<301; n+=50) {
            int c = 0, flips = 0;
            int m = d * n;
            for (int i=0; i<round; ++i) {
                KSAT problem(n, m, k, 0.5, 500000, false);
                int f = problem.solve();
                c += (f >= 0);
                flips += (f >= 0) * f;
            }
            double p = (double)c/round;
            double t = (double)flips/c;
            succeed.push_back(p);
            avgFlip.push_back(t);
            cout << "n: " << n << "; Success prob: " << p << "; Average flips: " << t << endl;
        }
        cout << d << ":\n";
        for (double i: succeed) cout << i << ',';
        cout << endl;
        for (double i: avgFlip) cout << i << ',';
        cout << endl;
    }
    
    // Different heuristics: greedy index
    round = 100;
    vector<double> h {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1};
    succeed.clear();
    for (double p: h) {
        int c = 0;
        for (int i=0; i<round; ++i) {
            KSAT problem(50, 200, k, p, 50000);
            c += problem.solve()>=0;
        }
        double r = (double)c/round;
        cout << "Random select prob: " << p << ", success rate: " << r << endl;
        succeed.push_back(r);
    }
    for (double i: succeed) cout << i << ',';
    cout << endl;
}
