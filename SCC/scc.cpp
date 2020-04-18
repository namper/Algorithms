#include<iostream>
#include<list>

using namespace std;

class Graph{
  int V;
  int time;
  list<int>* start;
  list<int>* finish;
  list<int>* adj;

  // ბმული სია: ტრანსპონირებული გრაფისთვის
  list<int>* adj_T;

  public:
    Graph(int V);
    void addEdge(int x, int y);
    void DFS_VISIT(int v, bool *visited, int *start, int *finish, list<int>& Queue);
    void DFS_VISIT(int v, bool *visited);
    void DFS();
};


Graph::Graph(int V){
  this->V = V;
  adj = new list<int>[V];
  adj_T = new list<int>[V];
}
void Graph::addEdge(int x, int y){
  adj[x].push_back(y);

  // ტრანსონირებისთვის
  adj_T[y].push_back(x);
}

void Graph::DFS_VISIT(int v, bool *visited, int *start, int *finish, list<int>& Queue){
  // რეკურსიული ვიზიტი
  visited[v] = true;
  time += 1;
  start[v] = time;
  for(auto i = adj[v].begin(); i != adj[v].end(); i++){
    if (!visited[*i]){ DFS_VISIT(*i, visited, start, finish, Queue);}
  }
  time += 1;
  finish[v] = time;
  
  Queue.push_front(v);
}

void Graph::DFS_VISIT(int v, bool *transponse_visited){
  transponse_visited[v] = true;
  cout << v << " ";
  for(auto i = adj_T[v].begin(); i != adj_T[v].end(); i++){  
    if (!transponse_visited[*i]){DFS_VISIT(*i, transponse_visited);} 
  }
}

void Graph::DFS(){
  list<int> Queue;

  // საწყისი მონაცემები DFS ისთვის
  bool *visited = new bool[V];
  bool *transponse_visited = new bool[V];
  int *start = new int[V];
  int *finish = new int[V];
  time = 0;
  for(int i=0; i < V; i++){ 
    visited[i] = false;
    transponse_visited[i] = false;
    }

  // სიღმერში ძებნა
  for(int i=0; i < V; i++){ if(!visited[i]){ DFS_VISIT(i, visited, start, finish, Queue);} }

  // სიღმრეში ძებნა ტრანსპონირებული გრაფისთვის
  int counter = 1;
  for(auto node: Queue){
    if(!transponse_visited[node]){
      cout << "ძლიერად ბმული კომპონენტი " << counter << " : { ";
      DFS_VISIT(node, transponse_visited);
      cout << "}" << endl;
      counter += 1;
      }
  }
}

int main(){
  // ა - 0, ბ - 1, ც - 2, დ - 3, ე - 4, ფ - 5
  Graph g(6);
  // ბ -> ც , დ
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  // ც - ე, ფ
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  // დ -> ა, ე
  g.addEdge(3, 0);
  g.addEdge(3, 4);
  // ე - ბ 
  g.addEdge(4, 1);
  g.DFS();
  return 0;
}