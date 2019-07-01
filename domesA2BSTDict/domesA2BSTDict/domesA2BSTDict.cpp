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

		bool deleteWord(string word) {
			//αν η λεξη που θελουμε να διαγραφει ειναι στη ριζα
			if (this->root != NULL && this->root->word == word) {
				//αν δεν υπαρχει δεξι υποδεντρο και υπαρχει αριστερο τοτε το πρωτο αριστερο στοιχειο παιρνει την θεση της ριζας.
				if (this->root->rightChild == NULL && this->root->leftChild != NULL) {
					Node *n = NULL;
					n = new Node();
					n = root->leftChild;
					delete this->root;
					this->root = n;
					return true;
				}
				//αν υπαρχει δεξι υποδεντρο τοτε παντοτε κοιταμε σε αυτο και αλλαζουμε τον διαγραφέντα κομβο
				//με τον κομβο που περιεχει την πιο "κοντινη" τιμη σε αυτον.
				if (this->root->rightChild != NULL) {
					Node *n = NULL;
					n = new Node();
					//επιστεφει το μικροτερο φυλο
					n = getSmallestLeaf(root->rightChild);

					if (n != this->root->rightChild) {
						n->rightChild = this->root->rightChild;
						n->leftChild = this->root->leftChild;
					}
					this->root = n;
					
					return true;
				}
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
	bst.deleteWord("a");
	bst.printInorder(bst.root);
    return 0;
}

