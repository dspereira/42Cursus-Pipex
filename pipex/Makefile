NAME			= pipex

GENE_SRCS	= 	srcs/alloc_mem.c \
				srcs/error_handling.c \
				srcs/get_fds.c \
				srcs/get_cmds.c \
				srcs/get_paths.c \
				srcs/close_fds.c \
				srcs/free_cmds.c \
				srcs/free_paths.c \
				srcs/utils.c \
				srcs/utils2.c \

PIPEX			= srcs/pipex.c
PIPEX_BONUS		= srcs/pipex_bonus.c

GENE_OBJS		= $(GENE_SRCS:.c=.o)
PIPEX_OBJ		= $(PIPEX:.c=.o)
PIPEX_BONUS_OBJ	= $(PIPEX_BONUS:.c=.o)

CC				= gcc 
CFLAGS			=  -Wall -Wextra -Werror -I.
RM				= rm -f

FT_PRINTF		= ft_printf/libftprintf.a
MAKE_FTPRINTF	= make -C ft_printf/
CLEAN_FTPRINTF 	= make clean -C ft_printf/
FCLEAN_FTPRINTF	= make fclean -C ft_printf/

all: $(NAME)

$(NAME): $(GENE_OBJS) $(PIPEX_OBJ)
	$(MAKE_FTPRINTF)
	$(CC) $(GENE_OBJS) $(PIPEX_OBJ) $(FT_PRINTF) -o $(NAME)

bonus: $(GENE_OBJS) $(PIPEX_BONUS_OBJ)
	$(MAKE_FTPRINTF)
	$(CC) $(GENE_OBJS) $(PIPEX_BONUS_OBJ) $(FT_PRINTF) -o $(NAME)

clean:
	$(CLEAN_FTPRINTF)
	$(RM) $(GENE_OBJS) $(PIPEX_OBJ) $(PIPEX_BONUS_OBJ)
	
fclean: clean
	$(FCLEAN_FTPRINTF)
	$(RM) $(NAME)

re:	fclean all