#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
 
int isPrime(int n)
{
  if (n > 1) {
  for (int i = 2; i < n; i++)
    if (n % i == 0)
      return 0;
    return 1;
  } else return 0;
}
 
int main(void)
{
  FILE *file;
  file = fopen("test.txt", "r");
  int pipefd[2];
  pid_t cpid;
  int count;
  int childcount;
  if(file < 0){
    printf("One of the files opened incorrectly\n");
    exit(1);
  }
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (cpid == 0) { /* Потомок читает из канала */
 
    while (read(pipefd[0], &childcount, sizeof(childcount)) > 0)
    {
        if ((childcount >= 1) && (isPrime(childcount) == 1)) {
          printf("%d\n", childcount);
        } else {
          close(pipefd[0]);
          close(pipefd[1]);
          fclose(file);
          exit(EXIT_SUCCESS);
        }
  }
} else {
  while(fscanf(file, "%d", &count) != EOF) {
    write(pipefd[1], &count, sizeof(count));
  }
  close(pipefd[0]);
  close(pipefd[1]);
  fclose(file);
  return 0;
  }
}
//Под линукс
