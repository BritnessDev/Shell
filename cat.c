#include<stdio.h>
#include<string.h>

int isExistFile(const char*);

int main(int argc,char **argv)
{
	if(argv[1] == NULL)

		fprintf(stderr, "uwu: \"cat\" incorrect\n");

	else
	{

		int p1=0, p2=0, op=0, i=1, j=1;

		while(argv[i] != NULL)
		{
			if (strcmp(argv[i],"-n") == 0 && op==0)
			{
				op=1;
				p1=i;
			} 

			else if (strcmp(argv[i],"-n")==0 && op!=0 && op!=1)
			{
				op=3;
				p2=i;
			} 

			else if (strcmp(argv[i],"-E")==0 && op==0){
				op=2;
				p1=i;
			} 

			else if (strcmp(argv[i],"-E")==0 && op!=0 && op!=2){
				op=3;
				p2=i;
			}

			i++;
		}

		if (op==0)
		{
			j = 1;
			while (argv[j]!=NULL){
				if(isExistFile(argv[j])==0){
					fprintf(stderr, "uwu: cannot find\n");
				}

				else{
					FILE *file;
					char line[128];
					memset(line, 0, sizeof(line));
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("\n");
						}
						printf("%s",line);
						it++;
					}
					fclose(file);
				}
				j++;
			}

		}

		else if (op==1){

			int j=1;
			while (argv[j]!=NULL){
				if (j==p1){
					j++;
					continue;
				}

				if(isExistFile(argv[j])==0){
					fprintf(stderr, "uwu: cannot find\n");
				}

				else{
					FILE *file;
					char line[128];
					memset(line, 0, sizeof(line));
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("\n");
						}
						printf("     %d  %s",(it+1),line);
						it++;
					}
					fclose(file);
				}
				j++;
			}
		}

		else if (op==2){

			int j=1;
			while (argv[j]!=NULL){
				if (j==p1){
					j++;
					continue;
				}

				if(isExistFile(argv[j])==0){
					fprintf(stderr, "uwu: cannot find\n");
				}

				else{
					FILE *file;
					char line[128];
					memset(line, 0, sizeof(line));
					file = fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("$\n");
						}
						printf("%s",line);
						it++;
					}
					fclose(file);
				}
				j++;
			}

			
		}

		else if (op==3){

			int j=1;
			while (argv[j]!=NULL){
				if (j==p1){
					j++;
					continue;
				}

				if(isExistFile(argv[j])==0){
					fprintf(stderr, "uwu: cannot find\n");
				}

				else{
					FILE *fp;
					char line[128];
					memset(line, 0, sizeof(line));
					fp = fopen(argv[j],"r");
					int it=0;
					while(fscanf(fp,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("$\n");
						}
						printf("     %d  %s",(it+1),line);
						it++;
					}
					fclose(fp);
				}
				j++;
			}

		} 

		else {
			fprintf(stderr, "uwu: incorrect syntax\n");
		}

	}

	return 1;
	
}

int isExistFile(const char *file_name)
{
	FILE *file;
	if ((file = fopen(file_name, "r")))
	{
		fclose(file);
		return 1;
	}
	else
		return 0;
}