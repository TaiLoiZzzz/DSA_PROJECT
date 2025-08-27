#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>
#include <functional>  // 🔥 Thêm để hỗ trợ std::function

template<typename K, typename V>
class BinarySearchTree {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        Node* parent;  // 🔥 Thêm parent pointer để dễ navigate
        
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    size_t size_;
    
    // Helper methods
    Node* insertRecursive(Node* node, const K& key, const V& value);
    Node* findRecursive(Node* node, const K& key) const;
    Node* removeRecursive(Node* node, const K& key);
    Node* findMin(Node* node) const;
    void clearRecursive(Node* node);
    void printRecursive(Node* node, int depth) const;
    
    // 🔥 NEW: Tree traversal methods without vector - sử dụng std::function
    void inorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    void preorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    void postorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const;
    
    // 🔥 NEW: Search methods without vector - sử dụng std::function
    void searchPartialCallback(Node* node, const K& partialKey, 
                              const std::function<bool(const K&, const K&)>& matchFunc,
                              const std::function<void(const K&, const V&)>& callback) const;
    void searchRangeCallback(Node* node, const K& startKey, const K& endKey, 
                           const std::function<void(const K&, const V&)>& callback) const;
    
public:
    BinarySearchTree() : root(nullptr), size_(0) {}
    ~BinarySearchTree() { clear(); }
    
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
    
    // 🔥 NEW: Traversal methods with std::function (no vector)
    void traverseInorder(const std::function<void(const K&, const V&)>& callback) const;
    void traversePreorder(const std::function<void(const K&, const V&)>& callback) const;
    void traversePostorder(const std::function<void(const K&, const V&)>& callback) const;
    
    // 🔥 NEW: Search methods with std::function (no vector)
    void searchPartial(const K& partialKey, 
                      const std::function<bool(const K&, const K&)>& matchFunc,
                      const std::function<void(const K&, const V&)>& callback) const;
    void searchRange(const K& startKey, const K& endKey, 
                    const std::function<void(const K&, const V&)>& callback) const;
    
    // 🔥 NEW: Iterator-like functionality without vector
    void forEach(const std::function<void(const K&, const V&)>& callback) const;
    void forEachReverse(const std::function<void(const K&, const V&)>& callback) const;
    
    // 🔥 NEW: Tree statistics without vector
    int getHeight() const;
    int getHeightRecursive(Node* node) const;
    int getNodeCount() const { return size_; }
    bool isBalanced() const;
    bool isBalancedRecursive(Node* node, int& height) const;
};

// Implementation
template<typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::insertRecursive(Node* node, const K& key, const V& value) {
    if (node == nullptr) {
        Node* newNode = new Node(key, value);
        return newNode;
    }
    
    if (key < node->key) {
        node->left = insertRecursive(node->left, key, value);
        if (node->left) node->left->parent = node;
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key, value);
        if (node->right) node->right->parent = node;
    } else {
        // Key already exists, update value
        node->value = value;
        return node;
    }
    
    return node;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::insert(const K& key, const V& value) {
    root = insertRecursive(root, key, value);
    if (root) root->parent = nullptr;
    size_++;
}

template<typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::findRecursive(Node* node, const K& key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return findRecursive(node->left, key);
    }
    
    return findRecursive(node->right, key);
}

template<typename K, typename V>
V* BinarySearchTree<K, V>::find(const K& key) {
    Node* node = findRecursive(root, key);
    return node ? &(node->value) : nullptr;
}

template<typename K, typename V>
const V* BinarySearchTree<K, V>::find(const K& key) const {
    Node* node = findRecursive(root, key);
    return node ? &(node->value) : nullptr;
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::contains(const K& key) const {
    return findRecursive(root, key) != nullptr;
}

template<typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template<typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::removeRecursive(Node* node, const K& key) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (key < node->key) {
        node->left = removeRecursive(node->left, key);
        if (node->left) node->left->parent = node;
    } else if (key > node->key) {
        node->right = removeRecursive(node->right, key);
        if (node->right) node->right->parent = node;
    } else {
        // Node to delete found
        
        // Case 1: Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            if (temp) temp->parent = node->parent;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            if (temp) temp->parent = node->parent;
            delete node;
            return temp;
        }
        
        // Case 2: Node with two children
        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->value = temp->value;
        node->right = removeRecursive(node->right, temp->key);
        if (node->right) node->right->parent = node;
    }
    
    return node;
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::remove(const K& key) {
    if (!contains(key)) {
        return false;
    }
    
    root = removeRecursive(root, key);
    if (root) root->parent = nullptr;
    size_--;
    return true;
}

// 🔥 NEW: Traversal methods with std::function (no vector)
template<typename K, typename V>
void BinarySearchTree<K, V>::inorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node) {
        inorderTraversalCallback(node->left, callback);
        callback(node->key, node->value);
        inorderTraversalCallback(node->right, callback);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::preorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node) {
        callback(node->key, node->value);
        preorderTraversalCallback(node->left, callback);
        preorderTraversalCallback(node->right, callback);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::postorderTraversalCallback(Node* node, const std::function<void(const K&, const V&)>& callback) const {
    if (node) {
        postorderTraversalCallback(node->left, callback);
        postorderTraversalCallback(node->right, callback);
        callback(node->key, node->value);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::traverseInorder(const std::function<void(const K&, const V&)>& callback) const {
    inorderTraversalCallback(root, callback);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::traversePreorder(const std::function<void(const K&, const V&)>& callback) const {
    preorderTraversalCallback(root, callback);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::traversePostorder(const std::function<void(const K&, const V&)>& callback) const {
    postorderTraversalCallback(root, callback);
}

// 🔥 NEW: Search methods with std::function (no vector)
template<typename K, typename V>
void BinarySearchTree<K, V>::searchPartialCallback(Node* node, const K& partialKey, 
                                                  const std::function<bool(const K&, const K&)>& matchFunc,
                                                  const std::function<void(const K&, const V&)>& callback) const {
    if (node) {
        // Check current node
        if (matchFunc(partialKey, node->key)) {
            callback(node->key, node->value);
        }
        
        // Recursively search left and right subtrees
        searchPartialCallback(node->left, partialKey, matchFunc, callback);
        searchPartialCallback(node->right, partialKey, matchFunc, callback);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::searchPartial(const K& partialKey, 
                                          const std::function<bool(const K&, const K&)>& matchFunc,
                                          const std::function<void(const K&, const V&)>& callback) const {
    searchPartialCallback(root, partialKey, matchFunc, callback);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::searchRangeCallback(Node* node, const K& startKey, const K& endKey, 
                                               const std::function<void(const K&, const V&)>& callback) const {
    if (node) {
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
void BinarySearchTree<K, V>::searchRange(const K& startKey, const K& endKey, const std::function<void(const K&, const V&)>& callback) const {
    searchRangeCallback(root, startKey, endKey, callback);
}

// 🔥 NEW: Iterator-like functionality without vector
template<typename K, typename V>
void BinarySearchTree<K, V>::forEach(const std::function<void(const K&, const V&)>& callback) const {
    traverseInorder(callback);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::forEachReverse(const std::function<void(const K&, const V&)>& callback) const {
    // Reverse inorder traversal (right -> root -> left)
    if (root) {
        Node* current = root;
        Node* prev = nullptr;
        
        while (current) {
            if (current->right == nullptr) {
                callback(current->key, current->value);
                current = current->left;
            } else {
                prev = current->right;
                while (prev->left && prev->left != current) {
                    prev = prev->left;
                }
                
                if (prev->left == nullptr) {
                    prev->left = current;
                    current = current->right;
                } else {
                    prev->left = nullptr;
                    callback(current->key, current->value);
                    current = current->left;
                }
            }
        }
    }
}

// 🔥 NEW: Tree statistics without vector
template<typename K, typename V>
int BinarySearchTree<K, V>::getHeightRecursive(Node* node) const {
    if (node == nullptr) {
        return -1;
    }
    
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);
    
    return 1 + std::max(leftHeight, rightHeight);
}

template<typename K, typename V>
int BinarySearchTree<K, V>::getHeight() const {
    return getHeightRecursive(root);
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::isBalancedRecursive(Node* node, int& height) const {
    if (node == nullptr) {
        height = -1;
        return true;
    }
    
    int leftHeight, rightHeight;
    bool leftBalanced = isBalancedRecursive(node->left, leftHeight);
    bool rightBalanced = isBalancedRecursive(node->right, rightHeight);
    
    height = 1 + std::max(leftHeight, rightHeight);
    
    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }
    
    return leftBalanced && rightBalanced;
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::isBalanced() const {
    int height;
    return isBalancedRecursive(root, height);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::clearRecursive(Node* node) {
    if (node) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::clear() {
    clearRecursive(root);
    root = nullptr;
    size_ = 0;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::printRecursive(Node* node, int depth) const {
    if (node) {
        printRecursive(node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->key << " -> " << node->value;
        if (node->parent) {
            std::cout << " (parent: " << node->parent->key << ")";
        }
        std::cout << std::endl;
        printRecursive(node->left, depth + 1);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::print() const {
    std::cout << "Binary Search Tree (size: " << size_ << ", height: " << getHeight() << "):" << std::endl;
    printRecursive(root, 0);
}

#endif // BINARY_SEARCH_TREE_H
