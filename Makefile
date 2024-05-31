NAME						= ircserv

SRC_DIR						= srcs
SRCS						= $(wildcard $(SRC_DIR)/*.cpp main.cpp)
OBJS						= $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

CC							= c++
FLAGS						= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address
INCLUDES					= -I ./Includes

RM							= rm -rf

BUILD_DIR					= .build

# Colors
GREEN 						= \033[0;32m
YELLOW 						= \033[0;33m
RESET 						= \033[0m

all:						$(NAME)

$(NAME):					$(OBJS)
								@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
								@echo "$(GREEN)✅Executable $(NAME) ready.$(RESET)"

$(BUILD_DIR)/%.o:			%.cpp
								@mkdir -p $(dir $@)
								@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
								@$(RM) $(BUILD_DIR)
								@echo "$(YELLOW)❌...Removing object files...$(RESET)"
								@echo "Object files removed.$(RESET)"

fclean:						clean
								@$(RM) $(NAME)
								@echo "$(YELLOW)❌...Removing executable $(NAME)...$(RESET)"
								@echo "Executable $(NAME) removed.$(RESET)"

re:							fclean all

.PHONY:						all clean fclean re