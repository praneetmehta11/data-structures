#include <iostream>
using namespace std;

/*
Implementation of stack is just after SinglyLinked List
beacuse SinglyLinkedList is used in stack 
*/

int stringLength(const char *msg)
{
	int length;
	for (length = 0; *msg; ++msg, ++length);
	return length;
}
void stringCopy(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
}

class SinglyLinkedListException : public exception
{
private:
	char *message;

public:
	SinglyLinkedListException(const char *message)
	{
		this->message = new char[stringLength(message) + 1];
		stringCopy(this->message, message);
	}
	SinglyLinkedListException(const SinglyLinkedListException &other)
	{
		this->message = new char[stringLength(other.message) + 1];
		stringCopy(this->message, other.message);
	}
	SinglyLinkedListException &operator=(SinglyLinkedListException other)
	{
		delete[] message;
		this->message = new char[stringLength(other.message) + 1];
		stringCopy(this->message, other.message);
		return *this;
	}
	virtual ~SinglyLinkedListException() throw()
	{
		delete[] message;
	}
	virtual const char *what() const throw()
	{
		return this->message;
	}
};

template <class T>
class SinglyLinkedListNode;
template <class T>
class SinglyLinkedListIterator;
template <class T>
class SinglyLinkedList;
template <class T>
class SinglyLinkedListNode
{
private:
	T data;
	SinglyLinkedListNode<T> *next;
	SinglyLinkedListNode(T data);
	friend class SinglyLinkedList<T>;
	friend class SinglyLinkedListIterator<T>;
};
template <class T>
SinglyLinkedListNode<T>::SinglyLinkedListNode(T data)
{
	this->data = data;
	this->next = NULL;
}

template <class T>
class SinglyLinkedListIterator
{
private:
	SinglyLinkedListNode<T> *node;
	SinglyLinkedListIterator(SinglyLinkedListNode<T> *);

public:
	SinglyLinkedListIterator(const SinglyLinkedListIterator<T> &);
	SinglyLinkedListIterator<T> &operator=(SinglyLinkedListIterator<T>);
	int hasNext();
	T next();
	friend class SinglyLinkedList<T>;
};
template <class T>
SinglyLinkedListIterator<T>::SinglyLinkedListIterator(SinglyLinkedListNode<T> *node)
{
	this->node = node;
}
template <class T>
SinglyLinkedListIterator<T>::SinglyLinkedListIterator(const SinglyLinkedListIterator<T> &other)
{
	this->node = other.node;
}
template <class T>
SinglyLinkedListIterator<T> &SinglyLinkedListIterator<T>::operator=(SinglyLinkedListIterator<T> other)
{
	this->node = other.node;
	return *this;
}
template <class T>
int SinglyLinkedListIterator<T>::hasNext()
{
	return this->node != NULL;
}
template <class T>
T SinglyLinkedListIterator<T>::next()
{
	if (this->node == NULL)
		throw SinglyLinkedListException(" Their is no more node in list to be iterated. ");
	T data;
	data = this->node->data;
	this->node = this->node->next;
	return data;
}
template <class T>
class SinglyLinkedList
{
private:
	SinglyLinkedListNode<T> *start;
	SinglyLinkedListNode<T> *end;
	int size;

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T> &);
	virtual ~SinglyLinkedList();
	SinglyLinkedList<T> &operator=(SinglyLinkedList<T>);
	T operator[](int);
	void add(T);
	void insert(int, T);
	T remove(int);
	T get(int);
	void clear();
	int getSize();
	SinglyLinkedListIterator<T> getIterator();
};
template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	this->start = NULL;
	this->end = NULL;
	this->size = 0;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &other)
{
	this->size = 0;
	this->start = NULL;
	this->end = NULL;
	SinglyLinkedList<T> *node;
	node = other.start;
	while (node != NULL)
	{
		this->add(node->data);
		node = node->next;
	}
}

template <class T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> other)
{
	this->clear();
	SinglyLinkedList<T> *node;
	node = other.start;
	while (node != NULL)
	{
		this->add(node->data);
		node = node->next;
	}
}

