#include <iostream>
#include <vector>
#include "PhoneBook.h"
#include "Contact.h"
#include "BinarySearchTree.h"

using namespace std;

/**
 * @brief Test memory management và copy constructor
 */
void testMemoryManagement() {
    cout << "=== TEST MEMORY MANAGEMENT ===" << endl;
    
    // Test 1: Tạo và xóa nhiều PhoneBook instances
    cout << "\n1. Test PhoneBook instances..." << endl;
    for (int i = 0; i < 5; i++) {
        PhoneBook* pb = PhoneBook::getInstance();
        cout << "Created PhoneBook instance " << i + 1 << endl;
        // Không xóa instance ở đây
    }
    
    // Test 2: Test BST copy constructor
    cout << "\n2. Test BST copy constructor..." << endl;
    {
        BinarySearchTree bst1;
        
        // Thêm một số liên hệ
        Contact c1("Test1", "0123456789", "test1@example.com");
        Contact c2("Test2", "0987654321", "test2@example.com");
        
        bst1.insert(c1);
        bst1.insert(c2);
        
        cout << "BST1 size: " << bst1.size() << endl;
        
        // Copy BST
        BinarySearchTree bst2 = bst1;
        cout << "BST2 size (copied): " << bst2.size() << endl;
        
        // Thêm vào BST2
        Contact c3("Test3", "1111111111", "test3@example.com");
        bst2.insert(c3);
        cout << "BST2 size after insert: " << bst2.size() << endl;
        cout << "BST1 size (should be unchanged): " << bst1.size() << endl;
        
        // BST1 và BST2 sẽ tự động được dọn dẹp khi ra khỏi scope
    }
    
    cout << "\n3. Test assignment operator..." << endl;
    {
        BinarySearchTree bst1, bst2;
        
        Contact c1("Assign1", "0123456789", "assign1@example.com");
        bst1.insert(c1);
        
        bst2 = bst1;
        cout << "BST2 size after assignment: " << bst2.size() << endl;
        
        // Thêm vào BST2
        Contact c2("Assign2", "0987654321", "assign2@example.com");
        bst2.insert(c2);
        cout << "BST2 size after insert: " << bst2.size() << endl;
        cout << "BST1 size (should be unchanged): " << bst1.size() << endl;
    }
    
    cout << "\n4. Test large BST..." << endl;
    {
        BinarySearchTree bst;
        
        // Thêm 100 liên hệ
        for (int i = 0; i < 100; i++) {
            string name = "User" + to_string(i);
            string phone = "0123456" + to_string(i).substr(0, 3);
            string email = "user" + to_string(i) + "@example.com";
            
            Contact c(name, phone, email);
            bst.insert(c);
        }
        
        cout << "Large BST size: " << bst.size() << endl;
        
        // BST sẽ tự động được dọn dẹp
    }
    
    cout << "\n=== MEMORY TEST COMPLETED ===" << endl;
    cout << "Nếu không có lỗi memory leak, chương trình sẽ kết thúc bình thường." << endl;
}

int main() {
    try {
        testMemoryManagement();
        
        // Cleanup PhoneBook instance
        PhoneBook::cleanup();
        
        cout << "\n🎉 Tất cả test đã hoàn thành thành công!" << endl;
        
    } catch (const exception& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
