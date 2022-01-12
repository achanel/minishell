NAME	= minishell

LIBRARY	= -lft -L$(LIBFT_DIRECTORY)

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I ~/.brew/opt/readline/include

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

HEADERS_LIST = minishell.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIRECTORY = ./src/
SRCS_LIST	=	minishell.c\
				utils_minishell.c\
				builtin/builtin.c\
				builtin/cd.c\
				builtin/echo.c\
				builtin/env.c\
				builtin/error_msg.c\
				builtin/exit.c\
				builtin/export.c\
				builtin/pwd.c\
				builtin/unset.c\
				builtin/utils_builtin.c\
				builtin/utils_env.c\
				builtin/utils_stack.c\
				builtin/change_shlvl.c\
				signal/signal.c\
				parser/parser.c\
				parser/pipex_bonus.c\
				parser/pipex_utils.c\
				parser/redirects.c\
				parser/split_pipe.c\
				parser/space_cut.c\

SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

# изменить поддтягивание файлов 			@rm -rf $(OBJS_DIRECTORY)

OBJS_DIRECTORY = src/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

CC			= gcc -g

# CFLAGS		= -Wall -Wextra -Werror
CFLAGS		=

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
			@rm -rf $(OBJS)

fclean:		clean
			@rm -f $(LIBFT)
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus