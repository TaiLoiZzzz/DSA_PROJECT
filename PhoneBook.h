#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "BinarySearchTree.h"
#include "Contact.h"
#include "UI_linux.h"
#include "Exceptions.h"
#include <set>
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * @brief Lớp quản lý danh bạ điện thoại với Singleton Pattern
 * Đảm bảo chỉ có một instance duy nhất của danh bạ trong toàn bộ ứng dụng
 */
class PhoneBook {
private:
    static PhoneBook* instance;  // Instance duy nhất (Singleton)
    BinarySearchTree bst;        // Cây tìm kiếm nhị phân lưu trữ liên hệ
    set<string> phoneNumbers;    // Set lưu trữ số điện thoại để kiểm tra trùng lặp
    UI ui;                       // Đối tượng giao diện người dùng

    /**
     * @brief Constructor riêng tư (Singleton)
     */
    PhoneBook() {}

    /**
     * @brief Kiểm tra xem số điện thoại đã tồn tại chưa
     * @param phone Số điện thoại cần kiểm tra
     * @return true nếu đã tồn tại
     */
    bool isPhoneNumberExists(const string& phone) const {
        return phoneNumbers.find(phone) != phoneNumbers.end();
    }

    /**
     * @brief Kiểm tra xem tên liên hệ đã tồn tại chưa
     * @param name Tên liên hệ cần kiểm tra
     * @return true nếu đã tồn tại
     */
    bool isNameExists(const string& name) const {
        return bst.search(name) != nullptr;
    }

    /**
     * @brief Nhập tên liên hệ từ người dùng với validation chi tiết
     * @return Tên hợp lệ
     * @throws InvalidNameException nếu tên không hợp lệ
     */
    string inputName() {
        string name;
        while (true) {
            try {
                cout << "Nhập tên: ";
                getline(cin, name);
                
                // Loại bỏ khoảng trắng thừa
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                
                // Kiểm tra validation
                if (name.empty()) {
                    throw InvalidNameException::emptyName();
                }
                
                if (name.length() > 50) {
                    throw InvalidNameException::tooLong(name);
                }
                
                // Kiểm tra tên chỉ chứa chữ cái, số và khoảng trắng
                for (char c : name) {
                    if (!isalnum(c) && c != ' ') {
                        throw InvalidNameException::invalidCharacters(name);
                    }
                }
                
                // Kiểm tra tên trùng lặp
                if (isNameExists(name)) {
                    throw InvalidNameException::duplicateName(name);
                }
                
                break; // Thành công
                
            } catch (const InvalidNameException& e) {
                ui.showError(e.what());
                cout << "Vui lòng nhập lại hoặc nhấn Enter để hủy thao tác: ";
                string choice;
                getline(cin, choice);
                if (choice.empty()) {
                    throw; // Re-throw để hủy thao tác
                }
            }
        }
        return name;
    }

    /**
     * @brief Nhập số điện thoại từ người dùng với validation chi tiết
     * @return Số điện thoại hợp lệ
     * @throws InvalidPhoneNumberException nếu số điện thoại không hợp lệ
     */
    string inputPhoneNumber() {
        string phone;
        while (true) {
            try {
                cout << "Nhập số điện thoại: ";
                getline(cin, phone);
                
                // Loại bỏ khoảng trắng
                phone.erase(remove(phone.begin(), phone.end(), ' '), phone.end());
                
                // Kiểm tra validation
                if (phone.empty()) {
                    throw InvalidPhoneNumberException::emptyNumber();
                }
                
                if (phone.length() < 10 || phone.length() > 15) {
                    throw InvalidPhoneNumberException::wrongLength(phone);
                }
                
                // Kiểm tra chỉ chứa số
                for (char c : phone) {
                    if (!isdigit(c)) {
                        throw InvalidPhoneNumberException::invalidFormat(phone);
                    }
                }
                
                // Kiểm tra trùng lặp
                if (isPhoneNumberExists(phone)) {
                    throw InvalidPhoneNumberException::duplicateNumber(phone);
                }
                
                break; // Thành công
                
            } catch (const InvalidPhoneNumberException& e) {
                ui.showError(e.what());
                cout << "Vui lòng nhập lại hoặc nhấn Enter để hủy thao tác: ";
                string choice;
                getline(cin, choice);
                if (choice.empty()) {
                    throw; // Re-throw để hủy thao tác
                }
            }
        }
        return phone;
    }

