#include "pch.h"
#include "LinkedList.h"

Node::Node(int value, Node *pNext)
	:value{ value }
	, pNext{ pNext }
{
}

LinkedList::LinkedList()
	:m_pFirstNode()
	,m_Size(0)
{
}

LinkedList::~LinkedList()
{
	
	while (m_pFirstNode != nullptr)
	{
		Node* destruct;
		destruct = m_pFirstNode;
		m_pFirstNode = m_pFirstNode->pNext;
		delete destruct;
	}

	delete m_pFirstNode;
	m_pFirstNode = nullptr;
}

LinkedList::LinkedList( const LinkedList& other )
{
}

LinkedList& LinkedList::operator=( const LinkedList& other )
{
	return *this;
}

LinkedList::LinkedList( LinkedList&& other )noexcept
{
}

LinkedList& LinkedList::operator=(  LinkedList&& other )noexcept
{
	return *this;
}

// Wrap the value in a new Node object and add it as first Node of the list
void LinkedList::PushFront( int  value )
{
	//Node* node{ new Node{ value,nullptr } };
	if (m_Size == 0)
	{
		Node* node{ new Node{ value,nullptr } };
		m_pFirstNode = node;
		m_Size++;
	}
	else
	{
		Node* node{ new Node{ value,m_pFirstNode} };
		m_pFirstNode = node;
		m_Size++;
	}
}

// Remove and delete first Node
void LinkedList::PopFront( )
{
	if (m_pFirstNode != nullptr)
	{
		Node* destruct;
		destruct = m_pFirstNode;
		m_pFirstNode = m_pFirstNode->pNext;
		delete destruct;
		m_Size--;
	}
}

// Remove all Nodes having this value
void LinkedList::Remove( int value )
{
	if (m_pFirstNode != nullptr) {
		while (m_pFirstNode->value == value)
		{
			PopFront();
		}
		
		Node* p = new Node{ 0,m_pFirstNode };
	//	p = m_pFirstNode;
		Node* before;
		while (p != nullptr) {
			before = p;
			p = p->pNext;
			if (p == nullptr)
			{
				break;
			}
			if (p->value == value) {
				before->pNext = p->pNext;
				delete p;
				m_Size--;
				break;
			}
		}
	}
}

// Wrap the value in a new Node object and insert it after the specified Node 
void LinkedList::InsertAfter( Node* pBefore, int value )
{
	Node* p;
	for (p = m_pFirstNode; p != 0; p = p->pNext) {
		if (p->pNext == pBefore->pNext)
		{
			Node* newNode{ new Node{ value,p->pNext } };
			p->pNext = newNode;
			m_Size++;
		}
	}
}

// Return pointer to first Node
Node* LinkedList::Begin( ) const
{
	return m_pFirstNode;
}

// Return number of Node objects in the list
size_t LinkedList::Size( ) const
{
	return m_Size;
}

// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<( std::ostream& out, const LinkedList& list )
{
	Node* p;
	for (p = list.Begin(); p != 0; p = p->pNext) {
		out << p->value << " ";
	}
	return out;
}
