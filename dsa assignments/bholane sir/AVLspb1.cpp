#include <iostream>
//#include <conio.h>
#include <string.h> // For string functions
using namespace std;

class Node
{
private:
	char word[50];
	char meaning[100];
	Node * left;
	Node * right;

public:
	Node()
	{
		strcpy(word, "");
		strcpy(meaning, "");
		left = NULL; right = NULL;
	}

	Node(const char w[], const char m[])
	{
		strcpy(word, w);
		strcpy(meaning, m);
		left = NULL; right = NULL;
	}

	friend class AVL;
};

class AVL
{
private:
	Node * root;
	Node * getNode(const char word[], const char meaning[]);
	Node * rotateLeft(Node *);
	Node * rotateRight(Node *);
	Node * LR(Node *);
	Node * RL(Node *);
	Node * insertNode(Node *root, const char word[], const char meaning[]);
	Node * deleteNode(Node *root, const char word[]);
	Node * findMin(Node *root);
	int height(Node *);
	void preorder(Node *root);

public :
	AVL(){root=NULL;}
	void create(void);
	void preorder( )    //Public interface since root
			    //not accessible in main
	{
	  preorder(root);   // Calls private interface where
			    //root is accessible
	}
	void insert(const char word[], const char meaning[]);
	void remove(const char word[]);
};

void AVL::insert(const char word[], const char meaning[]) {
	root = insertNode(root, word, meaning);
}

void AVL::remove(const char word[]) {
	root = deleteNode(root, word);
}

// Calculate maximum of two integers
int max(int no1, int no2)
{
	if(no1 > no2)
		return no1;
	else
		return no2;
}

