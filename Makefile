CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex
SRCS = Mandatory/ft_split.c Mandatory/pipex_utils1.c Mandatory/pipex.c Mandatory/pipex_utils2.c
SRCB = bonus/ft_split.c bonus/pipex_bonus.c bonus/utils2_bonus.c bonus/utils_bonus.c gnl/gnl.c gnl/utils.c bonus/utils3_bonus.c bonus/utils4_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(SRCB:.c=.o)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

all: $(NAME)

%.o: %.c Mandatory/pipex.h bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
