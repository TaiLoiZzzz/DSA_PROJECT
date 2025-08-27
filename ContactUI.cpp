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
            cout << "\n📊 Tổng số liên hệ: " << manager->getTotalContacts() << endl;
            break;
            case 6:
                showGoodbye();
                break;
                    default:
            cout << "❌ Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
        }
        
        if (choice != 6) {
            pause();
            clearScreen();
        }
    } while (choice != 6);
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
    cout << "1. Thêm liên hệ mới" << endl;
    cout << "2. Quản lý liên hệ" << endl;
    cout << "3. Tìm kiếm liên hệ" << endl;
    cout << "4. Hiển thị tất cả liên hệ" << endl;
    cout << "5. Thống kê" << endl;
    cout << "6. Thoát" << endl;
    cout << "=================" << endl;
}

void ContactUI::showContactMenu() const {
    cout << "\n=== QUẢN LÝ LIÊN HỆ ===" << endl;
    cout << "1. Chỉnh sửa liên hệ" << endl;
    cout << "2. Xóa liên hệ" << endl;
    cout << "3. Xem chi tiết liên hệ" << endl;
    cout << "4. Thêm số điện thoại" << endl;
    cout << "5. Thêm email" << endl;
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
            cout << "❌ Lựa chọn không hợp lệ!" << endl;
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
            cout << "❌ Tên không được để trống! Vui lòng nhập lại." << endl;
        } else if (name.length() < 2) {
            cout << "❌ Tên phải có ít nhất 2 ký tự! Vui lòng nhập lại." << endl;
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
        cout << "1. Thêm số điện thoại" << endl;
        cout << "2. Thêm email" << endl;
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
                cout << "❌ Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
        }
        
        if (choice != 6) {
            pause();
        }
    } while (choice != 6);
}

void ContactUI::addContactDetails(Contact* contact) const {
    cout << "\n=== THÊM THÔNG TIN CHI TIẾT ===" << endl;
    
    // Thêm số điện thoại
    cout << "Bạn có muốn thêm số điện thoại không? (y/n): ";
    string choice = getStringInput("");
    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "YES") {
        string phone = getStringInput("Nhập số điện thoại: ");
        if (!phone.empty()) {
            contact->addPhoneNumber(phone);
            cout << "✓ Số điện thoại đã được thêm!" << endl;
        }
    }
    
    // Thêm email
    cout << "\nBạn có muốn thêm email không? (y/n): ";
    choice = getStringInput("");
    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "YES") {
        string email = getStringInput("Nhập địa chỉ email: ");
        if (!email.empty()) {
            contact->addEmail(email);
            cout << "✓ Email đã được thêm!" << endl;
        }
    }
    
    // Thêm địa chỉ
    cout << "\nBạn có muốn thêm địa chỉ không? (y/n): ";
    choice = getStringInput("");
    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "YES") {
        string address = getStringInput("Nhập địa chỉ: ");
        if (!address.empty()) {
            contact->setAddress(address);
            cout << "✓ Địa chỉ đã được thêm!" << endl;
        }
    }
    
    // Thêm ghi chú
    cout << "\nBạn có muốn thêm ghi chú không? (y/n): ";
    choice = getStringInput("");
    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "YES") {
        string notes = getStringInput("Nhập ghi chú: ");
        if (!notes.empty()) {
            contact->setNotes(notes);
            cout << "✓ Ghi chú đã được thêm!" << endl;
        }
    }
    
    cout << "\n=== THÔNG TIN LIÊN HỆ HOÀN CHỈNH ===" << endl;
    contact->display();
    cout << "✓ Liên hệ đã được tạo hoàn chỉnh!" << endl;
}

