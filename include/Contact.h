#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <set>

using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;  // 🔑 Chỉ 1 số điện thoại duy nhất
    string email;        // 🔑 Chỉ 1 email duy nhất
    string address;
    string notes;
    int id;
    static int nextId;

public:
    Contact();
    Contact(const string& name);
    
    // Getters
    int getId() const;
    string getName() const;
    string getPhoneNumber() const;  // 🔑 Lấy số điện thoại duy nhất
    string getEmail() const;        // 🔑 Lấy email duy nhất
    string getAddress() const;
    string getNotes() const;
    
    // Setters
    void setName(const string& name);
    void setAddress(const string& address);
    void setNotes(const string& notes);
    
    // Phone and email management
    void setPhoneNumber(const string& phone);  // 🔑 Set số điện thoại (thay thế)
    void setEmail(const string& email);        // 🔑 Set email (thay thế)
    
    // Utility methods
    bool hasPhoneNumber() const;  // 🔑 Kiểm tra có số điện thoại không
    bool hasEmail() const;        // 🔑 Kiểm tra có email không
    void display() const;
    string toString() const;
};

#endif
