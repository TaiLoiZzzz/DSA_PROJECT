#!/bin/bash
# Script để compile và chạy ứng dụng với cấu trúc thư mục mới

echo "🔨 Compiling Smart Contact CLI..."
echo "📁 Using new directory structure..."

# Compile với đường dẫn mới
g++ -std=c++17 -Wall -Wextra -O2 \
    -I./include \
    src/main.cpp \
    src/Contact.cpp \
    src/ContactManager.cpp \
    src/ContactUI.cpp \
    -o smart_contact_cli

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "🚀 Running application..."
    echo "========================================="
    ./smart_contact_cli
else
    echo "❌ Compilation failed!"
    echo "💡 Make sure you have g++ installed and are in the project root directory"
fi
 