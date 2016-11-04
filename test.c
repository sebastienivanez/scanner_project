#include "logger.h"
#include "scanner.h"
int main(int argc, char *argv[])
{
	char* path = "/home/rcannaerts/graduation_project/log.txt";
	char text[6][1024]={{"penguin"},{"duck"},{"donkey"},{"llama"},{"monkey"},{"duck"}};
	for (int i = 0; i<6; i++)
	{
		int ret = logging(text[i],path);
	} 	
	scanner(path);
	return 0;
}
