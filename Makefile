CC = gcc
CFLAGS = -g
LDFLAGS = -lfftw3 -lm
SRC = src
OUT = build
LINE_DELIMITER = \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#

.PHONY = all clean init generate build_task_1 build_task_2 build_task_3 build_all

all: build_all

run: build_all
	echo $(LINE_DELIMITER)
	echo "Запуск задания 1:"
	$(OUT)/task_1
	echo $(LINE_DELIMITER)
	echo "Запуск задания 2:"
	$(OUT)/task_2
	echo $(LINE_DELIMITER)
	echo "Запуск задания 3:"
	$(OUT)/task_3
	echo $(LINE_DELIMITER)

build_all: clean init generate build_task_1 build_task_2 build_task_3

build_task_1:
	$(CC) $(CFLAGS) -o $(OUT)/task_1 $(SRC)/task_1.c $(LDFLAGS)

build_task_2:
	$(CC) $(CFLAGS) -o $(OUT)/task_2 $(SRC)/task_2.c $(LDFLAGS)

build_task_3:
	$(CC) $(CFLAGS) -o $(OUT)/task_3 $(SRC)/task_3.c $(LDFLAGS)

generate: task1_gen.py task2_gen.py task3_gen.py
	python3 task1_gen.py
	python3 task2_gen.py
	python3 task3_gen.py

init:
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
	rm -rf *.txt
