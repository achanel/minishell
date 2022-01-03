NAME	= minishell

LIBRARY	= -lft -L$(LIBFT_DIRECTORY)

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I ~/.brew/opt/readline/include

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

HEADERS_LIST = minishell.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIRECTORY = ./src/builtin/
SRCS_LIST	= ../minishell.c\
				builtin.c\
				cd.c\
				echo.c\
				env.c\
				error_msg.c\
				exit.c\
				export.c\
				pwd.c\
				unset.c\
				utils_builtin.c\
				utils_env.c\
				utils_stack.c
SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

CC			= gcc 

CFLAGS		= -Wall -Wextra -Werror

READLINE	= -lreadline -L ~/.brew/opt/readline/lib/

all:		${NAME}

$(NAME):	$(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
			@$(CC) $(CFLAGS) $(LIBRARY) $(INCLUDES) $(OBJS) $(READLINE) -o $(NAME)

$(OBJS_DIRECTORY):
			mkdir -p $(OBJS_DIRECTORY)

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
			@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
			@$(MAKE) -sC $(LIBFT_DIRECTORY)
		
clean:
			@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
			@rm -rf $(OBJS_DIRECTORY)

fclean:		clean
			@rm -f $(LIBFT)
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus