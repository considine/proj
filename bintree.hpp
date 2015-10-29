#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>

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
  } node_t;   //Each tree node
  node_t *root; //points to the root
  
//PRIVATE HELPER FUNCTION
void insert(const std::string& name, double p, node_t* t_node) {
    // Insert an element with name `name` and location `p`.
    if (p < t_node -> lon) {   //case that the new longitude is less than root long
      if (t_node->left != NULL) {
        insert(name, p, t_node->left); //RECURSE
      }
      else {
        t_node->left = new node_t;
        t_node->left->name = name;
        t_node->left->lon = p;
        t_node->left->left = NULL;        //extend to children here
        t_node->left->right = NULL;       // because that is where the insertion ocurrs
      }
    }
    else if ( p >= t_node ->lon) {
      if (t_node->right != NULL) {
        insert(name, p, t_node->right);
      }
      else {
        
        t_node->right = new node_t;
        t_node->right->name = name;
        t_node->right->lon = p;
        t_node->right->right = NULL;
        t_node->right->left = NULL;
      }
    }

  }




public:
  // Default constructor
  bintree() {
    root = NULL;
  }


  // Copy constructor
  bintree(const bintree &t) {

   copyHelper(root, t.root);
    
  }

  void copyHelper(node_t * &thisRoot, node_t * copiedRoot) {
    //BASE CASE:
    if(copiedRoot == NULL) {
      thisRoot = NULL;
    }
    else {
      thisRoot = new node_t;
      thisRoot->lon = copiedRoot->lon;
      thisRoot->name = copiedRoot->name;
      copyHelper(thisRoot->left, copiedRoot->left);
      copyHelper(thisRoot->right, copiedRoot->right);
    }
  }

  
  // Destructor
  ~bintree() {
    remove1(root); //#de
  }
  void remove1(node* t_node) {
    if (t_node == NULL) return; //base case
    remove1 (t_node->left);
    remove1 (t_node->right);
    delete t_node;
  }

  // Copy assignment is implemented using the copy-swap idiom
  // https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap
  friend void swap(bintree &t1, bintree &t2) {
    using std::swap;
    swap(t1.root, t2.root);
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
    if (root != NULL) {
      insert(name, p, root); //call helper function defined inprivate
    }
    else {
          root = new node_t;
          root-> name = name;
          root-> lon = p;
          root-> left = NULL;
          root -> right = NULL;

    }
   

  }
  bool isEmpty() {
    return root ==NULL;
  }

  void within_radius(double p, double r, std::vector<std::string> &result) const {
    result.clear();
    recurse_function(p, r, root, result);
  }


  void recurse_function (double p, double r, node_t *t, vector<string> &result) const{
    if ((t->lon <= p+r) && (t->lon >= p-r)) {
      result.push_back(t->name);
    }
    if (t->left !=NULL) recurse_function (p, r, t->left, result);  //recurse to the t
    if (t->right !=NULL) recurse_function (p, r, t->right, result); //two child nodes
  }
};

#endif
