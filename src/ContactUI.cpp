#include "ContactUI.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

ContactUI::ContactUI() {
    manager = ContactManager::getInstance();
}

ContactUI::~ContactUI() {}

void ContactUI::run() {
    showWelcome();
    
    int choice;
    do {
        showMainMenu();
        choice = getIntInput("Nhập lựa chọn của bạn: ");
        
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                showContactMenu();
                break;
            case 3:
                searchContacts();
                break;
            case 4:
                displayAllContacts();
                break;
                    case 5:
            cout << "\n Tổng số liên hệ: " << manager->getTotalContacts() << endl;
            break;
        case 6:
            manager->printTreeStructures();
            break;
        case 7:
            showGoodbye();
            break;
        default:
            cout << " Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
             
        }
        
        if (choice != 7) {
            pause();
            clearScreen();
        }
    } while (choice != 7);
}

void ContactUI::showWelcome() const {
    clearScreen();
    cout << "=========================================" << endl;
    cout << "    HỆ THỐNG QUẢN LÝ DANH BẠ THÔNG MINH" << endl;
    cout << "=========================================" << endl;
    cout << "Chào mừng bạn đến với trình quản lý danh bạ hiệu quả!" << endl;
    cout << "Được xây dựng với các cấu trúc dữ liệu tối ưu cho tốc độ cao." << endl;
    cout << "=========================================\n" << endl;
}

void ContactUI::showGoodbye() const {
    cout << "\nCảm ơn bạn đã sử dụng Hệ thống Quản lý Danh bạ!" << endl;
    cout << "Tạm biệt!\n" << endl;
}

void ContactUI::showMainMenu() const {
    cout << "\n=== MENU CHÍNH ===" << endl;
    cout << "1. Thêm liên hệ mới (số điện thoại tối đa 11 số, không trùng lặp)" << endl;
    cout << "2. Quản lý liên hệ" << endl;
    cout << "3. Tìm kiếm liên hệ" << endl;
    cout << "4. Hiển thị tất cả liên hệ" << endl;
    cout << "5. Thống kê" << endl;
    cout << "6.  Hiển thị cấu trúc cây dữ liệu" << endl;
    cout << "7. Thoát" << endl;
    cout << "=================" << endl;
}

void ContactUI::showContactMenu() const {
    cout << "\n=== QUẢN LÝ LIÊN HỆ ===" << endl;
    cout << "1. Chỉnh sửa liên hệ" << endl;
    cout << "2. Xóa liên hệ" << endl;
    cout << "3. Xem chi tiết liên hệ" << endl;
    cout << "4. Thêm/Cập nhật số điện thoại (tối đa 11 số, không trùng lặp)" << endl;
    cout << "5. Thêm/Cập nhật email (không trùng lặp)" << endl;
    cout << "6. Quay lại menu chính" << endl;
    cout << "=========================" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            editContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            viewContact();
            break;
        case 4:
            addPhoneToContact();
            break;
        case 5:
            addEmailToContact();
            break;
        case 6:
            return;
        default:
            cout << " Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::showSearchMenu() const {
    cout << "\n=== TÙY CHỌN TÌM KIẾM ===" << endl;
    cout << "1. Tìm kiếm theo tên" << endl;
    cout << "2. Tìm kiếm theo số điện thoại" << endl;
    cout << "3. Tìm kiếm theo email" << endl;
    cout << "4. Quay lại menu chính" << endl;
    cout << "=====================" << endl;
}

void ContactUI::addContact() const {
    cout << "\n=== THÊM LIÊN HỆ MỚI ===" << endl;
    
    // Nhập tên với validation
    string name;
    do {
        name = getStringInput("Nhập tên liên hệ: ");
        if (name.empty()) {
            cout << " Tên không được để trống! Vui lòng nhập lại." << endl;
        } else if (name.length() < 2) {
            cout << " Tên phải có ít nhất 2 ký tự! Vui lòng nhập lại." << endl;
        }
    } while (name.empty() || name.length() < 2);
    
    if (manager->addContact(name)) {
        Contact* contact = manager->findContact(name);
        if (contact) {
            cout << "✓ Liên hệ cơ bản đã được thêm thành công!" << endl;
            
            // Hiển thị menu thêm thông tin chi tiết
            showAddDetailsMenu(contact);
        }
    }
}

