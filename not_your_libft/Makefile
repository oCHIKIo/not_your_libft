
NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -I ./

LIBC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	   ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	   ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_tolower.c ft_toupper.c

ADDITIONAL = ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			 ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
	    ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c 

SRCS = $(LIBC) $(ADDITIONAL)
SRCS_ALL = $(LIBC) $(ADDITIONAL) $(BONUS)

OBJS = $(SRCS:.c=.o)
OBJS_ALL = $(SRCS_ALL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

bonus: $(NAME) $(OBJS_ALL)
	ar -rsc $(NAME) $(OBJS_ALL)

clean:
	rm -f $(OBJS) $(BONUS:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

.PHONY: all clean fclean re bonus