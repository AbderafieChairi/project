#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ###################### Client Class #############################

typedef struct 
{
	int id;
	char Nom[20];
	char Adress[20];
	char Email[20];
	char Password[20];

} Client;

Client init_Client(int a,char b[20],char c[20],char d[20],char e[20]){
	Client CL;
	CL.id=a;
	strcpy(CL.Nom,b);
	strcpy(CL.Adress,c);
	strcpy(CL.Email,d);
	strcpy(CL.Password,e);
	return CL;
}

Client Clients[100];
#define Empty_Client init_Client(0,"","","","");

int len_Client(){
	for (int i = 0; i < sizeof(Clients)/sizeof(Client); ++i)
	{
		if (Clients[i].id==0){return i;}

	}
}

void get_Client(){
	FILE *CP=fopen("Client.txt","a+");
	int id;
	char Nom[20],Adress[20],Email[20],Password[20];
	int i=0;
	do{	
		fscanf(CP,"%d\t%s\t%s\t%s\t%s\n",&id,Nom,Adress,Email,Password);
		Clients[i]=init_Client(id,Nom,Adress,Email,Password);i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Client(){
	FILE *CP=fopen("Client.txt","w+");
	int l=len_Client();
	for (int i = 0; i < l; ++i){
		Client C=Clients[i];
		fprintf(CP,"%d\t%s\t%s\t%s\t%s\n",C.id,C.Nom,C.Adress,C.Email,C.Password);
	}
	fclose(CP);
}

int max_id(){
	get_Client();
	int k = 0;
	for (int i = 0; i < sizeof(Clients)/sizeof(Client); ++i)
	{
		if (Clients[i].id>k){k=Clients[i].id;}

	}
	return k+1;
}

Client get_Client_by_id(int Id){
	get_Client();
	int l=len_Client();
	for (int i = 0; i < l; ++i){
		if (Clients[i].id==Id)	
		{
			return Clients[i];
		}
	}	
	return Empty_Client;
}
int Check_Client(char a[20],char b[20]){
	get_Client();
	int l=len_Client();
	for (int i = 0; i < l; ++i){
		if (strcmp(Clients[i].Email,a)==0 && strcmp(Clients[i].Password,b)==0)	
		{
			printf("%d", Clients[i].id);
			return 1;
		}
	}	
	printf("%d",0);;
	return 0;
}
void add_Client(Client C){
	// printf("id	Nom	Adress\n");
	// Client C;
	// scanf("%d\t%s\t%s\n",&C.id,C.Nom,C.Adress)
	get_Client();
	int l=len_Client();
	if (get_Client_by_id(C.id).id==0)
	{
	Clients[l]=C;
	set_Client();
	printf("Ajouter <Client %d>\n",C.id);
	}
	else{
	printf("<Client %d> deja existe\n",C.id);
	}   
}

void show_Client(){
	get_Client();
	int l = len_Client();
	for (int i = 0; i < l; ++i)
	{
		Client C=Clients[i];
		printf("%d\t%s\t%s\t%s\n",C.id,C.Nom,C.Adress,C.Email);
	}
}

void delete_Client(int Id){
	get_Client();
	int l = len_Client();
	int k=0;
	if (get_Client_by_id(Id).id==0)
	{
		printf("<Client %d> n'existe pas\n",Id);
	}else{
	for (int i = 0; i < l; ++i)
	{	
		if(Clients[i].id==Id && k==0){k=1;}
		if(k==1){
			Clients[i]=Clients[i+1];
			Clients[i+1]=Empty_Client;
		}
	}
	printf("supprimer <Client %d>\n",Id);

	set_Client();
	}
}

void modifier_Client(Client C){
	get_Client();
	int l = len_Client();
	if (get_Client_by_id(C.id).id!=0)
	{
	for (int i = 0; i < l; ++i)
	{	
		if(Clients[i].id==C.id){
			Clients[i]=C;
		}

	}
	set_Client();	
	printf("modifier <Client %d>\n",C.id);
	}
	else{
	printf("<Client  %d> n'existe pas\n",C.id);
	}
}

void tri_Nom_Client(){
	get_Client();
	int a=len_Client();
	Client tmp=Empty_Client;
	for (int i=0 ; i < a-1; i++)
	{
	for (int j=0 ; j < a-i-1; j++)
		{
			if (strcmp(Clients[j].Nom , Clients[j+1].Nom)==1)
			{
				tmp=Clients[j];
				Clients[j]=Clients[j+1];
				Clients[j+1]=tmp;
			}
		}
		}
	set_Client();
	printf("tri par Nom : \n\n");
	show_Client();
}


int main(int argc, char* argv[])
{	
    if (strcmp(argv[1], "-a")==0){
    	add_Client(init_Client(max_id(),argv[2],argv[3],argv[4],argv[5]));
    }
    if (strcmp(argv[1], "-u")==0){
    	modifier_Client(init_Client(atoi(argv[2]),argv[3],argv[4],argv[5],argv[6]));
    }
    if (strcmp(argv[1], "-c")==0){
    	Check_Client(argv[2],argv[3]);
    }
    if (strcmp(argv[1], "-d")==0){
    	delete_Client(atoi(argv[2]));
    }
    if (strcmp(argv[1], "-s")==0){
    	show_Client();
    }
}
