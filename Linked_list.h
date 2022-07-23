#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<typename T>
class Node{

protected:

	T val;
	Node<T>* next;

	template<typename W>
	friend class List;

public:

	Node(T val):val(val){next = nullptr;}

	T getVal(){return this->val;}

	Node<T>* getNext(){return this->next;}

	friend ostream& operator<< (ostream& os, const Node<T>& n){
		return os << n.val;
	}
};

template<typename T>
class List{

	Node<T>* head;

public:

	List(){head = nullptr;}

	Node<T>* getHead(){return this->head;}

	bool isEmpty(){return !head;}

	void insertHead(T val){

		if(isEmpty())
		{
			head = new Node<T>(val);
			return;
		}

		Node<T>* toinsert = new Node<T>(val);
		toinsert->next = head;
		head = toinsert;
		return;
	}

	void insertTail(T val){

		if(isEmpty())
		{
			insertHead(val);
			return;
		}

		Node<T>* cur = head;

		while(cur->next)
			cur = cur->next;

		Node<T>* toinsert = new Node<T>(val);
		cur->next = toinsert;
		return;
	}

	void insertInOrder(T val, char c){

		do
		{
			if(c == 'a') //ascending
			{
				insertInOrderAscending(val);
				return;
			}
			else if(c == 'd') //descending
			{
				insertInOrderDescending(val);
				return;
			}
			else
			{
				cerr << "\nChose between 'a' or 'd' ! " << endl;
				cin >> c;
			}

		}while(c != 'a' && c != 'd');
	}

	void insertInOrderAscending(T val){

		if(isEmpty() || val <= head->val)
		{
			insertHead(val);
			return;
		}

		Node<T>* cur = head;

		while(cur->next && val >= cur->val)
		{
			if(val < cur->next->val)
				break;

			cur = cur->next;
		}

		if(!cur->next)
		{
			insertTail(val);
			return;
		}

		Node<T>* toinsert = new Node<T>(val);
		toinsert->next = cur->next;
		cur->next = toinsert;
		return;
	}

	void insertInOrderDescending(T val){

		if(isEmpty() || val >= head->val)
		{
			insertHead(val);
			return;
		}

		Node<T>* cur = head;

		while(cur->next && val <= cur->val)
		{
			if(val > cur->next->val)
				break;

			cur = cur->next;
		}

		if(!cur->next)
		{
			insertTail(val);
			return;
		}

		Node<T>* toinsert = new Node<T>(val);
		toinsert->next = cur->next;
		cur->next = toinsert;
		return;
	}

	void removeHead(){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}

		Node<T>* ptr = head;
		head = head->next;
		delete ptr;

		return;
	}

	void removeTail(){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}

		Node<T>* cur = head;
		Node<T>* prev = nullptr;

		while(cur->next)
		{
			prev = cur;
			cur = cur->next;
		}

		prev->next = nullptr;
		delete cur;
		return;
	}

	void removeElement(T val){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}

		if(head->val == val)
		{
			removeHead();
			return;
		}

		Node<T>* cur = head;
		Node<T>* prev = nullptr;

		while(cur->next && cur->val != val)
		{
			prev = cur;
			cur = cur->next;
		}

		if(cur->val != val)
		{
			cerr << "Element with key " << val << " isn't in the List! " << endl;
			return;
		}

		prev->next = cur->next;
		delete cur;
		return;
	}

	friend ostream& operator<< (ostream& os, List<T>& l){

		if(l.isEmpty())
			return os << "\nEmpty List !" << endl;

		os << "\nHead: " << *l.head << endl;
		os << "\nLinked_list: " << endl;

		Node<T>* ptr = l.head;
		os << "\nHead --> ";
		while(ptr)
		{
			os << *ptr << " --> ";
			ptr = ptr->getNext();
		}

		return os << "NIL" << endl << "\nEnd List\n" << endl; 
	}
};

#endif