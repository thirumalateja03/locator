#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	long int custID, proID, mobileNo;
	char name[50], password[20];
	int cno, sto, cyo;
}cust;

cust ct;

int main(){
	FILE *f;
	f = fopen("countries.txt", "r");
	while(fread(&ct, sizeof(cust), 1, f)){
		printf("\n%s", ct.name);
	}
	fclose(f);
}
