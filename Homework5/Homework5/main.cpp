//  Homework 5
//  CS 341 C++ Data Structures
//  Spring 2018
//  Professor Maslanka
//  Written by Alana Martin

// Based on Professor Maslanka's BinarySearchTreeB.cpp

// Author: John Maslanka
// Date:   23-Jul-2002/ 4-Apr-2017
// Installation: Home PC with MicroSoft Visual C++ V10.0
//
// C++ program to illustrate Binary Tree development and
// access using a Node class to develop and query individual
// Nodes of the tree and a BST class to develop and query the
// entire tree. Each node is created only when it is needed
// to contain a new character value entered by the user.
// This example uses the Data Structure technique known as
// Aggegation.  Also, it uses a Container class for the
// Binary Search Tree.
//
// Edit 10/27/2014   Code for AVL tree balancing. Original
// code from Jeremy Wright.
//
// Edit 11/10/2014   Code to display a binary tree after
// Main & Savitch p 506, from Jimmy Goddard.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// nodewithparent.h
class Node {
private:
    string val; // user input provides value in collating sequence
    Node* lh; // pointer to left-hand descendant Node
    Node* rh; // pointer to right-hand descendant Node
    Node* parent; //pointer to parent Node or NULL if root Node
public:
    Node () { lh = rh = parent = NULL; val = ""; }
    void   putVal (string v) { val = v; }
    string getVal () { return val; }
    void   putLH (Node* x) { lh = x; }
    Node*  getLH () { return lh; }
    void   putRH (Node* x) { rh = x; }
    Node*  getRH () { return rh; }
    void   setParent(Node* x) {parent = x;}
    Node*  getParent() {return parent;}
};

// binarytree.h
class BST { // Container for Binary Search Tree
private:
    int count;
    Node* root;
    Node* tree;
private:
    Node* addNode (Node*, string);
    Node* findInsertion (Node* tree, string v);
    void inOrder (Node*);
    void preOrder (Node*);
    void postOrder (Node*);
    void locate (Node*, string);
    int  balanceFactor(Node*);
    int  subTreeHeight(Node*);
    void rotateRight (Node*);
    void rotateLeft (Node*);
    void postInsertionBalance (Node*);
    void treeDisplay(Node*, int);
public:
    BST ();
    void addNodeWrapper (string);
    void inOrderTraverse ();
    void preOrderTraverse ();
    void postOrderTraverse ();
    int  getCount () { return count; }
    void locateRoot (string);
    void treeDisplayWrapper();
};
// binarytree.cpp
BST::BST () { // Default Constructor
    root = tree = NULL; count = 0;
}

void BST::addNodeWrapper (string v)
{ if (root == NULL)
{
    root = tree = addNode (tree, v);
}
else
{ tree = root;
    tree = findInsertion (tree, v);
}
}

