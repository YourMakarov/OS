#include "lib1.h"
#include "lib2.h"
#include <stdio.h>
#include <dlfcn.h>

void help(){
    printf("USAGE: K arg1 arg2 ... arg N\n");
    printf("K = 0 - if you want to change the implementation\n");
    printf("K = 1 - if you want to take the derivative. arg1 = point A, arg2 = increment\n");
    printf("K = 2 - if you want to calculate the number E. arg1 = accuracy\n");
}

int main(){
    help();
    int command, curLib = 0;
    char* libs[] = {"./libd1.so", "./libd2.so"};
    void* lib_handler = dlopen(libs[curLib], RTLD_LAZY); // initial library is first (with implementation1)
    if (lib_handler == NULL){
        printf("sorry");
        return 1;
    }
    float (*Derivative)(float A, float deltaX);
    float (*E)(int x);
    Derivative = dlsym(lib_handler, "Derivative");
    E = dlsym(lib_handler, "E");
    while(scanf("%d", &command) != EOF){
        if (command == 0){
            dlclose(lib_handler);
            curLib = 1 - curLib;
            lib_handler = dlopen(libs[curLib], RTLD_LAZY);
            if (lib_handler == NULL){
                return 1;
            }
            Derivative = dlsym(lib_handler, "Derivative");
            E = dlsym(lib_handler, "E");
        }
        else if (command == 1){
            float A, deltaX;
            scanf("%f %f", &A, &deltaX);
            printf("cos'(%f) = %f\n", A, Derivative(A, deltaX));
        }
        else if (command == 2) {
            int x;
            scanf("%d", &x);
            printf("E = %f\n", E(x));

        } else{
            return -1;
        }
    }

    return 0;
}
