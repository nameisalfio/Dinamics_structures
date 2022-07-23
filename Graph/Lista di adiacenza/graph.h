#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"

template<typename T>
class Graph{

	List<vertex<T>> vertices;

	int n_vertex = 0;
	bool isOriented;

	public:

		Graph(bool isOriented = true) : isOriented(isOriented){}

		void add_vertex(T key){

			vertex<T> toinsert (key);
			vertices.insertTail(toinsert);
			n_vertex ++;
		}

		void add_edge(T key1, T key2){

			Node<vertex<T>>* node1 = search(key1);
			Node<vertex<T>>* node2 = search(key2);

			if(node1 && node2)
			{
				//devo aggiungere node2 alla lista di adiacenza di node 1 per creare l'arco
				node1->getVal().insertTail(key2);

				if(!isOriented)
					node2->getVal().insertTail(key1);
			}
			else
			{
				if(!node1)
					cerr << "There isn't vertex with key " << key1 << endl;
				else
					cerr << "There isn't vertex with key " << key2 << endl;
			}

		}

		Node<vertex<T>>* search(T key){

			if(n_vertex == 0)
			{
				cerr << "Graph is empty!" << endl;
				return nullptr;
			}

			Node<vertex<T>>* ptr = vertices.getHead();
			while(ptr)
			{
				if(key == ptr->getVal().getHead()->getVal())
					return ptr;

				ptr = ptr->getNext();
			}

			return nullptr;
		}

		friend ostream& operator<< (ostream& os, const Graph<T>& g){

			if(g.n_vertex == 0)
				return os << "\nEmpty Graph" << endl;

			if(!g.isOriented)
				os << "\nGraph isn't oriented";
			else 
				os << "\nGraph is oriented";

			os << "\tNumber of vertices: " << g.n_vertex << endl;
			return os << g.vertices << endl;

		}
};

#endif