NAME = Odyci

OBJS_DIR = .objs

SRCS = 	main.cpp \
		srcs/Window.cpp

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.cpp=%.o))
CXX = g++
CXXFLAGS = -lglfw -lGL -lGLEW

RED = \033[0;31m
ORANGE=\033[0;33m
GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME) $(CXXFLAGS)
	@echo "$(GREEN)Executable $(NAME) created successfully.$(NC)"

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(ORANGE)Compiled $< to $@$(NC)"

clean:
	@rm -f $(NAME)
	@echo "$(RED)Cleaned executable file.$(NC)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Cleaned project files.$(NC)"

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re