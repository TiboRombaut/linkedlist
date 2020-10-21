#include "pch.h"
#include <iostream>
#include <list>
#include <iterator>
#include "LinkedList.h" 
#include <cassert>
#include <windows.h>
#include <string>

void StartHeapControl();
void DumpMemoryLeaks();

void TestList( );
void TestConstructor( );
void TestDestructor( );
void TestBegin( const LinkedList&  testList, const std::list<int>& refList );
void TestPushFront( LinkedList&  testList, std::list<int>& refList );
void TestInsertAfter( LinkedList&  testList, std::list<int>& refList, int value );
void TestPopFront( LinkedList&  testList, std::list<int>& refList );
void TestRemove( LinkedList&  testList, std::list<int>& refList, int value );
void TestCopy( const LinkedList&  testList, const std::list<int>& refList );
void TestMove( );
void PrintBothLists( const LinkedList&  testList, const std::list<int>& refList );
void VerifyListContent( const LinkedList&  testList, const std::list<int>& refList, bool withPrint = false );
LinkedList CreateList( int firstNr, int lastNr );

int main( )
{
	StartHeapControl();

	TestList();

	DumpMemoryLeaks();

	std::cout << "Verify yourself that no memory leaks are reported in the output window\n";
	std::cout << "Press ENTER to continue";
	std::cin.get( );
	return 0;
}



void TestList( )
{
	// TODO: 1. Define constructor and operator <<,  then uncomment next line
	TestConstructor(  );
	{
		// TODO: 2. Define PushFront, then uncomment next 3 lines
		std::list<int> refList;
		LinkedList  testList;
		TestPushFront( testList, refList );
		
		// TODO: 3. Define destructor and uncomment next line
		TestDestructor( );

		// TODO: 4. Define InsertAfter and uncomment next line
		TestInsertAfter( testList, refList, 20 );
		
		// TODO: 5. Define PopFront and uncomment next line
		TestPopFront( testList, refList );

		// TODO: 6. Define Remove and uncomment next line
		TestRemove( testList, refList, 20 );
			
		// TODO: 7. Define copy constructor and copy assignment operator and uncomment next line
		//TestCopy( testList, refList );

		// TODO: 8. Define move constructor and move assignment operator and uncomment next line
		//TestMove( );
	}
}

void TestConstructor(  )
{
	std::cout << "\n--> Construct and print an empty list <--\n";
	const LinkedList  testList;
	const std::list<int> refList;
	VerifyListContent( testList, refList, true );
	std::cout << "<-- OK -->\n";
}

void TestBegin( const LinkedList&  testList, const std::list<int>& refList )
{
	Node* pTestNode = testList.Begin( );
	std::list<int>::const_iterator refIt = refList.cbegin( );
	if ( pTestNode == nullptr &&  refIt == refList.cend( ) ) // both empty
	{
		return;
	}
	if ( pTestNode != nullptr &&  refIt != refList.cend( ) ) // not empty lists
	{
		assert( pTestNode->value == *refIt ); // first value should be the same
		return;
	}
	std::cout << "Begin() doesn't give the expected value ";
	assert( false );
}

void TestPushFront( LinkedList&  testList, std::list<int>& refList )
{
	std::cout << "\n--> PushFront <--\n";
	for ( int nr{ 10 }; nr >= 1; --nr )
	{
		testList.PushFront( nr );
		refList.push_front( nr );
	}
	std::cout << "stop" << std::endl;
	VerifyListContent( testList, refList, true );
	std::cout << "<-- OK -->\n";
}

void TestDestructor( )
{
	std::cout << "\n--> Test Destructor <--\n";
	{
		LinkedList  testList;
		std::list<int> refList;

		for ( int nr{ 10 }; nr >= 1; --nr )
		{
			testList.PushFront( nr );
			refList.push_front( nr );
		}
	} // list goes out of scope
	std::cout << "<-- OK -->\n";
}

void TestInsertAfter( LinkedList&  testList, std::list<int>& refList, int value )
{
	std::cout << "\n--> InsertAfter <--\n";
	Node* beforeNode = testList.Begin( );
	std::cout << "- Insert value " << value << " after first node (" << beforeNode->value << ")\n";
	std::list<int>::iterator afterIt = refList.begin( );
	afterIt++;
	testList.InsertAfter( beforeNode, value );
	refList.insert( afterIt, value );
	VerifyListContent( testList, refList, true );

	// Somewhere in the middle
	afterIt = refList.begin( );
	size_t displacement{ refList.size( ) / 2 };
	beforeNode = testList.Begin( );
	for ( size_t nr{ 0 }; nr < displacement; ++nr )
	{
		afterIt++;
		beforeNode = beforeNode->pNext;
	}
	afterIt++;
	std::cout << "- Insert value " << value << " , after node with value " << beforeNode->value << "\n";
	testList.InsertAfter( beforeNode, value );
	refList.insert( afterIt, value );
	VerifyListContent( testList, refList, true );

	// After the last node
	std::cout << "- Insert value " << value << " at the end of the list " << "\n";
	//while ( beforeNode->pNext != nullptr )
	//{
	//	beforeNode = beforeNode->pNext;
	//}
	//testList.InsertAfter( beforeNode, value );
	//refList.push_back( value );
	//VerifyListContent( testList, refList, true );
	std::cout << "<-- OK -->\n";
}

