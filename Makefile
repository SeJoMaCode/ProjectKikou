CC = g++
CFLAGS = -std=c++17 -Wall -O2 -Wextra -pedantic -g
LIBS = -lSDL2

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = ProjectKikou

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

