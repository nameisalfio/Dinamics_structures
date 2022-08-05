#ifndef STATIC_STACK_H
#define STATIC_STACK_H

template<typename T>
class Stack_static{

	T* vet;
	int top = -1;
	int max_size;
	int size = 0;

public:

	Stack_static(int max_size = 10):max_size(max_size){vet = new T[max_size];}

	bool isEmpty(){return size == 0;}

	bool isFull(){return size == max_size;}

	T getTop(){

		if(isEmpty())
			throw "Void Stack! ";

		return vet[top];
	}

	void push(T val){

		if(isFull())
		{
			cerr << "Full stack!" << endl;
			return;
		}

		vet[++top] = val;
		size++;
		return;
	}

	T getLast(){

		if(isEmpty())
			throw "Empty queue!";

		return vet[top];
	}

	T pop(){

		if(isEmpty())
			throw "Void Stack! ";

		size--;
		return vet[top--];
	}

	friend ostream& operator<< (ostream& os, Stack_static& s){
		
		if(s.isEmpty())
			return os << "\nEmpty Stack!" << endl;
	
		if(s.isFull())
			os << "\nFull Stack!" << endl;
		
		os << "\nStack_static: " << endl;

		os << "\nSize: " << s.size << endl;
		os << "\nMax_size : " << s.max_size << endl;
		os << "\nTop->\t" << s.getTop() << endl ;

		for(int i=s.top-1; i>=0; i--)
			os << "\t" << s.vet[i] << endl;
		
		return os << "\nEnd stack" << endl;
	}
};

#endif