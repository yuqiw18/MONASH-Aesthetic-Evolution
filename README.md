# Aesthetic-Evolution
Monash University AI ALife Project II

## Usage
### Compile:  
```
g++ -o Evolution.out GL_routines.cpp main.cpp Flower.cpp World.cpp -framework GLUT -framework OpenGL
```

### Run:  
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

### Control
| Operation | Key |
| - | :-: |
| Select | **Enter**, when parent ID is given |
| Mate | **M**, when two parents are selected |
| Reset | **R**, which gives randomised result |
| Quit | **Q** |

*The parent ID is ranged from 1 to grid<sup>2</sup>; the ID sequence is from the top left to the bottom right.*
