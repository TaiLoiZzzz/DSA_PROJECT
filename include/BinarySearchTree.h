#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BSTNode.h"
#include "Exceptions.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Cây tìm kiếm nhị phân (Binary Search Tree) để lưu trữ liên hệ
 * Sắp xếp theo tên liên hệ để hỗ trợ tìm kiếm nhanh O(log n)
 */
class BinarySearchTree {
private:
    BSTNode* root;  // Con trỏ tới node gốc

    /**
     * @brief Thêm node mới vào cây (Helper function)
     * @param node Node hiện tại
     * @param contact Liên hệ cần thêm
     * @return Node mới sau khi thêm
     */
    BSTNode* insertHelper(BSTNode* node, const Contact& contact) {
        if (node == nullptr) {
            return new BSTNode(contact);
        }

        if (contact.name < node->data.name) {
            node->left = insertHelper(node->left, contact);
        } else if (contact.name > node->data.name) {
            node->right = insertHelper(node->right, contact);
        }

        return node;
    }

    /**
     * @brief Tìm node có giá trị nhỏ nhất trong cây
     * @param node Node gốc của cây con
     * @return Node có giá trị nhỏ nhất
     */
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief Xóa node khỏi cây (Helper function)
     * @param node Node hiện tại
     * @param name Tên liên hệ cần xóa
     * @return Node sau khi xóa
     */
    BSTNode* removeHelper(BSTNode* node, const string& name) {
        if (node == nullptr) {
            return nullptr;
        }

        if (name < node->data.name) {
            node->left = removeHelper(node->left, name);
        } else if (name > node->data.name) {
            node->right = removeHelper(node->right, name);
        } else {
            // Tìm thấy node cần xóa
            
            // Trường hợp 1: Node là lá
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Trường hợp 2: Node có 1 con
            else if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Trường hợp 3: Node có 2 con
            else {
                BSTNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeHelper(node->right, temp->data.name);
            }
        }
        return node;
    }

    /**
     * @brief Tìm kiếm liên hệ trong cây (Helper function)
     * @param node Node hiện tại
     * @param name Tên liên hệ cần tìm
     * @return Con trỏ tới Contact nếu tìm thấy, nullptr nếu không
     */
    Contact* searchHelper(BSTNode* node, const string& name) const {
        if (node == nullptr || node->data.name == name) {
            return node ? &node->data : nullptr;
        }

        if (name < node->data.name) {
            return searchHelper(node->left, name);
        } else {
            return searchHelper(node->right, name);
        }
    }

    /**
     * @brief Duyệt cây theo thứ tự in-order (Helper function)
     * @param node Node hiện tại
     */
    void displayHelper(BSTNode* node) const {
        if (node != nullptr) {
            displayHelper(node->left);
            node->data.display();
            displayHelper(node->right);
        }
    }

    /**
     * @brief Đếm số lượng node trong cây (Helper function)
     * @param node Node hiện tại
     * @return Số lượng node
     */
    int countHelper(BSTNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countHelper(node->left) + countHelper(node->right);
    }

    /**
     * @brief Xóa toàn bộ cây (Helper function)
     * @param node Node hiện tại
     */
    void clearHelper(BSTNode* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    /**
     * @brief Copy cây (Helper function)
     * @param node Node cần copy
     * @return Node mới đã copy
     */
    BSTNode* copyTree(BSTNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        BSTNode* newNode = new BSTNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    /**
     * @brief Tìm kiếm một phần (Helper function)
     * @param node Node hiện tại
     * @param partialName Tên một phần
     * @param results Vector kết quả
     */
    void searchPartialHelper(BSTNode* node, const string& partialName, vector<Contact>& results) const {
        if (node == nullptr) {
            return;
        }
        
        // Kiểm tra node hiện tại
        if (node->data.name.find(partialName) != string::npos) {
            results.push_back(node->data);
        }
        
        // Duyệt cây con trái
        searchPartialHelper(node->left, partialName, results);
        
        // Duyệt cây con phải
        searchPartialHelper(node->right, partialName, results);
    }

    /**
     * @brief Lấy tất cả liên hệ (Helper function)
     * @param node Node hiện tại
     * @param contacts Vector kết quả
     */
    void getAllContactsHelper(BSTNode* node, vector<Contact>& contacts) const {
        if (node == nullptr) {
            return;
        }
        
        // Duyệt cây con trái
        getAllContactsHelper(node->left, contacts);
        
        // Thêm node hiện tại
        contacts.push_back(node->data);
        
        // Duyệt cây con phải
        getAllContactsHelper(node->right, contacts);
    }

public:
    /**
     * @brief Constructor khởi tạo cây rỗng
     */
    BinarySearchTree() : root(nullptr) {}

    /**
     * @brief Destructor giải phóng bộ nhớ
     */
    ~BinarySearchTree() {
        clear();
    }

    /**
     * @brief Copy constructor
     */
    BinarySearchTree(const BinarySearchTree& other) : root(nullptr) {
        if (other.root) {
            root = copyTree(other.root);
        }
    }

    /**
     * @brief Assignment operator
     */
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            clear();
            if (other.root) {
                root = copyTree(other.root);
            }
        }
        return *this;
    }

