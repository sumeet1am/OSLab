// Simulation of "grep" command
#include<stdio.h>
#include<string.h>
void main()
{
char fn[10],pat[10],temp[200];
FILE *fp;
printf("Enter file name\n");
scanf("%s",fn);
printf("Enter pattern to be searched\n");
scanf("%s",pat);
fp=fopen(fn,"r");
while(!feof(fp))
{

fgets(temp,100,fp);
if(strstr(temp,pat))//finds the first occurrence of the substring in the string
 printf("%s",temp);
}
fclose(fp);
}
