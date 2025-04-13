CC = gcc
CFLAGS = -Wall -Wextra -I./src

BIN = bin/crux
SRC = src/main.c src/sysmon.c src/procpeek.c src/fswatch.c src/netspy.c src/cmdspy.c src/logspy.c src/uptimewatch.c src/diskspy.c src/pingspy.c src/procstat.c src/cpuheat.c

all:
	mkdir -p bin
	gcc -Wall -Wextra -I./src src/*.c -o bin/crux

clean:
	rm -rf bin/*