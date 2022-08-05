#ifndef QUEUE_STATIC_H
#define QUEUE_STATIC_H

template<typename T>
class Queue_static{

	T* vet;
	int head = 0;
	int tail = -1;

	int max_size;
	int size = 0;

public:

	Queue_static(int max_size = 10):max_size(max_size){vet = new T[max_size];}

	bool isEmpty(){return size == 0;}

	bool isFull(){return size == max_size;}

	void enqueue(T val){

		if(isFull())
		{
			cerr << "\nFull queue" << endl;
			return;
		}

		tail = ++tail % max_size;
		vet[tail] = val;
		size++;

		return;
	}

	T getFirst(){

		if(isEmpty())
			throw "Empty queue!";

		return vet[head];
	}

	T dequeue(){

		if(isEmpty())
			throw "Empty queue!";

		T tmp = vet[head];
		head = ++head % max_size;
		size--;

		return tmp;
	}

	friend ostream& operator<< (ostream& os, Queue_static<T>& s){

		if(s.isEmpty())
			os << "\nEmpty queue" << endl;

		if(s.isFull())
			os << "\nFull queue" << endl;

		os << "\nQueue_static: " << endl;

		os << "\nSize: " << s.size << endl;
		os << "\nMaxSize: " << s.max_size << endl << endl;

		for(int i=s.head, count=0; count < s.size; count++) //stampo size elementi a partire da head
		{
			os << "Vet[" << i << "] = " << s.vet[i] << endl;
			i = (i+1) % s.max_size;
		}
		
		return os << "\nEnd queue" << endl;
	}
};

#endif