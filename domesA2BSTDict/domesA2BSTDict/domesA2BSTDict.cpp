// domesA2BSTDict.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
//Το δυαδικο δεντρο αναζήτησης θα περιέχει κομβους.
//Καθε κομβος θα περιέχει ένα integer ο οποίος αναπαριστά το επίπεδο, 2 string την λεξη στα αγγλικα και την μετάφραση αντίστοιχα
//τέλος pointers στο αριστερό και δεξιό παιδί (κόμβο) του υποδέντρου.
class Node{
	public:
		int nodeLevel = 1;
		string word = "";
		string translation = "";
		Node *leftChild = NULL;
		Node *rightChild = NULL;

	/*Node::~Node(){
		delete this;
	}*/
		
};

//BST creation
//To BST αποτελείται από κόμβους της κλάσης Node.
class BinarySearchTree {
	public:
		Node *root = NULL;

		bool insert(string word, string translation) {

			//if the rood in NULL the we add the word and its translation 
			//to the root Node.
			if (this->root == NULL) {
				root = new Node();
				root->word = word;
				root->translation = translation;
				this->root = root;
				return true;
			}
			int countlevels = 1;
			//δεικτης που δειχνει στη ριζα
			Node *n = NULL;
			n = root;
			while (n != NULL) {
				//Αν η λεξη ειναι μικροτερη αλφαβητικά της λέξης του κομβού συνεχίζω προς το αριστερό παιδι αν αυτο υπαρχει.
				if (word < n->word && n->word != "" && n->leftChild != NULL) {
					n = n->leftChild;
					countlevels++;
				}
				//Αν η λεξη ειναι μικροτερη αλφαβητικά της λέξης του κομβού συνεχίζω και δεν υπαρχει αριστερο παιδι
				//το δημιουργω και αποθηκευω την λεξη
				if (word < n->word && n->word != "" && n->leftChild == NULL) {
					Node *leftChild = NULL;
					leftChild = new Node();
					leftChild->word = word;
					leftChild->translation = translation;
					leftChild->nodeLevel = countlevels;
					n->leftChild = leftChild;
					return true;
				}

				//Αν η λεξη ειναι μεγαλύτερη αλφαβητικά της λέξης του κομβού συνεχίζω προς το δεξί παιδι αν αυτο υπαρχει.
				if (word > n->word && n->word != "" && n->rightChild != NULL) {
					n = n->rightChild;
					countlevels++;
				
				}
				if (word > n->word && n->word != "" && n->rightChild == NULL) {
					Node *rightChild = NULL;
					rightChild = new Node();
					rightChild->word = word;
					rightChild->translation = translation;
					rightChild->nodeLevel = countlevels;
					n->rightChild = rightChild;
					return true;

				}

				//Αν ο κόμβος μας έχει τιμή Null τότε αυτό σημαίνει ότι δεν υπάρχει κάποια λέξη αποθηκευμένει σ αυτόν
				//Οποτε η λεξη αποθηκεύεται.
				/*if (root = NULL) {
					root = new Node();
					root->word = word;
					root->translation = translation;
					root->nodeLevel = countlevels++;
					return true;
				}*/
			}
			return false;
		}

		//βρισκει το μικροτερο σε τιμη φυλλο μεσα σε ενα δεντρο.
			 Node *getSmallestLeaf(Node *subtreeRoot) {
				 Node *n = NULL;
				 Node *prevNode = NULL;
			while (subtreeRoot != NULL) {
				if (subtreeRoot->leftChild == NULL && subtreeRoot->rightChild == NULL) {
					n = new Node();
					n->word = subtreeRoot->word;
					n->translation = subtreeRoot->translation;
					n->leftChild = NULL;
					n->rightChild = NULL;
					//delete subtreeRoot;
					subtreeRoot = NULL;
					//θετουμε το παιδι του γονέα null αφου θα το μετακινησουμε
					prevNode->leftChild = NULL;
					break;
				}
				//κραταμε τον γονεα του φυλλου
				if (subtreeRoot->leftChild != NULL && subtreeRoot->leftChild->leftChild == NULL) {
					prevNode = subtreeRoot;
				}
				n = subtreeRoot;
				subtreeRoot = subtreeRoot->leftChild;
				
			}
			
			
			//delete subtreeRoot;
			return n;
		}
			 Node * minValueNode( Node* node)
			 {
				 Node* current = node;

				 /* loop down to find the leftmost leaf */
				 while (current && current->leftChild != NULL)
					 current = current->leftChild;

				 return current;
			 }
			 /* Given a binary search tree and a key, this function deletes the key
			 and returns the new root */
			 struct Node* deleteNode( Node* root, string word)
			 {
				 // base case 
				 if (root == NULL) return root;

				 // If the key to be deleted is smaller than the root's key, 
				 // then it lies in left subtree 
				 if (word < root->word)
					 root->leftChild = deleteNode(root->leftChild, word);

				 // If the key to be deleted is greater than the root's key, 
				 // then it lies in right subtree 
				 else if (word > root->word)
					 root->rightChild = deleteNode(root->rightChild, word);

				 // if key is same as root's key, then This is the node 
				 // to be deleted 
				 else
				 {
					 // node with only one child or no child 
					 if (root->leftChild == NULL)
					 {
						 Node *temp = root->rightChild;
						 free(root);
						 return temp;
					 }
					 else if (root->rightChild == NULL)
					 {
						 Node *temp = root->leftChild;
						 free(root);
						 return temp;
					 }

					 // node with two children: Get the inorder successor (smallest 
					 // in the right subtree) 
					 Node* temp = minValueNode(root->rightChild);

					 // Copy the inorder successor's content to this node 
					 root->word = temp->word;

					 // Delete the inorder successor 
					 root->rightChild = deleteNode(root->rightChild, temp->word);
				 }
				 return root;
			 }
		void printInorder(Node *root) {

			if (root == NULL) {
				return;
			}

			printInorder(root->leftChild);
			cout << root->word << " ";
			printInorder(root->rightChild);

		}
			

};


int main()
{
	BinarySearchTree bst;
	bst.insert("a", "A");
	bst.insert("e", "E");
	//bst.insert("d", "E");
	bst.insert("g", "G");
	bst.insert("f", "f");
	//bst.insert("c", "C");
	//bst.insert("b", "B");
	/*bst.insert("c", "C");
	bst.insert("e", "E");
	bst.insert("g", "G");
	bst.insert("f", "F");
	*/bst.printInorder(bst.root);
	cout << endl;
	bst.deleteNode(bst.root,"e");
	bst.printInorder(bst.root);
    return 0;
}

