#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <utility>
#include <string>
#include <vector>

#include "distance.hpp"

class quadtree {
  // A point quadtree for locations on Earth.

  // Notes: 
  // - Assume a spherical Earth. But assume that if you keep traveling
  //   west, you will hit longitude -180 and stop, and if you keep
  //   traveling east, you will hit longitude +180 and stop; you don't
  //   have to worry about wrapping around like Magellan.
  // - Locations are measured in degrees latitude and longitude, but
  //   distances are measured in miles.

public:
  // See bintree.hpp for skeleton definitions of the default
  // constructor, copy constructor, destructor, and copy assignment
  // operator (and swap).

  void insert(const std::string& name, point p) {
    // Insert an element with name `name` and location `p`.
  }

  void within_radius(point p, double r, std::vector<std::string> &result) const {
    // Search for elements within the circle with center `p` (in
    // degrees latitude and longitude) and radius `r` (in miles).
    // Clears `result` and puts the elements in `result`.
    // Postcondition: `result` contains all (and only) the elements of
    // the tree, in any order, that lie within the circle defined by
    // `p` and `r`.
  }
};

#endif
