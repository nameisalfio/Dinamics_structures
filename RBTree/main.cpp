#include<iostream>
using namespace std;

#include"RBTree.h"

int main()
{
	RBTree<int> tree;
	tree.insertKey(50);
	tree.insertKey(20);
	tree.insertKey(40);
	cout << *tree.searchKey(20) << endl;
}