#include <dirent.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char **argv) {
	DIR *dir;
	struct dirent *dt;

	int p1 = 0, p2 = 0, opt = 0, isArg = 0, i = 1;


	while (argv[i])
	{
		if (strcmp(argv[i], "-1")==0 && opt==0){
			opt=1;
			p1=i;
		} 

		else if (strcmp(argv[i], "-1")==0 && opt!=0 && opt!=1){
			opt=3;
			p2=i;
		} 

		else if (strcmp(argv[i], "-a")==0 && opt==0){
			opt=2;
			p1=i;
		} 

		else if (strcmp(argv[i], "-a")==0 && opt!=0 && opt!=2){
			opt=3;
			p2=i;
		} 

		else if (strcmp(argv[i], "-a")!=0 && strcmp(argv[i],"-1")!=0){
			isArg=1;
		}

		i++;
	}

	if (opt==0){

		if (isArg==1){

			int j=1;

			while (argv[j]!=NULL){
				dir = opendir(argv[j]);

				if (dir==NULL){
					fprintf(stderr, "uwu: Cannot open specified directory.");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((dt = readdir(dir)) != NULL){
					if((dt->d_name[0]!='.')){
						printf("%s\t ", dt->d_name);
					}
				}

				printf("\n\n");
				closedir(dir);
				j++;
			}

		} else {

			dir = opendir(".");

			if (dir==NULL){
				fprintf(stderr, "uwu: cannot open specified dirn");
				return 1;
			}

			while ((dt = readdir(dir)) != NULL){
				if((dt->d_name[0]!='.')){
					printf("%s\t ", dt->d_name);
				}
			}
			printf("\n");
			closedir(dir);
		}
	}

	else if (opt==1){

		if (isArg==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1){
					j++;
					continue;
				}

				dir = opendir(argv[j]);

				if (dir==NULL){
					fprintf(stderr, "uwu: cannot open specified dirn");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((dt = readdir(dir)) != NULL){
					if((dt->d_name[0]!='.')){
						printf("%s\n", dt->d_name);
					}
				}

				printf("\n");
				closedir(dir);
				j++;
			}

		} else {

			dir = opendir(".");

			if (dir==NULL){
				fprintf(stderr, "uwu: cannot open specified dirn");
				return 1;
			}

			while ((dt = readdir(dir)) != NULL){
				if((dt->d_name[0]!='.')){
					printf("%s\n", dt->d_name);
				}
			}
			closedir(dir);
		}

	}

	else if (opt==2){
		if (isArg==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1){
					j++;
					continue;
				}

				dir = opendir(argv[j]);

				if (dir==NULL){
					fprintf(stderr, "uwu: cannot open specified dirn");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((dt = readdir(dir)) != NULL){
					printf("%s\t ", dt->d_name);
				}

				printf("\n\n");
				closedir(dir);
				j++;
			}

		} else {

			dir = opendir(".");

			if (dir==NULL){
				fprintf(stderr, "uwu: cannot open specified dirn");
				return 1;
			}

			while ((dt = readdir(dir)) != NULL){
				printf("%s\t ", dt->d_name);
			}
			printf("\n");
			closedir(dir);
		}
	}

	else if (opt==3){
		if (isArg==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==p1 || j==p2){
					j++;
					continue;
				}

				dir = opendir(argv[j]);

				if (dir==NULL){
					fprintf(stderr, "uwu: cannot open specified dirn");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((dt = readdir(dir)) != NULL){
					printf("%s\n", dt->d_name);
				}

				printf("\n");
				closedir(dir);
				j++;
			}

		} else {

			dir = opendir(".");

			if (dir==NULL){
				fprintf(stderr, "uwu: cannot open specified dirn");
				return 1;
			}

			while ((dt = readdir(dir)) != NULL){
				printf("%s\n", dt->d_name);
			}
			closedir(dir);
		}
	}

	else {
		fprintf(stderr, "uwu: improper format\n");
	}

	return 1;
}
