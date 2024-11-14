# Variáveis de compilador e diretórios
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -Wall -g -c -I$(INC) -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Nome do executável
EXE = $(BIN)/tp1.out

# Listar arquivos .cpp e arquivos objeto
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

# Alvo principal
all: directories $(EXE)

# Compilar o executável
$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

# Compilar arquivos .o a partir de arquivos .cpp
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Criar diretórios se não existirem
directories:
	mkdir -p $(OBJ) $(BIN)

debug: $(EXE)
	gdb $(EXE)

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXE) $(OBJS)
	rm -rf $(OBJ) $(BIN)

# Força recompilação
rebuild: clean all
