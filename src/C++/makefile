# Nombre del ejecutable
TARGET = optimizer

# Archivos fuente
SRCS = main.cpp utils.cpp

# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

# Regla principal
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Limpieza
clean:
	rm -f $(TARGET)

re: clean all