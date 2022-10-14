#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int isExistDirectory(const char*);
//Initializing history of size 500
#define max_calls 512

char preCalls[max_calls][ 100 * sizeof(char*) ];
int call_cnt=0;

int isExistDirectory(const char* dir)
{
	//Helper function that returns details about a directory 
	DIR* _dir=opendir(dir);
	if (_dir)
		return 1;
	else if (errno == ENOTDIR)
		return 0;
	return -1;
}

int execute(char** cmd){
	if (cmd[0] == NULL) {
		//No cmd entered
		return 1;
	} 

	else if (strcmp(cmd[0],"exit")==0){
		//Exit cmd. Status will be set to zero and hence loop will stop running when this is called.
		return 0;
	} 

	else if (strcmp(cmd[0],"cd")==0){
		char lt[64]; 

		if (cmd[1]==NULL || strcmp(cmd[1],"~")==0) {
			//Switches to home directory
			chdir(getenv("HOME"));
			printf("%s %s\n", "Current Directory:", getcwd(lt, 64));
		} 

		else if (cmd[2]!=NULL && cmd[2]!="-L"){
			//Error Handling
			fprintf(stderr, "UWU: too many arguments\n");
			exit(1);
		} 

		else {
			if (isExistDirectory(cmd[1])==1){
				//Switches to directory input by user
				chdir(cmd[1]); 
				printf("%s %s\n", "Current Directory:", getcwd(lt, 64));
			} else {
				//Error handling
				fprintf(stderr, "UWU: no such file or directory\n");
				exit(1);
			}
		}

		return 1;
	} 

	else if (strcmp(cmd[0],"echo")==0){
		if(cmd[1]==NULL){
			//No input
			printf("\n");
		}
		else if (cmd[1]!=NULL){
			if(strcmp(cmd[1],"*")==0){
				//Implementation of "*" flag
				DIR *d1;
				d1 = opendir("."); 
				struct dirent *bruh;
				while(d1)
				{
					bruh = readdir(d1);
					if (!bruh) break;
					if(bruh->d_name[0]!='.'){
						printf("%s  \t", bruh->d_name);
					}

				}
				closedir(d1);
				printf("\n");
			}

			else if(strcmp(cmd[1],"-n")==0){
				//Implementation of "-n" flag
				int p=2;

				while(1){
					if(cmd[p]==NULL){
						break;
					}
					p++;
				}

				int q=2;
				while (q!=p){
					if (q!=2){
						printf(" ");
					}
					printf("%s",cmd[q]);
					q++;
				}
			}

			else {
				//For valid string input
				int index1=1;
				while(1){
					if(cmd[index1]==NULL){
						break;
					}
					index1=index1+1;
				}

				for(int i=1;i<index1;i++)
				{
					printf("%s ",cmd[i]);
				}
				printf("\n");

			} 
		} 

		else {
			fprintf(stderr, "UWU: invalid input\n");
		}
		return 1;
	} 

	else if (strcmp(cmd[0],"pwd")==0)
	{
		if (cmd[1]==NULL || strcmp(cmd[1],"-L")==0 ||  strcmp(cmd[1],"-P")==0){
			char lt[128]; 
			printf("%s\n", getcwd(lt, 100));
		} else {
			//Error handling
			fprintf(stderr, "UWU: invalid input\n");
			exit(1);
		}
		return 1;
	} 

	else if (strcmp(cmd[0],"history")==0)
	{
		if (cmd[1] == NULL){
			//Prints all elements in history
			for(int i=0;i<call_cnt;i++){
				printf("%s",preCalls[i]);
			}
		} 

		else if (strcmp(cmd[1],"-c")==0){
			//Clears history
			call_cnt=0;
		} 

		else if (strcmp(cmd[1],"-a")==0){
			//Writes current history to the history file
			FILE *file ; 
			file=fopen("history.txt", "w") ; 

			if (file==NULL) { 
				fprintf(stderr, "UWU: error accessing history file\n");
				exit(1);
			} 

			else { 
				int i=0;
				while (i!=call_cnt){
					if (strlen(preCalls[i])>0) { 
						fputs(preCalls[i], file) ;    
						fputs("\n", file) ; 
					} 
					i++;
				}
				fclose(file) ; 
			}
		} 

		else {
				//Error handling
			fprintf(stderr, "UWU: invalid input\n");
			exit(1);
		}

		return 1;
	}

	else {
		//For other cmds

		char p[]="/home/dhairya/Documents/os1.2/";
		strcat(p,cmd[0]);
		cmd[0]=p;

		pid_t pid;
		int status;
		pid = fork();

		if (pid<0)
		{
			fprintf(stderr, "UWU: Invalid command\n");
			exit(1);
		}

		else if (pid == 0) 
		{
			if (execvp(cmd[0],cmd) == -1) 
			{
				fprintf(stderr, "UWU: Invalid command\n");
				exit(1);
			}
			exit(1);
		}

		else 
		{
			do { 
				wait(NULL); 
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		return 1;
	}
}

int main(int argc, char **argv)
{
	//loop ends when status is 0
	int status=1;

	while (status)
	{
		printf("\033[0;31mUWU command: \033[0m");

		char *userInput = NULL;
		ssize_t size=0;
		int getip;

		//Taking user input
		getip=getline(&userInput,&size,stdin);

		if(getip==-1){
			if(feof(stdin)){
				exit(1);
			}
			else{
				perror("Error 1: ");
				exit(1);
			}
		}

		//Adding command entered to history
		strcpy(preCalls[call_cnt],userInput);
		call_cnt++;

		char** inputData=malloc(100*sizeof(char*));

		//Processing input
		char *curr;
		curr=strtok(userInput," \n");
		int i=0;
		while(curr!=NULL){
			inputData[i]=curr;
			i++;
			curr=strtok(NULL," \n");
		}
		inputData[i]=NULL;

		//Calling the execute function that contains the details about all functions
		status=execute(inputData);

		//Freeing memory
		free(inputData);
		free(userInput);
	}
}
