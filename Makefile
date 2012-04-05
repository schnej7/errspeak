TARGET             = build/errspeak.so

SUCCESS_MSG        = '  [\e[32m DONE \e[0m]'

CC                 = gcc

CFLAGS    = -std=c99 -Wall -Wextra -fpic -shared -ldl


all: build

build: $(TARGET)

$(TARGET): src/errspeak.c src/errspeak.h
	@echo 'Building target:'
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@
	@echo -e $(SUCCESS_MSG)

clean:
	@echo 'Cleaning workspace:'
	@rm -rf build/
	@echo -e $(SUCCESS_MSG)

rebuild: clean all
