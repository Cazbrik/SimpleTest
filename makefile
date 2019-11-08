CC = gcc
CFLAGS = -W -Wall -std=c17 -pedantic

OUT_DIR = build

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.c' -print)
OBJ = $(addprefix $(OUT_DIR)/,$(SRC:.c=.o))

LIB = libtest

static : $(OBJ)
	ar -r $(LIB).a $^
	ranlib $(LIB).a
	sudo mv $(LIB).a /usr/local/lib/

dynamic : $(OBJ)
	$(CC) -shared -o $(LIB).so $^
	sudo mv $(LIB).so /usr/local/lib/

$(OUT_DIR)/%.o : %.c
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ -fpic -c $< $(CFLAGS)

clean: 
	rm -rf $(OUT_DIR)

clean_static : clean
	rm ctest.a

clean_dynamic: clean
	rm ctest.so
