#include <iostream>
#include <list>

using namespace std;

class Graph{
    int V;
    list<int> *adj;

    public:
        Graph(int V);
        void addEdge(int a, int b);
        bool isChromaticTwo();
};

Graph::Graph(int V){
        this->V = V;
        adj = new list<int>[V];
}
void Graph::addEdge(int a, int b){
    adj[a].push_back(b);
}
bool Graph::isChromaticTwo()
{
    // შემოვიღოთ წვეროების ფერის ბმული სია
    bool *color = new bool[V];
    bool *visited = new bool[V];
    for(int i=0; i<V; i++){
        color[i] = false;
        visited[i] = false;
    }
    list<int> Q;
    bool is_chromatic = true;

    // რანდომულად ავირჩიოთ წვერო
    srand(time(NULL));
    int s = rand() % V;

    visited[s] = true;
    Q.push_back(s);


    list<int>::iterator i;
    while(!Q.empty() && is_chromatic){
        s = Q.front();
        cout << s << " ";
        Q.pop_front();
        for(i=adj[s].begin(); i!=adj[s].end(); ++i){
            if(!visited[*i]){
                visited[*i]=true;
                Q.push_back(*i);
                // მივანიჭოთ ამ წვეროს
                // მისი მშობლისგან განსხავებული ფერი
                color[*i] = !color[s];

            }
            else{
                // თუ იარსებებს გზა ისეთ წვეროებს შორის
                // რომლებსაც იგივე ფერი აქვთ ე.ი
                // გრაფი ქრომატული რიცხვი არ უდრის 2-ს
                if(color[*i] == color[s]){
                    is_chromatic = false;
                }
            }
        }
    }
    return is_chromatic;
}


int main(){
    // a -> 0, b -> 1, c-> 2, d -> 3, e -> 4, f-> 5
    Graph g(6);
    g.addEdge(0, 2); // (a, c)
    g.addEdge(2, 0); // (c, a)
    g.addEdge(0, 3); // (a, d)
    g.addEdge(3, 0); // (d, a)
    g.addEdge(2, 1); // (c, b)
    g.addEdge(1, 2); // (b, c)
    g.addEdge(1, 3); // (b, d)
    g.addEdge(3, 1); // (d, b)
    g.addEdge(3, 5); // (d, f)
    g.addEdge(5, 3); // (f, d)

    if(g.isChromaticTwo()){
        cout << "გრაფის ქრომატული რიცხვია 2";
    }else{
        cout << "გრაფის ქრომატული რიცხვი არაა 2";
    }
    cout << endl;
    return 0;
}