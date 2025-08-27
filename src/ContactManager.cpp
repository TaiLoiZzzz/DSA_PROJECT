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
        
        if (contactsByName.contains(name)) {
            throw ContactAlreadyExists(name);
        }
        
        Contact* newContact = new Contact(name);
        addToIndexes(newContact);
        
        cout << " Liên hệ '" << name << "' đã được thêm thành công với ID: " << newContact->getId() << endl;
        return true;
    } catch (const ContactException& e) {
        cout << " Lỗi: " << e.what() << endl;
        return false;
    }
}

bool ContactManager::removeContact(int id) {
    try {
        Contact** contactPtr = contactsById.find(id);
        if (contactPtr == nullptr) {
            throw ContactNotFound("ID " + to_string(id));
        }
        
        Contact* contact = *contactPtr;
        string name = contact->getName();
        removeFromIndexes(contact);
        delete contact;
        
        cout << " Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << " Lỗi: " << e.what() << endl;
        return false;
    }
}

bool ContactManager::removeContact(const string& name) {
    try {
        Contact** contactPtr = contactsByName.find(name);
        if (contactPtr == nullptr) {
            throw ContactNotFound(name);
        }
        
        Contact* contact = *contactPtr;
        int id = contact->getId();
        removeFromIndexes(contact);
        delete contact;
        
        cout << " Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << "Lỗi: " << e.what() << endl;
        return false;
    }
}

Contact* ContactManager::findContact(int id) {
    Contact** contactPtr = contactsById.find(id);
    return contactPtr ? *contactPtr : nullptr;
}

Contact* ContactManager::findContact(const string& name) {
    Contact** contactPtr = contactsByName.find(name);
    return contactPtr ? *contactPtr : nullptr;
}

set<Contact*> ContactManager::searchByName(const string& name) {
    set<Contact*> results;
    
    // If input is empty, return empty results
    if (name.empty()) {
        return results;
    }
    
    // Convert input to lowercase for case-insensitive search
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    // Search for partial matches in names using tree traversal
    vector<pair<string, Contact*>> allPairs = contactsByName.getAllPairs();
    for (const auto& pair : allPairs) {
        string contactName = pair.first;
        string lowerContactName = contactName;
        transform(lowerContactName.begin(), lowerContactName.end(), lowerContactName.begin(), ::tolower);
        
        // Check if input is found in contact name
        if (lowerContactName.find(lowerName) != string::npos) {
            results.insert(pair.second);
        }
    }
    
    return results;
}

set<Contact*> ContactManager::searchByPhone(const string& phone) {
    set<Contact*> results;
    
    // First try exact match (fastest)
    Contact** contactPtr = contactsByPhone.find(phone);
    if (contactPtr != nullptr) {
        Contact* contact = *contactPtr;
        results.insert(contact);
        return results;
    }
    
    // If exact match not found, try partial search
    // Clean the input phone number (remove spaces, dashes, etc.)
    string cleanPhone = phone;
    cleanPhone.erase(remove_if(cleanPhone.begin(), cleanPhone.end(), 
                              [](char c) { return !isdigit(c); }), cleanPhone.end());
    
    // If input is empty after cleaning, return empty results
    if (cleanPhone.empty()) {
        return results;
    }
    
    // Debug: Print what we're searching for
 
    
    // Search for partial matches in phone numbers using tree traversal
    vector<pair<string, Contact*>> allPairs = contactsByPhone.getAllPairs();
    for (const auto& pair : allPairs) {
        string storedPhone = pair.first;
        string cleanStoredPhone = storedPhone;
        cleanStoredPhone.erase(remove_if(cleanStoredPhone.begin(), cleanStoredPhone.end(), 
                                       [](char c) { return !isdigit(c); }), cleanStoredPhone.end());
        
        
        // Check if clean input is found in clean stored phone
        if (cleanStoredPhone.find(cleanPhone) != string::npos) {
            cout << "  ✓ Match found!" << endl;
            results.insert(pair.second);
        }
    }
    
    return results;
}

