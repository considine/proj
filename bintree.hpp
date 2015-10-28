#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

class bintree {
  // A binary search tree for locations in Lineland.

  // Notes: 
  // - Assume a flon, one-dimensional world with locations from -180 to 180.
  // - All locations and distances are measured in the same units (degrees).
private:

  typedef struct node
  {
    string name;
    double lon;
    struct node * left;
    struct node * right;
  } node_t;
  node_t *root; //points to the root
  int srange[2]; // as defined
  int brange[2]; 
public:
  // Default constructor
  bintree() {
    root = NULL;
  }


  // Copy constructor
  bintree(const bintree &t) {

    //We need an actualy copy method so we can call this recursively
    if (t.root == NULL) { //in this case we know that the tree is empty
      root = NULL;
    } 
    else {
      copyTree (this->root, t.root);
    }
    
  }

  void copyTree(node_t * thisRoot, node_t * sourceRoot) {
    //BASE CASE:
    if(sourceRoot == NULL) {
      thisRoot = NULL;
    }
    else {
      thisRoot = new node_t;
      thisRoot->lon = sourceRoot->lon;
      thisRoot->name = sourceRoot->name;
      copyTree(thisRoot->left, sourceRoot->left);
      copyTree(thisRoot->right, sourceRoot->right);
    }
  }

  void search () {} //the actual searching function
  void within_radius (double longit, double range, vector<string> &result) { //self-explanatory
    //search function
    node_t * temp; // for traversals;
    temp = root;
    while (temp != NULL) { //as long as there are more spots
      if ( abs(temp->lon - longit) < range) {
        result.insert(result.begin(), temp->name);  //save the name 
        //need to check both right and left node in this case:
      }
      if (temp->lon < longit) { //in this case we need to move to the right

      }
    }
  }
  // Destructor
  ~bintree() {
    remove1(root); //#de
  }
  void remove1(node* root) {
    if (root == NULL) return; //base case
    remove1 (root->left);
    remove1 (root->right);
    delete root;
  }

  // Copy assignment is implemented using the copy-swap idiom
  // https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap
  friend void swap(bintree &t1, bintree &t2) {
    using std::swap;
    // Swap all data members here, e.g.,
    // swap(t1.foo, t2.foo);
    // Pointers should be swapped -- but not the things they point to.
  }
  bintree &operator= (bintree other) {
    // You don't need to modify this function.
    swap(*this, other);
    return *this;
  }

  void insert(const std::string& name, double p) {
    // Insert an element with name `name` and location `p`.

    node_t *t = new node_t; //create a new node
    node_t * parent;
    t->name = name;
    t->lon = p;       //set the data attributes
    t->left = NULL; t->right =NULL; //set the children to null for now

    //need to know if the tree is new or not!
    if (isEmpty()) root = t; //set the root to the value we just creaeted
    else {
      //Insert alon the tree
      //first must find the parent
      node_t * current; 
      current = root; // the starting point
      while (current) {  //traverse down tree til we find the proper spot
        parent = current;  //to store previous node
        if (t->lon > current->lon) current = current->right; //comparing 
        else current = current->left;
      }
 
      if(t->lon < parent->lon) {
        parent->left=t;
        parent->right = t;
      }

      else 
        parent->right=t;
        parent->left=t;

    }

  }
  bool isEmpty() {
    return root ==NULL;
  }

  void within_radius(double p, double r, std::vector<std::string> &result) const {
    // Search for elements within the range `p` plus or minus `r`.
    // Clears `result` and puts the elements in `result`.
    // Postcondition: `result` contains all (and only) elements of the
    // tree, in any order, that lie within the range `p` plus or minus
    // `r`.
  }
};

#endif
