#include "lib1.h"
#include <math.h>


float Derivative(float A, float deltaX){
    return (cos(A + deltaX) - cos(A))/deltaX;
}

float E(int X){
float x=X;
float f=1+1/x;
float h=1;
while(x>0){
x--;
h=h*f;
}
return h;
}

