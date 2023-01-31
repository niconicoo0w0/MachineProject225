/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
using namespace std;
#include <math.h>


template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  if (tail_ && !tail_->next) {
    ListNode* temp = new ListNode();
    temp->prev = tail_;
    tail_->next = temp;
  }
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if (tail_ && !tail_->next) {
    ListNode* temp = new ListNode();
    temp->prev = tail_;
    tail_->next = temp;
  }
  return tail_->next;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while(head_) {
    ListNode* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  head_ = tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode* newNode = new ListNode(ndata);
  if (head_ == nullptr) {
    head_ = tail_ = newNode;
    head_->prev = head_->next = nullptr;
    tail_->prev = tail_->next = nullptr;
    length_++;
    return;
  }
  head_->prev = newNode;
  newNode->next = head_;
  newNode -> prev = nullptr; 
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode* newNode = new ListNode(ndata);
  if (tail_ == nullptr) {
    head_ = tail_ = newNode;
    head_->prev = head_->next = nullptr;
    tail_->prev = tail_->next = nullptr;
    length_++;
    return;
  }
  tail_->next = newNode;
  newNode->next = nullptr;
  newNode->prev = tail_;
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (head_ == nullptr || start == nullptr) {
    return NULL;
  }
  if (splitPoint > length_) {
    return NULL;
  }
  ListNode * curr = start;
  for (int i = 0; i < splitPoint; i++) {
    if (curr->next) {
      curr = curr->next;
    }
  }
  if (curr->prev) {
    curr->prev->next = NULL;
    curr->prev = NULL;
  }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (head_ == nullptr || length_ < 3) {
    return;
  }
  ListNode* curr = head_;
  for (int j = 0; j < floor(length_/3); j++) { 
    ListNode* one = curr;
    ListNode* two = one->next;
    ListNode* three = two->next;
    ListNode* temp1 = one->prev;
    ListNode* temp2 = three->next;
    if (temp1) {
      temp1->next = two; //链接第二组更新后的第一个数字和上一组的最后一个数字
    }
    if (temp2) {
      temp2->prev = one; //链接第二组第一个数字和更新后的第一组的最后一个数字
    }
    one->prev = three;
    one->next = three->next;
    two->prev = temp1;
    two->next = three;
    three->next = one;
    three->prev = two;
    if (j == 0) {
        head_ = two;
        head_->prev = nullptr;
        head_->next = three;
    }
    if (length_ % 3 == 0 && j == floor(length_/3)-1) {
      tail_ = one;
      tail_->prev = three;
      tail_->next = nullptr;
    }
    curr = one->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == nullptr || endPoint == nullptr || length_ < 2 || startPoint == endPoint) {
    return;
  }
  ListNode* connect_start = startPoint->prev;
  ListNode* connect_end = endPoint->next;

  ListNode* curr = startPoint;
  ListNode* temp = curr->prev;
  
  curr->prev = curr->next;
  curr->next = connect_end;

  if (connect_end){
    connect_end->prev=curr;
  }
  curr=curr->prev;

  while(curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }

  curr->next = curr->prev;
  curr->prev = connect_start;
  if (startPoint == head_) {
    head_ = endPoint;
  } else {
    connect_start->next = curr;
  }
  if (endPoint == tail_) {
    tail_ = startPoint;
  } else {
    connect_end->prev = startPoint;
  }
  ListNode* s = startPoint;
  startPoint = endPoint;
  endPoint = s;
}
// /**
//  * Reverses blocks of size n in the current List. You should use your
//  * reverse( ListNode * &, ListNode * & ) helper function in this method!
//  *
//  * @param n The size of the blocks in the List to be reversed.
//  */
template <typename T>
void List<T>::reverseNth(int n) {
  if (n <= 1 || head_ == nullptr || length_ <= 1 || n >= length_) {
    return;
  }
  ListNode* temp = nullptr;
  ListNode* end = head_;
  ListNode* start = head_;
  ListNode* connect_end = nullptr;
  for (int j = 0; j < floor(length_/n) + 1 && start; j++) {
    end = start;
    for (int i = 0; i < n - 1; i++) {
      if (end->next) {
        end = end->next;
      }
    }
    reverse(start, end);
    temp = end->next;
    start = temp;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == nullptr) {
    return second;
  }
  if (second == nullptr) {
    return first;
  }
  ListNode* returnit = nullptr;
  if (!returnit) {
    if (first->data < second->data) {
      returnit = first;
      returnit->prev = nullptr;
      first = first->next;
    } else {
      returnit = second;
      returnit->prev = nullptr;
      second = second->next;
    }
  }
  while (first && second) {
    if (first->data < second->data) {
      returnit->next = first;
      first->prev = returnit;
      returnit = first;
      first = first->next;
    } else {
      returnit->next = second;
      second->prev = returnit;
      returnit = second;
      second = second->next;
    }
  }
  if (second) {
    returnit->next = second;
    second->prev = returnit;
  }
  if (first) {
    returnit->next = first;
    first->prev = returnit;
  }
  while (returnit->prev) {
    returnit = returnit->prev;
  }
  return returnit;
} 

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1) {
    return start;
  }
  ListNode * left = nullptr;
  ListNode * right = nullptr;
  int split_point = chainLength / 2;
  left = start;
  right = split(start, split_point);
  return merge(mergesort(left, split_point), mergesort(right, chainLength - split_point));
}
