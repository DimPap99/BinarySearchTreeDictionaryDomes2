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

		Node::~Node() {
			delete this;
		}
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
	bst.insert("d", "D");
	bst.insert("b", "B");
	bst.insert("e", "E");
	bst.printInorder(bst.root);
    return 0;
}

