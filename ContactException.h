#ifndef CONTACT_EXCEPTION_H
#define CONTACT_EXCEPTION_H

#include <string>
#include <exception>

using namespace std;

class ContactException : public exception {
private:
    string message;

public:
    ContactException(const string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Các loại exception cụ thể
class ContactNotFound : public ContactException {
public:
    ContactNotFound(const string& name) 
        : ContactException("Không tìm thấy liên hệ: " + name) {}
};

class ContactAlreadyExists : public ContactException {
public:
    ContactAlreadyExists(const string& name) 
        : ContactException("Liên hệ đã tồn tại: " + name) {}
};

class InvalidInput : public ContactException {
public:
    InvalidInput(const string& field) 
        : ContactException("Dữ liệu đầu vào không hợp lệ cho: " + field) {}
};

class EmptyInput : public ContactException {
public:
    EmptyInput(const string& field) 
        : ContactException("Trường " + field + " không được để trống") {}
};

#endif
