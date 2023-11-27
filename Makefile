NAME			= pipex

SRCS			= $(wildcard srcs/*.c)

SRCS_OBJS		= $(SRCS:.c=.o)

CC				= gcc 
CFLAGS			= -Wall -Wextra -Werror -I.
RM				= rm -f

FT_PRINTF		= ft_printf/libftprintf.a
MAKE_FTPRINTF	= make -C ft_printf/
CLEAN_FTPRINTF 	= make clean -C ft_printf/
FCLEAN_FTPRINTF	= make fclean -C ft_printf/

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(MAKE_FTPRINTF)
	$(CC) $(SRCS_OBJS) $(FT_PRINTF) -o $(NAME)

clean:
	$(CLEAN_FTPRINTF)
	$(RM) $(SRCS_OBJS)
	
fclean: clean
	$(FCLEAN_FTPRINTF)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re