#ifndef TREE_H
#define TREE_H

#include "Node.h"

template <class T>
class Tree {
protected:
    Node<T>* root;
    int size;
public:
    Tree() : root(NULL), size(0) {}

    Tree(const Tree<T>& other) {
        root = NULL;
        Copy(other.root);
    }

    Tree<T>& operator = (const Tree<T>& other) {
        if (this != &other) {
            Free();
            Copy(other.root);
        }
    }

    virtual Node<T>* Insert(Node<T>*, const T&);
    virtual void Insert(const T&);
    virtual Node<T>* Erase(Node<T>*, const T&);
    virtual void Erase(const T&);
    Node<T>* Find(Node<T>*, const T&) const;
    int Find(const T&) const;
    void Inorder(ostream&, const Node<T>*);
    void Copy(Node<T>*);

    Node<T>* Free(Node<T>*);
    void Free();
    Node<T>* getMin(Node<T>*);

    virtual int getTreeHeight(Node<T>*);
    void printLeaves(Node<T>*);
    void Extract(Node<T>*, T*, int&);

    virtual void printBalance(Node<T>*);
    
    template <class U> friend istream& operator >> (istream&, Tree<U>&);
    template <class U> friend ostream& operator << (ostream&, Tree<U>&);

    int getSize() {
        return size;
    }

    Node<T>* getRoot() {
        return root;
    }

    void incSize() {
        ++size;
    }
    
    void decSize() {
        --size;
    }
    
    virtual ~Tree() {
        Free();
        size = 0;
    }

    virtual void Show() = 0;
};

/// Makes Tree empty
template <class T>
Node<T>* Tree<T>::Free(Node<T>* node) {
    if (node == NULL)
        return NULL;
    Free(node->left);
    Free(node->right);
    delete node;
    this->decSize();
    return NULL;
}

template <class T>
void Tree<T>::Free() {
    root = Free(root);
}

/// Input
template <class T> 
istream& operator >> (istream& is, Tree<T>& tree) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        int value;
        is >> value;
        tree.Insert(value);
    }
    return is;
}


/// Prints Tree in Inorder
template <class T> 
void Tree<T>::Inorder(ostream& os, const Node<T>* node) {
    if (node == NULL)
        return;
    Inorder(os, node->left);
    os << node->data << ' ';
    Inorder(os, node->right);
}

/// Output
template <class T>
ostream& operator << (ostream& os, Tree<T>& tree) {
    tree.Inorder(os, tree.root);
    os << '\n';
    return os;
}

/// Insert funcion
template <class T> 
Node<T>* Tree<T>::Insert(Node<T>* node, const T& value) {
    if (node == NULL) {
        node = new Node<T>(value);
        this->incSize();
    }
    else if (value < node->data)
        node->left = Insert(node->left, value);
    else if (value > node->data)
        node->right = Insert(node->right, value);
    return node;
}

template <class T>
void Tree<T>::Insert(const T& value) {
    root = Insert(root, value);
} 


/// Gets greatest value smaller than the deleted one
template <class T>
Node<T>* Tree<T>::getMin(Node<T>* node) {
    if (node->right != NULL)
        return getMin(node->right);
    else return node;
}


/// Erase function
template <class T>
Node<T>* Tree<T>::Erase(Node<T>* node, const T& value) {
    if (node == NULL)
        return NULL;

    else if (value < node->data)
        node->left = Erase(node->left, value);
    else if (value > node->data)
        node->right = Erase(node->right, value);
    
    else {
        if (node->left != NULL && node->right != NULL) {
            Node<T>*aux = getMin(node->left);
            node->data = aux->data;
            node->left = Erase(node->left, node->data);
        } else if (node->left != NULL) {
            Node<T> *aux = node->left;
            delete node;
            node = aux;
            this->decSize();
        } else if (node->right != NULL) {
            Node<T> *aux = node->right;
            delete node;
            node = aux;
            this->decSize();
        } else {
            delete node;
            this->decSize();
            return NULL;
        }
    }
    
    return node;
}

template <class T>
void Tree<T>::Erase(const T& value) {
    root = Erase(root, value);
}

/// Function that gets tree height
template <class T>
int Tree<T>::getTreeHeight(Node<T>* node) {
    if (node == NULL)
        return 0;
    return 1 + max(getTreeHeight(node->left), getTreeHeight(node->right));
}

/// Function that prints all the leaves of the Tree
template <class T>
void Tree<T>::printLeaves(Node<T>* node) {
    if (node == NULL)
        return;
    printLeaves(node->left);
    if (node->left == NULL && node->right == NULL)
        cout << node->data << ' ';
    printLeaves(node->right);
}

/// Function that finds a value in a Tree
template <class T>
Node<T>* Tree<T>::Find(Node<T>* node, const T& value) const {
    if (node == NULL)
        return NULL;
    if (value < node->data)
        return Find(node->left, value);
    if (value > node->data)
        return Find(node->right, value);
    return node;
}

template <class T>
int Tree<T>::Find(const T& value) const {
    return Find(root, value) != NULL;
}

/// Function that copies data from another Tree
template <class T>
void Tree<T>::Copy(Node<T>* node) {
    if (node == NULL)
        return;
    Insert(node->data);
    Copy(node->left);
    Copy(node->right);
}

/// Function that transforms Tree into an array
template <class T>
void Tree<T>::Extract(Node<T>* node, T* arr, int& tp) {
    if (node == NULL)
        return;
    arr[tp++] = node->data;
    Extract(node->left, arr, tp);
    Extract(node->right, arr, tp);
}

/// Function that shows balance factors for each node of the tree
template <class T>
void Tree<T>::printBalance(Node<T>* node) {
    if (node == NULL)
        return;
    printBalance(node->left);
    cout << node->data << ' ' << getTreeHeight(node->left) - getTreeHeight(node->right) << '\n';
    printBalance(node->right);
}

#endif //TREE_H