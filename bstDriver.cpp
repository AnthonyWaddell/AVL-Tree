//----------------------------------------------------------------------------
// File:		bstDriver.cpp
// 
// Description: Test Driver for the bst class and it's
//				publicly inherited avl class
// 
// Programmer:  Anthony Waddell
//
// Functions:   main()
// 
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015
//-------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include "bst.h"
#include "avl.h";
using namespace std;

//---------------------------------------------------------------------------
// Function:	main()
// Title:		Using self-balancing avl trees
// Description: This file contains function main() which tests the 
//				bst class and its inherited avl class
//
// Programmer:	Anthony Waddell
// Date:		05-31-17
// Version:		1.0
// Environment: Hardware: PC, i7        
//				Software: OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		User-supplied elements to fill and test an inherited AVL tree
// Output:		Various operations performed on a AVL tree inherited from a
//				binary search tree
// Calls:		bst base class and it's inherited avl class
// Called By:	n/a
// Parameters:  None
// Returns:		EXIT_SUCCESS  upon successful execution
//
// History Log:	05-24-17 AW Began Project
//				06-05-17 AW Completed project
// Known Bugs:  avl<T>::popnode() does not properly rebalance the avl tree
//				avl<T>::poplow() does not properly rebalance the avl tree
//				avl<T>::popfirst() does not properly rebalance the avl tree
//----------------------------------------------------------------------------
int main(void)
{
	using AW_BST::bst;
	using AW_BST::node;
	using AW_BST::avl;
	try
	{
		avl<char> tree;
		avl<char> tree2;
		avl<char> tree3;
		avl<char> tree4;
		node<char>* marker = nullptr;
		char c;

		//	Test of insert(), reblance(), getHeightDifference, and rotatation 
		//	functions
		cout << "Test of insert(), rebalance, getHeightDifference, and"
			<< " rotation functions" << endl << endl;
		cout << "enter some characters for tree 1, followed by <ENTER>.\n" ;
		do
		{ 
			cin.get(c);
			if(c == '\n')
				break;
			tree.insert(c);
		}
		while(true);
		cout << "------------- tree 1 ----------------" << endl << endl;
		tree.printXlevel(cout);
		cout << "--------- reference tree ----------------" << endl << endl;
		avl<char> referenceTree(tree);
		referenceTree.printXlevel(cout);

		//	Test of operator= and operator+= 
		cout << endl << "Test of operator= on tree 2 and reference tree:"
			<< endl;
		tree2 = referenceTree;
		cout << "------------- tree 2 ----------------" << endl << endl;
		tree2.printXlevel(cout);
		cout << endl << "Enter some characters for tree 3, followed by <ENTER>.\n";
		do
		{
			cin.get(c);
			if (c == '\n')
				break;
			tree3.insert(c);
		}
		while (true);
		cout << "------------- tree 3 ----------------" << endl << endl;
		tree3.printXlevel(cout);
		cout << endl << "Test of operator += on tree 2 and tree 3" << endl;
		tree3 += tree2;
		cout << "------------- tree 3 ----------------" << endl << endl;
		tree3.printXlevel(cout);
		
		//	Test of operator+=(const T d)
		cout << endl << "Test of operator+=(const T d)" << endl;
		cout <<  "Enter an element to insert into tree3: ";
		cin >> c;
		tree3 += c;
		cout << "-------- tree 3 now contains ---------" << endl;
		tree3.printXlevel(cout);
		cin.get();

		//	Test of popnode()
		node<char>* test = tree3.getroot()->right;
		cout << endl << "Test of popnode()" << endl;
		cout << "Popping the right node of root of tree3" << endl;
		cout << tree3.popNode(test) << endl;
		cout << "-------- tree 3 now contains ---------" << endl;
		tree3.printXlevel(cout);

		//	Test of popfirst()
		cout << endl << "Test of popfirst()" << endl;
		cout << "Please enter the data of a node you wish to pop from tree3: ";
		cin >> c;
		cout << tree3.popfirst(c, tree3.getroot()) << endl;
		cout << "-------- tree 3 now contains ---------" << endl;
		tree3.printXlevel(cout);

		//	Test of poplow()
		cout << "Test of popLow()" << endl;
		cout << "Popping the left-most child node of root of tree3" << endl;
		cout << tree3.poplow(tree3.getroot());
		cout << "-------- tree 3 now contains ---------" << endl;
		tree3.printXlevel(cout);
		cin.get();

	}
	catch(invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(bad_alloc e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << endl << "press <Enter> to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
}