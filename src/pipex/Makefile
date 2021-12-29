NAME = pipex

HEADER = ./includes/pipex.h

UTILS_LIST = ./sourses/ft_split.c	./sourses/ft_strjoin.c	./sourses/ft_strlen.c\
	./sourses/ft_strnstr.c	./sourses/pipex_utils.c 

MAIN_LIST =	./sourses/pipex.c

BONUS_LIST =	./sourses/pipex_bonus.c

UTILS_OBJ = $(UTILS_LIST:.c=.o)

MAIN_OBJ = $(MAIN_LIST:.c=.o)

OBJ_B = $(BONUS_LIST:.c=.o)

FLAGS = -Werror -Wextra -Wall

all : $(NAME)

$(NAME): $(UTILS_OBJ) $(MAIN_OBJ)
		gcc $(UTILS_OBJ) $(MAIN_OBJ) -o $@
%.o : %.c $(HEADER)
		gcc $(FLAGS) -c $< -o $@

bonus :
	make fclean_bonus
	make MAIN_OBJ="$(OBJ_B)" all

clean :
	rm -rf $(OBJ_B) $(UTILS_OBJ) $(MAIN_OBJ)

fclean : clean
	rm -rf $(NAME)

clean_bonus: 
	rm -rf $(MAIN_OBJ)

fclean_bonus: clean_bonus
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re