#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <vector>
#include <string>

template<typename K, typename V>
class BinarySearchTree {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t size_;
    
    // Helper methods
    Node* insertRecursive(Node* node, const K& key, const V& value);
    Node* findRecursive(Node* node, const K& key) const;
    Node* removeRecursive(Node* node, const K& key);
    Node* findMin(Node* node) const;
    void inorderTraversal(Node* node, std::vector<V>& result) const;
    void clearRecursive(Node* node);
    void printRecursive(Node* node, int depth) const;
    
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
    std::vector<V> getAllValues() const;
    
    // Debug
    void print() const;
    
    // Iterator-like functionality
    std::vector<std::pair<K, V>> getAllPairs() const;
    void getAllPairsRecursive(Node* node, std::vector<std::pair<K, V>>& result) const;
};

// Implementation
template<typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::insertRecursive(Node* node, const K& key, const V& value) {
    if (node == nullptr) {
        return new Node(key, value);
    }
    
    if (key < node->key) {
        node->left = insertRecursive(node->left, key, value);
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key, value);
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
    } else if (key > node->key) {
        node->right = removeRecursive(node->right, key);
    } else {
        // Node to delete found
        
        // Case 1: Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        // Case 2: Node with two children
        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->value = temp->value;
        node->right = removeRecursive(node->right, temp->key);
    }
    
    return node;
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::remove(const K& key) {
    if (!contains(key)) {
        return false;
    }
    
    root = removeRecursive(root, key);
    size_--;
    return true;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::inorderTraversal(Node* node, std::vector<V>& result) const {
    if (node) {
        inorderTraversal(node->left, result);
        result.push_back(node->value);
        inorderTraversal(node->right, result);
    }
}

template<typename K, typename V>
std::vector<V> BinarySearchTree<K, V>::getAllValues() const {
    std::vector<V> result;
    inorderTraversal(root, result);
    return result;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::getAllPairsRecursive(Node* node, std::vector<std::pair<K, V>>& result) const {
    if (node) {
        getAllPairsRecursive(node->left, result);
        result.push_back(std::make_pair(node->key, node->value));
        getAllPairsRecursive(node->right, result);
    }
}

template<typename K, typename V>
std::vector<std::pair<K, V>> BinarySearchTree<K, V>::getAllPairs() const {
    std::vector<std::pair<K, V>> result;
    getAllPairsRecursive(root, result);
    return result;
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
        std::cout << node->key << " -> " << node->value << std::endl;
        printRecursive(node->left, depth + 1);
    }
}

template<typename K, typename V>
void BinarySearchTree<K, V>::print() const {
    std::cout << "Binary Search Tree (size: " << size_ << "):" << std::endl;
    printRecursive(root, 0);
}

#endif // BINARY_SEARCH_TREE_H
