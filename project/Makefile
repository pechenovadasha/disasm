.PHONY: all clean fclean re

NAME = disasm

FLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

SRC =	check_args.c \
		check_args_2.c \
		filling_out.c \
		init_free.c \
		main.c \
		op.c \
		open_and_check_instr.c

%.o: %.c
	@gcc $(FLAGS) -Ilibft -c $< -o $@

OBJ = $(subst .c,.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ) op.h dis_asm.h
	@make -C libft
	@gcc $(FLAGS) $(OBJ) libft/libft.a -Ilibft -o $(NAME)
	@echo "\n$(GREEN)$(DISASM)disasmbler created$(RESET)"
clean:
	@make clean -C libft
	@/bin/rm -f *.o
	@echo "\n$(RED)libft deleted$(RESET)"
fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)
	@echo "$(RED)deleted$(RESET)"
re: fclean all

