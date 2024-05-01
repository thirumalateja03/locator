#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int no;
	char name[20];
}country;

typedef struct { 
	int no1, no2;
	char name[20];
}state;

typedef struct {
	int no1, no2, no3;
	char name[20];
}city;

typedef struct
{
	long int custID, proID, mobileNo;
	char name[50], password[20];
	int cno, sto, cyo;
}cust;

typedef struct {
	long int custID, proID, mobileNo;
	char businessName[50], profession[20];
	int experience;
	float rating;
}pro;

cust ct,*cuu;
pro rt;
country co, *_co_;
state st, *_st_;
city cy, *_cy_;
FILE *t1, *t2, *t3, *fp;
int k=0;
int n1=0,n2=0,n3=0;//location numbers (country, state, city)
long int id,pass;

int clr(),l(char [] ,int size);
int locate();
int flushUsers();
int copycity(),copycountry(),copystate();
int countrydisc(FILE *),statedisc(FILE *),citydisc(FILE *);
int recust();
int profile(cust ),editcust(cust ),searchclient(cust ),bookings(cust ),youraddrs(cust ),veiwprofile(cust );
int editname(cust ),editno(cust ),editpassword(cust ),changetopro(cust ),signuppro(cust );
int check(long int a,long int b);
int signin();
int login(), acctExists(long int );
char *getCountry(int ), *getState(int ), *getCity(int );

int temp(){
	FILE *f;
	f = fopen("customers.txt", "r");
	while(fread(&ct, sizeof(cust), 1, f)){
		printf("%d", ct.custID);
		printf("%s\n", ct.name);
	}
	fclose(f);
}

int main(){
	clr();
	printf("flushed\n");
//	temp();
	signin();
}

int setLocation(){
	
}//sets location of customer

int l(char file_name[], int size){//file name must be array(string array) not pointers
	FILE *f;
	f=fopen(file_name,"r");
	fseek( f, 0, SEEK_END);
	int l = ftell(f)/size;
	fclose(f);
	return l-1;
}//returns no.of records for given file

int clr(){
	t1=fopen("temp1.txt","w");
	t2=fopen("temp2.txt","w");
	t3=fopen("temp3.txt","w");
	fclose(t1);
	fclose(t2);
	fclose(t3);
}//clear the data in temp files

int locate(){//locate function completed
	n1=0;
	n2=0;
	n3=0;
	int i=0,no;
	char name[20];
	country:
		printf("enter country\n>>>");
		scanf("%s",name);
		t1=fopen("temp1.txt","w");
		t2=fopen("countries.txt","r");
		while(fread(&co,sizeof(country),1,t2)){
			if(name[0]==co.name[0]){
				fwrite(&co,sizeof(country),1,t1);
			}
		}
		fclose(t1);
		fclose(t2);
		t1=fopen("temp1.txt","r");
		t2=fopen("temp2.txt","w");
		copycountry(t2, t1);
		for(i=0;i<strlen(name);i++){
			t2=fopen("temp2.txt","r");
			t1=fopen("temp1.txt","w");
			while(fread(&co,sizeof(country),1,t2)){
				if(name[i]==co.name[i]){
					fwrite(&co,sizeof(country ),1,t1);
				}
			}
			fclose(t1);
			fclose(t2);
			t1=fopen("temp1.txt","r");
			t2=fopen("temp2.txt","w");
			copycountry(t2 ,t1);
		}
		t1=fopen("temp1.txt","r");
		countrydisc(t1);
		fclose(t1);
		printf("\n\nIf country not found enter 1 else click enter>>>");
		int g;
		scanf("%d",&g);
	if(g==1)
		goto country;
	printf("enter your choice>>>");
	scanf("%d",&no);
	t1=fopen("temp1.txt","r");
	for(i=0;i<no;i++){
		fread(&co,sizeof(country),1,t1);
		n1=co.no;
	}
	printf("\n%s saved... no : %d",co.name, n1);
	fclose(t1);
	t2=fopen("temp2.txt","w");
	fp=fopen("states.txt","r");
	while(fread( &st, sizeof(state), 1, fp)){
		if(n1==st.no1)
			fwrite(&st,sizeof(state),1,t2);
	}
	fclose(fp);
	fclose(t2);
	printf("States under this country are...\n");
	t2=fopen("temp2.txt", "r");
	statedisc(t2);
	//printf("\nStates completed...\n");
	t3=fopen("temp3.txt","w");
	fp=fopen("cities.txt","r");
	while(fread(&cy,sizeof(city ),1,fp)){
		if(n1==cy.no1)
			fwrite(&cy,sizeof(city),1,t3);
	}
	fclose(fp);
	fclose(t3);
	//country decided work done>>
//	state://state label>>>
//		printf("enter state\n>>>");
//		scanf("%s",name);
//		for(i=0;i<strlen(name);i++){
//			t2=fopen("temp2.txt","r");
//			t3=fopen("temp.txt","w");
//			k=0;
//			while(fread(&st,sizeof( state),1,t2)){
//				if(name[i]==st.name[i]){
//					fwrite(&st,sizeof( state ),1,t3);
//				}
//				i++;
//			}
//			fclose(t3);
//			fclose(t2);
//			t3=fopen("temp.txt","r");
//			t2=fopen("temp2.txt","w");
//			copystate(t2 ,t3);
//		}
//		t2=fopen("temp2.txt","r");
//		//statedisc();
//		fclose(t2);
//		printf("If state not found enter 1 else click enter>>>");
//		scanf("%d",&g);
//	if(g==1)
//		goto state;
	printf("\nenter your choice>>>");
	scanf("%d",&no);
	t2=fopen("temp2.txt","r");
	for(i = 0; i < no; i++){
		fread(&st,sizeof(state ),1,t2);
		n2 = st.no2;
	}
	printf("\n%s saved... no : %d", st.name, n2);
	fclose(t2);
	t1=fopen("temp.txt","w");
	t2=fopen("temp3.txt","r");
	while(fread(&st,sizeof(city),1,t2)){
		if(n2==cy.no2)
			fwrite(&cy.no2,sizeof( city),1,t1);
	}
	fclose(t2);
	fclose(t1);
	t1 = fopen("temp.txt", "r");
	citydisc(t1);
	//states compled work done>>>
//	city://city label>>>
//		printf("enter city\n>>>");
//		scanf("%s",name);
//		for(i=0;i<strlen(name);i++){
//			t3=fopen("temp3.txt","r");
//			t1=fopen("temp.txt","w");
//			k=0;
//			while(fread(&cy,sizeof(city),1,t3)){
//				if(name[i]==cy.name[i]){
//					fwrite(&cy,sizeof(city ),1,t1);
//					break;
//					k++;
//				}
//			}
//			fclose(t1);
//			fclose(t2);
//			t1=fopen("temp.txt","r");
//			t3=fopen("temp3.txt","w");
//			copycity(t3 ,t1);
//		}
//		t3=fopen("temp3.txt","r");
//		//citydisc();
//		fclose(t3);
//		printf("If city not found enter 1 else click enter>>>");
//		scanf("%d",&g);
//	if(g==1)
//		goto city;
	printf("enter your choice>>>");
	scanf("%d",&no);
	t1=fopen("temp.txt","r");
	for(i = 0; i<no; i++){
		fread(&cy,sizeof(city),1,t1);
		n3 = cy.no3;
	}
	fclose(t1);
}//By the end of this function you can get the 3 variable that ar n1 n2 n3 which decides the location

