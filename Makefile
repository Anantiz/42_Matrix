CXX:=clang++
CPPFLAGS:= -Wall -Wextra -g3
AVX_FLAGS:= -mavx -march=native

NAME = libft_matrix.so

OBJ_PATH = ./obj
SRC_PATH = .

SRC_FILES =

SRC_OBJECTS := $(patsubst %.tpp, %.o, $(SRC_FILES))

all: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.tpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CPPFLAGS) -o $@

$(NAME): $(SRC_OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^

clean:
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
