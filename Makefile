APPS = ./apps
OUTPUT = ./output
INCLUDE = ./includes
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -o3 -Wall

all: libed app 

libed: \
	$(OBJ)/alianca.o \
	$(OBJ)/edificio.o \
	$(OBJ)/faccao.o \
	$(OBJ)/mensagens.o \
	$(OBJ)/unidade.o \
	$(OBJ)/mapa.o \

app: clean_apps \
	$(OUTPUT)/main \
	$(OUTPUT)/teste_faccao \
	$(OUTPUT)/teste_edificio \
	$(OUTPUT)/teste_unidade \
	$(OUTPUT)/teste_alianca \
	$(OUTPUT)/teste_mapa \

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

run:
	$(OUTPUT)/teste_edificio.out

$(OUTPUT)/%: $(APPS)/%.c
	gcc $(FLAGS) $< $(OBJ)/*.o -I $(INCLUDE) -o $@.out

export_lib:libed
	ar -rcs $(LIB)/libed.a $(OBJ)/*

clean:
	rm $(OUTPUT)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(OUTPUT)/*