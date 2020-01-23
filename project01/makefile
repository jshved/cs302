CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/lib_info

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/lib_info.o: src/lib_info.cpp include/lib_info.hpp
	g++ $(CFLAGS) -c -o obj/lib_info.o src/lib_info.cpp

# -------------------------
# Executables

bin/lib_info: obj/lib_info.o
	g++ $(CFLAGS) -o bin/lib_info obj/lib_info.o
