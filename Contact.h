#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <set>

using namespace std;

class Contact {
private:
    string name;
    set<string> phoneNumbers;
    set<string> emails;
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
    set<string> getPhoneNumbers() const;
    set<string> getEmails() const;
    string getAddress() const;
    string getNotes() const;
    
    // Setters
    void setName(const string& name);
    void setAddress(const string& address);
    void setNotes(const string& notes);
    
    // Phone and email management
    void addPhoneNumber(const string& phone);
    void removePhoneNumber(const string& phone);
    void addEmail(const string& email);
    void removeEmail(const string& email);
    
    // Utility methods
    bool hasPhoneNumber(const string& phone) const;
    bool hasEmail(const string& email) const;
    void display() const;
    string toString() const;
};

#endif
