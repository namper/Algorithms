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

typedef pair<int, int> iPair;

struct Tuple{
    int weight;
    string path;

    bool validate(){
        return weight != INF && !path.empty();
    }
};


class Graph
{
    int V;
    int source;
    int through;
    list< pair<int, int> > *adj;

    public:
        Graph(int V, int source, int through);
        void addEdge(int u, int v, int w);
        void executeSolution();
        void shortestPath(int s, string startingPath, int add_w);
        Tuple findShortestPath(int s, int t);
};

Graph::Graph(int V, int source, int through)
{   
    this->V = V;
    this->through = through;
    this->source = source;

    adj = new list<iPair>[V];

}


void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
}


Tuple Graph::findShortestPath(int s, int t){
    // უმოკლესი გზა საწყისიდან გამავლ წვერომდე
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    vector<int> dist(V, INF);
    vector<string> path(V);

    pq.push(make_pair(0, s));
    dist[s] = 0;
    path[s] = to_string(s);

    int u  = s;
    // თუ რიგიდან გამოვიდა t, ეი ნაპოვნია უმოკლესი გზა s დან  t-მდე და შევწყვიტავთ დეისქტრას ალგორითმს
    while (!pq.empty() && u != t)
    {
        u = pq.top().second;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
            if (dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                path[v] = path[u] + to_string(v);

                pq.push(make_pair(dist[v], v));
                }
        }
    }

    return {dist[t], path[t]};

}


void Graph::shortestPath(int s, string startingPath, int add_w)
{
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    vector<int> dist(V, INF);
    vector<string> path(V);

    pq.push(make_pair(0, s));
    dist[s] = 0;
    path[s] = startingPath;

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
    
    cout << "Path & Distance From Source: " << this->source << " Through: "<< this->through << "\n\n";

    for (int i = 0; i < V; ++i){
        if( dist[i] == INF ) {
            cout << "Exception: ";
            cout << i << " Doesn't Exists \n" << endl;;
            continue;
        }
        dist[i] += add_w;
        cout << i << " Path: " <<path[i] << " Weight: "<< dist[i] << endl;
        }
}


void Graph::executeSolution()
{
    
    Tuple res = findShortestPath(this->source, this->through);
    if (res.validate()){
        shortestPath(this->through, res.path, res.weight);
    }
    else{
        cout << "გრაფზე შეუძლებელია მოცემული ამოცანა" << endl;
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
    g.executeSolution();

    return 0;
}