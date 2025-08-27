CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I../include
TARGET = smart_contact_cli
SOURCES = ../src/main.cpp ../src/Contact.cpp ../src/ContactManager.cpp ../src/ContactUI.cpp
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

# Windows specific
ifeq ($(OS),Windows_NT)
clean:
	del /Q *.o $(TARGET).exe 2>nul || exit 0
run: $(TARGET)
	./$(TARGET).exe
endif