// Calculate height of tree rooted at 'root'
int AVL::height(Node * root)
{
	if(root==NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	else
		return(max(height(root->left),height(root->right))+1);
}

// Right rotation for LL imbalance
Node * AVL::rotateRight(Node * pivot)
{
	Node * temp;
	temp=pivot->left;        //preserve pivot's left child
	pivot->left=temp->right; //right child of (left child of pivot)
							 //becomes left child of pivot
	temp->right=pivot; 	   //attach pivot as right child
	return temp;  	   //return left child of pivot as it becomes root
}

// Left rotation for RR imbalance
Node * AVL::rotateLeft(Node * pivot)
{
	Node * temp;
	temp=pivot->right; 	  //preserve pivot's right child
	pivot->right=temp->left; //left child of (right child of pivot)
							 //becomes right child of pivot
	temp->left=pivot; 	  //attach pivot as left child
	return temp;		  //return right child of pivot as it becomes root
}

// LR rotation for LR imbalance
Node * AVL::LR(Node * pivot)
{
	pivot->left=rotateLeft(pivot->left);    // Left rotation
	pivot=rotateRight(pivot);                // Right rotation
	return pivot;
}

// RL rotation for RL imbalance
Node * AVL::RL(Node * pivot)
{
	pivot->right=rotateRight(pivot->right); // Right rotation
	pivot=rotateLeft(pivot);                 // Left rotation
	return pivot;
}

// Create AVL tree
void AVL::create(void)
{
	char word[50], meaning[100];
	char ch;
	while(1)
	{
		cout<<"\nEnter a Word: ";
		cin>>word;
		cout<<"\nEnter the Meaning: ";
		cin>>meaning;
		root = insertNode(root, word, meaning);
		cout<<"\nWant to Continue??";
		cin>>ch;
		if(ch=='y'|| ch=='Y')
			continue;
		else
			break;
	}
}

// Preorder traversal of AVL tree
void AVL::preorder(Node *root)
{
	if(root!=NULL)
	{
		cout<<" "<<root->word<<" - "<<root->meaning;
		preorder(root->left);
		preorder(root->right);
	}
}

// Insert node with key 'word' and 'meaning' into AVL tree rooted at 'root'
Node * AVL::insertNode(Node *root, const char word[], const char meaning[])
{
	int lh, rh;
	if(root == NULL)
	{
		root = getNode(word, meaning);  //create root / new node
	}
	else
	{
		int cmp = strcmp(word, root->word);
		if(cmp < 0)   // add to left subtree
		{
			root->left = insertNode(root->left, word, meaning);

			// Check and rotate for left subtree imbalance
			lh=height(root->left);
			rh=height(root->right);
			if((lh-rh)==2)   // imbalance at CURRENT root
			{
				if(strcmp(word, root->left->word) < 0) // left of left high
				{
					cout<<"\nImbalance due to LL insertion";
					cout<<word<<" inserted to left of "<<root->word<<" then left of "<<root->left->word;
					cout<<"\nRotate Right around Pivot "<<root->word;
					root=rotateRight(root);   //RIGHT ROTATE
				}
				else
				{
					cout<<"\nImbalance due to LR insertion at "<<root->word;
					root=LR(root);   //FIRST LEFT THEN RIGHT ROTATE
				}
			}
		}
		else if(cmp > 0)  // add to right subtree
		{
			root->right = insertNode(root->right, word, meaning);

			// Check and rotate for right subtree imbalance
			lh=height(root->left);
			rh=height(root->right);
			if((rh-lh)==2)   // imbalance at CURRENT root
			{
				if(strcmp(word, root->right->word) > 0) // right of right high
				{
					cout<<"\nImbalance due to RR insertion";
					cout<<"\nRotate Left around Pivot "<<root->word;
					root=rotateLeft(root);   //LEFT ROTATE
				}
				else
				{
					cout<<"\nImbalance due to RL insertion at "<<root->word;
					root=RL(root);   //FIRST RIGHT THEN LEFT ROTATE
				}
			}
		}
		else
			cout<<"\nDuplicate Word Found";
	}
	return root;
}

// Delete node with key 'word' from AVL tree rooted at 'root'
Node * AVL::deleteNode(Node *root, const char word[])
{
	if(root == NULL)
		return root;

	int cmp = strcmp(word, root->word);

	// If the word to be deleted is smaller, then it lies in the left subtree
	if(cmp < 0)
		root->left = deleteNode(root->left, word);

	// If the word to be deleted is greater, then it lies in the right subtree
	else if(cmp > 0)
		root->right = deleteNode(root->right, word);

	// If word is same as root's word, then this is the node to be deleted
	else
	{
		// Node with only one child or no child
		if(root->left == NULL)
		{
			Node *temp = root->right;
			delete root;
			return temp;
		}
		else if(root->right == NULL)
		{
			Node *temp = root->left;
			delete root;
			return temp;
		}

		// Node with two children: Get the inorder successor (smallest in the right subtree)
		Node* temp = findMin(root->right);

		// Copy the inorder successor's content to this node
		strcpy(root->word, temp->word);
		strcpy(root->meaning, temp->meaning);

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->word);
	}

	// If the tree had only one node then return
	if(root == NULL)
		return root;

	// Update height of the current node
	int lh = height(root->left);
	int rh = height(root->right);

	// Check balance factor to determine if rotation is needed
	if((lh - rh) >= 2)
	{
		if(height(root->left->left) >= height(root->left->right))
			root = rotateRight(root);
		else
			root = LR(root);
	}
	else if((rh - lh) >= 2)
	{
		if(height(root->right->right) >= height(root->right->left))
			root = rotateLeft(root);
		else
			root = RL(root);
	}

	return root;
}

// Find the node with minimum value in the tree rooted at 'root'
Node* AVL::findMin(Node* root)
{
	Node* current = root;

	// Loop down to find the leftmost leaf
	while(current && current->left != NULL)
		current = current->left;

	return current;
}

Node * AVL::getNode(const char word[], const char meaning[])
{
	Node * temp;
	temp = new Node(word, meaning);
	return temp;
}

int main()
{
	AVL t;
	char ch;
	//clrscr();
	t.create();
	cout<<"\n\nPre-Order Traversal Is :";
	t.preorder();
	do
	{
		cout<<"\n\nM E N U ";
		cout<<"\n1. Insert \n2. Delete \n3. Print \n4. Exit";cin>>ch;
		switch(ch)
		{
			case '1':
			{
				char word[50], meaning[100];
				cout<<"\nEnter the Word: ";cin>>word;
				cout<<"\nEnter the Meaning: ";cin>>meaning;
				t.insert(word, meaning);
				cout<<"\n\nPre-Order Traversal Is :";
				t.preorder();
				break;
			}
			case '2':
			{
				char word[50];
				cout<<"\nEnter the Word to Delete: ";cin>>word;
				t.remove(word);
				cout<<"\n\nPre-Order Traversal Is :";
				t.preorder();
				break;
			}
			case '3':
			{
				cout<<"\n\nPre-Order Traversal Is :";
				t.preorder();
				break;
			}
		}
	}while(ch!='4');
	//getch();
	return 0;
}