set<Contact*> ContactManager::searchByEmail(const string& email) {
    set<Contact*> results;
    
    // Convert input to lowercase for case-insensitive search
    string lowerEmail = email;
    transform(lowerEmail.begin(), lowerEmail.end(), lowerEmail.begin(), ::tolower);
    
    // Search for partial matches in emails using tree traversal
    vector<pair<string, Contact*>> allPairs = contactsByEmail.getAllPairs();
    for (const auto& pair : allPairs) {
        string storedEmail = pair.first;
        string lowerStoredEmail = storedEmail;
        transform(lowerStoredEmail.begin(), lowerStoredEmail.end(), lowerStoredEmail.begin(), ::tolower);
        
        // Check if input is found in stored email
        if (lowerStoredEmail.find(lowerEmail) != string::npos) {
            results.insert(pair.second);
        }
    }
    
    return results;
}

void ContactManager::displayAllContacts() const {
    if (contactsByName.empty()) {
        cout << " Không có liên hệ nào trong danh bạ!" << endl;
        return;
    }
    
    cout << "\n=== TẤT CẢ LIÊN HỆ (" << contactsByName.size() << ") ===" << endl;
    vector<pair<string, Contact*>> allPairs = contactsByName.getAllPairs();
    for (const auto& pair : allPairs) {
        pair.second->display();
    }
}

void ContactManager::displayContact(int id) const {
    try {
        Contact* const* contactPtr = contactsById.find(id);
        if (contactPtr == nullptr) {
            throw ContactNotFound("ID " + to_string(id));
        }
        Contact* contact = *contactPtr;
        contact->display();
    } catch (const ContactException& e) {
        cout << "Lỗi: " << e.what() << endl;
    }
}

void ContactManager::displayContact(const string& name) const {
    try {
        Contact* const* contactPtr = contactsByName.find(name);
        if (contactPtr == nullptr) {
            throw ContactNotFound(name);
        }
        Contact* contact = *contactPtr;
        contact->display();
    } catch (const ContactException& e) {
        cout << " Lỗi: " << e.what() << endl;
    }
}

int ContactManager::getTotalContacts() const {
    return contactsByName.size();
}

bool ContactManager::isEmpty() const {
    return contactsByName.empty();
}

void ContactManager::removeFromIndexes(Contact* contact) {
    contactsByName.remove(contact->getName());
    contactsById.remove(contact->getId());
    
    // Remove from phone index
    if (!contact->getPhoneNumber().empty()) {
        contactsByPhone.remove(contact->getPhoneNumber());
    }
    
    // Remove from email index
    if (!contact->getEmail().empty()) {
        contactsByEmail.remove(contact->getEmail());
    }
}

void ContactManager::addToIndexes(Contact* contact) {
    contactsByName.insert(contact->getName(), contact);
    contactsById.insert(contact->getId(), contact);
    
    // 🔑 Thêm số điện thoại vào index với validation
    if (!contact->getPhoneNumber().empty()) {
        if (!isPhoneNumberDuplicate(contact->getPhoneNumber(), contact)) {
            contactsByPhone.insert(contact->getPhoneNumber(), contact);
        } else {
        }
    }
    
    // 🔑 Thêm email vào index với validation
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail.insert(contact->getEmail(), contact);
        } else {
        }
    }
    
    cout << "  📊 Index sizes - Names: " << contactsByName.size() 
         << ", IDs: " << contactsById.size() 
         << ", Phones: " << contactsByPhone.size() 
         << ", Emails: " << contactsByEmail.size() << endl;
}

// ⚠️ QUAN TRỌNG: Hàm này để đồng bộ tất cả số điện thoại và email vào index
void ContactManager::syncAllIndexes(Contact* contact) {
    
    // 🔑 Sync phone number với validation
    if (!contact->getPhoneNumber().empty()) {
        if (!isPhoneNumberDuplicate(contact->getPhoneNumber(), contact)) {
            contactsByPhone.insert(contact->getPhoneNumber(), contact);
        } else {
        }
    }
    
    // 🔑 Sync email với validation
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail.insert(contact->getEmail(), contact);
        } else {
        }
    }
    
  
}

void ContactManager::updatePhoneIndex(Contact* contact, const string& oldPhone, const string& newPhone) {
    // Remove old phone from index if it exists
    if (!oldPhone.empty()) {
        contactsByPhone.remove(oldPhone);
    }
    
    // 🔑 Add new phone to index với validation
    if (!newPhone.empty()) {
        if (!isPhoneNumberDuplicate(newPhone, contact)) {
            contactsByPhone.insert(newPhone, contact);
        } else {
        }
    }
}

