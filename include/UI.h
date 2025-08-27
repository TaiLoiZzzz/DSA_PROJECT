#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

/**
 * @brief Lớp xử lý giao diện người dùng với Windows API
 * Cung cấp các chức năng hiển thị màu sắc và xóa màn hình console
 */
class UI {
private:
    HANDLE hConsole;  // Handle cho console

public:
    /**
     * @brief Constructor khởi tạo handle console
     */
    UI() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    /**
     * @brief Xóa màn hình console
     */
    void clearScreen() {
        system("cls");
    }

    /**
     * @brief Thiết lập màu chữ cho console
     * @param color Màu sắc cần thiết lập
     */
    void setTextColor(int color) {
        SetConsoleTextAttribute(hConsole, color);
    }

    /**
     * @brief Thiết lập màu mặc định (trắng)
     */
    void resetColor() {
        setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    /**
     * @brief Hiển thị thông báo lỗi với màu đỏ
     * @param message Thông báo cần hiển thị
     */
    void showError(const string& message) {
        setTextColor(FOREGROUND_RED);
        cout << "[LỖI] " << message << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị thông báo thành công với màu xanh lá
     * @param message Thông báo cần hiển thị
     */
    void showSuccess(const string& message) {
        setTextColor(FOREGROUND_GREEN);
        cout << "[THÀNH CÔNG] " << message << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị thông báo thông tin với màu vàng
     * @param message Thông báo cần hiển thị
     */
    void showInfo(const string& message) {
        setTextColor(FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "[THÔNG TIN] " << message << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị liên hệ với màu vàng
     * @param message Thông tin liên hệ
     */
    void showContact(const string& message) {
        setTextColor(FOREGROUND_RED | FOREGROUND_GREEN);
        cout << message << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị menu với màu xanh dương
     * @param message Nội dung menu
     */
    void showMenu(const string& message) {
        setTextColor(FOREGROUND_BLUE);
        cout << message << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị header của ứng dụng
     */
    void showHeader() {
        clearScreen();
        setTextColor(FOREGROUND_BLUE);
        cout << "==============================" << endl;
        cout << "      Danh Bạ Điện Thoại" << endl;
        cout << "==============================" << endl;
        resetColor();
    }

    /**
     * @brief Hiển thị menu chính
     */
    void showMainMenu() {
        showHeader();
        showMenu("1. Thêm liên hệ");
        showMenu("2. Xóa liên hệ");
        showMenu("3. Tìm kiếm liên hệ");
        showMenu("4. Hiển thị tất cả liên hệ");
        showMenu("5. Thoát");
        cout << "Vui lòng chọn một chức năng (1-5): ";
    }

    /**
     * @brief Hiển thị thông báo chờ người dùng nhấn Enter
     */
    void waitForEnter() {
        cout << "Nhấn Enter để quay lại menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    /**
     * @brief Hiển thị thông báo tạm biệt
     */
    void showGoodbye() {
        clearScreen();
        showSuccess("Cảm ơn bạn đã sử dụng ứng dụng Danh Bạ!");
        showSuccess("Hẹn gặp lại!");
    }

    /**
     * @brief Hiển thị thông báo danh bạ trống
     */
    void showEmptyMessage() {
        showInfo("Danh bạ trống!");
    }

    /**
     * @brief Hiển thị dấu phân cách
     */
    void showSeparator() {
        setTextColor(FOREGROUND_BLUE);
        cout << "----------------------------------------" << endl;
        resetColor();
    }
};

#endif // UI_H
