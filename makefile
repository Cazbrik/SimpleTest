CC = gcc
CFLAGS = -W -Wall -std=c17 -pedantic

OUT_DIR = build

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.c' -print)
OBJ = $(addprefix $(OUT_DIR)/,$(SRC:.c=.o))

LIB = libtest
MV_DIR = /usr/local/lib/

static : $(OBJ)
	@ar -r $(LIB).a $^ > /dev/null
	@ranlib $(LIB).a > /dev/null
	@sudo mv $(LIB).a $(MV_DIR)

dynamic : $(OBJ)
	@$(CC) -shared -o $(LIB).so $^
	@sudo mv $(LIB).so $(MV_DIR)

$(OUT_DIR)/%.o : %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) -o $@ -fpic -c $< $(CFLAGS)

clean: 
	@rm -rf $(OUT_DIR) > /dev/null
	@sudo rm $(MV_DIR)$(LIB).* > /dev/null