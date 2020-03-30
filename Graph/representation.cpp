#include<iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>


class Graph{
	std::map<char, std::list<char>> adjacents;
	bool oriented;
	std::map<int, char> iVar; // მატრიცისთვის მაპინგი
	int length;
    public:
        Graph(std::list<char> nodeNames, bool oriented){
			this->oriented=oriented;
			int length = 0;
			for(char node: nodeNames){
				this->adjacents[node] = {};
				this->iVar[length] = node;
				length+=1;
			} 
			this->length=length;
		}

        void addEdge(char vertexA, char vertexB){
			// დაამატე წიბო და გაითვალისწინე ორიენტირებულია თუ არა გრაფი
            this->adjacents[vertexA].push_back(vertexB);
			if(!oriented && vertexA != vertexB){ this->adjacents[vertexB].push_back(vertexA);}

        }

        void printGraph(){
			// ამობეჭდე გრაფისთვის ბმული სია
			for(auto node:this->adjacents){
				std::cout<<node.first << " -> ";
				for(auto adj: node.second){ std::cout << adj << " ";}
				std::cout << std::endl;
			}
		}

		void matrixForm(){
			// ამობეჭდე გრაფისთვის მატრიცული ფორმა
			for(auto i:this->iVar){
				std::list<char> currentList = this->adjacents[i.second];
				std::cout << i.second << " ";
				for(int j=0; j<this->length; j++){
					bool contains = std::find(currentList.begin(),
					currentList.end(),this->iVar[j]) != currentList.end();
					int w = contains ? 1: 0;
					std::cout << w << ' ';

				}
				std::cout << std::endl;
			}
		}
		
};


int main(){
	// პირველი ვარიანტი
	std::cout << "პირველი ვარიანიტი: " << std::endl;
    Graph g({'a', 'b', 'd', 'e', 'f'}, false);
    g.addEdge('a', 'd');
	g.addEdge('b', 'a');
    g.addEdge('b', 'e');
    g.addEdge('a', 'a');
    g.addEdge('e', 'e');
    g.addEdge('d', 'b');
    g.addEdge('e', 'd');
	g.addEdge('f', 'e');

    std::cout << "ბმული სიის სახით:  " <<std::endl;
    g.printGraph();
	std::cout << "მატრიცის სახით: " << std::endl;
	g.matrixForm();
	std::cout << std::endl;


	// მეორე ვარიანტი
	std::cout << "მეორე ვარიანიტი: " << std::endl;
	Graph G({'a', 'b', 'c', 'd', 'e', 'f'}, false);
	G.addEdge('a', 'd');
	G.addEdge('b', 'a');
	G.addEdge('b', 'e');
	G.addEdge('c', 'b');
	G.addEdge('a', 'e');
	G.addEdge('c', 'e');
	G.addEdge('d', 'b');
	G.addEdge('e', 'd');
	G.addEdge('f', 'e');
	G.addEdge('f', 'c');

	std::cout << "ბმული სიის სახით:  " <<std::endl;
    G.printGraph();
	std::cout << "მატრიცის სახით: " << std::endl;
	G.matrixForm();


    return 0;
}
