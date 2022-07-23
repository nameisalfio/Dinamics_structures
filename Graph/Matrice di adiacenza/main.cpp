#include<iostream>
using namespace std;

#include "graph.h"

int main(){

	Graph<int> g;

	g.add_vertex(0);
	g.add_vertex(1);
	g.add_vertex(2);
	g.add_vertex(3);

	g.add_edge(0,1);
	g.add_edge(1,2);
	g.add_edge(2,3);
	g.add_edge(0,3);

	cout << g << endl;
	g.print_adj();
}