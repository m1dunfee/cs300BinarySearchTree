//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    void destroy(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe (2)
    // recurse from root deleting every node
    destroy(root); //cant recusivly delete without changing the function definition or creating a new function..
}

/**
* Destructor helper
*/
void BinarySearchTree::destroy(Node* node) {
    //filo to left leaf delete, then sibling, then parent... < > ^ 
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (3a): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (4a): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (5a): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (6a) Implement inserting a bid into the tree
    // if root equarl to null ptr
      // root is equal to new node bid
    // else
      // add Node root and bid (what langauge was this originally written in, chinese?)
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        addNode(root, bid);
    }

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (7a) Implement removing a bid from the tree
    // remove node root bidID
    root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (8) Implement searching the tree for a bid
    // set current node equal to root

    // keep looping downwards until bottom reached or matching bidId found
        // if match found, return current bid

        // if bid is smaller than current node then traverse left
        // else larger so traverse right
    Node* cur = root;
    while (cur != nullptr && cur->bid.bidId != bidId) {
        if (bidId < cur->bid.bidId) {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    if (cur != nullptr) {
        return cur->bid;
    }
    else {
        return Bid(); //this line im not a big fan of. I rather check for null, but the syntax is throwing a fit and time is time.
    }

}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (6b) Implement inserting a bid into the tree
    // if node is larger then add to left
        // if no left node
            // this node becomes left
        // else recurse down the left node
    // else
        // if no right node
            // this node becomes right
        //else
            // recurse down the left node
    Node* cur = node;
    if (bid.bidId < cur->bid.bidId) {
        if (cur->left == nullptr) {
            cur->left = new Node(bid);
        }
        else {
            addNode(cur->left, bid);
        }
    }
    else {
        if (cur->right == nullptr) {
            cur->right = new Node(bid);
        }
        else {
            addNode(cur->right, bid);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
      // FixMe (3b): Pre order root
      //if node is not equal to null ptr
      //InOrder not left
      //output bidID, title, amount, fund
      //InOder right

      //this part make me realize how much I could refactor my code for readability, while the structure can be helpful, it also creates a lot of vertical space.
      // in the future I might try a refactor on this code where I use one line for single statment ifs and just not use else when not needed. 
      // I think there is an arguement for both, but I would like to see it. For now I will keep it the same for uniformity.
    if (node == nullptr) {
        return;
    }
    else {
        inOrder(node->left);
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
      // FixMe (4b): Pre order root
      //if node is not equal to null ptr
      //postOrder left
      //postOrder right
      //output bidID, title, amount, fund
    if (node == nullptr) {
        return;
    }
    else {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (5b): Pre order root
      //if node is not equal to null ptr
      //output bidID, title, amount, fund
      //postOrder left
      //postOrder right     
      
    //these three print functions dont feel dry. I rather have a loop and a sequence string. I suppse that would add to time complexity through... 3 functions at  O(1) or 1 funcion at O(1)x3 or less.
    //We are only suppose to care about the greatest funtion though and not the leading coeficients right? so 3xO(1) is still just O(1), right?
    if (node == nullptr) {
        return;
    }
    else {
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        postOrder(node->left);
        postOrder(node->right);
    }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // FIXME (7b) Implement removing a bid from the tree
    // if node = nullptr return node
    // (otherwise recurse down the left subtree)
    // check for match and if so, remove left node using recursive call 
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    // (otherwise no children so node is a leaf node)
    // if left node = nullptr && right node = nullptr delete node 
    // (otherwise check one child to the left)
    // if left node != nullptr && right node = nullptr delete node 
    // (otherwise check one child to the right)
    // if left node = nullptr && right node != nullptr delete node
    // (otherwise more than one child so find the minimum)
    // create temp node to right
    // while left node is not nullptr keep moving temp left
    // make node bid (right) equal to temp bid (left)
    // remove right node using recursive call
    // return node

    if (node == nullptr) {
        return nullptr;
    }
    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node* temp = node->left;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
	return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
