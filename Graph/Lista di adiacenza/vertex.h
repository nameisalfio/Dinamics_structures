#ifndef VERTEX_H
#define VERTEX_H

#include "Linked_list.h"
//Specifica la classe lista, infatti ogni vertice è rappresentato da una lista che ha il vertice stesso
//come head e tutti i vertici a se adiacenti come nodi della lista

template<typename T>
class vertex : public List<T>{

	public:

		vertex(T key) : List<T>(){
			List<T>::insert(key);
		}

		vertex() : vertex(NULL){}

		friend ostream& operator<< (ostream& os, const vertex<T>& v){

			//getVal() mi restituisce la parte informativa del vertice in testa
			os << "\nGraph vertex with key " << v.head->getVal() << ": ";

			//Stampo la lista di nodi adiacenti al vertice
			os << "\tAdjecency list: ";
			Node<T>* ptr = v.head;
			
			if(!ptr->getNext())
				return os << "no adjacent vertex !" << endl;

			while(ptr->getNext())
			{
				ptr = ptr->getNext();
				os << "-->" << ptr->getVal();
			}
			os << endl;

			return os;
		}
};

#endif