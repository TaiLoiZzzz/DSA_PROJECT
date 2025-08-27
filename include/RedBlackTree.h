#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <vector>
#include <string>

template<typename K, typename V>
class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct Node {
        K key;
        V value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(const K& k, const V& v) : key(k), value(v), color(RED), 
                                      left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    Node* nil;  // Sentinel node
    size_t size_;
    
    // Helper methods
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insertFixup(Node* z);
    void deleteFixup(Node* x);
    void transplant(Node* u, Node* v);
    Node* findRecursive(Node* node, const K& key) const;
    void inorderTraversal(Node* node, std::vector<V>& result) const;
    void clearRecursive(Node* node);
    void printRecursive(Node* node, int depth) const;
    void getAllPairsRecursive(Node* node, std::vector<std::pair<K, V>>& result) const;
    
public:
    RedBlackTree() : size_(0) {
        nil = new Node(K(), V());
        nil->color = BLACK;
        root = nil;
    }
    
    ~RedBlackTree() { 
        clear(); 
        delete nil;
    }
    
    // Core operations
    void insert(const K& key, const V& value);
    V* find(const K& key);
    const V* find(const K& key) const;
    bool remove(const K& key);
    bool contains(const K& key) const;
    
    // Utility methods
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    void clear();
    std::vector<V> getAllValues() const;
    
    // Debug
    void print() const;
    
    // Iterator-like functionality
    std::vector<std::pair<K, V>> getAllPairs() const;
};

// Implementation
template<typename K, typename V>
void RedBlackTree<K, V>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nil) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

template<typename K, typename V>
void RedBlackTree<K, V>::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    
    if (y->right != nil) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

template<typename K, typename V>
void RedBlackTree<K, V>::insertFixup(Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    
    root->color = BLACK;
}

template<typename K, typename V>
void RedBlackTree<K, V>::insert(const K& key, const V& value) {
    Node* z = new Node(key, value);
    Node* y = nullptr;
    Node* x = root;
    
    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            // Key already exists, update value
            x->value = value;
            delete z;
            return;
        }
    }
    
    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = nil;
    z->right = nil;
    z->color = RED;
    
    insertFixup(z);
    size_++;
}

template<typename K, typename V>
typename RedBlackTree<K, V>::Node* RedBlackTree<K, V>::findRecursive(Node* node, const K& key) const {
    if (node == nil || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return findRecursive(node->left, key);
    }
    
    return findRecursive(node->right, key);
}

template<typename K, typename V>
V* RedBlackTree<K, V>::find(const K& key) {
    Node* node = findRecursive(root, key);
    return (node != nil) ? &(node->value) : nullptr;
}

template<typename K, typename V>
const V* RedBlackTree<K, V>::find(const K& key) const {
    Node* node = findRecursive(root, key);
    return (node != nil) ? &(node->value) : nullptr;
}

template<typename K, typename V>
bool RedBlackTree<K, V>::contains(const K& key) const {
    return findRecursive(root, key) != nil;
}

template<typename K, typename V>
void RedBlackTree<K, V>::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    
    v->parent = u->parent;
}

template<typename K, typename V>
void RedBlackTree<K, V>::deleteFixup(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    
    x->color = BLACK;
}

template<typename K, typename V>
bool RedBlackTree<K, V>::remove(const K& key) {
    Node* z = findRecursive(root, key);
    if (z == nil) {
        return false;
    }
    
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;
    
    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = z->right;
        while (y->left != nil) {
            y = y->left;
        }
        
        yOriginalColor = y->color;
        x = y->right;
        
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    delete z;
    
    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
    
    size_--;
    return true;
}

template<typename K, typename V>
void RedBlackTree<K, V>::inorderTraversal(Node* node, std::vector<V>& result) const {
    if (node != nil) {
        inorderTraversal(node->left, result);
        result.push_back(node->value);
        inorderTraversal(node->right, result);
    }
}

template<typename K, typename V>
std::vector<V> RedBlackTree<K, V>::getAllValues() const {
    std::vector<V> result;
    inorderTraversal(root, result);
    return result;
}

template<typename K, typename V>
void RedBlackTree<K, V>::getAllPairsRecursive(Node* node, std::vector<std::pair<K, V>>& result) const {
    if (node != nil) {
        getAllPairsRecursive(node->left, result);
        result.push_back(std::make_pair(node->key, node->value));
        getAllPairsRecursive(node->right, result);
    }
}

template<typename K, typename V>
std::vector<std::pair<K, V>> RedBlackTree<K, V>::getAllPairs() const {
    std::vector<std::pair<K, V>> result;
    getAllPairsRecursive(root, result);
    return result;
}

template<typename K, typename V>
void RedBlackTree<K, V>::clearRecursive(Node* node) {
    if (node != nil) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::clear() {
    clearRecursive(root);
    root = nil;
    size_ = 0;
}

template<typename K, typename V>
void RedBlackTree<K, V>::printRecursive(Node* node, int depth) const {
    if (node != nil) {
        printRecursive(node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->key << " -> " << node->value 
                  << " (" << (node->color == RED ? "RED" : "BLACK") << ")" << std::endl;
        printRecursive(node->left, depth + 1);
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::print() const {
    std::cout << "Red-Black Tree (size: " << size_ << "):" << std::endl;
    printRecursive(root, 0);
}

#endif // RED_BLACK_TREE_H
