#include <iostream>
#include <climits>
#include <iomanip>
using namespace std;


#define N 5


void printSolution(int dist[N][N])
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (dist[i][j] == INT_MAX) cout << setw(5) << "inf";
            else cout<< setw(5)<< dist[i][j];}
        cout << endl;
        }
}


void FloydWarshell(int Graph[N][N])
{
    int T[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){ 
            int t = 0;
            if ((i == j) ||
             (Graph[i][j] != INT_MAX && Graph[i][j] != INT_MAX ))
                t = 1;
            T[i][j] = t;
        }
    }


    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                T[i][j] = T[i][j] || (T[i][k] && T[k][j] );
            }
        }
    }
    printSolution(T);
}
int main()
{
    int Graph[N][N] ={
        { 1, INT_MAX, INT_MAX, 1, INT_MAX}, // a -> d
        { INT_MAX, 1, INT_MAX, INT_MAX, 1}, // b -> e 
        { INT_MAX, 1, 1, INT_MAX, INT_MAX}, // c -> b
        { INT_MAX, 1, INT_MAX, 1, INT_MAX}, // d -> b 
        { INT_MAX, INT_MAX, INT_MAX, 1, 1}, // e -> d
    };
    FloydWarshell(Graph);
    return 0;
}