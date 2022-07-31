FLAG = -Werror -Wextra -Wall -g -MMD -O3
OBJ = pp_check_file_cmd_bonus.o pp_free_things_bonus.o pp_infile_outfile_bonus.o pp_utils_bonus.o pp_getenv_bonus.o pp_parse_cmd_path_lst_bonus.o pp_exec_bonus.o pp_parsing_bonus.o main.o
D_LST = pp_check_file_cmd_bonus.d pp_free_things_bonus.d pp_infile_outfile_bonus.d pp_utils_bonus.d pp_getenv_bonus.d pp_parse_cmd_path_lst_bonus.d pp_exec_bonus.d pp_parsing_bonus.d main.d
LIB = ../lib/libft
NAME = ../pipex_bonus

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -s -C $(LIB)
	$(CC) $(FLAG) $(OBJ) -L $(LIB) -lft -o $(NAME)

%.o: %.c
	$(CC) $(FLAG) -I $(LIB) -c $< -o $@

object:
	@mkdir -p obj

clean:
	@make clean -s -C $(LIB)
	rm -f $(NAME)

fclean: 
	@make fclean -s -C $(LIB)
	rm -f $(NAME)
	rm -f $(OBJ)
	rm -f $(D_LST)

re: fclean all

.PHONY: re all clean fclean
-include $(D_LST)
