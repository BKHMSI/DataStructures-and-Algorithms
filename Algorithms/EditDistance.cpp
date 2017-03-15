//
//  main.cpp
//  CSE373
//
//  Created by Badr AlKhamissi on 10/27/16.
//  Copyright © 2016 Badr AlKhamissi. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <limits.h>
#include <iomanip>

using namespace std;

struct cell{
    int cost;
    int parent;
    cell(){cost = 0;}
    cell(int c, int p){
        cost = c;
        parent = p;
    }
};

cell **dp;
#define MATCH  0
#define INSERT 1
#define DELETE 2

void dispMatrix(int n, int m){
    for(int i = 0; i<=n; i++)
        for(int j = 0; j<=m; j++)
            cout<<setw(2)<<dp[i][j].cost<<(j==m)[" \n"];
}

int editDistance(string s, string t){
    int opt[3];
    int n = (int)s.length(), m = (int)t.length();
    for(int i = 0; i<=n; i++)
        dp[i][0] = cell(i,DELETE);
    for(int i = 0; i<=m; i++)
        dp[0][i] = cell(i,INSERT);
    
    dp[0][0].parent = -1;
    
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            // Match
            opt[MATCH] = dp[i-1][j-1].cost + (s[i-1] != t[j-1]);
            // Insert
            opt[INSERT] = dp[i][j-1].cost + 1;
            // Delete
            opt[DELETE] = dp[i-1][j].cost + 1;
            
            dp[i][j] = cell(opt[MATCH],MATCH);
            
            for(int k = INSERT; k<=DELETE; k++)
                if(opt[k] < dp[i][j].cost)
                    dp[i][j] = cell(opt[k],k);
        }
    }
    
    return dp[n][m].cost;
}

void reconstructPath(string s, string t,int i, int j){
    if(dp[i][j].parent == -1) return;
    if(dp[i][j].parent == MATCH){
        reconstructPath(s,t,i-1, j-1);
        cout<<(s[i-1] == t[j-1] ? "M":"S");
        return;
    }
    if(dp[i][j].parent == INSERT){
        reconstructPath(s,t,i, j-1);
        cout<<"I";
        return;
    }
    if(dp[i][j].parent == DELETE){
        reconstructPath(s,t,i-1, j);
        cout<<"D";
        return;
    }
}

int main(int argc, const char * argv[]) {
    
    string s,t;
    getline(cin,s);
    getline(cin,t);
    
    dp = new cell*[(int)s.length()+1];
    for(int i = 0; i<=s.length(); i++)
        *(dp+i) = new cell[(int)t.length()+1];
    
    cout<<"Edit Distance from \""<<s<<"\" to \""<<t<<"\" is: ";
    cout<<editDistance(s,t)<<endl;
    
    reconstructPath(s,t,(int)s.length(),(int)t.length());
    cout<<endl;
    
    
    return 0;
}