void ContactManager::updateEmailIndex(Contact* contact, const string& oldEmail, const string& newEmail) {
    // Remove old email from index if it exists
    if (!oldEmail.empty()) {
        contactsByEmail.remove(oldEmail);
    }
    
    // 🔑 Add new email to index với validation
    if (!newEmail.empty()) {
        if (!isEmailDuplicate(newEmail, contact)) {
            contactsByEmail.insert(newEmail, contact);
        } else {
        }
    }
}

bool ContactManager::isValidPhone(const string& phone) const {
    // 🔑 Sử dụng validation mới (tối đa 11 số)
    return isPhoneNumberValid(phone);
}

bool ContactManager::isValidEmail(const string& email) const {
    regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

// 🔑 Kiểm tra số điện thoại có bị trùng lặp với liên hệ khác không
bool ContactManager::isPhoneNumberDuplicate(const string& phone, Contact* excludeContact) const {
    Contact* const* existingContactPtr = contactsByPhone.find(phone);
    if (existingContactPtr == nullptr) {
        return false;  // Không tìm thấy -> không trùng lặp
    }
    
    Contact* existingContact = *existingContactPtr;
    // Nếu tìm thấy, kiểm tra có phải liên hệ khác không
    if (excludeContact && existingContact == excludeContact) {
        return false;  // Cùng một liên hệ -> không trùng lặp
    }
    
    return true;  // Trùng lặp với liên hệ khác
}

// 🔑 Kiểm tra email có bị trùng lặp với liên hệ khác không
bool ContactManager::isEmailDuplicate(const string& email, Contact* excludeContact) const {
    Contact* const* existingContactPtr = contactsByEmail.find(email);
    if (existingContactPtr == nullptr) {
        return false;  // Không tìm thấy -> không trùng lặp
    }
    
    Contact* existingContact = *existingContactPtr;
    // Nếu tìm thấy, kiểm tra có phải liên hệ khác không
    if (excludeContact && existingContact == excludeContact) {
        return false;  // Cùng một liên hệ -> không trùng lặp
    }
    
    return true;  // Trùng lặp với liên hệ khác
}

// 🔑 Public method để kiểm tra có thể thêm số điện thoại không
bool ContactManager::canAddPhoneNumber(const string& phone, Contact* excludeContact) const {
    // Kiểm tra format và độ dài
    if (!isPhoneNumberValid(phone)) {
        return false;
    }
    
    // Kiểm tra trùng lặp
    if (isPhoneNumberDuplicate(phone, excludeContact)) {
        return false;
    }
    
    return true;
}

// 🔑 Public method để kiểm tra có thể thêm email không
bool ContactManager::canAddEmail(const string& email, Contact* excludeContact) const {
    // Kiểm tra format email
    if (!isValidEmail(email)) {
        return false;
    }
    
    // Kiểm tra trùng lặp
    if (isEmailDuplicate(email, excludeContact)) {
        return false;
    }
    
    return true;
}

// 🔑 Kiểm tra format và độ dài số điện thoại (tối đa 11 số)
bool ContactManager::isPhoneNumberValid(const string& phone) const {
    // Kiểm tra không rỗng
    if (phone.empty()) {
        return false;
    }
    
    // Kiểm tra độ dài tối đa 11 số
    if (phone.length() > 11) {
        return false;
    }
    
    // Kiểm tra tất cả ký tự đều là số
    for (char c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

ContactManager::~ContactManager() {
    clearAll();
}

void ContactManager::clearAll() {
    vector<pair<int, Contact*>> allPairs = contactsById.getAllPairs();
    for (auto& pair : allPairs) {
        delete pair.second;
    }
    contactsByName.clear();
    contactsByPhone.clear();
    contactsByEmail.clear();
    contactsById.clear();
}

void ContactManager::printTreeStructures() const {
    cout << "\n=== CẤU TRÚC CÂY DỮ LIỆU ===" << endl;
    
    cout << "\n🌳 Binary Search Tree - Contacts by Name:" << endl;
    contactsByName.print();
    
    cout << "\n🔴 Red-Black Tree - Contacts by Phone:" << endl;
    contactsByPhone.print();
    
    cout << "\n🔴 Red-Black Tree - Contacts by Email:" << endl;
    contactsByEmail.print();
    
    cout << "\n🌳 Binary Search Tree - Contacts by ID:" << endl;
    contactsById.print();
    
    cout << "=================================" << endl;
}