char* getCountry(int n){
	char *str;
	FILE *f;
	f = fopen("countries.txt", "r");
	while(fread(&co,sizeof(country),1,f)){
		if(n == co.no){
			strcpy(str, co.name);
			break;
		}
	}
	fclose(f);
	return str;
}

char* getState(int n){
	char *str;
	FILE *f;
	f = fopen("states.txt", "r");
	while(fread(&st, sizeof(state), 1, f)){
		if(n == st.no2){
			strcpy(str, st.name);
			break;
		}
	}
	fclose(f);
	return str;
}

char* getCity(int n){
	char *str;
	FILE *f;
	f = fopen("cities.txt", "r");
	while(fread(&cy, sizeof(city), 1, f)){
		if(n == cy.no3){
			strcpy(str, cy.name);
			break;
		}
	}
	fclose(f);
	return str;
}

int copycity(FILE *a ,FILE *b){
	int n = 0;
	for(n=0;fread(&cy,sizeof(city),1,b);n++)
		fwrite(&cy,sizeof(city ),1,a);
	fclose(b);
	fclose(a);
}

int copystate(FILE *a ,FILE *b)
{
	int n;
	for(n=0;fread(&st,sizeof(state ),1,b);n++)
		fwrite(&co,sizeof(state ),1,a);
	fclose(b);
	fclose(a);
}

int copycountry(FILE *a ,FILE *b)
{
	int n;
	for(n=0;fread(&co,sizeof(country),1,b);n++)
		fwrite(&co,sizeof(country ),1,a);
	fclose(b);
	fclose(a);
}

int countrydisc(FILE *fp){
	int __temp = 1;
	while(fread(&co, sizeof(country), 1, fp)){
		printf("\n%d . %s",__temp, co.name);
		__temp = __temp + 1;
	}
	fclose(fp);
}

int statedisc(FILE *g){
	int __temp = 1;
	while(fread( &st, sizeof(state), 1, g)){
		printf("\n%d . %s",__temp, st.name);
		__temp = __temp + 1;
	}
	fclose(g);
}

int citydisc(FILE *g){
	int __temp = 1;
	while(fread( &cy, sizeof(city), 1, g)){
		printf("\n%d . %s",__temp, cy.name);
		__temp = __temp + 1;
	}
	fclose(g);
}

int recust(){
	
}//teliyatla


int profile(cust ct){
	int choice;
	printf("Hello , %s\n----------Home--------",ct.name);
	printf("\n1.Veiw profile");
	printf("\n2.Search for clients");
	printf("\n3.Your bookings");
	printf("\n4.Add addresses");
	printf("\n5.Sign out");
	printf("\nYour choice>>>");
	scanf("%d", &choice);
	if(choice==1)
		veiwprofile(ct);
	else if(choice==2)
		editcust(ct);
	else if(choice==3)
		searchclient(ct);
	else if(choice==4)
		bookings(ct);
	else if(choice==5)
		youraddrs(ct);
	else if(choice==6)
		printf("not completed :(");
	else
		printf("invalid operation");
	sleep(1);
	profile(ct);
}//Customer profiles

