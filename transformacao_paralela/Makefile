CC = mpicc
TARGET = transformacao_paralela
SRC = transformacao_paralela.c

all: $(TARGET) run clean

$(TARGET): $(SRC)
	@$(CC) $(SRC) -o $(TARGET)
run:
	@mpirun -np=5 ./$(TARGET)

clean:
	@rm transformacao_paralela