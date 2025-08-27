#ifndef BSTNODE_H
#define BSTNODE_H

#include "Contact.h"

/**
 * @brief Node cho cây tìm kiếm nhị phân (Binary Search Tree)
 * Mỗi node chứa một liên hệ và con trỏ tới các node con
 */
struct BSTNode {
    Contact data;           // Dữ liệu liên hệ
    BSTNode* left;          // Con trỏ tới node con trái
    BSTNode* right;         // Con trỏ tới node con phải

    /**
     * @brief Constructor khởi tạo node
     * @param contact Liên hệ cần lưu trữ
     */
    BSTNode(const Contact& contact) 
        : data(contact), left(nullptr), right(nullptr) {}

    /**
     * @brief Copy constructor
     * @param other Node cần copy
     */
    BSTNode(const BSTNode& other) 
        : data(other.data), left(nullptr), right(nullptr) {}

    /**
     * @brief Assignment operator
     * @param other Node cần gán
     * @return Reference tới node hiện tại
     */
    BSTNode& operator=(const BSTNode& other) {
        if (this != &other) {
            data = other.data;
            // Không copy con trỏ để tránh double deletion
        }
        return *this;
    }

    /**
     * @brief Destructor giải phóng bộ nhớ
     */
    ~BSTNode() {
        // Đệ quy giải phóng các node con
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }
};

#endif // BSTNODE_H
