#ifndef AVL_H
#define AVL_H

#include "Tree.h"

template <class T>
class AVL : public Tree<T> {
private:
public:
    AVL() : Tree<T>() {}

    AVL(T value) : Tree<T>() {}

    AVL(const AVL& other) : Tree<T>(other) {}

    Node<T>* Insert(Node<T>*, const T&);
    void Insert(const T&);
    Node<T>* Erase(Node<T>*, const T&);
    void Erase(const T&);

    Node<T>* rotateLeft(Node<T>* &);
    Node<T>* rotateRight(Node<T>* &);
    Node<T>* rotateLeftRight(Node<T>* &);
    Node<T>* rotateRightLeft(Node<T>* &);

    int getTreeHeight(Node<T>*);
    int getHeight(Node<T>*);

    void printBalance(Node<T>*);

    AVL<T> operator + (const AVL<T>&);
    AVL<T> operator * (const AVL<T>&);
    AVL<T> operator - (const AVL<T>&);

    ~AVL() {}

    void Show() {"I'm an AVL :)\n";}
};

template <class T> 
int AVL<T>::getTreeHeight(Node<T>* node) {
    return getHeight(node);
}

template <class T>
int AVL<T>::getHeight(Node<T>* node) {
    return (node == NULL ? 0 : node->height);
}

/// Right single rotation
template <class T>
Node<T>* AVL<T>::rotateRight(Node<T>* &node) {
    Node<T>* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    aux->height = max(getHeight(aux->left), getHeight(aux->right)) + 1;
    return aux;
}

/// Left single rotation 
template <class T>
Node<T>* AVL<T>::rotateLeft(Node<T>* &node) {
    Node<T>* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    aux->height = max(getHeight(aux->right), getHeight(aux->right)) + 1;
    return aux;
}

/// Left right rotation
template <class T>
Node<T>* AVL<T>::rotateLeftRight(Node<T>* &node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

/// Right left rotation
template <class T>
Node<T>* AVL<T>::rotateRightLeft(Node<T>* &node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

/// Insert funcion
template <class T> 
Node<T>* AVL<T>::Insert(Node<T>* node, const T& value) {
    if (node == NULL) {
        node = new Node<T>(value);
        this->incSize();
    } else if (value < node->data) {
        node->left = Insert(node->left, value);
        if (getHeight(node->left) - getHeight(node->right) == 2) {
            cerr << value << endl;
            if (value < node->left->data)
                node = rotateRight(node);
            else 
                node = rotateLeftRight(node);
        }
    } else if (value > node->data) {
        node->right = Insert(node->right, value);
        if (getHeight(node->right) - getHeight(node->left) == 2) {
            if (value > node->right->data)
                node = rotateLeft(node);
            else node = rotateRightLeft(node);
        }
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

template <class T>
void AVL<T>::Insert(const T& value) {
    this->root = Insert(this->root, value);
}

/// Erase function
template <class T>
Node<T>* AVL<T>::Erase(Node<T>* node, const T& value) {
    Node<T>* aux;
    
    if (node == NULL)
        return NULL;

    else if (value < node->data)
        node->left = Erase(node->left, value);
    else if (value > node->data)
        node->right = Erase(node->right, value);
    
    else {
        if (node->left != NULL && node->right != NULL) {
            aux = this->getMin(node->left);
            node->data = aux->data;
            node->left = Erase(node->left, node->data);
        } else if (node->left != NULL) {
            aux = node;
            node = node->left;
            delete aux;
            this->decSize();
        } else if (node->right != NULL) {
            aux = node;
            node = node->right;
            delete aux;
            this->decSize();
        } else {
            delete node;
            this->decSize();
            return NULL;
        }
    }
    if (node == NULL)
        return NULL;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    if (getHeight(node->left) - getHeight(node->right) == 2) {
        if (getHeight(node->left->left) - getHeight(node->left->right) == 1)
            return rotateRight(node);
        else 
            return rotateLeftRight(node);
    }

    if (getHeight(node->right) - getHeight(node->left) == 2) {
        if (getHeight(node->right->right) - getHeight(node->right->left) == 1)
            return rotateLeft(node);
        else 
            return rotateRightLeft(node);
    }

    return node;
}

template <class T>
void AVL<T>::Erase(const T& value) {
    this->root = Erase(this->root, value);
}

/// Function that returns the disjunction of two AVLs
template <class T>
AVL<T> AVL<T>::operator + (const AVL<T>& other) {
    AVL<T> ans = *this;
    T arr[100000];
    int tp = 0;
    
    this->Extract(other.root, arr, tp);
    
    for (int i = 0; i < tp; i++)
        ans.Insert(arr[i]);
    
    return ans;
}   

/// Function that returns conjunction of two AVLs
template <class T>
AVL<T> AVL<T>::operator * (const AVL<T>& other) {
    AVL<T> ans;
    T arr[100000];
    int tp = 0;

    this->Extract(other.root, arr, tp);

    for (int i = 0; i < tp; i++)
        if (this->Find(arr[i]) == 1)
            ans.Insert(arr[i]);   

    return ans;
}

/// Function that returns difference of two AVLs
template <class T>
AVL<T> AVL<T>::operator - (const AVL<T>& other) {
    AVL<T> ans;
    T arr[100000];
    int tp = 0;

    this->Extract(this->root, arr, tp);

    for (int i = 0; i < tp; i++)
        if (other.Find(arr[i]) == 0)
            ans.Insert(arr[i]);

    return ans;
}

template <class T>
void AVL<T>::printBalance(Node<T>* node) {
    if (node == NULL)
        return;
    printBalance(node->left);
    cout << node->data << ' ' << getHeight(node->left) - getHeight(node->right) << '\n';
    printBalance(node->right);
}


#endif //AVL_H