template <class T>
T SinglyLinkedList<T>::operator[](int position)
{
	return this->get(position);
}

template <class T>
void SinglyLinkedList<T>::add(T data)
{
	SinglyLinkedListNode<T> *node = new SinglyLinkedListNode<T>(data);
	if (this->start == NULL)
	{
		this->start = node;
		this->end = node;
	}
	else
	{
		this->end->next = node;
		this->end = node;
	}
	this->size++;
}

template <class T>
void SinglyLinkedList<T>::insert(int position, T data)
{
	if (position > this->size)
		position = 0;
	if (position < 0)
		position = 0;
	if (position == this->size)
	{
		this->add(data);
		return;
	}
	SinglyLinkedListNode<T> *node;
	node = new SinglyLinkedListNode<T>(data);
	if (position == 0)
	{
		node->next = this->start;
		this->start = node;
	}
	else
	{
		SinglyLinkedListNode<T> *p1, *p2;
		p1 = this->start;
		for (int i = 0; i < position; ++i)
		{
			p2 = p1;
			p1 = p1->next;
		}
		p2->next = node;
		node->next = p1;
	}
	this->size++;
}

template <class T>
T SinglyLinkedList<T>::remove(int position)
{
	if (position < 0 || position >= this->size)
		throw SinglyLinkedListException(" -Invalid Index- ");
	SinglyLinkedListNode<T> *node;
	T data;
	if (this->size == 1)
	{
		node = this->start;
		this->start = NULL;
		this->end = NULL;
		this->size = 0;
		data = node->data;
		delete node;
		return data;
	}
	SinglyLinkedListNode<T> *temp;
	node = this->start;
	for (int i = 0; i < position; ++i)
	{
		temp = node;
		node = node->next;
	}
	if (this->start == node)
	{
		this->start = this->start->next;
		data = node->data;
		delete node;
		this->size--;
		return data;
	}
	if (this->end == node)
	{
		this->end = temp;
		this->end->next = NULL;
		this->size--;
		data = node->data;
		delete node;
		return data;
	}
	temp->next = node->next;
	this->size--;
	data = node->data;
	delete node;
	return data;
}

template <class T>
T SinglyLinkedList<T>::get(int position)
{
	if (position < 0 || position >= this->size)
		throw SinglyLinkedListException(" -Invalid Index- ");
	SinglyLinkedListNode<T> *node;
	node = this->start;
	for (int i = 0; i < position; ++i)
	{
		node = node->next;
	}
	return node->data;
}

template <class T>
void SinglyLinkedList<T>::clear()
{
	while (this->size > 0)
		this->remove(0);
}
template <class T>
int SinglyLinkedList<T>::getSize()
{
	return this->size;
}
template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	this->clear();
}
template <class T>
SinglyLinkedListIterator<T> SinglyLinkedList<T>::getIterator()
{
	return SinglyLinkedListIterator<T>(this->start);
}

//*********************************STACK************************************

template <class T>
class Stack
{
	SinglyLinkedList<T> list;

public:
	Stack();
	Stack(const Stack<T> &);
	~Stack();
	Stack<T> &operator=(Stack<T>);
	void push(T);
	T pop();
	T top();
	int isEmpty();
	int size();
};

template <class T>
Stack<T>::Stack()
{
}
template <class T>
Stack<T>::Stack(const Stack<T> &other)
{
	this->list = other.list;
}
template <class T>
Stack<T>::~Stack()
{
	this->list.clear();
}
template <class T>
Stack<T> &Stack<T>::operator=(Stack<T> other)
{
	this->list = other.list;
	return *this;
}
template <class T>
void Stack<T>::push(T data)
{
	this->list.insert(0, data);
}
template <class T>
T Stack<T>::pop()
{
	return this->list.remove(0);
}
template <class T>
int Stack<T>::isEmpty()
{
	return this->list.getSize() == 0;
}
template <class T>
int Stack<T>::size()
{
	return this->list->getSize();
}
template <class T>
T Stack<T>::top()
{
	return this->list.get(0);
}
