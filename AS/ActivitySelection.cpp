#include<iostream>
#include <vector>

using namespace std;

void printSolution(vector <int> A)
{   
    cout<<"ამორჩეული განცხადებების ნომერებია:  ";
    vector <int> :: iterator it; 
    for(it = A.begin(); it != A.end(); ++it) 
        cout <<*it<<" "; 
    cout << endl;
}

void GreedySelector(vector<int> s, vector<int> f) 
{ 
  int n = s.size();
  if(n == f.size()){
      int i = 0;
      vector <int> A;
      A.push_back(i);

    for (int j = 1; j < n; j++) 
    { 
          if (s[j] >= f[i]) 
          { 
              A.push_back(j);
              i = j; 
          } 
    } 
      printSolution(A);
  }else{
    cout << "არასოწრი მონაცემები" << endl;
  }
} 

int main() 
{   
	vector<int> s = {1, 3, 2, 5, 8, 5, 10}; 
	vector<int> f = {3, 7, 8, 9, 10, 12, 14}; 
	GreedySelector(s, f); 
	return 0; 
} 
