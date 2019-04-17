#ifndef Node_H
#define Node_H

#include <bits/stdc++.h>

using namespace std;

template <class T>
class Node {
protected:
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
public:
    Node() : data(-1), left(NULL), right(NULL), height(1) {}
    Node(T value) : data(value), left(NULL), right(NULL), height(1) {}

    Node(const Node& other) {
        data = other.data;
        left = other.left;
        right = other.right;
        height = other.height;
    }

    Node<T>& operator = (const Node<T>& other) {
        if (this != &other) {
            data = other.data;
            left = other.left;
            right = other.right;
            height = other.height;
        }
    }

    bool operator < (const Node<T>& other) const {
        return data < other.data;
    }

    bool operator == (const Node<T>& other) const {
        return data == other.data;
    }

    bool operator != (const Node<T>& other) const {
        return data != other.data;
    }

    ~Node() {
        data = -1;
        left = NULL;
        right = NULL;
        height = 0;
    }

    template <class U> friend class Tree;
    template <class U> friend class BST;
    template <class U> friend class AVL;
}; 

#endif //Node_H