void TestPopFront( LinkedList&  testList, std::list<int>& refList )
{
	std::cout << "\n--> Test PopFront <--\n";
	VerifyListContent( testList, refList, true );
	testList.PopFront( );
	refList.pop_front( );
	std::cout << "- After first call\n";
	VerifyListContent( testList, refList, true );

	testList.PopFront( );
	refList.pop_front( );
	std::cout << "- After second call\n";
	VerifyListContent( testList, refList, true );

	// On an empty list
	std::cout << "- Calling PopFront on an empty list\n";
	LinkedList emptyList;
	emptyList.PopFront();
	std::cout << "<-- OK -->\n";
}

void TestRemove( LinkedList&  testList, std::list<int>& refList, int value )
{
	std::cout << "\n--> Test Remove <--\n";
	// First add some nodes with same value
	testList.PushFront( value );
	refList.push_front( value );
	testList.PushFront( value );
	refList.push_front( value );

	// Print the lists before removing nodes
	std::cout << "Before removing value " << value << "\n";
	PrintBothLists( testList, refList );
	testList.Remove( value );
	refList.remove( value );
	std::cout << "After removing value " << value << "\n";
	PrintBothLists( testList, refList );
	VerifyListContent( testList, refList, false );

	// On an empty list
	std::cout << "- Calling Remove on an empty list\n";
	LinkedList emptyList;
	emptyList.Remove(20);

	std::cout << "<-- OK -->\n";
}

void TestCopy(const LinkedList&  list, const std::list<int>& refList)
{
	const LinkedList emptyList;
	const std::list<int> refEmptyList;
	// Copy constructor
	{
		std::cout << "\n--> Test copy constructor <--\n";
		std::cout << "- Argument is a non-empty LinkedList\n";
		LinkedList testList1{ list };
		VerifyListContent(testList1, refList);
		std::cout << "- Argument is an empty LinkedList\n";
		LinkedList testList2{ emptyList };
		VerifyListContent(testList2, refEmptyList);
	}
	std::cout << "<-- OK -->\n";

	// Copy assignment
	{
		std::cout << "\n--> Test copy assignment <--\n";
		{
			LinkedList testList{ list };
			std::cout << "- Self assignment\n";
			testList = testList; // self assignment
			VerifyListContent(testList, refList);

			std::cout << "- Copy assignment of a non-empty LinkedList\n";
			LinkedList testList1{ list };
			LinkedList testList2{ list };
			testList1 = testList2;
			VerifyListContent(testList1, refList);

			std::cout << "- Copy assignment of an empty LinkedList\n";
			testList1 = emptyList;
			VerifyListContent(testList1, refEmptyList);
		}
		std::cout << "<-- OK -->\n";
	}
}

void TestMove()
{
	// Create lists that will be used as a reference
	std::list<int> refList;
	const int firstNr{ 1 };
	const int lastNr{ 10 };
	for (int nr{ firstNr }; nr <= lastNr; ++nr)
	{
		refList.push_back(nr);
	}
	const std::list<int> refEmptyList;

	// Move constructor
	{
		std::cout << "\n--> Test Move constructor <--\n";
		std::cout << "- Argument is a non-empty LinkedList\n";
		LinkedList testList1{ CreateList(firstNr, lastNr) };
		VerifyListContent(testList1, refList);

		std::cout << "- Argument is an empty LinkedList\n";
		LinkedList emptyList;
		LinkedList testList2{ std::move(emptyList) };
		VerifyListContent(testList2, refEmptyList);
	}
	std::cout << "<-- OK -->\n";

	// Move assignment
	{
		std::cout << "\n--> Test Move assignment <--\n";
		std::cout << "- Self assignment\n";
		LinkedList testList1{ CreateList(firstNr + 10, lastNr + 10) };
		testList1 = std::move(testList1);

		std::cout << "- Move assignment of a non-empty LinkedList\n";
		testList1 = CreateList(firstNr, lastNr);
		VerifyListContent(testList1, refList);

		std::cout << "- Move assignment of an empty LinkedList\n";
		LinkedList emptyList;
		testList1 = std::move(emptyList);
		VerifyListContent(testList1, refEmptyList);
	}
	std::cout << "<-- OK -->\n";
}


void PrintBothLists( const LinkedList&  testList, const std::list<int>& refList )
{
	std::cout << "Yours   : " << testList << "\n";
	std::cout << "Expected: ";
	for ( Node node : refList )
	{
		std::cout << node.value;
		std::cout << " ";
	}
	std::cout << "\n";
}

void VerifyListContent( const LinkedList&  testList, const std::list<int>& refList, bool withPrint )
{
	// Check Begin
	TestBegin( testList, refList );

	if ( withPrint )
	{
		PrintBothLists( testList, refList );
	}

	// Check size
	size_t size = testList.Size( );
	assert( size == refList.size( ) );

	// Check values
	Node *pNode = testList.Begin( );
	std::list<int>::const_iterator it = refList.cbegin( );
	for ( size_t nr{ 0 }; nr < size; ++nr )
	{
		// Test values are equal
		int testValue{ pNode->value };
		int refvalue{ *it };
		assert( testValue == refvalue );

		// next
		pNode = pNode->pNext;
		++it;
	}
}

LinkedList CreateList( int firstNr, int lastNr )
{
	LinkedList list;
	for ( int value = lastNr; value >= firstNr; --value )
	{
		list.PushFront( value );
	}
	return list;
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}

void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 144 );
#endif
}
