#include "ContactManager.h"
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

ContactManager* ContactManager::instance = nullptr;

ContactManager::ContactManager() {}

ContactManager* ContactManager::getInstance() {
    if (instance == nullptr) {
        instance = new ContactManager();
    }
    return instance;
}

bool ContactManager::addContact(const string& name) {
    try {
        if (name.empty()) {
            throw EmptyInput("tên");
        }
        
        if (contactsByName.find(name) != contactsByName.end()) {
            throw ContactAlreadyExists(name);
        }
        
        Contact* newContact = new Contact(name);
        addToIndexes(newContact);
        
        cout << "✓ Liên hệ '" << name << "' đã được thêm thành công với ID: " << newContact->getId() << endl;
        return true;
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return false;
    }
}

bool ContactManager::removeContact(int id) {
    try {
        auto it = contactsById.find(id);
        if (it == contactsById.end()) {
            throw ContactNotFound("ID " + to_string(id));
        }
        
        Contact* contact = it->second;
        string name = contact->getName();
        removeFromIndexes(contact);
        delete contact;
        
        cout << "✓ Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return false;
    }
}

bool ContactManager::removeContact(const string& name) {
    try {
        auto it = contactsByName.find(name);
        if (it == contactsByName.end()) {
            throw ContactNotFound(name);
        }
        
        Contact* contact = it->second;
        int id = contact->getId();
        removeFromIndexes(contact);
        delete contact;
        
        cout << "✓ Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return false;
    }
}

Contact* ContactManager::findContact(int id) {
    auto it = contactsById.find(id);
    return (it != contactsById.end()) ? it->second : nullptr;
}

Contact* ContactManager::findContact(const string& name) {
    auto it = contactsByName.find(name);
    return (it != contactsByName.end()) ? it->second : nullptr;
}

set<Contact*> ContactManager::searchByName(const string& name) {
    set<Contact*> results;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    for (const auto& pair : contactsByName) {
        string contactName = pair.first;
        transform(contactName.begin(), contactName.end(), contactName.begin(), ::tolower);
        
        if (contactName.find(lowerName) != string::npos) {
            results.insert(pair.second);
        }
    }
    
    return results;
}

set<Contact*> ContactManager::searchByPhone(const string& phone) {
    set<Contact*> results;
    auto it = contactsByPhone.find(phone);
    if (it != contactsByPhone.end()) {
        results.insert(it->second);
    }
    return results;
}

set<Contact*> ContactManager::searchByEmail(const string& email) {
    set<Contact*> results;
    auto it = contactsByEmail.find(email);
    if (it != contactsByEmail.end()) {
        results.insert(it->second);
    }
    return results;
}

void ContactManager::displayAllContacts() const {
    if (contactsByName.empty()) {
        cout << "📭 Không có liên hệ nào trong danh bạ!" << endl;
        return;
    }
    
    cout << "\n=== TẤT CẢ LIÊN HỆ (" << contactsByName.size() << ") ===" << endl;
    for (const auto& pair : contactsByName) {
        pair.second->display();
    }
}

void ContactManager::displayContact(int id) const {
    try {
        auto it = contactsById.find(id);
        if (it == contactsById.end()) {
            throw ContactNotFound("ID " + to_string(id));
        }
        it->second->display();
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
    }
}

void ContactManager::displayContact(const string& name) const {
    try {
        auto it = contactsByName.find(name);
        if (it == contactsByName.end()) {
            throw ContactNotFound(name);
        }
        it->second->display();
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
    }
}

int ContactManager::getTotalContacts() const {
    return contactsByName.size();
}

bool ContactManager::isEmpty() const {
    return contactsByName.empty();
}

void ContactManager::removeFromIndexes(Contact* contact) {
    contactsByName.erase(contact->getName());
    contactsById.erase(contact->getId());
    
    // Remove from phone index
    for (const auto& phone : contact->getPhoneNumbers()) {
        contactsByPhone.erase(phone);
    }
    
    // Remove from email index
    for (const auto& email : contact->getEmails()) {
        contactsByEmail.erase(email);
    }
}

void ContactManager::addToIndexes(Contact* contact) {
    contactsByName[contact->getName()] = contact;
    contactsById[contact->getId()] = contact;
    
    // Add to phone index
    for (const auto& phone : contact->getPhoneNumbers()) {
        contactsByPhone[phone] = contact;
    }
    
    // Add to email index
    for (const auto& email : contact->getEmails()) {
        contactsByEmail[email] = contact;
    }
}

bool ContactManager::isValidPhone(const string& phone) const {
    regex phonePattern(R"(\d{10,15})");
    return regex_match(phone, phonePattern);
}

bool ContactManager::isValidEmail(const string& email) const {
    regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

ContactManager::~ContactManager() {
    clearAll();
}

void ContactManager::clearAll() {
    for (auto& pair : contactsById) {
        delete pair.second;
    }
    contactsByName.clear();
    contactsByPhone.clear();
    contactsByEmail.clear();
    contactsById.clear();
}
