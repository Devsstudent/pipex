FLAG = -Werror -Wextra -Wall -g -MMD
OBJ = $(addprefix obj/, pp_check_path.o pp_utils.o pp_check_file_cmd.o pp_infile_outfile.o pp_parsing.o pp_getenv.o pp_exec.o pp_free_things.o main.o)
D_LST = $(addprefix obj/, pp_check_path.d pp_utils.d pp_check_file_cmd.d pp_infile_outfile.d pp_parsing.d pp_getenv.d pp_exec.d pp_free_things.d main.d null.d)
LIB = ./lib/libft
HEAD = ./includes
NAME = pipex
BONUS = ./bonus_dir

all: $(NAME)

bonus :
	@make -C $(BONUS)

$(NAME): $(OBJ)
	@make bonus -s -C $(LIB)
	$(CC) $(FLAG) $(OBJ) -L $(LIB) -lft -o $(NAME)

obj/%.o: src/%.c | object
	$(CC) $(FLAG) -I $(LIB) -I $(HEAD) -c $< -o $@

object:
	@mkdir -p obj

clean:
	@make clean -s -C $(LIB)
	@make clean -s -C $(BONUS)
	rm -f $(NAME)

fclean: 
	@make fclean -s -C $(LIB)
	@make fclean -s -C $(BONUS)
	rm -f $(NAME)
	rm -rf obj

re: fclean all

.PHONY: re all clean fclean
-include $(D_LST)
