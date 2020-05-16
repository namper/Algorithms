#include <iostream>
#include <queue>
#include <functional>
#include <string>
#include <list>
using namespace std;

# define INF 0x3f3f3f3f

# define _e 0
# define _b 1
# define _c 2
# define _d 3
# define _a 4

// def: e: 0, b: 1, c: 2, d: 3, a: 4
typedef pair<int, int> iPair;


class Graph
{
    int V;

    int source;
    int through;
    int through_w;

    list< pair<int, int> > *adj;
    string *path;
    public:
    Graph(int V, int source, int through);
    void addEdge(int u, int v, int w);
    void shortestPath();
};

Graph::Graph(int V, int source, int through)
{   this->V = V;
    adj = new list<iPair>[V];
    path = new string[V];
    this->through = through;
    this->source = source;
    through_w = 0;
}


void Graph::addEdge(int u, int v, int w)
{
    if (u == this->source && v == this->through){
        this->through_w = w;
        w = 0;
    }
    adj[u].push_back(make_pair(v, w));
}


void Graph::shortestPath()
{

    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    vector<int> dist(V, INF);

    pq.push(make_pair(0, this->source));
    dist[this->source] = 0;
    path[this->source] = to_string(_e);

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
     

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {

            int v = (*i).first;
            int weight = (*i).second;

            // relaxation
            if (dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                path[v] = path[u] + to_string(v);
                pq.push(make_pair(dist[v], v));
                }
        }
    }
    
    cout << "Vertex Distance from Source\n" << endl;
    dist[0] -= this->through_w;

    for (int i = 0; i < V; ++i){
        cout << to_string(this->source) << " -> " << i << " Path: " <<path[i] << " W: "<< dist[i] + this->through_w << endl;
        }
}
int main()
{
    int V = 5;
    
    Graph g(V, _e, _b);

    g.addEdge(_e, _b, 2);
    g.addEdge(_e, _c, 4);
    g.addEdge(_e, _d, 3);
    g.addEdge(_b, _c, 1);
    g.addEdge(_b, _d, 2);
    g.addEdge(_d, _a, 6);
    g.addEdge(_a, _b, 3);

    g.shortestPath();

    return 0;
}