Node* BST::findInsertion(Node* tree, string v)
{
    string x;
    x = tree->getVal();
    // The following code up to the return statement provided by Patrick Abeya 11/2/2017
    // This code replaces the redundant code which existed in previous versions of this
    //  program. This code is similar to the code for Polymorphism.
    //
    Node * (Node::*getMethod)(void) = nullptr;
    void (Node::*putMethod)(Node *) = nullptr;
    
    // Next 8 lines decide whether to go to left or right child of current node
    if (v <= x) { // user data value <= data value in current node
        getMethod = &Node::getLH;  // Assign reference to method getLH to getMethod
        putMethod = &Node::putLH;  // Assign reference to method putLH to putMethod
    }
    else {  // else user data value > data value in current node
        getMethod = &Node::getRH;  // Assign reference to method getRH to getMethod
        putMethod = &Node::putRH;  // Assign reference to method putRH to putMethod
    }
    
    // Now decide if there is a Left or Right child
    if ((tree->*getMethod)() != NULL) {  // Yes
        tree = findInsertion((tree->*getMethod)(), v); // Call findInsertion recursively
    }
    else // No
    {
        Node* temp = NULL;         // provide field for reference to new node
        temp = addNode(temp, v);   // Create new Node
        (tree->*putMethod)(temp);  //  and put its reference into the node of its parent
        // Patrick Abeya's code ends here
        temp->setParent(tree);  //added functionality for parents; new child learns who its parent is
        postInsertionBalance(temp); //balance the tree
    }
    return tree;
}
Node* BST::addNode (Node* x, string v)
{ if (x = new Node)
{ x->putVal (v);
    ++count;
    x->putLH(NULL);
    x->putRH(NULL);
    x->setParent(NULL);
}
    return x;
}
void BST::locateRoot (string v) {
    if ( root == NULL )
        cout << "Tree is empty" << endl;
    else
        locate ( root, v );
}
void BST::locate (Node* y, string v) {  // Parameter Bug mentioned by Dan Glade
    string x;
    x = y -> getVal ();
    if ( v == x )
    { cout << "Value " << v << " is in Node at reference " << (size_t)y << endl;
        cout << " Left Child ref " << (size_t)y->getLH() << "    Right Child ref " << (size_t)y->getRH();
        cout << "    Parent ref " << (size_t)y->getParent() << endl;
    }
    else if ( v < x )
        if ( y -> getLH() != NULL )
            locate (y-> getLH(), v);
        else
            cout << "Value not in tree" << endl;
        else // if ( v > x )
            if ( y -> getRH() != NULL )
                locate ( y-> getRH(), v );
            else
                cout << "Value not in tree" << endl;
}
void BST::inOrderTraverse ()
{ cout << endl;
    inOrder (root);
}
void BST::inOrder (Node* n)
{ if (n != NULL) {
    inOrder (n->getLH());
    cout << n->getVal() << endl;
    inOrder (n->getRH());
}
    return;
}
void BST::preOrderTraverse ()
{ cout << endl;
    preOrder (root);
}
void BST::preOrder (Node* n)
{ if (n == NULL) return;
    cout << n->getVal() << endl;
    preOrder (n->getLH());
    preOrder (n->getRH());
}
void BST::postOrderTraverse ()
{ cout << endl;
    postOrder (root);
}
void BST::postOrder (Node* n)
{ if (n != NULL) //return;
{ postOrder (n->getLH());
    postOrder (n->getRH());
    cout << n->getVal() << endl;
}
}
void BST::treeDisplayWrapper() {
    treeDisplay(root, 0);
}

void BST::treeDisplay(Node* ref, int depth) {
    // Adapted from Main & Savitch, Data Structures and Oter Objects using C++,
    //    page 506 by Jimmy Goddard
    cout << setw(4*depth) << ""; // indentation
    if (ref == NULL) {
        // reached a NULL reference in an interior node
        cout << "[NULL]" << endl;
    } else if (ref->getLH() == NULL && ref->getRH() == NULL) {
        // a leaf
        cout << "Value " << ref->getVal() << " at Ref " << (size_t) ref;
        cout << " [leaf]" << endl;
    } else {
        // a nonleaf - interior node
        if ( depth == 0 )
            cout << "       Root ";
        cout << "Value " << ref->getVal() << " at Ref " << (size_t) ref << endl;
        cout << "Left Child  " << depth+1;
        treeDisplay(ref->getLH(), depth + 1);
        cout << "Right Child " << depth+1;
        treeDisplay(ref->getRH(), depth + 1);
    }
}
// AVL Dynamic BTree Balancing listed below: is done at post-insertion for each
//   new Node.  Original code from Jeremy Wright.
// This BST procedure uses rotations to do AVL-balance whenever a Node is added.
// In order to do this in all levels of the tree, it first calculates a balance
// factor, and uses this to determine when to rotate Nodes of the tree.  The
// rotations are made so as to preserve the efficiency of navigation thru the tree.
// The AVL balancing technique allows us to circumvent the problem of statically
// balancing the input (more about this later in the course) when we can rebalance
// the tree after each node is added. However, this procedure balances the tree
// from the point of view of depth and so it does not always produce a perfectly
// balanced tree. For ease of programming, nodes now keep track of their parents
// to facilitate the rotation procedures.
// Note that this AVL technique has not been tested to handle the problem of
// deleting a Node from a Binary Search Tree (BST).

