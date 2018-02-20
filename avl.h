#ifndef AVL_H
#define AVL_H
//--------------------------------------------------------------------
// An AVL tree class
// Compiled under MS Visual C++.Net 2005
// by Paul Bladek
// May, 2008
//--------------------------------------------------------------------
#include "bst.h"
using namespace std;

namespace AW_BST
{
	//--------------------------------------------------------------------
	// AVL Tree
	// Class:		avl<T>: public bst<T>
	//				REQUIRES Type T be able convert from int & have 
	//				< & == defined
	//
	// File:		avl.h
	// Title:		avl template Class; inherits from bst<T>
	// Description: This file contains the class definition for avl
	//
	// Programmer:	Paul Bladek
	//					Antony Waddell
	// 
	// Date:		May 2017
	// Version:		1.1
	// 
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	// 
	// class avl<T>:
	//
	//   Methods:
	// 
	//     inline: 
	//			avl() -- default constructor
	//			avl(const avl<T>& t) -- copy constructor (deep copy)
	//			avl<T>& operator+=(const T d) -- adds an element to the tree
	//			avl<T> operator+(const T d) -- adds an element to the tree
	//			void insert(T d) -- adds an element to the tree
	//			~avl() -- destructor	
	//
	//     non-inline:
	//			avl<T>& operator=(const avl<T>& t) -- deep copy
	//			avl<T>& operator+=(const avl<T>& t) -- adds an element to the tree
	//			void insert(T d, node<T>* &cur) -- adds an element to the tree
	//			T popnode(node<T>* &cur) -- returns element in node deleted
	//			T poplow(node<T>* &cur) -- returns element in leftmost node (deleted)
	//			T popfirst(const T& d, node<T>* np)
	//				-- returns element in first node matching d (deleted)
	//		protected:
	//			node<T>* rotateRight(node<T> *nodeN) -- balances tree	
	//			node<T>* rotateLeft(node<T> *nodeN) -- balances tree
	//			node<T>* rotateRightLeft(node<T> *nodeN) -- balances tree
	//			node<T>* rotateLeftRight(node<T> *nodeN) -- balances tree
	//			node<T>* rebalance(node<T> *&nodeN) -- balances tree
	//			int getHeightDifference(const node<T> *const nodeN)const
	//				-- returns the height difference between the left & right subtrees 
	//
	//
	// History Log: 
	//					May 20, 2008, PB  completed version 1.0 
	//					05-31-17 AW completed v 1.1
	//------------------------------------------------------------------- 

	template<class T>
	class avl : public bst<T>
	{
	public:
		avl() : bst() {}
		avl(const avl<T>& t) : bst(t) {}
		avl<T>& operator=(const avl<T>& t);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d) { insert(d); return *this; }
		avl<T> operator+(const T d)
		{
			avl<T> temp = *this; temp.insert(d); return temp;
		}
		bool insert(T d) { return insert(d, root); }
		bool insert(T d, node<T>* &cur);
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		~avl() { delTree(root); }

