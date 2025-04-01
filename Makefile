all: $(NAME)

$(NAME):
	@bash ./build.sh

clean:
	@bash ./clean.sh

fclean: clean
	@bash ./clean.sh

.PHONY: all clean fclean re
