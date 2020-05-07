#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> iPair;
struct Graph
{
       int V, E;
       vector < pair<int, iPair> > edges;
       Graph(int V, int E){ this->V = V;
        this->E = E;
        }
       void addEdge(int u, int v, int w)
       {
        edges.push_back({ w,{ u, v } });
       }

       int Kruskal_MST();
};

struct DisjointSets
{
    int *parent, *rnk;
    int n;
    
    DisjointSets(int n){
        this->n = n;
        parent = new int[n];
        rnk = new int[n];

        for(int i=0; i<n; i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    
    int find(int u){
    if (u != parent[u]){ parent[u] = find(parent[u]);}
    return parent[u];
    }

    void Union(int x, int y){
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::Kruskal_MST(){
    int mst_wt = 0; 
    sort(edges.begin(), edges.end());
    DisjointSets ds(V);
    vector< pair<int, iPair> >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v) {
            if (u != V-1 && v != V-1)
                cout << u << " - " << v << endl;
            mst_wt += it->first;
            ds.Union(set_u, set_v);
        }
    }
    return mst_wt;
}

int main() {
    int V = 6, E = 12;
     Graph g(V, E);
    
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 3, 3);
    g.addEdge(0, 4, 6);

    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 3);

    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 2);

    g.addEdge(3, 4, 1);

    // დავამატოთ ნულ წონიანი წიბოები 
    // სადგურებთან  და ჩავატაროთ კრასკალის ალგორითმი
    g.addEdge(5, 3, 0);
    g.addEdge(5, 0, 0);
    cout << "Edges of MST are \n";
    int mst_wt = g.Kruskal_MST();
    cout << "\nWeight of MST is " << mst_wt << endl;
    return 0;
}
