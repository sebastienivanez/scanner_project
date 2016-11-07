#include "scanner.h"
#include "logger.h"
int scanner(char *loc,char* arguments[])
{ 	
	pid_t pid1, pid2, pid;
	int status;
	pid1=fork();
	if (pid1!=0)
	{
		pid = wait(&status);
	}
	if(pid1==0){
		int fd = open(loc, O_WRONLY|O_CREAT, 0666);
		if (fd < 0) {
			printf("kut\n");
			return fd;
		}
		dup2(fd, 1);
		close(fd);
		//int ret = execlp("/usr/bin/scanimage", "scanimage", "--format", ".pnm","--mode","color","--brightness","0",NULL);
		int ret = execv("/usr/bin/scanimage",arguments);
		if (ret < 0) {
			printf("kak\n");
			return ret;
		
		} 
	return 0;
	}

}
int create_pdf(char *src, char *dest)
{
	printf("hier\n");
	int ret  =  execl("/usr/bin/convert","convert","-adjoin",src,dest,NULL);
	if (ret < 0) {
		printf("verdomme\n");
		return ret;	
	}
	return 0;
}
void arguments (char *test[])
{
	test[0]="scanimage";
	test[1]="-d";
	test[2]="hpaio:/usb/DeskJet_3630_series?serial=CN67F3H43F0658";
	test[3]="--format";
	test[4]=".pnm";
	test[5]="--mode";
	test[6]="color";
	test[7]="--brightness";
	test[8]="0";
	test[9]=NULL;
}

