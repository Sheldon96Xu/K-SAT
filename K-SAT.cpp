#include "K-SAT.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <climits>
#include <cstdlib>
using namespace std;


KSAT::KSAT(int m, int n, int k): nCls(m), nVar(n), K(k), walksatFixes(0), moserFixes(0) {
    //randomly assign truth values
    //randomly generate k-CNF
    for (int i = 1; i < n; i++) {
        bool val = rand() % 2;
        walksatResult.push_back(val);
        moserResult.push_back(val);
    }
    for (int i = 0; i < m; i++) {
        vector<int> clause;
        set<int> varIndices;
        for (int s = 0; s < k;) {
            int r = rand() % n;
            if (varIndices.find(r) == varIndices.end()) {
                varIndices.insert(r);
                if (rand() % 2) { //random negation
                    clause.push_back(r+1);
                }
                else {
                    clause.push_back(-r-1);
                }
                literals[r].push_back(i);
                ++s;
            }
        }
        //varIndicesAll.push_back(varIndices);
        clauses.push_back(clause);
        
    }
    for (int i = 0; i < nCls; i++) { //generate dependancies
        vector<int> neighbours;
        set<int> s;
        for (int j = 0; j < K; j++) {
            for (int n : literals[abs(clauses[i][j]) - 1]) {
                s.insert(n);
            }
        }
        neighbours.assign(s.begin(), s.end());
        dependancies.push_back(neighbours);
    }
    
}

void KSAT::printLiterals() {
    for (int i = 0; i < nVar; i++) {
        for (auto t : literals[i]) {
            cout << t << ' ';
        }
        cout << endl;
    }
}

void KSAT::printClauses() {
    for (int i = 0; i < nCls; i++) {
        for (int c = 0; c < K; c++) {
            cout << clauses[i][c] << ' ';
        }
        cout << endl;
    }
}

void KSAT::printAnswer(vector<bool> &result) {
    for (int i = 0; i < nVar; i++) {
        if (!result[i]) cout << '-';
        cout << i+1 << ' ';
    }
    cout << endl;
}

bool KSAT::Violated(int c, vector<bool> &result) {
    for (int i = 0; i < K; i++) {
        if ((clauses[c][i] > 0 && result[clauses[c][i] - 1] == true) ||
            (clauses[c][i] < 0 && result[-1 - clauses[c][i]] == false)) {
            return false;
        }
    }
    return true;
}

int KSAT::findFirstViolation(vector<int> &clauses, vector<bool> &result) {
    for (int n : clauses) {
        if (Violated(n, result)) {
            return n;
        }
    }
    return -1;
}

void KSAT::fixOne(int m) {
    while (1) {
        if (walksatFixes == INT_MAX) {
            throw "Fix limit exceeded -- WalkSAT!";
        }
        if (walksatFixes && walksatFixes % 5000000 == 0) {
            cout << walksatFixes << " fixes done\n";
        }
        int flipRand = abs(clauses[m][rand() % K]) - 1; //flipRand is the index of the variable (in all vars) flipped
        walksatResult[flipRand] = !walksatResult[flipRand];
        ++walksatFixes;
        walkSATStack.push(flipRand);
        m = findFirstViolation(literals[flipRand], walksatResult);
        while (m < 0) {
            walkSATStack.pop();
            if (!walkSATStack.empty()) {
                m = findFirstViolation(literals[walkSATStack.top()], walksatResult);
            }
            else {
                return;
            }
        }
    }
}

void KSAT::fixAll(int m) { 
    while (1) {
        if (moserFixes == INT_MAX) {
            throw "Fix limit exceeded -- Moser!";
        }
        if (moserFixes && moserFixes % 5000000 == 0) {
            cout << moserFixes << " fixes done\n";
        }
        int flipInd;
        for (int i = 0; i < K; i++) {
            if (rand() % 2) {
                flipInd = abs(clauses[m][i]) - 1;
                moserResult[flipInd] = !moserResult[flipInd];
            }
        }
        ++moserFixes;
        moserStack.push(m);
        m = findFirstViolation(dependancies[m], moserResult);
        while (m < 0) {
            moserStack.pop();
            if (!moserStack.empty()) {
                m = findFirstViolation(dependancies[moserStack.top()], moserResult);
            }
            else {
                return;
            }
        }
    }
}

int KSAT::WalkSAT() {
    for (int i = 0; i < nCls; i++) {
        if (Violated(i, walksatResult)) {
            fixOne(i);
        }
    }
    printAnswer(walksatResult);
    return walksatFixes;
}

int KSAT::Moser() {
    for (int i = 0; i < nCls; i++) {
        if (Violated(i, moserResult)) {
            fixAll(i);
        }
    }
    printAnswer(moserResult);
    return moserFixes;
}
