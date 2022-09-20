gcc -O3 -shared -fPIC -o sdl_gawk.so sdl_gawk.c -lSDL2 && AWKLIBPATH=$(pwd) gawk -M -b -lsdl_gawk -f  sdl_demo.awk
