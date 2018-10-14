Compile:
g++ -o Evolution.out GL_routines.cpp main.cpp Flower.cpp World.cpp -framework GLUT -framework OpenGL

Optional:
./Evolution.out -grid <int> -mRate <int>

Example:
./Evolution.out -grid 12 -mRate 50

default grid value = 4
default mRate value = 15

*Mutation rate is in percentage

