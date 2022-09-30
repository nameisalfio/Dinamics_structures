#ifndef BST_H
#define BST_H

#include "BSTNode.h"

template<typename T>
class BST{
	
		BSTNode<T>* root;

	public:

		BST(){root = nullptr;}
		
		BSTNode<T>* getRoot(){return this->root;}

		bool isEmpty(){return root == nullptr;}

		void insert(T key){
			
			if(isEmpty())
			{
				root = new BSTNode<T>(key);
				return;
			}

			insert(root, key);
		}

		void insert(BSTNode<T>* ptr, T key){

			if(!ptr->left && key <= ptr->key)
			{
				ptr->left = new BSTNode<T>(key);
				ptr->left->setParent(ptr);
				return;
			}

			if(!ptr->right && key > ptr->key)
			{
				ptr->right = new BSTNode<T>(key);
				ptr->right->setParent(ptr);
				return;
			}

			if(key <= ptr->key)
				insert(ptr->left, key);

			else
				insert(ptr->right, key);
		}

		void visit(BSTNode<T>* ptr) { cout << "\n" << *ptr << endl; }

		void pre_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			visit(ptr);
			pre_order(ptr->left);
			pre_order(ptr->right);
		}

		void pre_order(){pre_order(root);}
 
		void in_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			in_order(ptr->left);
			visit(ptr);
			in_order(ptr->right);
		}

		void in_order(){in_order(root);}

		void post_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			post_order(ptr->left);
			post_order(ptr->right);
			visit(ptr);
		}

		void post_order(){post_order(root);}

		BSTNode<T>* max(){return max(root);}

		BSTNode<T>* max(BSTNode<T>* from){

			if(isEmpty())
                throw out_of_range("Empty bst...");

			BSTNode<T>* ptr = from;
			while(ptr->right)
				ptr = ptr->right;

			return ptr;
		}

		BSTNode<T>* min(){return min(root);}

		BSTNode<T>* min(BSTNode<T>* from){

			if(isEmpty())
                throw out_of_range("Empty bst...");

			BSTNode<T>* ptr = from;
			while(ptr->left)
				ptr = ptr->left;

			return ptr;
		}

        BSTNode<T>* successor(T key){

            BSTNode<T>* ptr = search(key);
            if(!ptr || ptr == max())
                throw out_of_range("...successor doesn't exist...");

            return successor(ptr);
        }

		BSTNode<T>* successor(BSTNode<T>* x){

			if(isEmpty())
				return nullptr;

			if(x->right) 
				return min(x->right);

			BSTNode<T>* y = x->parent;
			while(x && x == y->right)  //fino a che x non è un figlio sinistro
			{
				x = y;
				y = y->parent;
			}

			return y;
		}

        BSTNode<T>* predecessor(T key){

            BSTNode<T>* ptr = search(key);
            if(!ptr || ptr == min())
                throw out_of_range("...predecessor doesn't exist...");

            return predecessor(ptr);
        }

		BSTNode<T>* predecessor(BSTNode<T>* x){

			if(isEmpty())
				return nullptr;

			if(x->left)
				return max(x->left);

			BSTNode<T>* y = x->parent;
			while(x && x == y->left)  //fino a che x non è un figlio destro
			{
				x = y;
				y = y->parent;
			}
			
			return y;
		}

		BSTNode<T>* search(T key){
			if(isEmpty())
                throw out_of_range("Empty bst...");

			return search(root, key);
		}

		BSTNode<T>* search(BSTNode<T>*ptr , T key){

			if(!ptr)
				return nullptr;

			if(ptr->key == key)
				return ptr;

			if(key <= ptr->key)
				return search(ptr->left, key);

			else
				return search(ptr->right, key);
		}

		int from_successor(T key){

            int count=0;
            BSTNode<T> * ptr = search(key);

            if(!ptr || ptr == max()) 
                throw out_of_range ("...successor doesn't exist...");

            //Caso 1: il nodo ha un sottoalbero dx
            if(ptr->right) 
            {
                ptr = ptr->right;
                count++; //mi sono comunque spostato di un nodo

                while(ptr->left) //Cerco il minimo del sottoalbero dx
                {
                    ptr = ptr->left;
                    count++;
                }

                return count;
            }

            //Caso 2: il nodo è una foglia

            BSTNode<T>* y = ptr->parent; //passo induttivo
            count++; //mi sono comunque spostato di un nodo

            while(ptr && ptr == y->right) //fino a che ptr non è un figlio sinistro
            {
                ptr = ptr->parent;
                y = y->parent;
                count ++;
            }

            return count;
        }

		int from_root(BSTNode<T>* nodo_h, BSTNode<T>* partenza){

			//partenza = radice del sottoalbero ottenuto mettendo nodo_k come radice

			if(partenza->key == nodo_h->key) //distanza tra un nodo e se stesso
				return 0;

			BSTNode<T>* tmp = partenza;
			int counter = 0;  //distanza tra padre e figlio

			while(tmp && tmp->key != nodo_h->key) //esco quando arrivo ad una foglia 
												//oppure quando trovo il nodo
			{
				if(nodo_h->key > tmp->key) 
					tmp = tmp->right;
				else 
					tmp=tmp->left;

				counter++;
			}
			
			if(!tmp) 
				return -1;
			else 
				return counter;  
			
		}

		int between_nodes(T k, T h) {

			BSTNode<T>* nodo_k = search(k);
			BSTNode<T>* nodo_h = search(h);

			int counter=0;

			if(!nodo_k || !nodo_h)
						throw out_of_range("Chiavi errate!");
					
			if(k <= h)
			{
				BSTNode<T>* tmp = nodo_k;
				bool flag = true;

				while(tmp && flag) 
				{
					int distance = from_root(nodo_h, tmp); 

					if(distance == 0) //k e h coincidono
						flag = false;
					
					else if(distance == -1)
					{
						tmp = tmp->parent;  //salgo 
						counter++; 
					}
					else 
					{
						counter += distance;
						flag = false;
					}
				}

				return counter;
			}
			else
				return between_nodes(h, k); //inverto per ottenere k <= h
		}

		BSTNode<T>* remove(BSTNode<T>* node){ 

			//Caso 1: node è una foglia
			if(!node->left && !node->right)
			{
				if(node == node->parent->left)
					node->parent->left = nullptr;

				else if(node == node->parent->right)
					node->parent->right = nullptr;

				return node;
			}

			//Caso 2: node ha un solo figlio
			if(!node->right && node->left)
			{
				node->left->setParent(node->parent);

				if(node == node->parent->left)
					node->parent->left = node->left;

				else if(node == node->parent->right)
					node->parent->right = node->left;

				return node;
			}

			if(!node->left && node->right)
			{
				node->right->setParent(node->parent);

				if(node == node->parent->left)
					node->parent->left = node->right;

				else if(node == node->parent->right)
					node->parent->right = node->right;

				return node;
			}

			return nullptr;
		}

		BSTNode<T>* remove(T key){

			if(isEmpty()) //albero vuoto
				return nullptr;

			BSTNode<T>* node = search(key);

			if(!node)  //nodo non trovato
				return nullptr;

			BSTNode<T>* toDelete = remove(node);

			//se non sono nel terzo caso mi ritorno il valore del nodo, che ho comunque cancellato con "remove(node)"

			if(toDelete != nullptr) 
				return toDelete;

			//Caso 3 -> Voglio eliminare un nodo con due figli

			//Sostituisco il nodo da cancellare con il successore
			BSTNode<T>* next = successor(node);

			//Sostituisco la chiave
			T swap = node->key;
			node->key = next->key;
			next->key = swap;

			toDelete = remove(next); //stavolta sono sicuramente in uno dei due casi precedenti
			return toDelete;
		}

        //Below 
	    void cancel_below(BSTNode<T>* ptr, T key){
	        if(ptr->key <= key)
	            remove(ptr->key);
	    }

	    void remove_below(BSTNode<T>* ptr, T key){
	        if(!ptr)
	            return;

	        remove_below(ptr->right, key);
	        cancel_below(ptr, key);
	        remove_below(ptr->left, key);
	    }

	    void remove_below(T key){remove_below(root, key);}

	    //Above
		void cancel_above(BSTNode<T>* ptr, T key){
			if(ptr->key >= key)
				remove(ptr->key);
		}

		void remove_above(BSTNode<T>* ptr, T key){
			if(!ptr)
				return;

			remove_above(ptr->right, key);
			cancel_above(ptr, key);
			remove_above(ptr->left, key);
		}

		void remove_above(T key){remove_above(root, key);}

		//Equal
		void cancel_equal(BSTNode<T>* ptr, T key){
			if(ptr->key == key)
				remove(ptr->key);
		}

		void remove_equal(BSTNode<T>* ptr, T key){

			if(!ptr)
				return;

			remove_equal(ptr->right, key);
			cancel_equal(ptr, key);
			remove_equal(ptr->left, key);
		}

		void remove_equal(T key){remove_equal(root, key);}

		int depth(BSTNode<T>* ptr){
			if(isEmpty())
				throw out_of_range("..empty BST...");

			int deep = 0;
			while(ptr->parent){
				deep ++;
				ptr = ptr->parent;
			}
			return deep;
		}

		friend ostream& operator<< (ostream& os, BST<T>& bst){

			if(bst.isEmpty())
				return os << "\nEmpty BST!" << endl;

			os << "\nBST: " << endl;
			bst.in_order();
			return os;
		}
};

#endif