void BST::postInsertionBalance(Node* n)  //Run after every insertion of a Node
// to balance the tree.  Any imbalances can be dealt with by looking at
// the parent line to the root of the new Node as described above.
{
//    cout << "Entering postInsertionBalance" << endl;
    Node* p;
    if (balanceFactor(n) == 2)
    {
        p = n->getLH();
        if (balanceFactor(p) == -1)
        {
            rotateLeft(p);
        }
        rotateRight(n);
    }
    else if (balanceFactor(n) == -2)
    {
        p = n->getRH();
        if (balanceFactor(p) == 1)
        {
            rotateRight(p);
        }
        rotateLeft(n);
    }
    if (n != root) //run until we travel up to root
    {
        postInsertionBalance(n->getParent());
    }
}

int BST::balanceFactor(Node* n)
{
    return subTreeHeight(n->getLH()) - subTreeHeight(n->getRH());
}

int BST::subTreeHeight(Node* n) //tells the height of the larger subtree under this node.
{
    int subHeightL;
    int subHeightR;
    if(n == NULL)
    {
        return -1;
    }
    if(n->getLH() == NULL)
    {
        if(n->getRH() == NULL)
        {
            return 0;
        }
        else
        {
            subHeightR = subTreeHeight(n->getRH())+1;
            return subHeightR;
        }
    }
    else if(n->getRH() == NULL)
    {
        subHeightL = subTreeHeight(n->getLH())+1;
        return subHeightL;
    }
    else
    {
        subHeightL = subTreeHeight(n->getLH()) + 1;
        subHeightR = subTreeHeight(n->getRH()) + 1;
        if(subHeightL > subHeightR)
        {
            return subHeightL;
        }
        else
        {
            return subHeightR;
        }
    }
}
void BST::rotateRight(Node* subRoot)  //rotates a tree right, with subRoot as
// its original root and pivot as the new root
{
    cout << "Entering rotate Right" << endl;
    Node* pivot = subRoot->getLH();   //new root of this subtree is the left child
    Node* parentRoot = subRoot->getParent();  //store parent of subtree
    subRoot->putLH(pivot->getRH());  //the root takes the right child of the pivot
    // to preserve BST structure
    if(subRoot->getRH() != NULL)
    {
        subRoot->getRH()->setParent(subRoot);  //make sure child knows its parent
    }
    pivot->putRH(subRoot); //the root becomes the right child of the pivot
    subRoot->setParent(pivot);
    if(subRoot == root)
    {
        root = pivot;
        pivot->setParent(NULL);
    }
    else  //connect subtree to its parent
    {
        if(parentRoot->getLH() == subRoot)
        {
            parentRoot->putLH(pivot);
            pivot->setParent(parentRoot);
        }
        else
        {
            parentRoot->putRH(pivot);
            pivot->setParent(parentRoot);
        }
    }
}
void BST::rotateLeft(Node* subRoot) //Rotates Nodes left, symmetrical with Rotate_Right
{
    cout << "Entering Rotate Left" << endl;
    Node* pivot = subRoot->getRH();
    Node* parentRoot = subRoot->getParent();
    subRoot->putRH(pivot->getLH());
    if(subRoot->getRH() != NULL)
    {
        subRoot->getRH()->setParent(subRoot);
    }
    pivot->putLH(subRoot);
    subRoot->setParent(pivot);
    if(subRoot == root) // Need to test if entire tree is balanced!!!
    {
        root = pivot;
        pivot->setParent(NULL);
    }
    else
    {
        if(parentRoot->getLH() == subRoot)
        {
            parentRoot->putLH(pivot);
            pivot->setParent(parentRoot);
        }
        else
        {
            parentRoot->putRH(pivot);
            pivot->setParent(parentRoot);
        }
    }
}

// Added Functions and Classes:

// Move All Menu Details to a new function.
void print_menu();

// Added Class for managing Homework assignment updates.
class STUDENT_LIST {
public:
    STUDENT_LIST(){}
    ~STUDENT_LIST(){}
    
