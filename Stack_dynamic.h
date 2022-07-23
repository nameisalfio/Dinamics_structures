#ifndef STACK_DYNAMIC_H
#define STACK_DYNAMIC_H

#include "Linked_list.h"

template<typename T>
class Stack_dynamic : protected List<T>{

	int size = 0;

public:

	Stack_dynamic() : List<T>(){}

	bool isEmpty(){return size == 0;}

	Node<T>* getTop(){

		if(isEmpty())
			return nullptr;

		return List<T>::getHead();
	}

	void push(T val){

		List<T>::insertHead(val);
		size++;

		return;
	}

	Node<T>* pop(){

		if(isEmpty())
			return nullptr;

		Node<T>* ptr = getTop();
		List<T>::removeHead();
		size--;

		return ptr;
	}

	friend ostream& operator<< (ostream& os, Stack_dynamic<T>& s){
		
		//os << (List<T>)s;  //Per richiamare il metodo della superclasse
		
		if(s.isEmpty())
		{
			os << "\nEmpty Stack!" << endl;
			return os;
		}
		
		os << "\nStack_dynamic: " << endl;
		os << "\nSize : " << s.size << endl;
		os << "\nTop-->\t" << *s.getTop() << endl;
		
		while(s.pop())
		{
			if(s.getTop())
			os << "\t" << *s.getTop() << "\n" ;
		}
		
		return os << "\nEnd stack" << endl;
	}
};

#endif