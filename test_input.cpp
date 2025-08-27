#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    cout << "=== TEST LUỒNG INPUT ===" << endl;
    
    int choice;
    string name, phone, email;
    
    // Test 1: Nhập lựa chọn menu
    cout << "\nNhập lựa chọn (1-5): ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lỗi: Không phải số!" << endl;
        return 1;
    }
    
    // XÓA BUFFER INPUT - Đây là bước quan trọng!
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Bạn đã chọn: " << choice << endl;
    
    // Test 2: Nhập tên
    cout << "\nNhập tên: ";
    getline(cin, name);
    cout << "Tên: [" << name << "]" << endl;
    
    // Test 3: Nhập số điện thoại
    cout << "Nhập số điện thoại: ";
    getline(cin, phone);
    cout << "Số điện thoại: [" << phone << "]" << endl;
    
    // Test 4: Nhập email
    cout << "Nhập email: ";
    getline(cin, email);
    cout << "Email: [" << email << "]" << endl;
    
    cout << "\n=== KẾT QUẢ ===" << endl;
    cout << "Lựa chọn: " << choice << endl;
    cout << "Tên: " << name << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Email: " << email << endl;
    
    return 0;
}
