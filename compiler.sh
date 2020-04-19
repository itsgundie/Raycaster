#!/bin/bash
cd libft && make && cd ..
gcc src/*.c libft/libft.a -o w3 -I includes/wolf3d.h -I SDL/inc/ -L SDL/lib/ -l SDL2-2.0.0 -L SDL/lib/ -l SDL2_image-2.0.0