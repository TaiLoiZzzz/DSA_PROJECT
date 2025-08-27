#include "UI_linux.h"
#include "PhoneBook.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * @brief Hàm main - điểm khởi đầu của chương trình (Phiên bản Linux)
 * Quản lý menu chính và tương tác với người dùng
 */
int main() {
    // Không cần thiết lập locale đặc biệt trên Linux
    // system("chcp 65001 > nul"); // Loại bỏ lệnh Windows
    
    PhoneBook* phoneBook = PhoneBook::getInstance();
    int choice;
    
    do {
        try {
            phoneBook->showMainMenu();
            
            // Nhập lựa chọn từ người dùng
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw UIException::invalidMenuChoice("không phải số");
            }
            
            // Xóa buffer input để tránh ảnh hưởng đến getline() sau này
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // Xử lý lựa chọn
            switch (choice) {
                case 1:
                    phoneBook->addContact();
                    break;
                case 2:
                    phoneBook->deleteContact();
                    break;
                case 3:
                    phoneBook->searchContact();
                    break;
                case 4:
                    phoneBook->displayAllContacts();
                    break;
                case 5:
                    phoneBook->showGoodbye();
                    break;
                default:
                    throw UIException::invalidMenuChoice(to_string(choice));
            }
            
        } catch (const ContactValidationException& e) {
            phoneBook->showError("Lỗi validation: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const ContactNotFoundException& e) {
            phoneBook->showError("Lỗi tìm kiếm: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const DataStructureException& e) {
            phoneBook->showError("Lỗi cấu trúc dữ liệu: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const UIException& e) {
            phoneBook->showError("Lỗi giao diện: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const SystemException& e) {
            phoneBook->showError("Lỗi hệ thống: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const ConfigurationException& e) {
            phoneBook->showError("Lỗi cấu hình: " + string(e.what()));
            phoneBook->waitForEnter();
        } catch (const exception& e) {
            phoneBook->showError("Lỗi không xác định: " + string(e.what()));
            phoneBook->waitForEnter();
        }
        
    } while (choice != 5);
    
    // Dọn dẹp tài nguyên trước khi thoát
    PhoneBook::cleanup();
    
    return 0;
}
