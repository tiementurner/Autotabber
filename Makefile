CC_FLAGS = -MD

NAME = PitchRecog

CC = c++

FILES = src/main.cpp \

OFILES = $(FILES:.cpp=.o)

GREEN = \033[0;38;5;114m
RED = \033[38;5;124m
BLUE = \033[38;5;153m
NORMAL = \033[38;5;255m

all : $(NAME)

$(NAME) : $(OFILES) 
	@$(CC) $(CC_FLAGS) $(OFILES) -o $(NAME)
	@echo "-----------------------------------"
	@echo "$(BLUE)Created executable:$(NORMAL)	$(NAME)"
	@echo "-----------------------------------"


%.o : %.cpp 
	@echo "$(GREEN)Created object file:$(NORMAL)	$@"
	@$(CC) $(CC_FLAGS) -c $< -o $@ 

-include $(OFILES:.o=.d)

clean	:
	@echo "-----------------------------------"
	@echo "$(RED)Object files removed.$(NORMAL)"
	@echo "-----------------------------------"
	@rm -rf $(OFILES) $(OFILES:.o=.d)

fclean	:	clean
	@echo "$(RED)./$(NAME) removed.$(NORMAL)"
	@echo "-----------------------------------"
	@rm -rf $(NAME)

re		: fclean all