int veiwprofile(cust ct){
	int choice;
	printf("----------Profile view----------");
	printf("\nUser ID : ", ct.custID);
	printf("\nName : ", ct.name);
	printf("\nMobile no : ", ct.mobileNo);
	printf("\nAddress : ");
	printf("\nCountry : ", getCountry(ct.cno));
	printf("\nState : ", getState(ct.sto));
	printf("\nCity : ", getCity(ct.cyo));
	printf("\n--------------------------------\n");
//	printf("\n1.Edit your profile");
//	printf("\n2.Back");
//	printf("\nEnter your choice : ");
//	scanf("%d", &choice);
//	if(choice == 1){
//		editcust(ct);
//	}else if(choice == 2){
//		profile(ct);
//	}else{
//		printf("Invalid operation...!");
//		veiwprofile(ct);
//	}
//	return 0;
}//veiw details

int searchclient(cust cu){
	
}//search

int bookings(cust cu){
	
}//To book

int youraddrs(cust cu){
	
}//multiple addrs

int editcust(cust cu){
	int choice;
	printf("\n\t--------Edit--------");
	printf("\n1.Edit name");
	printf("\n2.Edit mobile number");
	printf("\n3.change password");
	printf("\n4.Switch to pro account");
	printf("\n5.Go to Home");
	printf("\nEnter your choice>>>");
	if(choice==1)
		editname(cu);
	else if(choice==2)
		editno(cu);
	else if(choice==3)
		editpassword(cu);
	else if(choice==4)
		changetopro(cu);
	else if(choice==5)
		profile(cu);
	else
		printf("invalid operation");
	editcust(cu);
}//To edit customer profile

int editname(cust cu){
	
}//edit name

int editno(cust cu){
	
}//edit mobile number

int editpassword(cust cu){
	
}//edit password

int changetopro(cust cu){
	
}//change to pro acct

int signuppro(cust cu){
//	FILE *g;
//	printf("\n------signup form------");
//	g=fopen("proacc.txt","a");
//	rt.mno=cu.c_no;
//	rt.pass = cu.pas;
//	printf("\nEnter your age");
//	scanf("%d",&rt.age);
//	printf("\nsearch for your profession in the below list that we are offering :");
//	//search for profession
//	fwrite(&rt,sizeof(pro),1,g);
//	fclose(g);
//	signuppro(cu);
}//create an new pro acct

int acctlist(){
	FILE *f;
	f = fopen("customers.txt", "r");
	while(fread(&ct, sizeof(cust), 1, f)){
		printf("name : %s\n", ct.name);
	}
	fclose(f);
}

int flushUsers(){
	FILE *f;
	f = fopen("customers.txt", "w");
	fclose(f);
}

int signin(){
	printf("\n------signup form------\n");
	printf("\nEnter your name : ");
	scanf("%s",ct.name);
	ct.custID = 1100001 + l("customers.txt", sizeof(cust));
	//locate();
	ct.cno = 1;//change it to n1
	ct.sto = 2;//change it to n2
	ct.cyo = 3;//change it to n3
	printf("\nEnter your mobile number : ");
	scanf("%ld",&ct.mobileNo);
	if(acctExists(ct.mobileNo) == 1){
		printf("Uh....:(\nAccount already exists plz try again...\n");
		signin();
	}
	printf("create your password\nnote : It must be <20 characters!\n>>>");
	scanf("%s",&ct.password);
	printf("\nUser ID : %ld", ct.custID);
	fp=fopen("customers.txt","a");
	fwrite( &ct, sizeof(cust), 1, fp);
	fclose(fp);
	printf("\nsignup completed...");
	acctlist();
	printf("\n----------\n");
	main();
}//sign in

int acctExists(long int no){
	int boolean = 0;
	FILE *f;
	f = fopen("customers.txt", "r");
	while(fread(&ct, sizeof(cust), 1, f)){
		if(no == ct.mobileNo){
			boolean = 1;
			break;
		}
	}
	fclose(f);
	return boolean;
}//return 1 if account already exits

int login(){
	printf("\n--------login form---------\n");
	long int no;
	char pass[20];
	FILE *g;
	printf("\nEnter mobile number : ");
	scanf("%ld",&no);
	printf("\nEnter password : ");
	scanf("%s",&pass);
	g=fopen("customers.txt","r");
	while(fread( &ct, sizeof(cust), 1, g)){
		if((ct.mobileNo==no)&&(strcmp(pass, ct.password))){
			fclose(g);
			printf("\nLogin successfull...\n");
			profile(ct);//redirect to profile
		}
	}
	fclose(g);
	printf("Incorrect number or password!\n");
	int o;
	printf("\nEnter 1 to login again\n\t  0 to exit");
	scanf("%d",&o);
	if(o==1)
		login();
}//login
