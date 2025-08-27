#include "Contact.h"
#include <iostream>
#include <sstream>

using namespace std;

int Contact::nextId = 1;

Contact::Contact() : id(nextId++) {
    name = "";
    phoneNumber = "";
    email = "";
    address = "";
    notes = "";
}

Contact::Contact(const string& name) : id(nextId++) {
    this->name = name;
    phoneNumber = "";
    email = "";
    address = "";
    notes = "";
}

int Contact::getId() const {
    return id;
}

string Contact::getName() const {
    return name;
}

string Contact::getPhoneNumber() const {
    return phoneNumber;
}

string Contact::getEmail() const {
    return email;
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

void Contact::setPhoneNumber(const string& phone) {
    phoneNumber = phone;  // 🔑 Thay thế số điện thoại cũ
}

void Contact::setEmail(const string& email) {
    this->email = email;  // 🔑 Thay thế email cũ
}

bool Contact::hasPhoneNumber() const {
    return !phoneNumber.empty();  // 🔑 Kiểm tra có số điện thoại không
}

bool Contact::hasEmail() const {
    return !email.empty();  // 🔑 Kiểm tra có email không
}

void Contact::display() const {
    cout << "\n=== Liên hệ ID: " << id << " ===" << endl;
    cout << "Tên: " << name << endl;
    
    if (!phoneNumber.empty()) {
        cout << "Số điện thoại: " << phoneNumber << endl;
    }
    
    if (!email.empty()) {
        cout << "Email: " << email << endl;
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