	protected:
		node<T>* rotateRight(node<T> *nodeN);
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		int getHeightDifference(const node<T> *const nodeN)const;
	};

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline avl<T>& avl<T>::operator=(const avl<T>& t)
	// Title:		Overloaded equal operator for avl class
	// Description: Sets *this avl tree equal to t
	//
	// Programmer:	Anthony Waddell
	// Date:		06-02-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		isempty()
	//				delTree()
	//				node<T>; constructor
	// Called By:	main()
	// Parameters:	const avl<T>& t; the tree to set *this equal to
	// Returns:		*this; an avl tree that is equal to t
	// History Log: 06-02-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline avl<T>& avl<T>::operator=(const avl<T>& t)
	{
		if (this != &t)
		{
			if (!isempty())
				delTree(root);

			if (!t.isempty())
			{
				root = new node<T>(*(t.root));
			}
		}
		return *this;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline avl<T>& avl<T>::operator+=(const avl<T>& t)
	// Title:		Adds one tree to another
	// Description: Adds contents of one tree to another tree
	//
	// Programmer:	Anthony Waddell
	// Date:		06-02-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		avl<T>; constructor
	//				isempty();
	//				popNode()
	//				getroot();
	//				insert()
	// Called By:	main()
	// Parameters:	const avl<T>& t; the tree to add the contents of
	// Returns:		*this; a tree that is the contains both it's original
	//				data as well as the data contained in t
	// History Log: 06-02-17 AW Completed v 1.0
	// Known Bugs:	Seems ineffecient
	//------------------------------------------------------------------------
	template<class T>
	inline avl<T>& avl<T>::operator+=(const avl<T>& t)
	{
		avl<char> tempTree = t;
		while (!tempTree.isempty())
		{
			T temp = popNode(tempTree.getroot());
			insert(temp, root);
		}
		return *this;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline bool avl<T>::insert(T d, node<T>*& cur)
	// Title:		Insert an element
	// Description: Inserts an element into the avl tree, does not allow 
	//				duplicate insertions.
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		<T> d; user supplied data from console
	// Output:		N/A
	// Calls:		isempty()
	//				node<T> *temp; constructor
	//				setHeight()
	//				value()
	//				insert(); recursively
	//				rebalance();
	// Called By:	operator+=(const T d)
	//				operator+(const T d)
	//				bool insert(T d, node<T>* &cur);
	//				bool insert(T d) ; recursively
	//				main()
	// Parameters:	T d; the data tp be inserted into the avl tree
	//				node<T>* &cur; parent node of the node to be inserted
	// Returns:		true if element was inserted; false if not
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline bool avl<T>::insert(T d, node<T>* &cur)
	{
		bool duplicate = false;
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (isempty())
				root = cur;
		}
		else
		{
			if (d == cur->value())
				return duplicate;
			else if (d < cur->value())
			{
				insert(d, cur->left);
				duplicate = true;
				rebalance(cur);
			}
			else
			{
				insert(d, cur->right);
				duplicate = true;
				rebalance(cur);
			}
			if (root != nullptr)
				root->setHeight();
		}
		return duplicate;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline T avl<T>::popnode(node<T>*& cur)
	// Title:		Removes a node from the tree
	// Description: Pops a node off of the avl tree and returns it's data
	//
	// Programmer:	Anthony Waddell
	// Date:		05-31-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		bst::popNode()
	//				rebalance()
	// Called By:	main()
	// Parameters:	node<T>*& cur; the node to remove from the avl tree
	// Returns:		T contents; the piece of m_data contained in the node
	//				that was removed
	// History Log: 05-31-17 AW Began v 1.0
	// Known Bugs:  Does not rebalance the tree after removal
	//------------------------------------------------------------------------
	template<class T>
	inline T avl<T>::popnode(node<T>*& cur)
	{
		T contents = bst::popNode(cur);
		rebalance(cur);
		return contents;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline T avl<T>::poplow(node<T>*& cur)
	// Title:		Removes the leftmost child
	// Description: Pops the left-most child off of the node passed in
	//				and returns it's data
	//
	// Programmer:	Anthony Waddell
	// Date:		06-01-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		bst::popLow()
	//				rebalance()
	// Called By:	main()
	// Parameters:	node<T>*& cur; the node to remove from the avl tree
	// Returns:		T contents; the piece of m_data contained in the node
	//				that was removed
	// History Log: 05-31-17 AW Began v 1.0
	// Known Bugs:  Does not rebalance the tree after removal
	//------------------------------------------------------------------------
	template<class T>
	inline T avl<T>::poplow(node<T>*& cur)
	{
		T contents = bst::popLow(cur);
		rebalance(cur);
		return contents;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline T avl<T>::popfirst(const T & d, node<T>* np)
	// Title:		Removes first occurence of node
	// Description: Pops the node containing the first occurence of that data
	//				passed in and returns that data
	//
	// Programmer:	Anthony Waddell
	// Date:		06-01-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		bst::popLow()
	//				rebalance()
	// Called By:	main()
	// Parameters:	node<T>*& cur; the node to remove from the avl tree
	// Returns:		T contents; the piece of m_data contained in the node
	//				that was removed
	// History Log: 05-31-17 AW Began v 1.0
	// Known Bugs:  Does not rebalance the tree after removal
	//------------------------------------------------------------------------
	template<class T>
	inline T avl<T>::popfirst(const T & d, node<T>* np)
	{
		//bool removed = false;
		////node<T> *temp = *this->getroot();
		//if (d < np->value())
		//{
		//	popfirst(d, np->left);
		//}
		//else if (d > np->value())
		//{
		//	popfirst(d, np->right);
		//}
		//else
		//{
		//	node<T> *temp;
		//	//temp = np->left;
		//	//node<T> *temp = np;
		//	//T contents = np->value();
		//	T contents = popnode(np);
		//	rebalance(*parentptr);
		//	return  contents;
		//}

		node<char>* parent = *parentptr;
		T contents = bst::popFirstOf(d, np);
		/*while (getHeightDifference(parent) > 1 || getHeightDifference(parent) < -1)*/
		rebalance(np);
		if (!contents)
			cout << "Could not locate node containing that data in tree" << endl;
		return contents;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline node<T>* avl<T>::rotateRight(node<T>* nodeN)
	// Title:		Right Right rotation
	// Description: Performs a right right rotation to balance the tree
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		node<T> *temp; constructor
	//				setHeight()
	// Called By:	rebalance()
	//				rotateRightLeft()
	//				rotateLeftRight()
	// Parameters:	node<T>* nodeN; the node to balance
	// Returns:		temp; the parent node to perform a right right rotation on
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline node<T>* avl<T>::rotateRight(node<T>* nodeN)
	{
		node<T> *temp;
		// Get temp to middle
		temp = nodeN->left;
		nodeN->left = temp->right;
		// Bring parent node to temp right to make into triangle
		temp->right = nodeN;
		nodeN->setHeight();
		temp->setHeight();
		return temp;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline node<T>* avl<T>::rotateLeft(node<T>* nodeN)
	// Title:		Left Left rotation
	// Description: Performs a left left rotation to balance the tree
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		node<T> *temp; constructor
	//				setHeight()
	// Called By:	rebalance()
	//				rotateRightLeft()
	//				rotateLeftRight()
	// Parameters:	node<T>* nodeN; the node to balance
	// Returns:		temp; the parent node to perform a left left rotation on
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline node<T>* avl<T>::rotateLeft(node<T>* nodeN)
	{
		node<T> *temp;
		// Get temp as middle nide
		temp = nodeN->right;
		nodeN->right = temp->left;
		// Bring parent node down to form balanced trianlge
		temp->left = nodeN;
		nodeN->setHeight();
		temp->setHeight();
		return temp;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline node<T>* avl<T>::rotateRightLeft(node<T>* nodeN)
	// Title:		Right Left rotation
	// Description: Performs a right left rotation to balance the tree
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		node<T> *temp; constructor
	//				rotateLeft()
	//				rotateRight()
	// Called By:	rebalance()
	// Parameters:	node<T>* nodeN; the node to balance
	// Returns:		temp; the parent node to perform a right left rotation on
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline node<T>* avl<T>::rotateRightLeft(node<T>* nodeN)
	{
		node<T> *temp;
		// Prepare for left rotation
		temp = nodeN->right;
		nodeN->right = rotateRight(temp);
		// Perform left rotation
		return rotateLeft(nodeN);
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline node<T>* avl<T>::rotateLeftRight(node<T>* nodeN)
	// Title:		Left Right rotation
	// Description: Performs a left right rotation to balance the tree
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		node<T> *temp; constructor
	//				rotateLeft()
	//				rotateRight()
	// Called By:	rebalance()
	// Parameters:	node<T>* nodeN; the node to balance
	// Returns:		temp; the parent node to perform a left right rotation on
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline node<T>* avl<T>::rotateLeftRight(node<T>* nodeN)
	{
		node<T> *temp;
		// Prepare for right rotation
		temp = nodeN->left;
		// Perform right rotation
		nodeN->left = rotateLeft(temp);
		return rotateRight(nodeN);
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline int avl<T>::getHeightDifference(const node<T>* 
	//				const nodeN) const
	// Title:		Gets height difference
	// Description: Gets the height difference between nodeN's left and right
	//				child nodes
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		getHeight()
	// Called By:	rebalance()
	// Parameters:	const node<T>* const nodeN; the node to get the height
	//				difference of child nodes from
	// Returns:		int m_heightDifference; the height difference between
	//				nodeN's left and right child nodes
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline int avl<T>::getHeightDifference(const node<T>* const nodeN) const
	{
		int m_leftHeight;
		int m_rightHeight;
		if (nodeN == nullptr)
			return 0;
		if ((nodeN->left) == nullptr)
		{
			m_leftHeight = 0;
		}
		else m_leftHeight = (nodeN->left)->getHeight();

		if ((nodeN->right) == nullptr)
		{
			m_rightHeight = 0;
		}
		else m_rightHeight = (nodeN->right)->getHeight();

		int m_heightDifference = m_leftHeight - m_rightHeight;
		return m_heightDifference;
	}

	//------------------------------------------------------------------------
	// Class:		avl.h
	// Function:	template<class T>
	//				inline node<T>* avl<T>::rebalance(node<T>*& nodeN)
	// Title:		Balances the avl tree
	// Description: Performs various balances on the avl tree
	//
	// Programmer:	Anthony Waddell
	// Date:		05-30-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		getHeightDifference()
	//				rotateRight()
	//				rotateLeft()
	//				rotateRightLeft()
	//				rotateLeftRight()
	// Called By:	insert()
	// Parameters:	node<T>*& nodeN); the node to perform a balance on
	// Returns:		node<T>* nodeN; the balanced node
	// History Log: 05-30-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	inline node<T>* avl<T>::rebalance(node<T>*& nodeN)
	{
		int leftImbalance = 1;
		int rightImbalance = -1;
		int balance = getHeightDifference(nodeN);
		if (nodeN == NULL)
			return nodeN;
		//If there are more elements on LHS
		if (balance > leftImbalance)
		{
			if (getHeightDifference(nodeN->left) > 0)
			{
				nodeN = rotateRight(nodeN);
			}
			else
			{
				nodeN = rotateLeftRight(nodeN);
			}
		}
		//If there are more elements on RHS
		else if (balance < rightImbalance)
		{
			if (getHeightDifference(nodeN->right) < 0)
			{
				nodeN = rotateLeft(nodeN);
			}
			else
			{
				nodeN = rotateRightLeft(nodeN);
			}
		}
		return nodeN;
	}
}
#endif
