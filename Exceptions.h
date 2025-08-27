#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

using namespace std;

/**
 * @brief Exception cơ bản cho ứng dụng danh bạ
 */
class PhoneBookException : public std::exception {
protected:
    string message;

public:
    PhoneBookException(const string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @brief Exception cho lỗi validation dữ liệu liên hệ
 */
class ContactValidationException : public PhoneBookException {
private:
    string fieldName;
    string invalidValue;

public:
    ContactValidationException(const string& field, const string& value, const string& reason)
        : PhoneBookException("Lỗi validation cho " + field + ": '" + value + "' - " + reason),
          fieldName(field), invalidValue(value) {}
    
    string getFieldName() const { return fieldName; }
    string getInvalidValue() const { return invalidValue; }
};

/**
 * @brief Exception cho lỗi tên liên hệ
 */
class InvalidNameException : public ContactValidationException {
public:
    InvalidNameException(const string& name, const string& reason)
        : ContactValidationException("Tên", name, reason) {}
    
    static InvalidNameException emptyName() {
        return InvalidNameException("", "Tên không được để trống");
    }
    
    static InvalidNameException invalidCharacters(const string& name) {
        return InvalidNameException(name, "Tên chỉ được chứa chữ cái, số và khoảng trắng");
    }
    
    static InvalidNameException tooLong(const string& name) {
        return InvalidNameException(name, "Tên quá dài (tối đa 50 ký tự)");
    }
    
    static InvalidNameException duplicateName(const string& name) {
        return InvalidNameException(name, "Tên đã tồn tại trong danh bạ");
    }
};

/**
 * @brief Exception cho lỗi số điện thoại
 */
class InvalidPhoneNumberException : public ContactValidationException {
public:
    InvalidPhoneNumberException(const string& phone, const string& reason)
        : ContactValidationException("Số điện thoại", phone, reason) {}
    
    static InvalidPhoneNumberException emptyNumber() {
        return InvalidPhoneNumberException("", "Số điện thoại không được để trống");
    }
    
    static InvalidPhoneNumberException invalidFormat(const string& phone) {
        return InvalidPhoneNumberException(phone, "Số điện thoại chỉ được chứa các chữ số");
    }
    
    static InvalidPhoneNumberException wrongLength(const string& phone) {
        return InvalidPhoneNumberException(phone, "Số điện thoại phải có độ dài từ 10 đến 15 ký tự");
    }
    
    static InvalidPhoneNumberException duplicateNumber(const string& phone) {
        return InvalidPhoneNumberException(phone, "Số điện thoại đã tồn tại trong danh bạ");
    }
};

/**
 * @brief Exception cho lỗi email
 */
class InvalidEmailException : public ContactValidationException {
public:
    InvalidEmailException(const string& email, const string& reason)
        : ContactValidationException("Email", email, reason) {}
    
    static InvalidEmailException invalidFormat(const string& email) {
        return InvalidEmailException(email, "Định dạng email không hợp lệ");
    }
    
    static InvalidEmailException tooLong(const string& email) {
        return InvalidEmailException(email, "Email quá dài (tối đa 100 ký tự)");
    }
};

/**
 * @brief Exception cho lỗi tìm kiếm
 */
class ContactNotFoundException : public PhoneBookException {
private:
    string searchCriteria;
    string searchValue;

public:
    ContactNotFoundException(const string& criteria, const string& value)
        : PhoneBookException("Không tìm thấy liên hệ với " + criteria + ": '" + value + "'"),
          searchCriteria(criteria), searchValue(value) {}
    
    string getSearchCriteria() const { return searchCriteria; }
    string getSearchValue() const { return searchValue; }
};

/**
 * @brief Exception cho lỗi cấu trúc dữ liệu
 */
class DataStructureException : public PhoneBookException {
private:
    string operation;
    string detail;

public:
    DataStructureException(const string& op, const string& detail_msg)
        : PhoneBookException("Lỗi cấu trúc dữ liệu trong " + op + ": " + detail_msg),
          operation(op), detail(detail_msg) {}
    
    string getOperation() const { return operation; }
    string getDetail() const { return detail; }
    
    static DataStructureException insertFailed(const string& reason = "Không thể chèn liên hệ") {
        return DataStructureException("INSERT", reason);
    }
    
    static DataStructureException deleteFailed(const string& reason = "Không thể xóa liên hệ") {
        return DataStructureException("DELETE", reason);
    }
    
    static DataStructureException searchFailed(const string& reason = "Không thể tìm kiếm") {
        return DataStructureException("SEARCH", reason);
    }
};

/**
 * @brief Exception cho lỗi giao diện người dùng
 */
class UIException : public PhoneBookException {
private:
    string uiComponent;
    string userAction;

public:
    UIException(const string& component, const string& action, const string& reason)
        : PhoneBookException("Lỗi giao diện " + component + " trong " + action + ": " + reason),
          uiComponent(component), userAction(action) {}
    
    string getUIComponent() const { return uiComponent; }
    string getUserAction() const { return userAction; }
    
    static UIException invalidMenuChoice(const string& choice) {
        return UIException("Menu", "Chọn lựa chọn", "Lựa chọn '" + choice + "' không hợp lệ");
    }
    
    static UIException inputError(const string& field) {
        return UIException("Input", "Nhập dữ liệu", "Lỗi nhập dữ liệu cho trường '" + field + "'");
    }
};

/**
 * @brief Exception cho lỗi hệ thống
 */
class SystemException : public PhoneBookException {
private:
    string systemComponent;
    int errorCode;

public:
    SystemException(const string& component, int code, const string& description)
        : PhoneBookException("Lỗi hệ thống " + component + " (Code: " + to_string(code) + "): " + description),
          systemComponent(component), errorCode(code) {}
    
    string getSystemComponent() const { return systemComponent; }
    int getErrorCode() const { return errorCode; }
    
    static SystemException memoryError(const string& operation) {
        return SystemException("Memory", -1, "Lỗi bộ nhớ trong " + operation);
    }
    
    static SystemException fileError(const string& operation) {
        return SystemException("File", -2, "Lỗi file trong " + operation);
    }
    
    static SystemException windowsAPIError(const string& operation) {
        return SystemException("Windows API", -3, "Lỗi Windows API trong " + operation);
    }
};

/**
 * @brief Exception cho lỗi cấu hình
 */
class ConfigurationException : public PhoneBookException {
private:
    string configItem;

public:
    ConfigurationException(const string& item, const string& reason)
        : PhoneBookException("Lỗi cấu hình '" + item + "': " + reason),
          configItem(item) {}
    
    string getConfigItem() const { return configItem; }
    
    static ConfigurationException invalidLocale() {
        return ConfigurationException("Locale", "Không thể thiết lập locale cho tiếng Việt");
    }
    
    static ConfigurationException invalidConsoleSettings() {
        return ConfigurationException("Console", "Không thể thiết lập cấu hình console");
    }
};

#endif // EXCEPTIONS_H