    /**
     * @brief Nhập email từ người dùng
     * @return Email (có thể rỗng)
     */
    string inputEmail() {
        string email;
        cout << "Nhập email (có thể để trống): ";
        getline(cin, email);
        return email;
    }

public:
    /**
     * @brief Destructor
     */
    ~PhoneBook() {
        // Không xóa instance trong destructor
        // Instance sẽ được quản lý bởi hệ thống
    }

    /**
     * @brief Lấy instance duy nhất của PhoneBook (Singleton)
     * @return Con trỏ tới PhoneBook instance
     */
    static PhoneBook* getInstance() {
        if (instance == nullptr) {
            instance = new PhoneBook();
        }
        return instance;
    }

    /**
     * @brief Thêm liên hệ mới vào danh bạ với xử lý exception chi tiết
     */
    void addContact() {
        try {
            ui.showHeader();
            ui.showInfo("=== THÊM LIÊN HỆ MỚI ===");
            
            try {
                string name = inputName();
                string phone = inputPhoneNumber();
                string email = inputEmail();
                
                // Tạo liên hệ mới sử dụng Factory Pattern
                Contact newContact = ContactFactory::createContact(name, phone, email);
                
                // Thêm vào BST và set
                try {
                    if (bst.insert(newContact)) {
                        phoneNumbers.insert(phone);
                        ui.showSuccess("Liên hệ " + name + " đã được thêm thành công!");
                    } else {
                        throw DataStructureException::insertFailed("Thao tác insert trả về false");
                    }
                } catch (const DataStructureException& e) {
                    ui.showError(e.what());
                }
                
            } catch (const InvalidNameException& e) {
                ui.showError("Lỗi nhập tên: " + string(e.what()));
            } catch (const InvalidPhoneNumberException& e) {
                ui.showError("Lỗi nhập số điện thoại: " + string(e.what()));
            } catch (const ContactValidationException& e) {
                ui.showError("Lỗi validation: " + string(e.what()));
            }
            
        } catch (const exception& e) {
            ui.showError("Lỗi không xác định: " + string(e.what()));
        }
        
        ui.waitForEnter();
    }

    /**
     * @brief Xóa liên hệ khỏi danh bạ với xử lý exception chi tiết
     */
    void deleteContact() {
        try {
            ui.showHeader();
            ui.showInfo("=== XÓA LIÊN HỆ ===");
            
            if (bst.isEmpty()) {
                ui.showEmptyMessage();
                ui.waitForEnter();
                return;
            }
            
            try {
                string name;
                cout << "Nhập tên liên hệ cần xóa: ";
                getline(cin, name);
                
                // Kiểm tra tên không rỗng
                if (name.empty()) {
                    throw UIException::inputError("Tên liên hệ");
                }
                
                // Tìm liên hệ trước khi xóa
                Contact* contact = bst.search(name);
                if (contact == nullptr) {
                    throw ContactNotFoundException("Tên", name);
                }
                
                // Lưu số điện thoại trước khi xóa
                string phoneToRemove = contact->phoneNumber;
                
                // Xóa khỏi BST và set
                try {
                    if (bst.remove(name)) {
                        phoneNumbers.erase(phoneToRemove);
                        ui.showSuccess("Liên hệ " + name + " đã được xóa thành công!");
                    } else {
                        throw DataStructureException::deleteFailed("Thao tác remove trả về false");
                    }
                } catch (const DataStructureException& e) {
                    ui.showError(e.what());
                }
                
            } catch (const ContactNotFoundException& e) {
                ui.showError(e.what());
            } catch (const UIException& e) {
                ui.showError("Lỗi nhập liệu: " + string(e.what()));
            }
            
        } catch (const exception& e) {
            ui.showError("Lỗi không xác định: " + string(e.what()));
        }
        
        ui.waitForEnter();
    }