    void add_student( string name ) {
        if( tree_created ) {
            cout << "** Error ** You have already created a tree. Unable to add new names." << endl;
        }
        else {
            if ( 0 == student_count ) {
                string *tempArray;
                student_count = 1;
                tempArray     =  new string[ student_count ];
                if ( nullptr != tempArray ) {
                    tempArray[0]  = name;
                    students  = tempArray;
                }
                else {
                    cout << "   *** Error Condition *** " << endl << "  Out of heap. " << endl;
                }
            }
            else {
                string *tempArray;
                tempArray = new string[ student_count + 1 ];
                if ( nullptr != tempArray ) {
                    for ( int i = 0; i < ( student_count ); i++ ) { // Use the original student size to loop.
                        tempArray[i] = students[i];
                    }
                    tempArray[ student_count ] = name; // Don't increment yet because 0 indexing.
                    students = tempArray;
                    student_count++; // Final step increment student count.
                }
                else {
                    cout << "   *** Error Condition *** " << endl << "  Out of heap. " << endl;
                }
            }
            sort( students, students + student_count ); // Keep list sorted at all times.
        }
    }
    
    void list_students(){
        
        if ( 0 == student_count ) {
            cout << endl << "No Students have been added." << endl;
        }
        else {
            cout << endl << "Student List" << endl;
            for ( int i = 0; i < student_count; i++ ) {
                cout << i << "  " << students[i] << endl;
            }
        }
    }
    
    void print_list_width_balanced(){
        if( tree_created ) {
            cout << "You have already created a tree with this list: " << endl;
            print_tree_sorted_vector();
        }
        else{
            middle_vector.clear();
            get_middle();
            print_middled_vector();
            tree_sorted_vector.clear();
            create_width_array();
            print_tree_sorted_vector();
            
        }
    }
    
    void get_middle( ){
        int nr;
        int level=0;
        nr = student_count;
        if (nr > 2) {
//            cout << "Level" << "   Person" << endl;
            FindMiddle(1, nr, (level + 1), nr, 1);
        }
        else {
            cout << "\n** error ** No middle with 2 or less items." << endl;
        }
    }
    
    // create a width vector based on middle vector.
    void create_width_array(){
    
        int level = 1;
        int max_level = 1;
        
        // Determine how many levels exist.
        for( int i = 0; i < middle_vector.size(); i++ ){
            if( max_level < middle_vector[i][1] ){
                max_level = middle_vector[i][1];
            }
        }
        
        // Move items to width balances vector based on level.
        while( level <= max_level ) {
            for( int i = 0; i < middle_vector.size(); i++ ) {
                if ( level == middle_vector[i][1] ) {
                    tree_sorted_vector.push_back( students[ middle_vector[i][0] ] );
                }
            }
            level++;
        }
    }
    
    void create_binary_tree( BST *TREE ){
        if( ! tree_created ) {
            middle_vector.clear();
            get_middle();
            tree_sorted_vector.clear();
            create_width_array();
            for ( int i = 0; i < tree_sorted_vector.size(); i++ ){
                cout << "Adding " << tree_sorted_vector[i] << " to the tree." << endl;
                TREE->addNodeWrapper( tree_sorted_vector[i] );
            }
            tree_created = true;
            cout << "Tree Created!" << endl;
        }
        else {
            cout << "** Error ** You can only create a tree once per run of program." << endl;
        }
    }
    
    void better_tree_print(){
        // TODO: make a better print function for tree in the tree.
    }
    
    void print_middled_vector() {
        if( 0 < middle_vector.size() ) {
            cout << "\nStudent\tLevel" << endl;
            for ( int i = 0; i < middle_vector.size(); i++ ){
                cout << middle_vector[i][0] << "\t\t" <<  middle_vector[i][1] << endl;
            }
        }
    }
    
    void print_tree_sorted_vector() {
        if( 0 < tree_sorted_vector.size() ){
            cout << "\nWidth Balanced Order" << endl;
            for ( int i = 0; i < tree_sorted_vector.size(); i++ ){
                cout << tree_sorted_vector[i] << endl;
            }
        }
    }
    
private:
    string *students;
    int student_count = 0;
    vector <string> tree_sorted_vector;
    vector<vector< int> > middle_vector;
    bool tree_created = false;
    
    void add_row( int person, int position){
        vector<int> newrow;
        newrow.push_back( person);
        newrow.push_back( position);
        middle_vector.push_back( newrow );
    }
    

