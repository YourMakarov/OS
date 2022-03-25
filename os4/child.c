#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
 
bool isPrime(int n)
{
    if (n > 1)
    {
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return 0;
        return 1;
    }
    else
        return 0;
}
 
int main(int argc, char* argv[]){
	int desc = open(argv[1], O_RDWR);
	if(desc < 0){
		perror("Tmp file not created\n");
		return -6;
	}
	struct stat buff;
	stat(argv[1], &buff);
	int n=buff.st_size;
	int *fd = mmap(NULL, sizeof(int)*15,PROT_WRITE|PROT_READ,MAP_SHARED,desc, 0);
		if (fd == MAP_FAILED){
		perror("mmap error\n");
		return -5;
	}
	for(int i=0;i<n;i++){
		if (isPrime(fd[i]) == 1) {
			printf("%d\n", fd[i]);
		} else {
		printf("end\n");
		return 0;
		}
	}
	msync(fd, sizeof(char)*n, MS_SYNC);
	munmap(fd, sizeof(char)*n);
	close(desc);
	return 0;
}