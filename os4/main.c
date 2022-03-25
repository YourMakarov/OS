#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "unistd.h"
 
int main(){
char template[] = "./tmpXXXXXX";
int desc = mkstemp(template);
if(desc < 0){
printf("1\n");
perror("Tmp file not created\n");
return -6;
}
printf("%s\n", template);
FILE *test;
if ((test = fopen("test.txt", "r")) == NULL)
{
printf("Не удалось открыть файл");
return 1;
}
printf("ftruncate\n");
ftruncate(desc, sizeof(int)*100);
printf("mmap\n");
int *fd = mmap(NULL, sizeof(int)*15, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
if (fd == MAP_FAILED){
printf("3\n");
perror("mmap error\n");
return -5;
}
 
int n=0;
printf("fscanf\n");
int count = 0;
for(int i = 0; fscanf(test,"%d",&n) != EOF; i++){
fd[i] = n;
count++;
}
fclose(test);
ftruncate(desc, sizeof(int)*count);
int id1 = fork();
if (id1 == -1) {
printf("2\n");
perror("fork error");
return -1;
} else if (id1 == 0){
sleep(2);
execl("child.out", "child.out", template, NULL);
printf("execl\n");
int status;
waitpid(id1, &status,WUNTRACED);
if(WEXITSTATUS(status)){
return -1;
}
unlink(template);
return 0;

}
}

