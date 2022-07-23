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
				throw "Void BST!";

			BSTNode<T>* ptr = from;
			while(ptr->right)
				ptr = ptr->right;

			return ptr;
		}

		BSTNode<T>* min(){return min(root);}

		BSTNode<T>* min(BSTNode<T>* from){

			if(isEmpty())
				throw "Void BST!";

			BSTNode<T>* ptr = from;
			while(ptr->left)
				ptr = ptr->left;

			return ptr;
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

		BSTNode<T>* search(T key){return search(root, key);}

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

		void cancel_below(BSTNode<T>* ptr, T key){
				
			if(ptr->key < key)
				remove(ptr);
		}

		void remove_below(BSTNode<T>* ptr, T key){

			if(!ptr)
				return;

			remove_below(ptr->right, key);
			cancel_(ptr, key);
			remove_below(ptr->left, key);
		}

		void remove_below(T key){remove_below(root, key);}

		void cancel_above(BSTNode<T>* ptr, T key){
				
			if(ptr->key > key)
				remove(ptr);
		}

		void remove_above(BSTNode<T>* ptr, T key){

			if(!ptr)
				return;

			remove_above(ptr->right, key);
			cancel_above(ptr, key);
			remove_above(ptr->left, key);
		}

		void remove_above(T key){remove_above(root, key);}

		void cancel_equal(BSTNode<T>* ptr, T key){
				
			if(ptr->key == key)
				remove(ptr);
		}

		void remove_equal(BSTNode<T>* ptr, T key){

			if(!ptr)
				return;

			remove_equal(ptr->right, key);
			cancel_equal(ptr, key);
			remove_equal(ptr->left, key);
		}

		void remove_equal(T key){remove_equal(root, key);}

		friend ostream& operator<< (ostream& os, BST& bst){

			if(bst.isEmpty())
				return os << "\nEmpty BST!" << endl;

			os << "\nBST: " << endl;
			bst.in_order();
			return os;
		}
};

#endif