void ContactUI::showAddDetailsMenu(Contact* contact) const {
    cout << "\n=== THÊM THÔNG TIN CHI TIẾT ===" << endl;
    cout << "Liên hệ: " << contact->getName() << " (ID: " << contact->getId() << ")" << endl;
    
    int choice;
    do {
        cout << "\n=== MENU THÊM THÔNG TIN ===" << endl;
        cout << "1. Thêm/Cập nhật số điện thoại (tối đa 11 số, không trùng lặp)" << endl;
        cout << "2. Thêm/Cập nhật email (không trùng lặp)" << endl;
        cout << "3. Thêm địa chỉ" << endl;
        cout << "4. Thêm ghi chú" << endl;
        cout << "5. Xem thông tin hiện tại" << endl;
        cout << "6. Hoàn tất và quay lại" << endl;
        cout << "=========================" << endl;
        
        choice = getIntInput("Nhập lựa chọn của bạn: ");
        
        switch (choice) {
            case 1:
                addPhoneToContact(contact);
                break;
            case 2:
                addEmailToContact(contact);
                break;
            case 3:
                addAddressToContact(contact);
                break;
            case 4:
                addNotesToContact(contact);
                break;
            case 5:
                cout << "\n=== THÔNG TIN HIỆN TẠI ===" << endl;
                contact->display();
                break;
            case 6:
                cout << "\n=== THÔNG TIN LIÊN HỆ HOÀN CHỈNH ===" << endl;
                contact->display();
                cout << "✓ Liên hệ đã được tạo hoàn chỉnh!" << endl;
                return;
            default:
                cout << " Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
        }
        
        if (choice != 6) {
            pause();
        }
    } while (choice != 6);
}



void ContactUI::showEditContactMenu(Contact* contact) const {
    cout << "\n=== CHỈNH SỬA LIÊN HỆ ===" << endl;
    cout << "Liên hệ: " << contact->getName() << " (ID: " << contact->getId() << ")" << endl;
    
    int choice;
    do {
        cout << "\n=== MENU CHỈNH SỬA ===" << endl;
        cout << "1. Thay đổi tên" << endl;
        cout << "2. Quản lý số điện thoại (tối đa 11 số, không trùng lặp)" << endl;
        cout << "3. Quản lý email (không trùng lặp)" << endl;
        cout << "4. Thay đổi địa chỉ" << endl;
        cout << "5. Thay đổi ghi chú" << endl;
        cout << "6. Xem thông tin hiện tại" << endl;
        cout << "7. Quay lại" << endl;
        cout << "=====================" << endl;
        
        choice = getIntInput("Nhập lựa chọn của bạn: ");
        
        switch (choice) {
            case 1:
                editContactName(contact);
                break;
            case 2:
                managePhoneNumbers(contact);
                break;
            case 3:
                manageEmails(contact);
                break;
            case 4:
                addAddressToContact(contact);
                break;
            case 5:
                addNotesToContact(contact);
                break;
            case 6:
                cout << "\n=== THÔNG TIN HIỆN TẠI ===" << endl;
                contact->display();
                break;
            case 7:
                cout << "✓ Đã hoàn tất chỉnh sửa!" << endl;
                return;
            default:
                cout << " Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
        }
        
        if (choice != 7) {
            pause();
        }
    } while (choice != 7);
}