    /**
     * @brief Tìm kiếm liên hệ theo tên với xử lý exception chi tiết
     */
    void searchContact() {
        try {
            ui.showHeader();
            ui.showInfo("=== TÌM KIẾM LIÊN HỆ ===");
            
            try {
                string name;
                cout << "Nhập tên liên hệ cần tìm (có thể nhập một phần): ";
                getline(cin, name);
                
                // Kiểm tra tên không rỗng
                if (name.empty()) {
                    throw UIException::inputError("Tên liên hệ");
                }
                
                // Tìm kiếm chính xác trước
                Contact* contact = bst.search(name);
                if (contact != nullptr) {
                    // Hiển thị thông tin liên hệ tìm thấy
                    ui.showInfo("Thông tin liên hệ:");
                    ui.showSeparator();
                    ui.showContact("| Tên: " + contact->name);
                    ui.showContact("| Số điện thoại: " + contact->phoneNumber);
                    ui.showContact("| Email: " + contact->email);
                    ui.showSeparator();
                } else {
                    // Tìm kiếm một phần
                    vector<Contact> partialMatches = bst.searchPartial(name);
                    if (!partialMatches.empty()) {
                        ui.showInfo("Tìm thấy " + to_string(partialMatches.size()) + " liên hệ phù hợp:");
                        ui.showSeparator();
                        for (const Contact& c : partialMatches) {
                            ui.showContact("| " + c.name + " | " + c.phoneNumber + " | " + c.email + " |");
                        }
                        ui.showSeparator();
                    } else {
                        throw ContactNotFoundException("Tên", name);
                    }
                }
                
            } catch (const ContactNotFoundException& e) {
                ui.showError(e.what());
            } catch (const UIException& e) {
                ui.showError("Lỗi nhập liệu: " + string(e.what()));
            }
            
        } catch (const exception& e) {
            ui.showError("Lỗi không xác định: " + string(e.what()));
        }
        
        ui.waitForEnter();
    }

    /**
     * @brief Hiển thị tất cả liên hệ trong danh bạ
     */
    void displayAllContacts() {
        try {
            ui.showHeader();
            ui.showInfo("=== DANH SÁCH TẤT CẢ LIÊN HỆ ===");
            
            if (bst.isEmpty()) {
                ui.showEmptyMessage();
            } else {
                // Lấy tất cả liên hệ
                vector<Contact> contacts = bst.getAllContacts();
                
                // Hiển thị header
                ui.showSeparator();
                ui.showContact("| Tên\t\t| Số điện thoại\t| Email\t\t|");
                ui.showSeparator();
                
                // Hiển thị từng liên hệ
                for (const Contact& contact : contacts) {
                    string displayLine = "| " + contact.name;
                    // Căn chỉnh cột tên
                    if (contact.name.length() < 8) {
                        displayLine += "\t\t";
                    } else if (contact.name.length() < 16) {
                        displayLine += "\t";
                    }
                    
                    displayLine += "| " + contact.phoneNumber + "\t| " + contact.email + " |";
                    ui.showContact(displayLine);
                }
                
                ui.showSeparator();
                ui.showInfo("Tổng cộng: " + to_string(contacts.size()) + " liên hệ");
            }
            
        } catch (const exception& e) {
            ui.showError("Lỗi không xác định: " + string(e.what()));
        }
        
        ui.waitForEnter();
    }

    /**
     * @brief Lấy số lượng liên hệ trong danh bạ
     * @return Số lượng liên hệ
     */
    int getContactCount() const {
        return bst.size();
    }

    /**
     * @brief Hiển thị menu chính
     */
    void showMainMenu() {
        ui.showMainMenu();
    }

    /**
     * @brief Hiển thị thông báo lỗi
     */
    void showError(const string& message) {
        ui.showError(message);
    }

    /**
     * @brief Hiển thị thông báo chờ người dùng nhấn Enter
     */
    void waitForEnter() {
        ui.waitForEnter();
    }

    /**
     * @brief Hiển thị thông báo tạm biệt
     */
    void showGoodbye() {
        ui.showGoodbye();
    }

    /**
     * @brief Dọn dẹp tài nguyên
     */
    static void cleanup() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
};

// Khởi tạo static member
PhoneBook* PhoneBook::instance = nullptr;

#endif // PHONEBOOK_H
