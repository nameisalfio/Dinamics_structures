#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

template<typename T>
class DLNode{

	T val;
	DLNode<T>* next;
	DLNode<T>* prev;

	template<typename W>
	friend class DLList;

public:

	DLNode(T val):val(val){
		prev = nullptr;
		next = nullptr;
	}

	T getVal(){return this->val;}

	DLNode<T>* getNext(){return this->next;}

	DLNode<T>* getPrev(){return this->prev;}

	friend ostream& operator<< (ostream& os, const DLNode<T>& n){return os << n.val;}
};

template<typename T>
class DLList{

protected:
	
	DLNode<T>* head;
	DLNode<T>* tail;

public:

	DLList(){
		head = nullptr;
		tail = nullptr;
	}

	DLNode<T>* getHead(){return this->head;}

	DLNode<T>* getTail(){return this->tail;}

	bool isEmpty(){return (!head && !tail);}

	void insertHead(T val){

		if(isEmpty())
		{
			head = new DLNode<T>(val);
			tail = head;
			return;
		}

		DLNode<T>* toinsert = new DLNode<T>(val);
		toinsert->next = head;
		head->prev = toinsert;
		head = toinsert;
		return;
	}

	void insertTail(T val){

		if(isEmpty())
		{
			insertHead(val);
			return;
		}

		DLNode<T>* toinsert = new DLNode<T>(val);
		tail->next = toinsert;
		toinsert->prev = tail;
		tail = toinsert;
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

		if(val >= tail->val)
		{
			insertTail(val);
			return;
		}

		DLNode<T>* cur = head;

		while(cur->next && val >= cur->val)
		{
			if(val < cur->next->val)
				break;

			cur = cur->next;
		}

		DLNode<T>* toinsert = new DLNode<T>(val);

		toinsert->next = cur->next;
		toinsert->prev = cur;

		cur->next->prev = toinsert;
		cur->next = toinsert;
		return;
	}

	void insertInOrderDescending(T val){

		if(isEmpty() || val >= head->val)
		{
			insertHead(val);
			return;
		}

		if(val <= tail->val)
		{
			insertTail(val);
			return;
		}

		DLNode<T>* cur = head;

		while(cur->next && val <= cur->val)
		{
			if(val > cur->next->val)
				break;

			cur = cur->next;
		}

		DLNode<T>* toinsert = new DLNode<T>(val);
		
		toinsert->next = cur->next;
		toinsert->prev = cur;

		cur->next->prev = toinsert;
		cur->next = toinsert;
		return;
	}

	void removeHead(){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}

		DLNode<T>* ptr = head;
		head = head->next;
		ptr->next->prev = nullptr;
		delete ptr;

		return;
	}

	void removeTail(){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}

		DLNode<T>* ptr = tail;
		tail->prev->next = nullptr;
		tail = tail->prev;							
		delete ptr;

		return;
	}

	DLNode<T>* search(T val){

		if(isEmpty())
			throw out_of_range("...list is empty...");

		if(head->val == val)
			return head;

		DLNode<T>* cur = head;

		while(cur->next && cur->val != val)
			cur = cur->next;
		
		if(cur->val != val)
		{
			cerr << "Element with key " << val << " not found!" << endl;
			return nullptr;
		}

		return cur;
	}


	void removeElement(T val){

		if(isEmpty())
		{
			cerr << "Empty List! Operation isn't avaible! " << endl;
			return;
		}
		
		DLNode<T>* toremove = search(val);

		if(!toremove)
			return;

		if(toremove->val == head->val){
			removeHead();
			return;
		}

		if(toremove->val == tail->val){
			removeTail();
			return;
		}

		DLNode<T>* cur = head;

		while(cur->next && cur->val != toremove->val)
			cur = cur->next;

		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;
	}

	friend ostream& operator<< (ostream& os,  DLList<T>& d){

		if(d.isEmpty())
			return os << "\nEmpty List !" << endl;

		os << "\nHead: " << *d.head << "\tTail: " << *d.tail << endl;
		os << "\nDouble_linked_list: " << endl;

		DLNode<T>* ptr = d.head;
		os << "\nHead --> ";
		while(ptr)
		{
			if(ptr != d.tail)
				os << *ptr << " <--> ";
			else
				os << *ptr << " --> ";

			ptr = ptr->getNext();
		}

		return os << "NIL" << endl << "\nEnd List\n" << endl; 
	}
};

#endif