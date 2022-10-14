#include<stdio.h> 
#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int isExistDirectory(const char*);
int isExistDirectory(const char* dir)
{
	DIR* thisdir = opendir(dir);

	if(thisdir != NULL)
	{
		closedir(thisdir);
		return 0;
	} 
	else if(errno == ENOTDIR) 
		return 1;
	return -1;
}

int main(int c, char *argv[]) {
	
	if(argv[1]==NULL)
	{
		fprintf(stderr, "uwu: \"rm\" missing operand\n");
	}

	else
	{
		int p1=0, p2=0, opt=0, i=1;

		while(argv[i]!=NULL)
		{
			if (strcmp(argv[i],"-i") == 0 && opt == 0){
				opt=1;
				p1=i;
			} 

			else if (strcmp(argv[i],"-i") == 0 && opt != 0 && opt != 1)
			{
				opt=3;
				p2=i;
			} 

			else if (strcmp(argv[i],"-v") == 0 && opt == 0){
				opt=2;
				p1=i;
			} 

			else if (strcmp(argv[i],"-v") == 0 && opt != 0 && opt != 2){
				opt=3;
				p2=i;
			} 

			i++;

		}

		if (opt==0){

			int j=1;

			while (argv[j]!=NULL){
				if(isExistDirectory(argv[j])==1){
					remove(argv[j]);    
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
				}
				j++;
			}
		}

		else if (opt==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1){
					j++;
					continue;
				}

				if(isExistDirectory(argv[j])==1){
					char* a=NULL;
					ssize_t sizea=0;
					printf("rm: remove file %s? ",argv[j]);
					getline(&a, &sizea, stdin);
					if(strcmp(a,"y\n")==0){
						remove(argv[j]);
					} else {
						//do nothing
					}
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
				}

				j++;
			}

		}

		else if (opt==2){

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1){
					j++;
					continue;
				}

				if(isExistDirectory(argv[j])==1){
					printf("%s\n",argv[j]);
					remove(argv[j]);   
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
				}

				j++;

			}
		} 

		else if (opt==3) {

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1 || j==p2){
					j++;
					continue;
				}

				if(isExistDirectory(argv[j])==1){
					char* a=NULL;
					ssize_t sizea=0;
					printf("rm: remove file %s? ",argv[j]);
					getline(&a, &sizea, stdin);
					if(strcmp(a,"y\n")==0){
						printf("removed %s\n",argv[j]);
						remove(argv[j]);
					} else {
						//do nothing
					}
				}

				else {
					fprintf(stderr, "uwu: improper format\n");
				}


				j++;
			}

		}

		else {
			fprintf(stderr, "uwu: improper format\n");
		}


		return 1; 

	}
}