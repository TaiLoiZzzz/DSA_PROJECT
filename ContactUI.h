#ifndef CONTACT_UI_H
#define CONTACT_UI_H

#include "ContactManager.h"
#include <string>

using namespace std;

class ContactUI {
private:
    ContactManager* manager;
    
    // Menu methods
    void showMainMenu() const;
    void showContactMenu() const;
    void showSearchMenu() const;
    
    // Input methods
    string getStringInput(const string& prompt) const;
    int getIntInput(const string& prompt) const;
    void clearScreen() const;
    void pause() const;
    
    // Validation methods
    bool isValidPhoneNumber(const string& phone) const;
    bool isValidEmail(const string& email) const;
    
    // Contact operations
    void addContact() const;
    void addContactDetails(Contact* contact) const;
    void showAddDetailsMenu(Contact* contact) const;
    void showEditContactMenu(Contact* contact) const;
    void editContact() const;
    void deleteContact() const;
    void viewContact() const;
    void addPhoneToContact() const;
    void addPhoneToContact(Contact* contact) const;
    void addEmailToContact() const;
    void addEmailToContact(Contact* contact) const;
    void addAddressToContact(Contact* contact) const;
    void addNotesToContact(Contact* contact) const;
    void editContactName(Contact* contact) const;
    void managePhoneNumbers(Contact* contact) const;
    void manageEmails(Contact* contact) const;
    void deletePhoneNumber(Contact* contact) const;
    void deleteEmail(Contact* contact) const;
    
    // Search operations
    void searchContacts() const;
    void searchByName() const;
    void searchByPhone() const;
    void searchByEmail() const;
    
    // Display operations
    void displayAllContacts() const;
    void displaySearchResults(const set<Contact*>& results) const;

public:
    ContactUI();
    ~ContactUI();
    
    void run();
    void showWelcome() const;
    void showGoodbye() const;
};

#endif
