//
//  K-SAT.h
//  K-SAT research
//
//  Created by Sheldon Xu on 2019/2/7.
//  Copyright © 2019 Sheldon Xu. All rights reserved.
//

#ifndef K_SAT_h
#define K_SAT_h
#endif /* K_SAT_h */
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class KSAT
{
    bool showRes;
    int nVar, nCls, K, flips, flipLimit;
    double prob;
    vector<vector<int>> clauses;
    unordered_map<int, vector<int>> literals; //where each literal is located, by clause
    vector<int> T, falseClauses, numSatisfied; //number of satisfied literals each clause
public:
    KSAT(int n, int m, int k, double p, int l, bool show);
    
    int solve();
    
    void randomCNF();
            
    void setFalseClauses();
        
    void flip(int x);
    
    void chooseFlip(vector<int>&C);
};
