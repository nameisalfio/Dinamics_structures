#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<typename T>
class Node{

	protected:

		T val;
		Node<T>* next;
		static int count ;  //Variabile di classe
		
		template<typename U>
		friend class List;
		
	public:
	
		Node(T val):val(val){
			next = nullptr;
			count++;
		}
		
		T& getVal(){
			return this->val;
		}
		
		Node<T>* getNext() const {
			return this -> next;
		}

		friend ostream& operator<< (ostream& out, const Node<T>& node){
			//out << "node val =" << node.val << " - next= " << node.next;
			out << node.val;
			return out;
		}
		
};

template<typename T>
int Node<T> :: count = 0;  //Una variabile di classe va inizializzata esternamente

template<typename T>
class List{
	
	protected:
		Node<T>* head;
		Node<T>* tail;
		
	public:
	
		List(){
			head = nullptr;
			tail = nullptr;
		}
		
		Node<T>* getHead()const{
			return head;
		}
		
		Node<T>* getTail()const{
			return tail;
		}
		
		unsigned int getLen()const{
			return Node<T> :: count;
		}
		
		bool isEmpty(){
			return head == nullptr;
		}
		
		void insert(T val){
			if(this->isEmpty())
			{
				head = new Node<T>(val);
				tail = head;
				return;
			}
		}
		
		void insertHead(T val){
			if(this->isEmpty())
			{
				this->insert(val);
				return;
			}
	
			Node<T>* tmp = new Node<T>(val);
			tmp->next = head;
			this->head = tmp;
		}

		void insertTail(T val){
			
			if(this->isEmpty())
			{
				this->insert(val);
				return;
			}
			
			Node<T>* toinsert = new Node<T> (val);
			tail->next = toinsert;
			tail = toinsert;
		}

		void insertInOrderAscending(T val){
			
			if(this->isEmpty())
			{
				this->insert(val);
				return;
			}
			
			if(val <= head->val) //Controllo che il valore che voglio inserire sia minore o uguale del primo nodo
			{
				this->insertHead(val);
				return;
			}
			
			Node<T>* tmp = head;
			
			//Il while mi serve a posizionarmi sull'elemento corretto prima dell'inserimento
			
			while(tmp->getNext() && val >= tmp->val) //Finchè l'elemento da inserire è maggiore di quello corrente
			{
				if(val < tmp->next->val) //Se l'elemento da inserire è minore del successivo
					break;
				
				tmp = tmp->next;
			}
			
			if(!tmp->next)  //Se non ci sono altri elementi dopo tmp
			{
				this->insertTail(val);
				return;
			}
			
			Node<T>* toInsert = new Node<T>(val);
			toInsert->next = tmp->next; //Collego il nodo da inserire al successivo di ptr
			tmp->next = toInsert; //Stacco il collegamento del precedente facendolo puntare all'elemento aggiunto
			return;
		}
		
		void insertInOrderDescending(T val){
			
			if(isEmpty())
			{
				this->insert(val);
				return;
			}
			
			if(val >= head->val)
			{
				insertHead(val);
				return;
			}
			
			Node<T>* tmp = head;
			
			while(tmp->next && val <= tmp->val) //Finchè l'elemento da inserire è minore di quello corrente
			{
				if(val >= tmp->next->val)
					break;
				
				tmp = tmp->next;
			}

			if(!tmp->next)  //Se non ci sono altri elementi dopo tmp
			{
				this->insertTail(val);
				return;
			}
			
			Node<T>* toinsert = new Node<T>(val);
			toinsert->next = tmp->next; //Collego il nodo da inserire al successivo di ptr
			tmp->next = toinsert; //Stacco il collegamento del precedente facendolo puntare all'elemento aggiunto
			return;
		
		}
		
		void insertInOrder(T val, string c){
			
			if(c == "Crescente")
			{
				insertInOrderAscending(val);
				return;
			}
			
			if(c == "Decrescente")
			{
				insertInOrderDescending(val);
				return;
			}
		}
		
		void removeHead(){
			
			if(this->isEmpty())
			{
				cerr << "Empty list!" << endl;
				return;
			}
			
			Node<T> :: count --;
			
			Node<T> * tmp = head;
			head = head -> next;  //Sposto in avanti la testa 
			delete tmp;  //Cancello l'indirizzo della vecchia testa
		}
		
		void removeTail(){
			
			if(this->isEmpty())
			{
				cerr << "Empty list!" << endl;
				return;
			}
			
			Node<T> :: count --;
			
			if(head == tail) //Se c'è un solo elemento 
			{
				Node<T>* ptr = tail;
				head = nullptr;  //Annullo i collegamenti
				tail = nullptr;
				delete ptr;  //Elimino la coda
			}
			
			Node<T>* cur = head;
			Node<T>* prev = nullptr;
			
			while(cur->next)
			{
				prev = cur;
				cur = cur->next;
			}
			
			tail = prev;
			prev->next = nullptr;
			delete cur;
		}

		void removeElement(T val){
			
			if(this->isEmpty())
			{
				cerr << "Empty list!" << endl;
				return;
			}
			
			if(head->val == val)
			{
				this->removeHead();
				return;
			}

			if(head->val == tail)
			{
				this->removeTail();
				return;
			}
			
			Node<T>* cur = head;  //Per scorrere la lista
			Node<T>* prev = nullptr;  //Precedente
			
			while(cur->next && cur->val != val)  //Mi posiziono al massimo al penultimo elemento
			{
				prev = cur;
				cur = cur->getNext();
			}
			
			if(cur->val != val) //Se sono uscito dal while perchè ho finito gli elementi
			{
				cerr << "Element with value " << val << " not found" << endl;
				return;
			}
			
			Node<T> :: count --;
			
			prev->next = cur->next;  //il successivo del precedente deve essere il successivo dell'elemento corrente
			delete cur;  //Cancello
			return;
		}
		
		friend ostream& operator<< (ostream& out, const List<T> &list){

			out << "\nList head : " << list.head << endl;
			out << "List tail : " << list.tail << endl << endl;

			Node<T>* ptr = list.head;
			while(ptr) //ptr != nullptr
			{
				out << *ptr << endl;
				ptr = ptr->getNext();
			}
			
			return out;
		}

		
};

#endif