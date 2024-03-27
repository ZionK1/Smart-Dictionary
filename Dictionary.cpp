/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA8
 * Dictionary.cpp
 * Source Code for Dictionary ADT
 * ***************************************************************************/
#include "Dictionary.h"
#include <iostream>
#include <string>

#define BLACK -1
#define RED -2

// Helper Functions (Optional) ---------------------------------------------
// inOrder, preOrder, postOrder functions done following provided pseudocode

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
// NOTE TO SELF: Optimize by calling += multiple times (Tutor Norton Choy)
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        //s += (R->key + " : " + std::to_string(R->val) + "\n");
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        //s += (R->key + "\n");
        s += R->key;
        if (R->color == RED) {
            s += " (RED)";
        }
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M) {
    Node* x = M; // new pair to insert
    x->right = nil;
    x->left = nil;
    Node* a = nil; // y = NIL
    Node* b = root; // x = T.root
    while (b != nil) { // while x != NIL
        a = b; // y = x
        if (x->key < b->key) { // case 1 key not matching
            b = b->left; 
        }
        else if (x->key > b->key) { // case 2 key not matching
            b = b->right;
        }
        else { // key found
            b = x;
            return;
        }
    }
    x->parent = a; // z.parent = y
    if (a == nil) { 
        root = x; // T.root = z
    }
    else if (x->key < a->key) {
        a->left = x; // y.left = z
    }
    else {
        a->right = x; // y.right = z
    }
    num_pairs += 1; // increment pair count
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    // if (R != nil) {
    if (R != N) { // recursion terminates at N
        //setValue(R->key, R->val);
        BST_insert(N);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R->key == k) { // if k is equal to key of curr node R
        return R;
    }
    else if (R == nil) {
        return nil;
    }
    else if (k < R->key) { // k is less than key of R
        return search(R->left, k); // look to left
    }
    else if (k > R->key) { // if k is greater than key of R
        return search(R->right, k); // look to right
    }
    //else { // return nil otherwise
    //    return nil;
    //}
    return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R != nil) {
        Node* curr = R; // get pointer
        while (curr->left != nil) {
            curr = curr->left;
        }
        return curr; // return pointer to leftmost Node
    }
    return nil; // return nil otherwise
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R != nil) {
        Node* curr = R; // get pointer
        while (curr->right != nil) {
            curr = curr->right;
        }
        return curr; // return pointer to rightmost Node
    } 
    return nil; // return nil otherwise
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {
        return nil;
    }
    //Node *curr = N;
    if (N->right != nil) {
    //if (curr->right != nil) {
        return findMin(N->right);
        //return findMin(curr->right);
    }
    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {
        return nil;
    }
    //Node *curr = N;
    if (N->left != nil) {
    //if (curr->left != nil) {
        return findMin(N->left);
        //return findMin(curr->left);
    }
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    // set y
    Node *y = N->right;

    // turn y's left subtree into x's right subtree
    N->right = y->left;
    if (y->left != this->nil) { // not necessary if using sentinal nil node
        y->left->parent = N;
    }

    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = y;
    }
    else if (N == N->parent->left) {
        N->parent->left = y;
    }
    else {
        N->parent->right = y;
    }
    
    // put x on y's left
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y
    Node *y = N->left;

    // turn y's right subtree into x's left subtree
    N->left = y->right;
    if (y->right != this->nil) { // not necessary if using sentinal nil node
        y->right->parent = N;
    }

    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = y;
    }
    else if (N == N->parent->right) {
        N->parent->right = y;
    }
    else {
        N->parent->left = y;
    }
    
    // put x on y's right
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node *y = N->parent->parent->right;
            if (y->color == RED) { // case 1
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->right) { // case 2
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK; // case 3
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else {
            Node *y = N->parent->parent->left;
            if (y->color == RED) { // case 4
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->left) { // case 5
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK; // case 6
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == this->nil) {
        this->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != this->root && N->color == BLACK) {
        if (N == N->parent->left) {
            Node *w = N->parent->right;
            if (w->color == RED) { // case 1
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { // case 2
                w->color = RED;
                N = N->parent;
            }
            else {
                if (w->right->color == BLACK) { // case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color; // case 4
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = this->root;
            }
        }
        else {
            Node *w = N->parent->left;
            if (w->color == RED) { // case 5
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) { // case 6
                w->color = RED;
                N = N->parent;
            }
            else { 
                if (w->left->color == BLACK) { // case 7
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = this->root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node *x;
    Node *y = N;
    int y_original_color = y->color;
    if (N->left == this->nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == this->nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

// Creates new Dictionary in the empty state
Dictionary::Dictionary() {
    nil = new Node("xd", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("xd", 0);
    // root = nullptr; ??
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    delete nil; // delete nil node
    clear(); // clean out all Nodes and set dict params to empty state
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (search(root, k) == nil) { // search from root for key k
        return false;
    }
    return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node *lol = search(this->root, k); 
    if (lol == nil) {
        throw std::logic_error("Dictionary: getValue(): invalid key");
    }
    return lol->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current is undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current is undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    current = nil;
    root = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // basic check for if pair exists
    Node *n = search(root, k);
    if (n != nil) {
        n->val = v;
        return;
    }
    Node *z = new Node(k, v);
    Node *y = this->nil;
    Node *x = this->root;
    while (x != this->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == this->nil) {
        this->root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = this->nil;
    z->right = this->nil;
    z->color = RED;
    num_pairs += 1;
    RB_InsertFixUp(z);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): key doesn't exist");
    }
    Node *n = search(root, k);
    if (n == current) {
        current = nil;
    }
    RB_Delete(n);
    delete n;
    num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (size() > 0) { // if non-empty
        current = findMin(root); // place current iterator at first pair
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (size() > 0) { // if non-empty
        current = findMax(root); // place current iterator at last pair
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string str = "";
    inOrderString(str, root);
    return str;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string str = "";
    preOrderString(str, root);
    return str;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    if (size() != D.size()) { // basic check for same size
        return false;
    }
    std::string x = this->to_string();
    std::string y = D.to_string();
    if (x != y) { // compare strings of Dicts
        return false;
    }
    return true;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if(this != &D) { // not self assignment
        // make a copy of D
        Dictionary temp = D;

        // then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}