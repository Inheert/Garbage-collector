NAME = garbage_collector.a

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror

INCLUDES = -I ./includes/

SRC_DIR = .
BIN_DIR = ./bin

SOURCES = src/garbage_collector.c \
			src/manipulation.c \
			src/ft_malloc.c \
			src/t_ptr_stockage_utils.c \

OBJECTS = $(addprefix $(BIN_DIR)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(AR) rcs $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -rf $(BIN_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
