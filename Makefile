NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

RM = rm -rf

SRC = parseo.c philo.c init_data.c monitor.c routine.c actions.c\

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "${CIAN}Compiling...${NC}"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${LGREEN}Program compiled✅${NC}"

clean : 
	@$(RM) $(OBJS)
	@echo "${MAGENTA}Objects deleted🧹${NC}"

fclean : clean
	@$(RM) $(NAME)
	@echo "${MAGENTA}All clean✨${NC}"

re: fclean all

.PHONY: all clean fclean re