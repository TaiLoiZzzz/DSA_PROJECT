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
        
        cout << " Liên hệ '" << name << "' đã được thêm thành công với ID: " << newContact->getId() << endl;
        return true;
    } catch (const ContactException& e) {
        cout << " Lỗi: " << e.what() << endl;
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
        
        cout << " Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << " Lỗi: " << e.what() << endl;
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
        
        cout << " Liên hệ '" << name << "' (ID: " << id << ") đã được xóa thành công!" << endl;
        return true;
    } catch (const ContactException& e) {
        cout << "Lỗi: " << e.what() << endl;
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
    
    // If input is empty, return empty results
    if (name.empty()) {
        return results;
    }
    
    // Convert input to lowercase for case-insensitive search
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    // Search for partial matches in names
    for (const auto& pair : contactsByName) {
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
    auto it = contactsByPhone.find(phone);
    if (it != contactsByPhone.end()) {
        results.insert(it->second);
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
 
    
    // Search for partial matches in phone numbers
    for (const auto& pair : contactsByPhone) {
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
    
    // Search for partial matches in emails
    for (const auto& pair : contactsByEmail) {
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
        cout << "Lỗi: " << e.what() << endl;
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
    contactsByName.erase(contact->getName());
    contactsById.erase(contact->getId());
    
    // Remove from phone index
    if (!contact->getPhoneNumber().empty()) {
        contactsByPhone.erase(contact->getPhoneNumber());
    }
    
    // Remove from email index
    if (!contact->getEmail().empty()) {
        contactsByEmail.erase(contact->getEmail());
    }
}

void ContactManager::addToIndexes(Contact* contact) {
    contactsByName[contact->getName()] = contact;
    contactsById[contact->getId()] = contact;
    
    // 🔑 Thêm số điện thoại vào index với validation
    if (!contact->getPhoneNumber().empty()) {
        if (!isPhoneNumberDuplicate(contact->getPhoneNumber(), contact)) {
            contactsByPhone[contact->getPhoneNumber()] = contact;
        } else {
        }
    }
    
    // 🔑 Thêm email vào index với validation
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail[contact->getEmail()] = contact;
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
            contactsByPhone[contact->getPhoneNumber()] = contact;
        } else {
        }
    }
    
    // 🔑 Sync email với validation
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail[contact->getEmail()] = contact;
        } else {
        }
    }
    
  
}



void ContactManager::updatePhoneIndex(Contact* contact, const string& oldPhone, const string& newPhone) {
    // Remove old phone from index if it exists
    if (!oldPhone.empty()) {
        contactsByPhone.erase(oldPhone);
    }
    
    // 🔑 Add new phone to index với validation
    if (!newPhone.empty()) {
        if (!isPhoneNumberDuplicate(newPhone, contact)) {
            contactsByPhone[newPhone] = contact;
        } else {
        }
    }
}

void ContactManager::updateEmailIndex(Contact* contact, const string& oldEmail, const string& newEmail) {
    // Remove old email from index if it exists
    if (!oldEmail.empty()) {
        contactsByEmail.erase(oldEmail);
    }
    
    // 🔑 Add new email to index với validation
    if (!newEmail.empty()) {
        if (!isEmailDuplicate(newEmail, contact)) {
            contactsByEmail[newEmail] = contact;
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
    auto it = contactsByPhone.find(phone);
    if (it == contactsByPhone.end()) {
        return false;  // Không tìm thấy -> không trùng lặp
    }
    
    // Nếu tìm thấy, kiểm tra có phải liên hệ khác không
    Contact* existingContact = it->second;
    if (excludeContact && existingContact == excludeContact) {
        return false;  // Cùng một liên hệ -> không trùng lặp
    }
    
    return true;  // Trùng lặp với liên hệ khác
}

// 🔑 Kiểm tra email có bị trùng lặp với liên hệ khác không
bool ContactManager::isEmailDuplicate(const string& email, Contact* excludeContact) const {
    auto it = contactsByEmail.find(email);
    if (it == contactsByEmail.end()) {
        return false;  // Không tìm thấy -> không trùng lặp
    }
    
    // Nếu tìm thấy, kiểm tra có phải liên hệ khác không
    Contact* existingContact = it->second;
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
    for (auto& pair : contactsById) {
        delete pair.second;
    }
    contactsByName.clear();
    contactsByPhone.clear();
    contactsByEmail.clear();
    contactsById.clear();
}
