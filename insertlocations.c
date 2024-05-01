#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <conio.h>
#include <unistd.h>
int len(FILE *,int ), len2(FILE *, int );
char* retcon(int );
char* retst(int );
int d();
int coun();
int sta();
int cty();
int clr();
struct country
{
	int cno;
	char name[20];
}*co,cn;
struct state
{
	int cno,sno;
	char name[20];
}st,*sa;
struct city
{
	int cno,sno,cyo;
	char name[20];
}*cy,ct;
int main()
{
	//clrscr();
	printf("\n");
	int a;
	printf("1.countries\n2.states\n3.cities\n4.clear all data\nenter your choice : ");
	scanf("%d",&a);
	if(a==1)
		coun();
	else if(a==2)
		sta();
	else if(a==3)
		cty();
	else if(a==4)
		clr();
	else
		d();
}
int coun()
{
	FILE *fp;
	int a;
	fp=fopen("countries.txt","r");
	cn.cno=len(fp,sizeof(struct country ))+1;
	printf("\ncountry no %d\n",cn.cno);
	fp=fopen("countries.txt","a");
	printf("enter name>>>",cn.name);
	scanf("%s",cn.name);
	fwrite(&cn,sizeof(struct country ),1,fp);
	fclose(fp);
	printf("saved\npress enter to enter nxt\nenter 1 to exit");
	scanf("%d",&a);
	if(a!=1)
		coun();
	main();
}
int sta()
{
	FILE *fp;
	int a,i;
	fp=fopen("states.txt","a");
	printf("enter name of state no : %d>>>",st.sno);
	scanf("%s",st.name);
	printf("enter country no");
	scanf("%d",&st.cno);
	st.sno=len2(fp,sizeof(struct state), st.cno)+1;
	fwrite(&st,sizeof(struct state),1,fp);
	fclose(fp);
	fp=fopen("countries.txt","r");
	while(fread(&cn, sizeof(struct country), 1, fp)){
		if(cn.cno==st.cno){
			break;
		}
	}
	fclose(fp);
	printf("saved\nstate no:%d||country name:%s||state name:%s\npress enter to enter nxt state\nenter 1 to exit",st.sno,cn.name,st.name);
	scanf("%d",&a);
	if(a!=1)
		sta();
	main();
}
int cty()
{
	FILE *fp,*ft;
	int a;
	ft=fopen("cities.txt","a");
	ct.cyo=len2(ft,sizeof(struct city),st.sno)+1;
	printf("enter name of city  no : %d>>>",ct.cyo);
	scanf("%s",ct.name);
	printf("enter country no>>");
	scanf("%d",&ct.cno);
	fp=fopen("countries.txt","r");
	while(fread(&cn, sizeof(struct country), 1, fp)){
		if(cn.cno==ct.cno){
			break;
		}
	}
	fclose(fp);
	printf("enter state no");
	scanf("%d",&ct.sno);
	fp=fopen("states.txt","r");
	while(fread(&st, sizeof(struct state), 1, fp)){
		if(ct.cno==cn.cno&&ct.sno==st.sno){
			break;
		}
	}
	fclose(fp);
	fwrite(&ct,sizeof(struct city),1,ft);
	fclose(ft);
	printf("saved\ncity no:%d||country name:%s||state name:%s||city name:%s\npress enter to enter nxt city\nenter 1 to exit",ct.cyo,cn.name,st.name,ct.name);
	scanf("%d",&a);
	if(a!=1)
		cty();
	main();
}
int len(FILE *f,int a)
{
	fseek(f,0,SEEK_END);
	int l=ftell(f)/a;
	return l;
	fclose(f);
}
char* retcon(int a)
{
	FILE *f;
	int i=0;
	f=fopen("countries.txt","r");
	co=(struct country *)malloc(len(f,sizeof(struct country ))*sizeof(struct country));
	for(i=0;fread(&co[i],sizeof(struct country),1,f);i++)
	{
		if(a==co[i].cno);
		{
			return co[i].name;
			break;
		}
	}
	free(co);
	fclose(f);
}
char* retst(int a)
{
	FILE *f;
	int i=0;
	f=fopen("states.txt","r");
	sa=(struct state *)malloc(len(f,sizeof(struct state))*sizeof(struct state));
	for(i=0;fread(&sa[i],sizeof(struct state),1,f);i++)
	{
		if(a==sa[i].sno);
		{
			return sa[i].name;
			break;
		}
	}
	free(sa);
	fclose(f);
}
int clr()
{
	FILE *fp;
	fp=fopen("countries.txt","w");
	fclose(fp);
	fp=fopen("states.txt","w");
	fclose(fp);
	fp=fopen("cities.txt","w");
	fclose(fp);
	printf("data cleared");
	sleep(1);
	main();
}
int d()
{
	int i;
	FILE *g;
	g=fopen("countries.txt","r");
	printf("\nentered\n");
	int n=len(g,sizeof(struct country));
	co=(struct country *)malloc(n*sizeof(struct country ));
	for(i=0;fread( &co[i], sizeof(struct country ), 1, g);i++)
	{
		printf("city::%s\tcode:%d\n",co[i].name,co[i].cno);
		i++;
	}
	printf("\nclosed");
	fclose(g);
}
int lenC(int n){
	int count=0;
	FILE *f1;
	while(fread(&cn, sizeof(struct country), 1, f1)){
		if(cn.cno == n)
			count++;
	}
	fclose(f1);
	return count;
}
int lenC(int n){
	int count=0;
	FILE *f1;
	while(fread(&cn, sizeof(struct country), 1, f1)){
		if(cn.cno == n)
			count++;
	}
	fclose(f1);
	return count;
}
int lenC(int n){
	int count=0;
	FILE *f1;
	while(fread(&cn, sizeof(struct country), 1, f1)){
		if(cn.cno == n)
			count++;
	}
	fclose(f1);
	return count;
}
int lenS(int n){
	int count=0;
	FILE *f1;
	while(fread(&st, sizeof(struct state), 1, f1)){
		if(st.cno == n)
			count++;
	}
	fclose(f1);
	return count;
}
