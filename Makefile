SERVER_NAME = server
CLIENT_NAME = client

FT_PRINTF_DIR = ft_printf
FT_PRINTF_SRCS = $(wildcard $(FT_PRINTF_DIR)/*.c)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)

LIBFT_DIR	= 42-libft-master
LIBFT_SRCS	= $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJS	= $(LIBFT_SRCS:.c=.o)
LIBFT		= libft.a

CC			= clang
FLAGS 		= -g
SANITIZE	= -fsanitize=address

all: $(SERVER_NAME) $(CLIENT_NAME)

$(CLIENT_NAME): $(LIBFT) client.o $(FT_PRINTF_OBJS)
	$(CC) $(FLAGS) -o $@ client.o $(FT_PRINTF_OBJS) $(LIBFT)

$(SERVER_NAME): $(LIBFT) server.o $(FT_PRINTF_OBJS)
	$(CC) $(FLAGS) -o $@ server.o $(FT_PRINTF_OBJS) $(LIBFT)




$(LIBFT):		$(LIBFT_OBJS)
				ar rcs $@ $^

%.o: %.c
				$(CC) -c $(FLAGS) -o $@ $^

clean :
				/bin/rm -rf $(LIBFT_OBJS) $(FT_PRINTF_OBJS) server.o client.o

fclean : clean
				/bin/rm -rf $(SERVER_NAME) $(CLIENT_NAME) $(LIBFT)

re : fclean all
.PHONY			: all clean fclean re
