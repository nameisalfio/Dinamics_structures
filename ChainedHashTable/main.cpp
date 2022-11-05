#include<iostream>
#include<list>
using namespace std;

#include "ChainedHashTable.h"

int main(){
	
	DivChainedHashTable<int>* table = new DivChainedHashTable<int>(7);

	int a[] = { 15, 11, 27, 8, 12 };	//Inserisco gli elementi nella tabella e la stampo
	for (int i = 0; i < 5; i++)
		table->insertKey(a[i]);
	cout << *table << endl;
	cout << "Size: " << table->slot() << endl;

	int idx = -1;
	int pos = -1;
	table->searchKey(15, idx, pos);
	cout << "\nKey 15 found at index " << idx << " in position " << pos << endl;

	cout<<"\nDeleting key 8"<<endl;
	table->deleteKey(8);
	cout << *table << endl;
	cout << "Size: " << table->slot() << endl;
	
	cout<<"\nDeleting key 12"<<endl;
	table->deleteKey(12);
	cout << *table << endl;
	cout << "Size: " << table->slot() << endl;

	cout << "Searching keys..." << endl;
	cout << "Key 27 :"<< table->searchKey(27) << endl;
	cout << "Key 899: "<< table->searchKey(899) << endl;	//not found
}