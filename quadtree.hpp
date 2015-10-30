
#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <utility>
#include <string>
#include <vector>
#include "distance.hpp"

using namespace std;







class quadtree {
  // A point quadtree for locations on Earth.

  // Notes: 
  // - Assume a spherical Earth. But assume that if you keep traveling
  //   west, you will hit longitude -180 and stop, and if you keep
  //   traveling east, you will hit longitude +180 and stop; you don't
  //   have to worry about wrapping around like Magellan.
  // - Locations are measured in degrees latitude and longitude, but
  //   distances are measured in miles.

	private:
		typedef struct node {
			string name;
			point loc; // LAt and longitude in special point member function
			struct node *northwest; 
			struct node *northeast; 
			struct node *southwest; 
			struct node *southeast; // Each of the children of the nodes
		} node_t; // owhat we will call this struct
		
		node_t *root;
		int brange;
		int srange;

		void insert(const std::string& name, point p, node_t *t_node){
			//INSERTING NORTHWEST CHILDREN
			if ((p.lat >= t_node->loc.lat) && (p.lon < t_node->loc.lon)){
				if (t_node->northwest != NULL) {
					insert(name, p, t_node->northwest);
				}
				else {
					t_node->northwest = new node_t;//instantiating
					t_node->northwest->name = name;
					t_node->northwest->loc = p;
					t_node->northwest->northwest = NULL;
					t_node->northwest->northeast = NULL;
					t_node->northwest->southwest = NULL;
					t_node->northwest->southeast = NULL;
				}
			}
			// INSERTING NORTHWEST CHILDREN
			else if ((p.lat >= t_node->loc.lat) && (p.lon >= t_node->loc.lon)){
                                if (t_node->northeast != NULL) {
                                        insert(name, p, t_node->northeast);
                                }
                                else {
                                        t_node->northeast = new node_t;//instantiating
                                        t_node->northeast->name = name;
                                        t_node->northeast->loc = p;
                                        t_node->northeast->northwest = NULL;
                                        t_node->northeast->northeast = NULL;
                                        t_node->northeast->southwest = NULL;
                                        t_node->northeast->southeast = NULL;
                                }
                        }
			
			// INSERTING SOUTHEAST CHILDREN
			else if ((p.lat < t_node->loc.lat) && (p.lon >= t_node->loc.lon)){
                                if (t_node->southeast != NULL) {
                                        insert(name, p, t_node->southeast);
                                }
                                else {
                                        t_node->southeast = new node_t;  //instantiating
                                        t_node->southeast->name = name;
                                        t_node->southeast->loc = p;
                                        t_node->southeast->northwest = NULL;
                                        t_node->southeast->northeast = NULL;
                                        t_node->southeast->southwest = NULL;
                                        t_node->southeast->southeast = NULL;  //setting all the children to null
                                }
                        } 
			// INSERTING SOUTHWEST CHILDREN
			else if ((p.lat < t_node->loc.lat) && (p.lon < t_node->loc.lon)){
                                if (t_node->southwest != NULL) {
                                        insert(name, p, t_node->southwest);
                                }
                                else {
                                        t_node->southwest = new node_t; //instantiating
                                        t_node->southwest->name = name;
                                        t_node->southwest->loc = p;
                                        t_node->southwest->northwest = NULL;
                                        t_node->southwest->northeast = NULL;
                                        t_node->southwest->southwest = NULL;
                                        t_node->southwest->southeast = NULL;
                                }
                        }
		}

	public:
  		// Default Constructor
  		quadtree() {


			root = NULL;
		}
		
		// Copy Constructor and helper copy function
		quadtree(const quadtree &t) {
			copyHelper(root, t.root);
		}
		void copyHelper(node_t *&thisRoot, node_t * tRoot) {
                        if(tRoot == NULL) {
                                thisRoot = NULL;
                        }
                        else {
                                thisRoot = new node_t;//instantiating
                                thisRoot->loc = tRoot->loc;
				thisRoot->name = tRoot->name;
                                copyHelper(thisRoot->northwest, tRoot->northwest);
                                copyHelper(thisRoot->northeast, tRoot->northeast);
				copyHelper(thisRoot->southwest, tRoot->southwest);
                                copyHelper(thisRoot->southeast, tRoot->southeast);
                        }
                }		
		
		
		// DESTRUCTOR AND REMOVE HELPER FUNCTION
		~quadtree(){
			remove(root);
		}
		void remove(node_t * t) {
			if (t == NULL) return;
			remove (t->northwest);   //THIS FUNCTION IS CALLED RECURSIVELY
			remove (t->northeast);
			remove (t->southwest);
			remove (t->southeast);
			delete t;
		}
		
		// Copy Assingment Operator and swap
		friend void swap(quadtree &t1, quadtree &t2) {
			using std::swap;
			swap(t1.root, t2.root);
		}
		quadtree &operator = (quadtree other){
			swap(*this, other);
			return *this;	
		}
		
		// Insert Function
		void insert(const std::string& name, point p) {
    			// Insert an element with name `name` and location `p`.
  			if (root != NULL) {
				insert(name, p, root);   //helper function gets called here from private part
			}
			else {
				root = new node_t;
				root->name = name;
				root->loc = p; 
				root->northwest = NULL;
				root->northeast = NULL;
				root->southwest = NULL;   //insert function
				root->southeast = NULL;
			}
		}
		void within_radius(point p, double r, std::vector<std::string> &result) const {
    			// Search for elements within the circle with center `p` (in
    			// degrees latitude and longitude) and radius `r` (in miles).
    			// Clears `result` and puts the elements in `result`.
    			// Postcondition: `result` contains all (and only) the elements of
    			// the tree, in any order, that lie within the circle defined by
    			// `p` and `r`.
  		
			result.clear();
		

			point ne(90, 180); 
           		point sw(-90, -180); //Here are the boudaries for locating coordinates
			search(p, r, root, result, sw, ne);
		}
		
		void search(point p, double r, node_t *t_node, vector<string> &result, point sw_point, point ne_point) const {
			if (distance_to_box(p, sw_point, ne_point) <= r) { // See pseudo code
			if (distance(t_node->loc, p) <= r) { // 
				result.push_back(t_node->name);
			}
			if (t_node->northwest != NULL){
				search(p, r, t_node->northwest, result, point(t_node->loc.lat, sw_point.lon), point(ne_point.lat, t_node->loc.lon));
			}
			if (t_node->northeast != NULL){
				search(p, r, t_node->northeast, result, t_node->loc, ne_point);
			}
			if (t_node->southwest != NULL){
				search(p, r, t_node->southwest, result, sw_point, t_node->loc);
			}
			if (t_node->southeast != NULL){
				search(p, r, t_node->southeast, result, point(sw_point.lat, t_node->loc.lon), point(t_node->loc.lat, ne_point.lon));
			}
		}	
		}

  		


};

#endif

