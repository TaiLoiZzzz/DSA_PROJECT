#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>
#include <functional>  // 🔥 Thêm để hỗ trợ std::function

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
    void clearRecursive(Node* node);
    void printRecursive(Node* node, int depth) const;
    
    void inorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    void preorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    void postorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    
    void searchPartialCallback(Node* node, const K& partialKey, 
                              const std::function<bool(const K&, const K&)>& matchFunc,
                              const std::function<void(const K&, const V&)>& callback) const;
    void searchRangeCallback(Node* node, const K& startKey, const K& endKey, 
                           const std::function<void(const K&, const V&)>& callback) const;
    
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
    
    // Debug
    void print() const;
    
    void traverseInorder(const std::function<void(const K&, const V&)>& callback) const;
    void traversePreorder(const std::function<void(const K&, const V&)>& callback) const;
    void traversePostorder(const std::function<void(const K&, const V&)>& callback) const;
    
    void searchPartial(const K& partialKey, 
                      const std::function<bool(const K&, const K&)>& matchFunc,
                      const std::function<void(const K&, const V&)>& callback) const;
    void searchRange(const K& startKey, const K& endKey, 
                    const std::function<void(const K&, const V&)>& callback) const;
    
    void forEach(const std::function<void(const K&, const V&)>& callback) const;
    void forEachReverse(const std::function<void(const K&, const V&)>& callback) const;
    
    int getHeight() const;
    int getHeightRecursive(Node* node) const;
    int getNodeCount() const { return size_; }
    bool isBalanced() const;
    bool isBalancedRecursive(Node* node, int& height) const;
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
void RedBlackTree<K, V>::inorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node != nil) {
        inorderTraversalCallback(node->left, callback);
        callback(node->key, node->value);
        inorderTraversalCallback(node->right, callback);
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::preorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node != nil) {
        callback(node->key, node->value);
        preorderTraversalCallback(node->left, callback);
        preorderTraversalCallback(node->right, callback);
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::postorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node != nil) {
        postorderTraversalCallback(node->left, callback);
        postorderTraversalCallback(node->right, callback);
        callback(node->key, node->value);
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::searchPartialCallback(Node* node, const K& partialKey, 
                              const std::function<bool(const K&, const K&)>& matchFunc,
                              const std::function<void(const K&, const V&)>& callback) const {
    if (node != nil) {
        if (matchFunc(node->key, partialKey)) {
            callback(node->key, node->value);
        }
        searchPartialCallback(node->left, partialKey, matchFunc, callback);
        searchPartialCallback(node->right, partialKey, matchFunc, callback);
    }
}

template<typename K, typename V>
void RedBlackTree<K, V>::searchRangeCallback(Node* node, const K& startKey, const K& endKey, 
                           const std::function<void(const K&, const V&)>& callback) const {
    if (node != nil) {
        // If current node is within range, add it
        if (node->key >= startKey && node->key <= endKey) {
            callback(node->key, node->value);
        }
        
        // If current key is greater than start, search left subtree
        if (node->key > startKey) {
            searchRangeCallback(node->left, startKey, endKey, callback);
        }
        
        // If current key is less than end, search right subtree
        if (node->key < endKey) {
            searchRangeCallback(node->right, startKey, endKey, callback);
        }
    }
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

template<typename K, typename V>
void RedBlackTree<K, V>::traverseInorder(const std::function<void(const K&, const V&)>& callback) const {
    inorderTraversalCallback(root, callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::traversePreorder(const std::function<void(const K&, const V&)>& callback) const {
    preorderTraversalCallback(root, callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::traversePostorder(const std::function<void(const K&, const V&)>& callback) const {
    postorderTraversalCallback(root, callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::searchPartial(const K& partialKey, 
                      const std::function<bool(const K&, const K&)>& matchFunc,
                      const std::function<void(const K&, const V&)>& callback) const {
    searchPartialCallback(root, partialKey, matchFunc, callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::searchRange(const K& startKey, const K& endKey, 
                    const std::function<void(const K&, const V&)>& callback) const {
    searchRangeCallback(root, startKey, endKey, callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::forEach(const std::function<void(const K&, const V&)>& callback) const {
    traverseInorder(callback);
}

template<typename K, typename V>
void RedBlackTree<K, V>::forEachReverse(const std::function<void(const K&, const V&)>& callback) const {
    traversePostorder(callback);
}

template<typename K, typename V>
int RedBlackTree<K, V>::getHeight() const {
    return getHeightRecursive(root);
}

template<typename K, typename V>
int RedBlackTree<K, V>::getHeightRecursive(Node* node) const {
    if (node == nil) {
        return 0;
    }
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

template<typename K, typename V>
bool RedBlackTree<K, V>::isBalanced() const {
    int height;
    return isBalancedRecursive(root, height);
}

template<typename K, typename V>
bool RedBlackTree<K, V>::isBalancedRecursive(Node* node, int& height) const {
    if (node == nil) {
        height = 0;
        return true;
    }
    int leftHeight, rightHeight;
    if (!isBalancedRecursive(node->left, leftHeight) || !isBalancedRecursive(node->right, rightHeight)) {
        return false;
    }
    height = 1 + std::max(leftHeight, rightHeight);
    return std::abs(leftHeight - rightHeight) <= 1;
}

#endif // RED_BLACK_TREE_H