void ContactUI::editContact() const {
    cout << "\n=== CHỈNH SỬA LIÊN HỆ ===" << endl;
    string name = getStringInput("Nhập tên liên hệ cần chỉnh sửa: ");
    
    Contact* contact = manager->findContact(name);
    if (!contact) {
        cout << " Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    showEditContactMenu(contact);
}

void ContactUI::deleteContact() const {
    cout << "\n=== XÓA LIÊN HỆ ===" << endl;
    cout << "1. Xóa theo tên" << endl;
    cout << "2. Xóa theo ID" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    if (choice == 1) {
        string name = getStringInput("Nhập tên liên hệ cần xóa: ");
        manager->removeContact(name);
    } else if (choice == 2) {
        int id = getIntInput("Nhập ID liên hệ cần xóa: ");
        manager->removeContact(id);
    } else {
        cout << " Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::viewContact() const {
    cout << "\n=== XEM LIÊN HỆ ===" << endl;
    cout << "1. Xem theo tên" << endl;
    cout << "2. Xem theo ID" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    if (choice == 1) {
        string name = getStringInput("Nhập tên liên hệ: ");
        manager->displayContact(name);
    } else if (choice == 2) {
        int id = getIntInput("Nhập ID liên hệ: ");
        manager->displayContact(id);
    } else {
        cout << " Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::addPhoneToContact() const {
    cout << "\n=== THÊM SỐ ĐIỆN THOẠI ===" << endl;
    string name = getStringInput("Nhập tên liên hệ: ");
    
    Contact* contact = manager->findContact(name);
    if (!contact) {
        cout << " Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    addPhoneToContact(contact);
}

void ContactUI::addPhoneToContact(Contact* contact) const {
    cout << "\n=== THÊM/CẬP NHẬT SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị số điện thoại hiện tại
    if (contact->hasPhoneNumber()) {
        cout << "Số điện thoại hiện tại: " << contact->getPhoneNumber() << endl;
        cout << "⚠️ Lưu ý: Số điện thoại mới sẽ thay thế số cũ!" << endl;
    } else {
        cout << "Chưa có số điện thoại nào." << endl;
    }
    
    string phone;
    do {
        phone = getStringInput("Nhập số điện thoại mới (tối đa 11 số): ");
        if (phone.empty()) {
            cout << " Số điện thoại không được để trống!" << endl;
        } else if (!manager->canAddPhoneNumber(phone, contact)) {
            // 🔑 Sử dụng validation mới từ ContactManager
            if (!manager->isPhoneNumberValid(phone)) {
                cout << "  Số điện thoại không hợp lệ! Chỉ được chứa số và tối đa 11 ký tự." << endl;
            } else if (manager->isPhoneNumberDuplicate(phone, contact)) {
                cout << "  Số điện thoại này đã tồn tại trong liên hệ khác!" << endl;
            }
        }
    } while (phone.empty() || !manager->canAddPhoneNumber(phone, contact));
    
    contact->setPhoneNumber(phone);  // 🔑 Thay thế số điện thoại cũ
    
    // ⚠️ QUAN TRỌNG: Đồng bộ tất cả index để đảm bảo tìm kiếm chính xác
    manager->syncAllIndexes(contact);
    
    cout << "✓ Số điện thoại '" << phone << "' đã được cập nhật thành công!" << endl;
}

void ContactUI::addEmailToContact() const {
    cout << "\n=== THÊM EMAIL ===" << endl;
    string name = getStringInput("Nhập tên liên hệ: ");
    
    Contact* contact = manager->findContact(name);
    if (!contact) {
        cout << " Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    addEmailToContact(contact);
}

void ContactUI::addEmailToContact(Contact* contact) const {
    cout << "\n=== THÊM/CẬP NHẬT EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị email hiện tại
    if (contact->hasEmail()) {
        cout << "Email hiện tại: " << contact->getEmail() << endl;
        cout << "⚠️ Lưu ý: Email mới sẽ thay thế email cũ!" << endl;
    } else {
        cout << "Chưa có email nào." << endl;
    }
    
    string email;
    do {
        email = getStringInput("Nhập địa chỉ email mới: ");
        if (email.empty()) {
            cout << " Email không được để trống!" << endl;
        } else if (!manager->canAddEmail(email, contact)) {
            // 🔑 Sử dụng validation mới từ ContactManager
            if (!manager->isValidEmail(email)) {
                cout << "  Email không hợp lệ! Vui lòng nhập lại." << endl;
            } else if (manager->isEmailDuplicate(email, contact)) {
                cout << "  Email này đã tồn tại trong liên hệ khác!" << endl;
            }
        }
    } while (email.empty() || !manager->canAddEmail(email, contact));
    
    contact->setEmail(email);  // 🔑 Thay thế email cũ
    
    // ⚠️ QUAN TRỌNG: Đồng bộ tất cả index để đảm bảo tìm kiếm chính xác
    manager->syncAllIndexes(contact);
    
    cout << "✓ Email '" << email << "' đã được cập nhật thành công!" << endl;
}

void ContactUI::addAddressToContact(Contact* contact) const {
    cout << "\n=== THÊM ĐỊA CHỈ ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị địa chỉ hiện tại
    string currentAddress = contact->getAddress();
    if (!currentAddress.empty()) {
        cout << "Địa chỉ hiện tại: " << currentAddress << endl;
    }
    
    string address;
    do {
        address = getStringInput("Nhập địa chỉ mới: ");
        if (address.empty()) {
            cout << " Địa chỉ không được để trống!" << endl;
        } else if (address.length() < 5) {
            cout << " Địa chỉ phải có ít nhất 5 ký tự!" << endl;
        }
    } while (address.empty() || address.length() < 5);
    
    contact->setAddress(address);
    cout << "✓ Địa chỉ đã được cập nhật thành công!" << endl;
}

void ContactUI::addNotesToContact(Contact* contact) const {
    cout << "\n=== THÊM GHI CHÚ ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị ghi chú hiện tại
    string currentNotes = contact->getNotes();
    if (!currentNotes.empty()) {
        cout << "Ghi chú hiện tại: " << currentNotes << endl;
    }
    
    string notes = getStringInput("Nhập ghi chú mới: ");
    if (!notes.empty()) {
        contact->setNotes(notes);
        cout << "✓ Ghi chú đã được cập nhật thành công!" << endl;
    } else {
        cout << "ℹ Không có thay đổi gì." << endl;
    }
}

void ContactUI::editContactName(Contact* contact) const {
    cout << "\n=== THAY ĐỔI TÊN ===" << endl;
    cout << "Tên hiện tại: " << contact->getName() << endl;
    
    string newName;
    do {
        newName = getStringInput("Nhập tên mới: ");
        if (newName.empty()) {
            cout << " Tên không được để trống!" << endl;
        } else if (newName.length() < 2) {
            cout << " Tên phải có ít nhất 2 ký tự!" << endl;
        } else if (newName == contact->getName()) {
            cout << "Tên mới giống tên cũ!" << endl;
            return;
        }
    } while (newName.empty() || newName.length() < 2);
    
    contact->setName(newName);
    cout << "✓ Tên đã được thay đổi từ '" << contact->getName() << "' thành '" << newName << "'!" << endl;
}

void ContactUI::managePhoneNumbers(Contact* contact) const {
    cout << "\n=== QUẢN LÝ SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    if (contact->hasPhoneNumber()) {
        cout << "Số điện thoại hiện tại: " << contact->getPhoneNumber() << endl;
    } else {
        cout << "📭 Chưa có số điện thoại nào." << endl;
    }
    
    cout << "\n=== TÙY CHỌN ===" << endl;
    cout << "1. Thêm/Cập nhật số điện thoại (tối đa 11 số, không trùng lặp)" << endl;
    cout << "2. Xóa số điện thoại" << endl;
    cout << "3. Quay lại" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            addPhoneToContact(contact);
            break;
        case 2:
            if (contact->hasPhoneNumber()) {
                deletePhoneNumber(contact);
            } else {
                cout << " Không có số điện thoại để xóa!" << endl;
            }
            break;
        case 3:
            return;
        default:
            cout << " Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::manageEmails(Contact* contact) const {
    cout << "\n=== QUẢN LÝ EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    if (contact->hasEmail()) {
        cout << "Email hiện tại: " << contact->getEmail() << endl;
    } else {
        cout << " Chưa có email nào." << endl;
    }
    
    cout << "\n=== TÙY CHỌN ===" << endl;
    cout << "1. Thêm/Cập nhật email (không trùng lặp)" << endl;
    cout << "2. Xóa email" << endl;
    cout << "3. Quay lại" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            addEmailToContact(contact);
            break;
        case 2:
            if (contact->hasEmail()) {
                deleteEmail(contact);
            } else {
                cout << " Không có email để xóa!" << endl;
            }
            break;
        case 3:
            return;
        default:
            cout << " Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::deletePhoneNumber(Contact* contact) const {
    cout << "\n=== XÓA SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    if (!contact->hasPhoneNumber()) {
        cout << " Không có số điện thoại để xóa!" << endl;
        return;
    }
    
    cout << "Số điện thoại hiện tại: " << contact->getPhoneNumber() << endl;
    
    string confirm = getStringInput("Bạn có chắc muốn xóa số điện thoại này? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << " Đã hủy xóa số điện thoại." << endl;
        return;
    }
    
    contact->setPhoneNumber("");  // 🔑 Xóa số điện thoại bằng cách set rỗng
    
    // ⚠️ QUAN TRỌNG: Đồng bộ tất cả index để đảm bảo tìm kiếm chính xác
    manager->syncAllIndexes(contact);
    
    cout << "✓ Số điện thoại đã được xóa!" << endl;
}

void ContactUI::deleteEmail(Contact* contact) const {
    cout << "\n=== XÓA EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    if (!contact->hasEmail()) {
        cout << " Không có email để xóa!" << endl;
        return;
    }
    
    cout << "Email hiện tại: " << contact->getEmail() << endl;
    
    string confirm = getStringInput("Bạn có chắc muốn xóa email này? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << " Đã hủy xóa email." << endl;
        return;
    }
    
    contact->setEmail("");  // 🔑 Xóa email bằng cách set rỗng
    
    // ⚠️ QUAN TRỌNG: Đồng bộ tất cả index để đảm bảo tìm kiếm chính xác
    manager->syncAllIndexes(contact);
    
    cout << "✓ Email đã được xóa!" << endl;
}

void ContactUI::searchContacts() const {
    showSearchMenu();
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            searchByName();
            break;
        case 2:
            searchByPhone();
            break;
        case 3:
            searchByEmail();
            break;
        case 4:
            return;
        default:
            cout << " Lựa chọn không hợp lệ!" << endl;
            pause();
    }
}

