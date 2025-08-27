#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include "Contact.h"
#include "ContactException.h"
#include <map>
#include <set>
#include <string>

using namespace std;

class ContactManager {
private:
    static ContactManager* instance;
    ContactManager();
    
    // Main data structures for O(log n) operations
    map<string, Contact*> contactsByName;  // Sorted by name
    map<string, Contact*> contactsByPhone; // Phone number -> Contact
    map<string, Contact*> contactsByEmail; // Email -> Contact
    map<int, Contact*> contactsById;       // ID -> Contact
    
    // Helper methods
    void removeFromIndexes(Contact* contact);
    void addToIndexes(Contact* contact);
    bool isValidPhone(const string& phone) const;
    bool isValidEmail(const string& email) const;

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
};

#endif
