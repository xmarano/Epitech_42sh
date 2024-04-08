##
## EPITECH PROJECT, 2023
## sitting_up
## File description:
## Makefile
##

NAME2	=	make -C code/

NAME	=	make -C lib/my/

all :
	$(NAME)
	$(NAME2)

fclean :
	rm -f lib/my/libmy.a
	rm -f code/libmy.a
	rm -f mysh

re: fclean all
