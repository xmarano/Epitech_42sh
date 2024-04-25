##
## EPITECH PROJECT, 2023
## B-PSU-200-MAR-2-1-42sh-anthony.colombani-gailleur
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
	rm -f 42sh

re: fclean all
