CXX:=clang++ -std=c++17
CPPFLAGS:= -Wall -Wextra -g3 -I./src/ -mavx -mavx2 -march=native
AVX_FLAGS:=

NAME = tester

OBJ_PATH = ./obj
SRC_PATH = .

SRC_FILES = the_tester.cpp

SRC_OBJECTS := $(patsubst %.cpp, %.o, $(SRC_FILES))

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
