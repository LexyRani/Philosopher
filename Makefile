NAME = philo

#--Source--s

#******************************************************************************#
#*									PARSING	  								  *#
#******************************************************************************#

SRCS += Sources/Parsing/main.c
SRCS += Sources/Parsing/init.c
SRCS += Sources/Parsing/routine.c
SRCS += Sources/Parsing/routine2.c

#******************************************************************************#
#*									ERRORS  								  *#
#******************************************************************************#


#******************************************************************************#
#*									UTILS	  								  *#
#******************************************************************************#
SRCS += Sources/Utils/Utils.c

OBJS = $(SRCS:.c=.o)

HEADER += Include/


#******************************************************************************/
#*									COMPILATEURS	  						  */
#******************************************************************************/
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3  #-fsanitize=thread #-fsanitize=address  


#******************************************************************************/
#*									RULES	  								  */
#******************************************************************************/

#-- COLORS --#
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m
YELLOW		= \033[0;33m
BACK_WHITE  = \033[0;47;30m

all:  $(NAME) header

$(NAME): $(OBJS) $(HEADER)
		${CC} ${CFLAGS} ${SRCS} -I$(HEADER) -o ${NAME}
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(HEADER) -o $@ -c $< 

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

header:
	clear
	@echo " $(CYAN) $$HEADER_PROJECT $(NOC)" 

.PHONY: all clean fclean re

define HEADER_PROJECT                                                                       
                           
______ _     _ _                       _               
| ___ \ |   (_) |                     | |              
| |_/ / |__  _| | ___  ___  ___  _ __ | |__   ___ _ __ 
|  __/| '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__|
| |   | | | | | | (_) \__ \ (_) | |_) | | | |  __/ |   
\_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|   
                                | |                    
                                |_|                    
  
endef
export HEADER_PROJECT
