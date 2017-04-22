CFLAGS=-std=c99 -g -Wall -Wextra -O0 -pedantic $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
BIN=bin/patmat

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libtp.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET)

dev: CFLAGS=-g -Werror -O0 -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
		ar rcs $@ $(OBJECTS)
		ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
		$(CC) -shared -o $@ $(OBJECTS)

build:
		@mkdir -p build
		@mkdir -p bin

.PHONY: bin
bin:
		gcc -O0 $(TARGET) -o $(BIN)

valgrind:
		VALGRIND="valgrind -v --track-origins=yes --leak-resolution=high --leak-check=full --show-reachable=yes --log-file=/tmp/valgrind-%p.log" $(MAKE)

clean:
		rm -rf build $(OBJECTS) $(TESTS)
		find . -name "*.gc*" -exec rm {} \;
		rm -rf `find . -name "*.dSYM" -print`
