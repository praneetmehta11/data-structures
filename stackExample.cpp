#include<iostream>
#include"stack.h"
using namespace std;
int main()
{
	Stack<int> s;
	s.push(1); // push 1 into the stack
	s.push(2); // push 2 into the stack
	s.push(3); // push 3 into the stack
	s.push(4); // push 4 into the stack
	cout<<"Top element : "<<s.top()<<endl;
	while(!s.isEmpty()) cout<<s.pop()<<endl;
	return 0;
}