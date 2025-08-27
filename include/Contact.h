#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <iostream>
#include "Exceptions.h"

using namespace std;

/**
 * @brief Struct đại diện cho một liên hệ trong danh bạ
 * Sử dụng Factory Pattern để tạo các đối tượng Contact
 */
struct Contact {
    string name;        // Tên liên hệ (bắt buộc)
    string phoneNumber; // Số điện thoại (bắt buộc)
    string email;       // Email (không bắt buộc)

    /**
     * @brief Constructor khởi tạo liên hệ
     * @param n Tên liên hệ
     * @param phone Số điện thoại
     * @param e Email (có thể để trống)
     */
    Contact(const string& n = "", const string& phone = "", const string& e = "")
        : name(n), phoneNumber(phone), email(e) {}

    /**
     * @brief Hiển thị thông tin liên hệ theo định dạng đẹp
     */
    void display() const {
        cout << "| " << name << " | " << phoneNumber << " | " << email << " |" << endl;
    }

    /**
     * @brief Kiểm tra tính hợp lệ của dữ liệu liên hệ
     * @throws InvalidNameException, InvalidPhoneNumberException, InvalidEmailException
     */
    void validate() const {
        // Kiểm tra tên
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
        
        // Kiểm tra số điện thoại
        if (phoneNumber.empty()) {
            throw InvalidPhoneNumberException::emptyNumber();
        }
        
        if (phoneNumber.length() < 10 || phoneNumber.length() > 15) {
            throw InvalidPhoneNumberException::wrongLength(phoneNumber);
        }
        
        // Kiểm tra số điện thoại chỉ chứa số
        for (char c : phoneNumber) {
            if (!isdigit(c)) {
                throw InvalidPhoneNumberException::invalidFormat(phoneNumber);
            }
        }
        
        // Kiểm tra email (nếu có)
        if (!email.empty()) {
            if (email.length() > 100) {
                throw InvalidEmailException::tooLong(email);
            }
            
            // Kiểm tra định dạng email đơn giản
            size_t atPos = email.find('@');
            size_t dotPos = email.find('.', atPos);
            
            if (atPos == string::npos || dotPos == string::npos || atPos == 0 || 
                dotPos == email.length() - 1 || dotPos <= atPos + 1) {
                throw InvalidEmailException::invalidFormat(email);
            }
        }
    }

    /**
     * @brief Kiểm tra tính hợp lệ của dữ liệu liên hệ (legacy)
     * @return true nếu hợp lệ, false nếu không
     */
    bool isValid() const {
        try {
            validate();
            return true;
        } catch (...) {
            return false;
        }
    }

    /**
     * @brief So sánh hai liên hệ theo tên (dùng cho BST)
     * @param other Liên hệ khác
     * @return true nếu this < other
     */
    bool operator<(const Contact& other) const {
        return name < other.name;
    }

    /**
     * @brief So sánh bằng hai liên hệ
     * @param other Liên hệ khác
     * @return true nếu bằng nhau
     */
    bool operator==(const Contact& other) const {
        return name == other.name && phoneNumber == other.phoneNumber;
    }
};

/**
 * @brief Factory Pattern để tạo các đối tượng Contact
 * Đảm bảo tính linh hoạt khi cần mở rộng các loại liên hệ khác
 */
class ContactFactory {
public:
    /**
     * @brief Tạo một liên hệ mới với validation chi tiết
     * @param name Tên liên hệ
     * @param phone Số điện thoại
     * @param email Email
     * @return Contact object nếu hợp lệ
     * @throws InvalidNameException, InvalidPhoneNumberException, InvalidEmailException
     */
    static Contact createContact(const string& name, const string& phone, const string& email = "") {
        try {
            Contact contact(name, phone, email);
            contact.validate();
            return contact;
        } catch (const ContactValidationException& e) {
            // Re-throw để giữ nguyên thông tin chi tiết
            throw;
        } catch (const exception& e) {
            throw ContactValidationException("Liên hệ", "unknown", "Lỗi không xác định: " + string(e.what()));
        }
    }
};

#endif // CONTACT_H
