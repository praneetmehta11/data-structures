#include <iostream>
#include "queue.h"
using namespace std;
int main()
{
	Queue<int> queue;
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.push(4);
	queue.push(5);
	cout << "Element at the front : " << queue.front() << endl;
	cout << "Element at the back : " << queue.back() << endl;
	cout << "Size : " << queue.size() << endl;
	while (!queue.isEmpty())
		cout << queue.pop() << endl;
	return 0;
}