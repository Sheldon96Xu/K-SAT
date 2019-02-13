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
#include <set>
#include <unordered_map>
using namespace std;

class KSAT
{
    int nCls, nVar, K, walksatFixes, moserFixes;
    vector<bool> walksatResult, moserResult;
    vector<vector<int>> clauses;
    unordered_map<int, vector<int>> literals; //where each literal is located, by clause
    vector<vector<int>> dependancies; //map of each clause and its dependent neighbours
    stack<int> walkSATStack;
    stack<int> moserStack;
public:
    KSAT(int m, int n, int k);
    
    void printLiterals();
    
    void printClauses();
    
    void printAnswer(vector<bool> &result);
    
    bool Violated(int c, vector<bool> &result);
    
    int findFirstViolation(vector<int> &clauses, vector<bool> &result);
    
    void fixOne(int m); //flip a random variable in clause m
        
    void fixAll(int m);//randomly flip all truth values for variables in clause m
    
    int WalkSAT();
    
    int Moser();
};
