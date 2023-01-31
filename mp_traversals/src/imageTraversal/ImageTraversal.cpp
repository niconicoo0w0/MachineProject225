#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = nullptr;
  curr_ = Point(-1,-1);
  start_ = Point(-1,-1);
  for (unsigned int i = 0; i < png_.width(); i++) {
    vector<bool> temp;
    for (unsigned int j = 0; j < png_.height(); j++) {
      temp.push_back(false);
    }
    visited_.push_back(temp);
    temp.clear();
  }
  finish_ = true;
}

ImageTraversal::Iterator::Iterator(PNG& png, ImageTraversal* traversal, Point& start, double& tolerance) {
  start_ = start;
  traversal_ = traversal;
  tolerance_ = tolerance;
  curr_ = traversal_->peek();
  png_ = png;
  
  for (unsigned int i = 0; i < png_.width(); i++) {
    vector<bool> temp;
    for (unsigned int j = 0; j < png_.height(); j++) {
      temp.push_back(false);
    }
    visited_.push_back(temp);
    temp.clear();
  }
  if (status(start) == 1) {
    visited_[start_.x][start_.y] = true;
  }
  finish_ = false;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  curr_ = traversal_->pop();

  // Set Neighbors
  Point right = Point(curr_.x + 1, curr_.y);
  Point below = Point(curr_.x, curr_.y + 1);
  Point left = Point(curr_.x - 1, curr_.y);
  Point above = Point(curr_.x, curr_.y - 1);
  
  if (right.x >= 0 && right.y >=0 && right.x < png_.width() && right.y < png_.height()) {
    if (!visited_[right.x][right.y]) {
      if (status(right) == 1) {
        traversal_->add(right);
      }
    }
  }
  if (below.x >= 0 && below.y >=0 && below.x < png_.width() && below.y < png_.height()) {
    if (!visited_[below.x][below.y]) {
      if (status(below) == 1) {
        traversal_->add(below);
      }
    }
  }
  if (left.x >= 0 && left.y >=0 && left.x < png_.width() && left.y < png_.height()) {
    if (!visited_[left.x][left.y]) {
      if (status(left) == 1) {
        traversal_->add(left);
      } 
    }
  }
  if (above.x >= 0 && above.y >=0 && above.x < png_.width() && above.y < png_.height()) {
    if (!visited_[above.x][above.y]) {
      if (status(above) == 1) {
        traversal_->add(above);
      }   
    }
  }

  visited_[curr_.x][curr_.y] = true;
  curr_ = traversal_->peek();

  while (!traversal_->empty()) {
    if (visited_[curr_.x][curr_.y]) {
      curr_ = traversal_->pop();
      curr_ = traversal_->peek();
    } else {
      break;
    }
  }
  if (traversal_->empty()) {
    finish_ = true;
  } else {
    finish_ = false;
  }
  return *this;
}

/*
  Helper function:
    Point out of bound || visited || tolerance => return -1
*/
int ImageTraversal::Iterator::status(Point next) {
  if (next.x >= png_.width() || next.y >= png_.height()) {
    return -1;
  }
  if (next.x < 0 || next.y < 0) {
    return -1;
  }
  if (visited_[next.x][next.y]) {
    return -1;
  }
  if (calculateDelta(png_.getPixel(next.x, next.y), png_.getPixel(start_.x, start_.y)) >= tolerance_) {
    return -1;
  }
  return 1;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this->finish_ == other.finish_) {
    return false;
  }
  return true;
}
