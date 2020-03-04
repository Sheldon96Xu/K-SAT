#include "K-SAT.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <climits>
#include <cstdlib>
using namespace std;


KSAT::KSAT(int n, int m, int k, double p, int l, bool show): nVar(n), nCls(m), K(k), prob(p), flipLimit(l), flips(0), showRes(show){}


int KSAT::solve() {
    randomCNF();
    setFalseClauses();
    while (!falseClauses.empty()) {
        if (flips > flipLimit) {
            if (showRes) cout << "UNKNOWN" << endl;
            return -1;
        }
        int f = (int)falseClauses.size();
        int r = rand()%f;
        if ((double)rand()/(RAND_MAX) > prob) {
            chooseFlip(clauses[falseClauses[r]]);
        }
        else {
            int s = rand()%K;
            flip(abs(clauses[falseClauses[r]][s]) - 1);
        }
        setFalseClauses();
    }
    if (showRes) cout << flips<<" Flips"<<endl;
    return flips;
}

void KSAT::randomCNF() {
    for (int i=0; i<nCls; ++i) {
        vector<int> clause;
        unordered_set<int> selected;
        for (int j=0; j<K; ++j) {
            int v = rand()%nVar + 1;
            while (selected.find(v) != selected.end()) {
                v = rand()%nVar + 1;
            }
            int t = rand()%2 * 2 - 1;
            selected.insert(v);
            clause.push_back(t*v);
            literals[t*v].push_back(i);
        }
        clauses.push_back(clause);
    }
    for (int i=1; i<=nVar; ++i) {
        int t = rand()%2 * 2 - 1;
        T.push_back(t*i);
    }
    numSatisfied.resize(nCls);
}


void KSAT::setFalseClauses() {
    falseClauses.clear();
    int count = 0;
    for (int i=0; i<nCls; ++i) {
        for (int l: clauses[i]) {
            if (T[abs(l)-1] == l) ++count;
        }
        if (count == 0) falseClauses.push_back(i);
        numSatisfied[i] = count;
        count = 0;
    }
}

void KSAT::flip(int x) {
    ++flips;
    T[x] *= -1;
}

void KSAT::chooseFlip(vector<int>& C) {
    int pos = -1;
    int maxGain = 1-nCls;
    for (int v: C) {
        int gain = 0, loss = 0;
        for (int u: literals[v]) {
            if (numSatisfied[u] == 0) ++gain;
        }
        for (int u: literals[0-v]) {
            if (numSatisfied[u] == 1) ++loss;
        }
        if (maxGain < gain - loss) {
            maxGain = gain - loss;
            pos = abs(v) - 1;
        }
    }
    
    flip(pos);
}
