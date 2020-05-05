#!/bin/bash
cd libft && make && cd ..
clang src/*.c libft/libft.a -o w3_linux -I includes/ -I SDL2_Linux/inc/ -L SDL2_Linux/lib/ -l SDL2 -lm -l SDL2_image -v