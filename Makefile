BIN = ./bin

all:
	clang novcrypt.c auth.c substituicao.c -lsodium -lsqlite3 -o $(BIN)/novcrypt

run:
	$(BIN)/novcrypt

teste:
	clang testes.c -o $(BIN)/teste

Rteste:
	$(BIN)/teste

clean:
	rm $(BIN)/*