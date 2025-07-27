CC = gcc
CFLAGS = -g
LDFLAGS = -lfftw3 -lm
SRC = src
OUT = build

.PHONY = all clean init generate build_task_1

all: clean init generate build_task_1

build_task_1:
	$(CC) $(CFLAGS) -o $(OUT)/task_1 $(SRC)/task_1.c $(LDFLAGS)

generate:
	python3 task1_gen.py

init:
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
	rm -rf *.txt
