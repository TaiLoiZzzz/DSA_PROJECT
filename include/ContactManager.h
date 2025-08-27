#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include "Contact.h"
#include "ContactException.h"
#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include <set>
#include <string>

using namespace std;

class ContactManager {
private:
    static ContactManager* instance;
    ContactManager();
    
    // Main data structures using custom implementations
    BinarySearchTree<string, Contact*> contactsByName;  // Sorted by name
    RedBlackTree<string, Contact*> contactsByPhone;    // Phone number -> Contact (balanced)
    RedBlackTree<string, Contact*> contactsByEmail;    // Email -> Contact (balanced)
    BinarySearchTree<int, Contact*> contactsById;      // ID -> Contact
    
    // Helper methods
    void removeFromIndexes(Contact* contact);
    void addToIndexes(Contact* contact);
    void updatePhoneIndex(Contact* contact, const string& oldPhone, const string& newPhone);
    void updateEmailIndex(Contact* contact, const string& oldEmail, const string& newEmail);

public:
    static ContactManager* getInstance();
    
    // Core operations
    bool addContact(const string& name);
    bool removeContact(int id);
    bool removeContact(const string& name);
    Contact* findContact(int id);
    Contact* findContact(const string& name);
    
    // Search operations
    set<Contact*> searchByName(const string& name);
    set<Contact*> searchByPhone(const string& phone);
    set<Contact*> searchByEmail(const string& email);
    
    // Display operations
    void displayAllContacts() const;
    void displayContact(int id) const;
    void displayContact(const string& name) const;
    
    // Statistics
    int getTotalContacts() const;
    bool isEmpty() const;
    
    // Cleanup
    ~ContactManager();
    void clearAll();
    
    // 🔧 Debug và sửa chữa
    void syncAllIndexes(Contact* contact);  // ⚠️ QUAN TRỌNG: Đồng bộ tất cả index
    
    // 🔑 Public validation methods
    bool canAddPhoneNumber(const string& phone, Contact* excludeContact = nullptr) const;
    bool canAddEmail(const string& email, Contact* excludeContact = nullptr) const;
    
    // 🔑 Validation methods for duplicate checking
    bool isPhoneNumberDuplicate(const string& phone, Contact* excludeContact = nullptr) const;
    bool isEmailDuplicate(const string& email, Contact* excludeContact = nullptr) const;
    bool isPhoneNumberValid(const string& phone) const;  // Check length and format
    bool isValidPhone(const string& phone) const;
    bool isValidEmail(const string& email) const;
    
    // 🔍 Debug methods for tree visualization
    void printTreeStructures() const;
};

#endif
