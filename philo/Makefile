NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g
RM			=	rm
RMFLAGS		=	-f

SRCDIR		=	./src
CFILES		=	$(SRCDIR)/philosophers.c \
				$(SRCDIR)/init_table.c \
				$(SRCDIR)/init_philo.c \
				$(SRCDIR)/free_philo.c \
				$(SRCDIR)/utils.c \
				$(SRCDIR)/philo_routine.c \
				$(SRCDIR)/threads.c \
				$(SRCDIR)/monitoring.c \
				$(SRCDIR)/print.c
					
OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include/
IFILES		=	$(INCLDIR)philosophers.h

all:			$(NAME)

# Compile object files
%.o:			%.c $(IFILES)
				@printf "\rCompiling $<..."
				@$(CC) $(CFLAGS) -I$(INCLDIR) -c $< -o $@

# Compile minishell with the existing libs
$(NAME):		$(OBJS)
				@printf "\rCompiling $(NAME)..."
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@printf "\r\n\033[32m$(NAME) compiled.\033[0m\n"
clean:
				@printf "\rCleaning object files"
				@$(RM) $(RMFLAGS) $(OBJS)
				@printf "\rObject files cleaned.\n"

fclean:			clean
				@printf "\rRemoving $(NAME)..."
				@$(RM) $(RMFLAGS) $(NAME)
				@printf "\r$(NAME) Removed.\n"

re:				fclean all

.PHONY:			all clean fclean re