void ContactUI::searchByName() const {
    cout << "\n=== TÌM KIẾM THEO TÊN ===" << endl;
    string name = getStringInput("Nhập tên cần tìm: ");
    
    set<Contact*> results = manager->searchByName(name);
    displaySearchResults(results);
    pause();
}

void ContactUI::searchByPhone() const {
    cout << "\n=== TÌM KIẾM THEO SỐ ĐIỆN THOẠI ===" << endl;
    string phone = getStringInput("Nhập số điện thoại cần tìm: ");
    
    set<Contact*> results = manager->searchByPhone(phone);
    displaySearchResults(results);
    pause();
}

void ContactUI::searchByEmail() const {
    cout << "\n=== TÌM KIẾM THEO EMAIL ===" << endl;
    string email = getStringInput("Nhập email cần tìm: ");
    
    set<Contact*> results = manager->searchByEmail(email);
    displaySearchResults(results);
    pause();
}

void ContactUI::displayAllContacts() const {
    manager->displayAllContacts();
}

void ContactUI::displaySearchResults(const set<Contact*>& results) const {
    if (results.empty()) {
        cout << " Không tìm thấy liên hệ nào!" << endl;
        return;
    }
    
    cout << "\n=== KẾT QUẢ TÌM KIẾM (" << results.size() << " kết quả) ===" << endl;
    for (Contact* contact : results) {
        contact->display();
    }
}

string ContactUI::getStringInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int ContactUI::getIntInput(const string& prompt) const {
    int value;
    cout << prompt;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

void ContactUI::clearScreen() const {
    #ifdef _WIN32
        (void)system("cls");
    #else
        (void)system("clear");
    #endif
}

void ContactUI::pause() const {
    cout << "\nNhấn Enter để tiếp tục...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool ContactUI::isValidPhoneNumber(const string& phone) const {
    // 🔑 Sử dụng validation mới từ ContactManager (tối đa 11 số)
    return manager->isPhoneNumberValid(phone);
}

bool ContactUI::isValidEmail(const string& email) const {
    // 🔑 Sử dụng validation mới từ ContactManager
    return manager->isValidEmail(email);
}
