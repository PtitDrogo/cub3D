#---------------------------------Variables---------------------------------#

OBJS_DIR	=	.objs
DEPS_DIR	=	.deps
SRCS_DIR	=	sources
HEADER_DIR	=	includes
LIBFT		=	./libft/libft.a
MINIBILX	=	./minilibx-linux/libmlx_Linux.a
NAME		=	cub3D
OBJS	=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
DEPS 	= 	$(OBJS:.o=.d)
#------------------------------------------------------------------------#

#---------------------------------Sources---------------------------------#
SRCS =		$(SRCS_DIR)/parsing/parsing.c \
			$(SRCS_DIR)/main.c \
			
#------------------------------------------------------------------------#

#---------------------------------Compilation & Linking---------------------------------#
CC		=	cc
RM		=	rm -f

CFLAGS	=	-g3 -Wall -Wextra -Werror
LINKLIBS = -L minilibx-linux/ -lmlx_Linux -L libft/ -lft
INCLUDES = -I $(HEADER_DIR) -I minilibx-linux -I libft -MMD -MP

#------------------------------------------------------------------------#


#---------------------------------Pretty---------------------------------#
YELLOW	=	\033[1;33m
GREEN	=	\033[1;32m
RESET	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"
#------------------------------------------------------------------------#


all: $(NAME)
-include $(DEPS)

$(LIBFT): FORCE
	@$(MAKE) --no-print-directory -C ./libft

$(MINIBILX) : FORCE
	@$(MAKE) --no-print-directory -C ./minilibx-linux

FORCE:

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 
	@printf $(UP)$(CUT)

$(NAME): $(OBJS) $(MINIBILX) $(LIBFT) Makefile 
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LINKLIBS) -lXext -lX11 -lz -o $@ 
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@echo "$(YELLOW)cleaning files$(RESET)"
	@$(RM) $(OBJS) rm -rf $(OBJS_DIR)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) files deleted !$(RESET)"
	@$(MAKE) --no-print-directory -C ./libft clean
	@$(MAKE) --no-print-directory -C ./minilibx-linux clean

fclean:	clean
	@echo "$(YELLOW)cleaning files$(RESET)"
	@$(RM) $(NAME)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) executable deleted !$(RESET)"
	@$(RM) $(LIBFT)
	@echo "$(GREEN)libft.a executable deleted !$(RESET)"
	@$(RM) $(MINIBILX)
	@echo "$(GREEN)libmlx_Linux.a executable deleted !$(RESET)"

re:	fclean $(NAME)

.PHONY:	all clean fclean re bonus FORCE