/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim) {
      return false;
    }
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] > second[curDim]) {
      return false;
    } 
    return first < second;
}

// template <int Dim>
// vector<double> KDTree<Dim>::getDistance(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) {
//   vector<double> returnit = {0.0, 0.0};
//   for (int i = 0; i < Dim; i++) {
//     returnit[0] += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
//     returnit[1] += (target[i] - potential[i])*(target[i] - potential[i]);
//   }
//   return returnit;
// }

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    // vector<double> distance = this.getDistance(target, currentBest, potential);
    double curr = 0.0;
    double pot = 0.0;
    for (int i = 0; i < Dim; i++) {
      curr += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
      pot += (target[i] - potential[i])*(target[i] - potential[i]);
    }
    if (curr < pot) {
      return false;
    } else if (curr > pot) {
      return true;
    }
    return potential < currentBest;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, unsigned left, unsigned right, unsigned pivotIndex, int curDim) {
  Point<Dim> pivotValue = list[pivotIndex];
  // swap list[pivotIndex] and list[right]
  unsigned storeIndex = left;
  swap(list, pivotIndex, right);
  for (unsigned i = left; i < right; i++) {
    if (smallerDimVal(list[i], pivotValue, curDim) == true) {
      //swap list[storeIndex] and list[i];
      swap(list, i, storeIndex);
      storeIndex++;
    }
  }
  swap(list, storeIndex, right);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::swap(vector<Point<Dim>>& list, unsigned index_1, unsigned index_2) {
  Point<Dim> curr = list[index_1];
  list[index_1] = list[index_2];
  list[index_2] = curr;
  return;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, unsigned left, unsigned right) {
  if (points.empty()) {
    return nullptr;
  }
  if (left < 0 || right >= points.size() || left > right) {
    return nullptr;
  }
  if (left <= right) {
    unsigned middle = (left + right) / 2;
    typename KDTree<Dim>::KDTreeNode* root = new typename KDTree<Dim>::KDTreeNode(select(points, left, right, middle, dim%Dim));
    size++;
    root->left = buildTree(points, dim + 1, left, middle - 1);
    root->right = buildTree(points, dim + 1, middle + 1, right);
    return root;
  }
  return nullptr;
}


template <int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>>& list, unsigned left, unsigned right, int k, int curDim) {
  if (left == right) {
    return list[left];
  } 
  int pivotIndex = k;
  pivotIndex = partition(list, left, right, pivotIndex, curDim);
  if (k == pivotIndex) {
    return list[k];
  } else if (k < pivotIndex) {
    return select(list, left, pivotIndex-1, k, curDim);
  } else {
    return select(list, pivotIndex+1, right, k, curDim);
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) {
      size = 0;
      root = nullptr;
      return;
    }
    vector<Point<Dim>> points;
    for (unsigned i = 0; i < newPoints.size(); i++) {
      points.push_back(newPoints[i]);
    }
    size = 0;
    root = buildTree(points, 0, 0, newPoints.size() - 1); 
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  this = other;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if (this == &rhs) {
    return *this;
  }
  delete *this;
  this = new KDTree(rhs);
}

/**
* KDTree destructor frees all memory associated with the tree by calling the clean helper function.
**/
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}


template <int Dim>
Point<Dim> KDTree<Dim>::Neighbor_helper(const Point<Dim>& query, int dim, KDTreeNode* root) const {
  if (!root) {
    return Point<Dim>();
  }
  if (!root->left && !root->right) {  //leaf, return curr point
    return root->point;
  }
  Point<Dim> nearest = root->point;
  bool already_recurse = false;
  if (smallerDimVal(query, root->point, dim)) {
    if (root->left) {
      nearest = Neighbor_helper(query, (dim+1)%Dim, root->left);
    } else {
      nearest = Neighbor_helper(query, (dim+1)%Dim, root->right);
    }
    already_recurse = true;
  } else {
    if (root->right) {
      nearest = Neighbor_helper(query, (dim+1)%Dim, root->right);
    } else {
      nearest = Neighbor_helper(query, (dim+1)%Dim, root->left);
    }
  }
  if (shouldReplace(query, nearest, root->point)) {
    nearest = root->point;      //update nearest
  }
  //Calculate radius between query and nearest
  double radius = 0.0;
  for (unsigned i = 0; i < Dim; i++) {
    radius += (query[i] - nearest[i])*(query[i] - nearest[i]);
  }
  double splitDist = (root->point[dim] - query[dim])*(root->point[dim] - query[dim]);

  Point<Dim> tempNearest;
  if (radius >= splitDist) {
    if (already_recurse) {
      if (root->right) {
        tempNearest = Neighbor_helper(query, (dim+1)%Dim, root->right);
      } else {
        tempNearest = Neighbor_helper(query, (dim+1)%Dim, root->left);
      }
    } else {
      if (root->left) {
        tempNearest = Neighbor_helper(query, (dim+1)%Dim, root->left);
      } else {
        tempNearest = Neighbor_helper(query, (dim+1)%Dim, root->right);
      }
    }
    if (shouldReplace(query, nearest, tempNearest)) {
      nearest = tempNearest;
    }
  }
  return nearest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return Neighbor_helper(query, 0, root);
}

