# Aesthetic-Evolution
Monash University AI ALife Project II

## Usage
Compile:  
```
g++ -o Evolution.out GL_routines.cpp main.cpp Flower.cpp World.cpp -framework GLUT -framework OpenGL
```

Run:  
```
./Evolution.out -grid `<int>` -mRate `<int>`
```

Example:  
```
./Evolution.out -grid 12 -mRate 50
```

Mutation rate is in **percentage**  
Default grid value = 4  
Default mRate value = 15