    /**
     * @brief Xóa toàn bộ cây
     */
    void clear() {
        clearHelper(root);
        root = nullptr;
    }

    /**
     * @brief Thêm liên hệ mới vào cây
     * @param contact Liên hệ cần thêm
     * @return true nếu thêm thành công
     * @throws DataStructureException nếu không thể thêm
     */
    bool insert(const Contact& contact) {
        try {
            root = insertHelper(root, contact);
            return true;
        } catch (const std::bad_alloc& e) {
            throw DataStructureException::insertFailed("Lỗi cấp phát bộ nhớ: " + string(e.what()));
        } catch (const exception& e) {
            throw DataStructureException::insertFailed("Lỗi không xác định: " + string(e.what()));
        }
    }

    /**
     * @brief Xóa liên hệ khỏi cây
     * @param name Tên liên hệ cần xóa
     * @return true nếu xóa thành công
     * @throws DataStructureException nếu không thể xóa
     */
    bool remove(const string& name) {
        try {
            root = removeHelper(root, name);
            return true;
        } catch (const std::bad_alloc& e) {
            throw DataStructureException::deleteFailed("Lỗi cấp phát bộ nhớ: " + string(e.what()));
        } catch (const exception& e) {
            throw DataStructureException::deleteFailed("Lỗi không xác định: " + string(e.what()));
        }
    }

    /**
     * @brief Tìm kiếm liên hệ theo tên
     * @param name Tên liên hệ cần tìm
     * @return Con trỏ tới Contact nếu tìm thấy, nullptr nếu không
     */
    Contact* search(const string& name) const {
        return searchHelper(root, name);
    }

    /**
     * @brief Tìm kiếm liên hệ theo tên (một phần)
     * @param partialName Tên một phần cần tìm
     * @return Vector chứa các liên hệ phù hợp
     */
    vector<Contact> searchPartial(const string& partialName) const {
        vector<Contact> results;
        searchPartialHelper(root, partialName, results);
        return results;
    }

    /**
     * @brief Hiển thị tất cả liên hệ theo thứ tự in-order
     */
    void displayAll() const {
        if (isEmpty()) {
            cout << "Danh bạ trống!" << endl;
            return;
        }
        cout << "+----------------------------------------+" << endl;
        cout << "| Tên\t\t| Số điện thoại\t| Email\t\t|" << endl;
        cout << "+----------------------------------------+" << endl;
        displayHelper(root);
        cout << "+----------------------------------------+" << endl;
    }

    /**
     * @brief Lấy tất cả liên hệ theo thứ tự in-order
     * @return Vector chứa tất cả liên hệ
     */
    vector<Contact> getAllContacts() const {
        vector<Contact> contacts;
        getAllContactsHelper(root, contacts);
        return contacts;
    }

    /**
     * @brief Kiểm tra cây có rỗng không
     * @return true nếu rỗng
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief Đếm số lượng liên hệ trong cây
     * @return Số lượng liên hệ
     */
    int size() const {
        return countHelper(root);
    }
};

#endif // BINARYSEARCHTREE_H
