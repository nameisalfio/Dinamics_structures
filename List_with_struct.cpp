#include<iostream>

using namespace std;

struct node {
	int info;
	node* next;
};

node* start = nullptr;

void insert_head(node* &start, node* another){
	
	another->next = start;
	start = another;
}

void insert_tail(node* &start, node* another){

	node* last = nullptr;
	
	if(start == nullptr)  //if void list
	{
		//another->next = start;  //add new node in the list
		//start = another;
		insert_head(start, another);
	}	
	else
	{
		last = start;
		
		while(last->next != nullptr)
			last = last->next;  //pointer to next node in the list
		
		last->next = another;  //add new node in the list
	}
	
}

void print_list(node* start){
	
	if(start == nullptr)
		cout<<"Void list! \n";
	
	else{
		cout<<"List: \n"<<endl;
		
		while(start->next != nullptr)
		{
			cout<<start->info<<" ";
			start = start->next;
		}
		cout<<endl;
	}
	
	cout<<endl;
}

node* search(node* start, int key, node* &previous){
	
	print_list(start);
	previous = nullptr;
	
	//Use start to scroll trough the list

	while(start != nullptr && start->info != key)
	{
		previous = start;
		start = start -> next;
	}		
	
	if(start == nullptr)
		cerr<<"Element with key "<<key<<" not found or empty list! "<<endl;
	
	return start;
}

node* modify(node* start, int key, node* new_info){
	
	node* previous = nullptr;
	
	node* result = search(start, key, previous); //Search for the element to be modified
	
	if (!result) //if result is a nullpointer
	{
		cerr << "\nImpossible modify element with key "<<key<<endl;
		return nullptr;
	}
	else
	{
		result -> info = new_info -> info;  //update info part
		return result;
	}
}

void destroy_list (node* &start){
	
	node* tmp = start;
	
	while(start != nullptr)
	{
		tmp = start->next;
		delete start;
		start = tmp;
	}
	
}

int main(){
	
	node* element;
	
	for(int i=0; i<10; i++)
	{
		element = new node;
		element->info = i * i * i;
		
		insert_head(start, element);
		
	}
	
	print_list(start);
	
	for(int i=1; i<=10; i++)
	{
		element = new node;
		element-> info = i * i * i;
		element-> next = nullptr;
		
		insert_tail(start, element);
	}
	
	print_list(start);
	
	destroy_list(start);
	
	for(int i=0; i<10; i++)
	{
		element = new node;
		element->info = i * i * i;
		
		insert_head(start, element);
		
	}
	
	node* previous = nullptr;
	node* found = search(start, 0, previous);
	
	if(found && previous)
		cout<<"Found element with key ("<<found->info<<").\nPrevious element in list is "<< previous->info<<endl;
	
	node* change = new node;
	change->info = 1000;
	
	//NON STAMPA IL CERR "VEDI MODIFY"
	modify(start, 200, change);
	
	print_list(start);
}
