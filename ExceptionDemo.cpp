#include <iostream>
#include "Exceptions.h"
#include "Contact.h"

using namespace std;

/**
 * @brief Demo các loại exception trong ứng dụng danh bạ
 */
int main() {
    cout << "=== DEMO XỬ LÝ EXCEPTION TRONG ỨNG DỤNG DANH BẠ ===" << endl << endl;
    
    // Test 1: InvalidNameException
    cout << "Test 1: InvalidNameException" << endl;
    try {
        Contact contact1("", "0123456789", "test@email.com");
        contact1.validate();
    } catch (const InvalidNameException& e) {
        cout << "  ✓ Bắt được InvalidNameException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    try {
        Contact contact2("Nguyen@Van#A", "0123456789", "test@email.com");
        contact2.validate();
    } catch (const InvalidNameException& e) {
        cout << "  ✓ Bắt được InvalidNameException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    // Test 2: InvalidPhoneNumberException
    cout << "\nTest 2: InvalidPhoneNumberException" << endl;
    try {
        Contact contact3("Nguyen Van A", "", "test@email.com");
        contact3.validate();
    } catch (const InvalidPhoneNumberException& e) {
        cout << "  ✓ Bắt được InvalidPhoneNumberException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    try {
        Contact contact4("Nguyen Van A", "123456", "test@email.com");
        contact4.validate();
    } catch (const InvalidPhoneNumberException& e) {
        cout << "  ✓ Bắt được InvalidPhoneNumberException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    try {
        Contact contact5("Nguyen Van A", "abc123def", "test@email.com");
        contact5.validate();
    } catch (const InvalidPhoneNumberException& e) {
        cout << "  ✓ Bắt được InvalidPhoneNumberException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    // Test 3: InvalidEmailException
    cout << "\nTest 3: InvalidEmailException" << endl;
    try {
        Contact contact6("Nguyen Van A", "0123456789", "invalid-email");
        contact6.validate();
    } catch (const InvalidEmailException& e) {
        cout << "  ✓ Bắt được InvalidEmailException: " << e.what() << endl;
        cout << "  - Field: " << e.getFieldName() << endl;
        cout << "  - Value: '" << e.getInvalidValue() << "'" << endl;
    }
    
    // Test 4: ContactNotFoundException
    cout << "\nTest 4: ContactNotFoundException" << endl;
    try {
        throw ContactNotFoundException("Tên", "Nguyen Van B");
    } catch (const ContactNotFoundException& e) {
        cout << "  ✓ Bắt được ContactNotFoundException: " << e.what() << endl;
        cout << "  - Search Criteria: " << e.getSearchCriteria() << endl;
        cout << "  - Search Value: '" << e.getSearchValue() << "'" << endl;
    }
    
    // Test 5: DataStructureException
    cout << "\nTest 5: DataStructureException" << endl;
    try {
        throw DataStructureException::insertFailed("Lỗi cấp phát bộ nhớ");
    } catch (const DataStructureException& e) {
        cout << "  ✓ Bắt được DataStructureException: " << e.what() << endl;
        cout << "  - Operation: " << e.getOperation() << endl;
        cout << "  - Detail: " << e.getDetail() << endl;
    }
    
    // Test 6: UIException
    cout << "\nTest 6: UIException" << endl;
    try {
        throw UIException::invalidMenuChoice("99");
    } catch (const UIException& e) {
        cout << "  ✓ Bắt được UIException: " << e.what() << endl;
        cout << "  - UI Component: " << e.getUIComponent() << endl;
        cout << "  - User Action: " << e.getUserAction() << endl;
    }
    
    // Test 7: SystemException
    cout << "\nTest 7: SystemException" << endl;
    try {
        throw SystemException::memoryError("Tạo node mới");
    } catch (const SystemException& e) {
        cout << "  ✓ Bắt được SystemException: " << e.what() << endl;
        cout << "  - System Component: " << e.getSystemComponent() << endl;
        cout << "  - Error Code: " << e.getErrorCode() << endl;
    }
    
    // Test 8: ConfigurationException
    cout << "\nTest 8: ConfigurationException" << endl;
    try {
        throw ConfigurationException::invalidLocale();
    } catch (const ConfigurationException& e) {
        cout << "  ✓ Bắt được ConfigurationException: " << e.what() << endl;
        cout << "  - Config Item: " << e.getConfigItem() << endl;
    }
    
    // Test 9: Factory Pattern với Exception
    cout << "\nTest 9: Factory Pattern với Exception" << endl;
    try {
        Contact validContact = ContactFactory::createContact("Nguyen Van A", "0123456789", "test@email.com");
        cout << "  ✓ Tạo liên hệ hợp lệ thành công: " << validContact.name << endl;
    } catch (const ContactValidationException& e) {
        cout << "  ✗ Lỗi validation: " << e.what() << endl;
    }
    
    try {
        Contact invalidContact = ContactFactory::createContact("", "0123456789", "test@email.com");
        cout << "  ✗ Không nên tạo được liên hệ không hợp lệ" << endl;
    } catch (const InvalidNameException& e) {
        cout << "  ✓ Đúng - Không thể tạo liên hệ với tên rỗng: " << e.what() << endl;
    }
    
    cout << "\n=== DEMO HOÀN THÀNH ===" << endl;
    cout << "Tất cả exception đã được test thành công!" << endl;
    
    return 0;
}
