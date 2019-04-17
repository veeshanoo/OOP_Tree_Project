#ifndef BST_H
#define BST_H

#include "Tree.h"

template <class T>
class BST : public Tree<T> {
public:
    BST() : Tree<T>() {}

    BST(T value) : Tree<T>() {}

    BST(const BST& other) : Tree<T>(other) {}

    BST<T> operator + (const BST<T>&);
    BST<T> operator * (const BST<T>&);
    BST<T> operator - (const BST<T>&);

    ~BST() {}

    void Show() {"I'm a BST :)\n";}
};

/// Function that returns the disjunction of two BSTs
template <class T>
BST<T> BST<T>::operator + (const BST<T>& other) {
    BST<T> ans = *this;
    T arr[100000];
    int tp = 0;
    
    this->Extract(other.root, arr, tp);
    
    for (int i = 0; i < tp; i++)
        ans.Insert(arr[i]);

    return ans;
}   

/// Function that returns conjunction of two BSTs
template <class T>
BST<T> BST<T>::operator * (const BST<T>& other) {
    BST<T> ans;
    T arr[100000];
    int tp = 0;

    this->Extract(other.root, arr, tp);

    for (int i = 0; i < tp; i++)
        if (this->Find(arr[i]) == 1)
            ans.Insert(arr[i]);

    return ans;
}

/// Function that returns difference of two BSTs
template <class T>
BST<T> BST<T>::operator - (const BST<T>& other) {
    BST<T> ans;
    T arr[100000];
    int tp = 0;

    this->Extract(this->root, arr, tp);

    for (int i = 0; i < tp; i++)
        if (other.Find(arr[i]) == 0)
            ans.Insert(arr[i]);

    return ans;
}

#endif //BST_H