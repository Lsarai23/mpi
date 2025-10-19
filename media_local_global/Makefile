CC = mpicc
TARGET = media_local_global
SRC = media_local_global.c
NP ?= 2
N ?= 5

all: $(TARGET) run clean

$(TARGET): $(SRC)
	@$(CC) $(SRC) -o $(TARGET)
run:
	@mpirun -np=$(NP) ./$(TARGET) $(N)

clean:
	@rm media_local_global