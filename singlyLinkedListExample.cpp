#include<iostream>
#include "singlyLinkedList.h"
using namespace std;
int main()
{
	cout << "Singly Linked List Example" << endl;
	SinglyLinkedList<int> list;
	list.add(1);								 // add 1 to the list
	list.add(2);								 // add 1 to the list
	list.add(3);								 // add 1 to the list
	list.add(4);								 // add 1 to the list
	list.add(5);								 // add 1 to the list
	cout << "Size : " << list.getSize() << endl; // get size of the list
	cout << "Content of the list" << endl;
	for (SinglyLinkedListIterator<int> i = list.getIterator(); i.hasNext();) cout << i.next() << endl;
	list.remove(2);								 // remove 2nd indexed element
	cout << "Size : " << list.getSize() << endl; // get size of the list
	cout << "Content of the list" << endl;
	for (SinglyLinkedListIterator<int> i = list.getIterator(); i.hasNext();) cout << i.next() << endl;
	list.insert(1, 10); //insert 10 at 1st index
	cout << "Content of the list" << endl;
	for (SinglyLinkedListIterator<int> i = list.getIterator(); i.hasNext();) cout << i.next() << endl;
	list.clear(); // clear the list
	cout << "Size : " << list.getSize() << endl; // get size of the list
	return 0;
}