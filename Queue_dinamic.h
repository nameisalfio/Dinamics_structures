#ifndef QUEUE_DYNAMIC_H
#define QUEUE_DYNAMIC_H

#include "Double_linked_list.h"

template<typename T>
class Queue_dynamic : protected DLList<T>{

	int size;

public:

	Queue_dynamic() : DLList<T>(){}

	bool isEmpty(){return size == 0;}

	void enqueue(T val){

		DLList<T>::insertTail(val);
		size++;

		return;
	}

	DLNode<T>* dequeue(){

		if(isEmpty())
			return nullptr;

		DLNode<T>* ptr = DLList<T>::getHead();
		DLList<T>::removeHead();
		size--;

		return ptr;
	}

	friend ostream& operator<< (ostream& os, Queue_dynamic<T>& q){
		
		if(q.isEmpty())
		{
			os << "\nEmpty Queue" << endl;
			return os;
		}

		os << "\nQueue_dynamic: " << endl;
		os << "\nSize=" << q.size << endl;

		DLNode<T>* ptr  = q.head;
		os << "\nQueue starting at: " << *ptr << endl;

		while(ptr)
		{
			os << "\t" << *ptr << endl;
			ptr = ptr->getNext();
		}

		return os << "\nEnd Queue" << endl;
	}
};

#endif