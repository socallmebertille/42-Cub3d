NAME			=	cub3d
BONUS			=	cub3d_bonus

CC				=	cc
C_FLAGS			=	-Wall -Wextra -Werror -g3

SRCS_DIR		=	srcs
OBJ_DIR			=	objs
SRCS_NAMES		=	main.c \
					check_map_file.c \
					map_file_parse.c \
					get_texture.c \
					recup_color.c \
					check_color.c \
					map_parse.c \
					map_access.c \
					create_rgb.c \
					utils.c \
					free.c \
					render_game.c \
					moves.c \
					put_img.c
OBJS_NAMES		=	$(SRCS_NAMES:.c=.o)
SRCS			=	$(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS			=	$(addprefix $(OBJ_DIR)/,$(OBJS_NAMES))

SRCS_DIR_BONUS	=	srcs_bonus
OBJ_DIR_BONUS	=	objs_bonus
SRCS_N_BONUS	=	main_bonus.c \
					check_map_file_bonus.c \
					map_file_parse_bonus.c \
					get_texture_bonus.c \
					recup_color_bonus.c \
					check_color_bonus.c \
					map_parse_bonus.c \
					map_access_bonus.c \
					create_rgb_bonus.c \
					init_game_bonus.c \
					utils_bonus.c \
					free_bonus.c \
					render_game_bonus.c \
					moves_bonus.c \
					get_radius_bonus.c \
					render_mini_map_bonus.c \
					render_handlebars_bonus.c \
					update_handlebars_bonus.c \
					mouse_bonus.c \
					put_img_bonus.c
OBJS_N_BONUS	=	$(SRCS_N_BONUS:.c=.o)
SRCS_BONUS		=	$(addprefix $(SRCS_DIR_BONUS)/,$(SRCS_N_BONUS))
OBJS_BONUS		=	$(addprefix $(OBJ_DIR_BONUS)/,$(OBJS_N_BONUS))

INCLUDES		=	-I./minilibx-linux/ -I./includes/

LIBFT			=	libft/libft.a
L_MLX			=	-L./minilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11 -Imlx -lm -lz -O3

GREEN			=	\033[1;32m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
ORANGE			=	\033[38;5;214m
PURPLE			=	\033[1;35m
BOLD			:=	\033[1m
RESET			=	\033[0m

SUCCESS			=	[ ✔ ]
ERROR			=	[ ✗ ]
CLEAN			=	[ ♻ ]
REMOVE			=	[ 🗑 ]
REDO			=	[ 🗘 ]

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@make -C minilibx-linux --no-print-directory
	@$(CC) $(OBJS) $(INCLUDES) $(LIBFT) $(L_MLX) -lreadline -o $(NAME) || (echo "\n$(RED) ============ $(ERROR) Linking failed ! ====================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Executable created ! ================================== $(RESET)"

$(LIBFT):
	@make -C libft --no-print-directory

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ || (echo "\n$(RED) ============ $(ERROR) Compilation failed ! ================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Successful compilation ! ============================== $(RESET)"

bonus: $(LIBFT) $(BONUS)

$(BONUS): $(OBJS_BONUS)
	@make -C minilibx-linux --no-print-directory
	@$(CC) $(OBJS_BONUS) $(INCLUDES) $(LIBFT) $(L_MLX) -o $(BONUS) || (echo "\n$(RED) ============ $(ERROR) Linking failed ! ====================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Executable created ! ================================== $(RESET)"

$(OBJ_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ || (echo "\n$(RED) ============ $(ERROR) Compilation failed ! ================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Successful compilation ! ============================== $(RESET)"

clean:
	@make clean -C libft --no-print-directory
	@make clean -C minilibx-linux --no-print-directory
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "$(YELLOW) ============ $(CLEAN) Successful binary & dependances cleaning ! ============ $(RESET)"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -rf $(NAME) $(BONUS)
	@echo "$(BOLD)$(ORANGE) ============ $(REMOVE) Deleted executable ! ================================== $(RESET)"

re: fclean all
	@echo "$(PURPLE) ============ $(REDO) Redo completed ! ====================================== $(RESET)"

.PHONY: all clean fclean re bonus
