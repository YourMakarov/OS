#include "lib2.h"
#include <math.h>


float Derivative(float A, float deltaX){
    return (cos(A + deltaX) - cos(A - deltaX))/(2 * deltaX);
}

float E(int x){
float f=1;
float k=1;
for(int i=1;i<=x;i++){
k=k*i;
f=f+1/k;
}
return f;
}
