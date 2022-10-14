#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int isExistDirectory(const char *path)
{
	struct stat pbs;
	stat(path, &pbs);
	if (S_ISDIR(pbs.st_mode)){
		return 0;
	}
	return 1;
}


int main(int argc,char **argv)
{

	if(argv[1]==NULL){
		fprintf(stderr, "uwu: \"mkdir\" missing operand\n");
	}

	int p1=0, p2=0, opt=0;

	int i=1;

	while(argv[i]!=NULL){
		if (strcmp(argv[i],"-v")==0 && opt==0){
			opt=1;
			p1=i;
		} 

		else if (strcmp(argv[i],"-v")==0 && opt!=0 && opt!=1){
			opt=3;
			p2=i;
		} 

		else if (strcmp(argv[i],"-p")==0 && opt==0){
			opt=2;
			p1=i;
		} 

		else if (strcmp(argv[i],"-p")==0 && opt!=0 && opt!=2){
			opt=3;
			p2=i;
		} 

		i++;

	}

	if (opt==0){
		int j=1;

		while (argv[j]!=NULL){

			if(isExistDirectory(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(check){
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
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

			if(isExistDirectory(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(!check){
					printf("mkdir: created directory %s\n",argv[j]);
				}
				else{
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
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


			if(isExistDirectory(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(check){
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}


			j++;
		}

	}

	else if (opt==3){
		int j=1;

		while (argv[j]!=NULL){

			if (j==p1 || j==p2){
				j++;
				continue;
			}


			if(isExistDirectory(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(!check){
					printf("mkdir: created directory %s\n",argv[j]);
				}
				else{
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}


			j++;
		}
	}

	else {
		fprintf(stderr, "uwu: improper format\n");
	}

	return 1;

}