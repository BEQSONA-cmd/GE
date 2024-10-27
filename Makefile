NAME = ge
CC = c++
FLAGS = -Wall -Werror -Wextra 

SRC = main.cpp Parser.cpp Executer.cpp utils/Parser_utils.cpp utils/Hash_Map.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