void ContactUI::showEditContactMenu(Contact* contact) const {
    cout << "\n=== CHỈNH SỬA LIÊN HỆ ===" << endl;
    cout << "Liên hệ: " << contact->getName() << " (ID: " << contact->getId() << ")" << endl;
    
    int choice;
    do {
        cout << "\n=== MENU CHỈNH SỬA ===" << endl;
        cout << "1. Thay đổi tên" << endl;
        cout << "2. Quản lý số điện thoại" << endl;
        cout << "3. Quản lý email" << endl;
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
                cout << "❌ Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
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
        cout << "❌ Không tìm thấy liên hệ!" << endl;
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
        cout << "❌ Lựa chọn không hợp lệ!" << endl;
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
        cout << "❌ Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::addPhoneToContact() const {
    cout << "\n=== THÊM SỐ ĐIỆN THOẠI ===" << endl;
    string name = getStringInput("Nhập tên liên hệ: ");
    
    Contact* contact = manager->findContact(name);
    if (!contact) {
        cout << "❌ Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    addPhoneToContact(contact);
}

void ContactUI::addPhoneToContact(Contact* contact) const {
    cout << "\n=== THÊM SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị số điện thoại hiện tại
    auto phones = contact->getPhoneNumbers();
    if (!phones.empty()) {
        cout << "Số điện thoại hiện tại: ";
        for (const auto& phone : phones) {
            cout << phone << " ";
        }
        cout << endl;
    }
    
    string phone;
    do {
        phone = getStringInput("Nhập số điện thoại mới: ");
        if (phone.empty()) {
            cout << "❌ Số điện thoại không được để trống!" << endl;
        } else if (!isValidPhoneNumber(phone)) {
            cout << "❌ Số điện thoại không hợp lệ! Vui lòng nhập lại." << endl;
        } else if (contact->hasPhoneNumber(phone)) {
            cout << "❌ Số điện thoại này đã tồn tại!" << endl;
        }
    } while (phone.empty() || !isValidPhoneNumber(phone) || contact->hasPhoneNumber(phone));
    
    contact->addPhoneNumber(phone);
    cout << "✓ Số điện thoại '" << phone << "' đã được thêm thành công!" << endl;
}

void ContactUI::addEmailToContact() const {
    cout << "\n=== THÊM EMAIL ===" << endl;
    string name = getStringInput("Nhập tên liên hệ: ");
    
    Contact* contact = manager->findContact(name);
    if (!contact) {
        cout << "❌ Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    addEmailToContact(contact);
}

void ContactUI::addEmailToContact(Contact* contact) const {
    cout << "\n=== THÊM EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    // Hiển thị email hiện tại
    auto emails = contact->getEmails();
    if (!emails.empty()) {
        cout << "Email hiện tại: ";
        for (const auto& email : emails) {
            cout << email << " ";
        }
        cout << endl;
    }
    
    string email;
    do {
        email = getStringInput("Nhập địa chỉ email mới: ");
        if (email.empty()) {
            cout << "❌ Email không được để trống!" << endl;
        } else if (!isValidEmail(email)) {
            cout << "❌ Email không hợp lệ! Vui lòng nhập lại." << endl;
        } else if (contact->hasEmail(email)) {
            cout << "❌ Email này đã tồn tại!" << endl;
        }
    } while (email.empty() || !isValidEmail(email) || contact->hasEmail(email));
    
    contact->addEmail(email);
    cout << "✓ Email '" << email << "' đã được thêm thành công!" << endl;
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
            cout << "❌ Địa chỉ không được để trống!" << endl;
        } else if (address.length() < 5) {
            cout << "❌ Địa chỉ phải có ít nhất 5 ký tự!" << endl;
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
        cout << "ℹ️ Không có thay đổi gì." << endl;
    }
}

void ContactUI::editContactName(Contact* contact) const {
    cout << "\n=== THAY ĐỔI TÊN ===" << endl;
    cout << "Tên hiện tại: " << contact->getName() << endl;
    
    string newName;
    do {
        newName = getStringInput("Nhập tên mới: ");
        if (newName.empty()) {
            cout << "❌ Tên không được để trống!" << endl;
        } else if (newName.length() < 2) {
            cout << "❌ Tên phải có ít nhất 2 ký tự!" << endl;
        } else if (newName == contact->getName()) {
            cout << "ℹ️ Tên mới giống tên cũ!" << endl;
            return;
        }
    } while (newName.empty() || newName.length() < 2);
    
    contact->setName(newName);
    cout << "✓ Tên đã được thay đổi từ '" << contact->getName() << "' thành '" << newName << "'!" << endl;
}

void ContactUI::managePhoneNumbers(Contact* contact) const {
    cout << "\n=== QUẢN LÝ SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    auto phones = contact->getPhoneNumbers();
    if (phones.empty()) {
        cout << "📭 Chưa có số điện thoại nào." << endl;
    } else {
        cout << "Số điện thoại hiện tại:" << endl;
        int i = 1;
        for (const auto& phone : phones) {
            cout << i++ << ". " << phone << endl;
        }
    }
    
    cout << "\n=== TÙY CHỌN ===" << endl;
    cout << "1. Thêm số điện thoại mới" << endl;
    cout << "2. Xóa số điện thoại" << endl;
    cout << "3. Quay lại" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            addPhoneToContact(contact);
            break;
        case 2:
            if (!phones.empty()) {
                deletePhoneNumber(contact);
            } else {
                cout << "❌ Không có số điện thoại để xóa!" << endl;
            }
            break;
        case 3:
            return;
        default:
            cout << "❌ Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::manageEmails(Contact* contact) const {
    cout << "\n=== QUẢN LÝ EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    auto emails = contact->getEmails();
    if (emails.empty()) {
        cout << "📭 Chưa có email nào." << endl;
    } else {
        cout << "Email hiện tại:" << endl;
        int i = 1;
        for (const auto& email : emails) {
            cout << i++ << ". " << email << endl;
        }
    }
    
    cout << "\n=== TÙY CHỌN ===" << endl;
    cout << "1. Thêm email mới" << endl;
    cout << "2. Xóa email" << endl;
    cout << "3. Quay lại" << endl;
    
    int choice = getIntInput("Nhập lựa chọn của bạn: ");
    
    switch (choice) {
        case 1:
            addEmailToContact(contact);
            break;
        case 2:
            if (!emails.empty()) {
                deleteEmail(contact);
            } else {
                cout << "❌ Không có email để xóa!" << endl;
            }
            break;
        case 3:
            return;
        default:
            cout << "❌ Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::deletePhoneNumber(Contact* contact) const {
    cout << "\n=== XÓA SỐ ĐIỆN THOẠI ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    auto phones = contact->getPhoneNumbers();
    cout << "Danh sách số điện thoại:" << endl;
    int i = 1;
    for (const auto& phone : phones) {
        cout << i++ << ". " << phone << endl;
    }
    
    int choice = getIntInput("Chọn số thứ tự để xóa (0 để hủy): ");
    if (choice == 0) {
        cout << "ℹ️ Đã hủy thao tác." << endl;
        return;
    }
    
    if (choice < 1 || choice > phones.size()) {
        cout << "❌ Lựa chọn không hợp lệ!" << endl;
        return;
    }
    
    auto it = phones.begin();
    advance(it, choice - 1);
    string phoneToDelete = *it;
    
    contact->removePhoneNumber(phoneToDelete);
    cout << "✓ Đã xóa số điện thoại: " << phoneToDelete << endl;
}

void ContactUI::deleteEmail(Contact* contact) const {
    cout << "\n=== XÓA EMAIL ===" << endl;
    cout << "Liên hệ: " << contact->getName() << endl;
    
    auto emails = contact->getEmails();
    cout << "Danh sách email:" << endl;
    int i = 1;
    for (const auto& email : emails) {
        cout << i++ << ". " << email << endl;
    }
    
    int choice = getIntInput("Chọn số thứ tự để xóa (0 để hủy): ");
    if (choice == 0) {
        cout << "ℹ️ Đã hủy thao tác." << endl;
        return;
    }
    
    if (choice < 1 || choice > emails.size()) {
        cout << "❌ Lựa chọn không hợp lệ!" << endl;
        return;
    }
    
    auto it = emails.begin();
    advance(it, choice - 1);
    string emailToDelete = *it;
    
    contact->removeEmail(emailToDelete);
    cout << "✓ Đã xóa email: " << emailToDelete << endl;
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
            cout << "❌ Lựa chọn không hợp lệ!" << endl;
    }
}

void ContactUI::searchByName() const {
    cout << "\n=== TÌM KIẾM THEO TÊN ===" << endl;
    string name = getStringInput("Nhập tên cần tìm: ");
    
    set<Contact*> results = manager->searchByName(name);
    displaySearchResults(results);
}

void ContactUI::searchByPhone() const {
    cout << "\n=== TÌM KIẾM THEO SỐ ĐIỆN THOẠI ===" << endl;
    string phone = getStringInput("Nhập số điện thoại cần tìm: ");
    
    set<Contact*> results = manager->searchByPhone(phone);
    displaySearchResults(results);
}

void ContactUI::searchByEmail() const {
    cout << "\n=== TÌM KIẾM THEO EMAIL ===" << endl;
    string email = getStringInput("Nhập email cần tìm: ");
    
    set<Contact*> results = manager->searchByEmail(email);
    displaySearchResults(results);
}

void ContactUI::displayAllContacts() const {
    manager->displayAllContacts();
}

void ContactUI::displaySearchResults(const set<Contact*>& results) const {
    if (results.empty()) {
        cout << "🔍 Không tìm thấy liên hệ nào!" << endl;
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
    // Loại bỏ khoảng trắng và ký tự đặc biệt
    string cleanPhone = phone;
    cleanPhone.erase(remove_if(cleanPhone.begin(), cleanPhone.end(), 
                              [](char c) { return !isdigit(c); }), cleanPhone.end());
    
    // Kiểm tra độ dài (10-15 số)
    if (cleanPhone.length() < 10 || cleanPhone.length() > 15) {
        return false;
    }
    
    // Kiểm tra tất cả là số
    return all_of(cleanPhone.begin(), cleanPhone.end(), ::isdigit);
}

bool ContactUI::isValidEmail(const string& email) const {
    // Kiểm tra cơ bản email format
    if (email.empty() || email.length() < 5) {
        return false;
    }
    
    // Kiểm tra có @ và .
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    
    if (atPos == string::npos || dotPos == string::npos) {
        return false;
    }
    
    // Kiểm tra @ không ở đầu hoặc cuối
    if (atPos == 0 || atPos == email.length() - 1) {
        return false;
    }
    
    // Kiểm tra . không ở cuối
    if (dotPos == email.length() - 1) {
        return false;
    }
    
    // Kiểm tra có ký tự trước @
    if (atPos < 1) {
        return false;
    }
    
    // Kiểm tra có ký tự sau .
    if (dotPos >= email.length() - 1) {
        return false;
    }
    
    return true;
}