    // Code from Professor Maslanka from FindMiddleRB.cpp.
    // Modified for use in this STUDENT_LIST class.
    // Subtracted 1 from X & Y so these can be used as zero based array indexes.
    // Moved results into a function instead of outputting to screen.
    void FindMiddle(int x, int y, int level, int nr, int round) {
        int mid;
        
        if ( abs( x - y ) < 2 ) {
            
            if ( x == 1 ) {
//              cout << "  " << level << "    " << setw(2) << x - 1 << endl;
                add_row( x - 1, level );
            }
            
            if ( y == nr ) {
//              cout << "  " << level << "    " << setw(2) << y - 1  << endl;
                add_row( y - 1, level );
            }
            return;
        }
        
        if ( ( y + x ) % 2 ) {
            mid=(x+y+round)/2;
//          cout << "  " << level << "    " << setw(2) << mid - 1 << endl;
            add_row( mid - 1, level );
        }
        else {
            mid = ( x + y ) / 2;
//          cout << "  " << level << "    " << setw(2) << mid - 1 << endl;
            add_row( mid - 1, level );
        }
        
        FindMiddle(x,mid,(level+1),nr,-1); // round down left
        FindMiddle(mid,y,(level+1),nr,1);  // round up right
        return;
    }
};

// End Added functions and Classes.


// BinaryTreeApplication.cpp
int main () {
    string x;
    char op = ' ';
    char confirm = ' ';
    BST TREE;
    
    // Added Variables.
    STUDENT_LIST STUDENTS;
    string name;
    // End Added Variables.
    
    // Create inorder Binary treee
    print_menu();
    while (!cin.eof() && op != 'E' && op != 'e')  // build binary tree in this loop
    { cout << "Enter your operation: ";
        cin >> op;
        if (!cin.eof () && op != 'E' && op != 'e')
            switch (op)
        {
            case 'A': case 'a':
            { cout << "Enter your string: ";
                cin >> x;
                if (!cin.eof())
                    TREE.addNodeWrapper (x);
                break;
            }
            case 'S': case 's':
            {if ( TREE.getCount ())
            { cout << endl << "In-OrderTree Traversal" << endl;
                TREE.inOrderTraverse ();
                //              cout << "Pre-Order Tree Traversal" << endl << endl;
                //              TREE.preOrderTraverse();
                //              cout << "Post-Order Tree Traversal" << endl << endl;
                //              TREE.postOrderTraverse();
            }
                break;
            }
            case 'D': case 'd':
            { cout << endl << "Enter User value of Node to Display: ";
                cin >> x;
                if (!cin.eof())
                { TREE.locateRoot ( x );
                    cout << endl;
                }
                break;
            }
            case 'T': case 't':
                {if ( TREE.getCount ())
                { cout << endl << "Display Tree:" << endl;
                    TREE.treeDisplayWrapper ();
                }
                else
                    cout << endl << "Tree is empty. No entries found.";
                    cout << endl;
                    break;
                }
            case 'H': case 'h':
                { cout << "Enter your operation using the capital letter shown in your selection." << endl;
                    print_menu();
                    break;
                }
            case '1':
                {
                    cout << "Enter student name: ";
                    cin >> name;
                    if ( !cin.eof() ) {
                        STUDENTS.add_student( name );
                    }
                    break;
                }
            case '2':
                {
                    STUDENTS.list_students();
                    break;
                }
            case '3': {
                STUDENTS.print_list_width_balanced();
                break;
            }

            case '4': {
                STUDENTS.create_binary_tree( &TREE );
                break;
            }
            case 'E': case 'e':
            { break;
            }
            default:
            { cout << "Invalid operation. Try again!" << endl;
                print_menu();
                break;
            }
        }
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}

void print_menu(){
    cout << "To create your Binary tree, use the menu below." << endl << endl;
    cout << "Enter your operation using the capital letter shown in your selection." << endl;
    cout << "Add a node\nDisplay a node\nShow sorted list\nTree Display\nHelp\nExit\n" << endl;
    cout << "Enhanced Options - Select by Number" << endl;
    cout << "1 Add a Name to the Array" << endl;
    cout << "2 Print Ascending Sorted Array" << endl;
    cout << "3 Print name middle points and print names sorted." << endl;
    cout << "4 Create Binary Tree based on width balanced array" << endl << endl;
}
