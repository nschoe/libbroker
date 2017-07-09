CXX=g++
CXXFLAGS=-Wall -fPIC -Iinclude
LDFLAGS=-shared
LIB_NAME=libbroker.so
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_HEADER_DIR=/usr/local/include

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

src/libbroker.o: include/libbroker.hpp

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

install: $(LIB_NAME) include/libbroker.hpp
	@echo "Installing $(LIB_NAME) into $(INSTALL_LIB_DIR)..."
	@cp $(LIB_NAME) $(INSTALL_LIB_DIR)/
	@echo "Installing header file into $(INSTALL_HEADER_DIR)..."
	@cp include/libbroker.hpp $(INSTALL_HEADER_DIR)/

uninstall:
	@echo "Uninstalling $(LIB_NAME) from $(INSTALL_LIB_DIR)..."
	@rm -f $(INSTALL_LIB_DIR)/$(LIB_NAME)
	@echo "Uninstalling libbroker.hpp from $(INSTALL_HEADER_DIR)..."
	@rm -rf $(INSTALL_HEADER_DIR)/libbroker.hpp

.PHONY: clean mrproper install uninstall

clean:
	rm -rf src/*.o

mrproper: clean
	rm -rf $(LIB_NAME)
