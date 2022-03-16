NAME		= pipex

SRCS		= $(wildcard srcs/*.c)		  				
OBJS		= $(SRCS:.c=.o)

CC			= gcc 
CFLAGS		=  -Wall -Wextra -Werror -I./includes
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS) $(CHECKER_OBJS)
	

fclean: clean
	$(RM) $(NAME) $(CHECKER_NAME)

re:	fclean all