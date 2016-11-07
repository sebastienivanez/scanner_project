#include "logger.h"
#include "scanner.h"
int main(int argc, char *argv[])
{
	char* path = "log.txt";
	char text[6][1024]={{"penguin"},{"duck"},{"donkey"},{"llama"},{"monkey"},{"duck"}};
	for (int i = 0; i<6; i++)
	{
		int ret = logging(text[i],path);
	} 
	
	char* arg[10];
	arguments (arg);
	int ret = scanner("dees.pnm",arg);
	printf("%d\n",ret);
	printf("hier\n");
	create_pdf("dees.pnm","aap.pdf");
	return 0;
}
