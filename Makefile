NAME = ircserv
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp
INC = 
OBJ_PATH = ./objs/
OBJS = $(patsubst %.cpp,$(OBJ_PATH)%.o,$(SRCS))

all:$(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	@c++ $(FLAGS) $(OBJS) -o $(NAME)
	@echo "                                                         "
	@echo " \033[1;32m  ___|   _ \    \  |   _ \ _ _|  |      ____|  __ \   | "
	@echo "  |      |   |  |\/ |  |   |  |   |      __|    |   |  | "
	@echo "  |      |   |  |   |  ___/   |   |      |      |   | _| "
	@echo " \____| \___/  _|  _| _|    ___| _____| _____| ____/  _) \033[0m"
	@echo "                                                         "

$(OBJ_PATH)%.o: %.cpp $(INC)
	@c++ $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;32m.o files removed!\033[0m"

fclean:
	@rm -rf $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;32mbinary files removed!\033[0m"

re: fclean all