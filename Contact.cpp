#include "Contact.h"
#include <iostream>
#include <sstream>

using namespace std;

int Contact::nextId = 1;

Contact::Contact() : id(nextId++) {
    name = "";
    address = "";
    notes = "";
}

Contact::Contact(const string& name) : id(nextId++) {
    this->name = name;
    address = "";
    notes = "";
}

int Contact::getId() const {
    return id;
}

string Contact::getName() const {
    return name;
}

set<string> Contact::getPhoneNumbers() const {
    return phoneNumbers;
}

set<string> Contact::getEmails() const {
    return emails;
}

string Contact::getAddress() const {
    return address;
}

string Contact::getNotes() const {
    return notes;
}

void Contact::setName(const string& name) {
    this->name = name;
}

void Contact::setAddress(const string& address) {
    this->address = address;
}

void Contact::setNotes(const string& notes) {
    this->notes = notes;
}

void Contact::addPhoneNumber(const string& phone) {
    phoneNumbers.insert(phone);
}

void Contact::removePhoneNumber(const string& phone) {
    phoneNumbers.erase(phone);
}

void Contact::addEmail(const string& email) {
    emails.insert(email);
}

void Contact::removeEmail(const string& email) {
    emails.erase(email);
}

bool Contact::hasPhoneNumber(const string& phone) const {
    return phoneNumbers.find(phone) != phoneNumbers.end();
}

bool Contact::hasEmail(const string& email) const {
    return emails.find(email) != emails.end();
}

void Contact::display() const {
    cout << "\n=== Liên hệ ID: " << id << " ===" << endl;
    cout << "Tên: " << name << endl;
    
    if (!phoneNumbers.empty()) {
        cout << "Số điện thoại: ";
        for (const auto& phone : phoneNumbers) {
            cout << phone << " ";
        }
        cout << endl;
    }
    
    if (!emails.empty()) {
        cout << "Email: ";
        for (const auto& email : emails) {
            cout << email << " ";
        }
        cout << endl;
    }
    
    if (!address.empty()) {
        cout << "Địa chỉ: " << address << endl;
    }
    
    if (!notes.empty()) {
        cout << "Ghi chú: " << notes << endl;
    }
    cout << "========================\n" << endl;
}

string Contact::toString() const {
    stringstream ss;
    ss << "ID: " << id << ", Tên: " << name;
    return ss.str();
}
