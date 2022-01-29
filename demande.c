#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// ###################### Service Class #############################

typedef struct 
{
	int id;
	char Nom[20];
	int price;
} Service;

Service init_Service(int a,char b[20],int c){
	Service CL;
	CL.id=a;
	strcpy(CL.Nom,b);
	CL.price=c;
	return CL;
}

Service Services[100];
#define Empty_Service init_Service(0,"",0);

int len_Service(){
	for (int i = 0; i < sizeof(Services)/sizeof(Service); ++i)
	{
		if (Services[i].id==0){return i;}

	}
}

void get_Service(){
	FILE *CP=fopen("Service.txt","a+");
	int id,price;
	char Nom[20];
	int i=0;
	do{	
		fscanf(CP,"%d\t%s\t%d\n",&id,Nom,&price);
		Services[i]=init_Service(id,Nom,price);i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Service(){
	FILE *CP=fopen("Service.txt","w+");
	int l=len_Service();
	for (int i = 0; i < l; ++i){
		Service C=Services[i];
		fprintf(CP,"%d\t%s\t%d\n",C.id,C.Nom,C.price);
	}
	fclose(CP);
}

Service get_Service_by_id(int Id){
	get_Service();
	int l=len_Service();
	for (int i = 0; i < l; ++i){
		if (Services[i].id==Id)	
		{
			return Services[i];
		}
	}	
	return Empty_Service;
}
Service get_Service_by_name(char n[20]){
	get_Service();
	int l=len_Service();
	for (int i = 0; i < l; ++i){
		if (strcmp(Services[i].Nom,n)==0)	
		{
			return Services[i];
		}
	}	
	return Empty_Service;
}
// ###################### Date Class ##############################

typedef struct 
{
	int jour;
	int mois;
	int annee;
} Date;

Date init_Date(int a,int b,int c){
	Date date;
	date.jour=a;
	date.mois=b;
	date.annee=c;
	return date;
}
int calcul(int a ,Date s,Date e){
	int cout=get_Service_by_id(a).price;
	int nbr = (e.jour-s.jour)+30*(e.mois-s.mois)+366*(e.annee-s.annee);
	return cout*nbr;
}
int compare(Date d,Date end){

	if ((d.jour-end.jour)+30*(d.mois-end.mois)+366*(d.annee-end.annee)>0)
	{return 1;}
	else{
	return 0;
	}
}

// ###################### Demande Class ##############################

typedef struct 
{
	int nbr;    // nombre de chambre
	int id;		// id de client
	Date start;	// la date depart de Demande de chambre
	Date end;	// la date final de Demande de chambre
	int price;
} Demande;

Demande init_Demande(int a,int b,Date s,Date e){
	Demande B;
	B.nbr=a;
	B.id=b;
	B.start=s;
	B.end=e;
	B.price=calcul(a,s,e);
	return B;
}
Demande empty(){
	Demande B;
	B.nbr=0;
	B.id=0;
	B.start=init_Date(0,0,0);
	B.end=init_Date(0,0,0);
	B.price=0;
	return B;
}

Demande Demandes[100];
#define Empty_Demande empty()

int len_Demande(){
	for (int i = 0; i < sizeof(Demandes)/sizeof(Demande); ++i)
	{
		if (Demandes[i].id==0){return i;}

	}
}
void get_Demande(){
	FILE *CP=fopen("Demande.txt","a+");
	int nbr,id,price;
	Date s,e;
	int i=0;
	do{	
		fscanf(CP,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",&nbr,&id,&s.jour,&s.mois,&s.annee,&e.jour,&e.mois,&e.annee,&price);
		Demandes[i]=init_Demande(nbr,id,s,e);
		// Demandes[i].start=s;
		// Demandes[i].end=e;
		// Demandes[i].price=price;
		;i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Demande(){
	FILE *CP=fopen("Demande.txt","w+");
	int l=len_Demande();
	for (int i = 0; i < l; ++i){
		Demande C=Demandes[i];
		fprintf(CP,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",C.nbr,C.id,C.start.jour,C.start.mois,C.start.annee,C.end.jour,C.end.mois,C.end.annee,C.price);
	}
	fclose(CP);
}

// ###################### Gestion des Demandes #############################



Demande get_Demande_by_nbr(int nbr){
	get_Demande();
	int l=len_Demande();
	// printf("%d\n", l);
	int k=0;
	Demande R;
	for (int i = 0; i < l; ++i){
		// printf("%d : %d\n", Demandes[i].nbr,nbr);
		if (Demandes[i].nbr==nbr)	
		{
			R= Demandes[i];k=1;
		}
	}	
	if (k==1){
		return R;
	}
	return Empty_Demande;
}




void add_Demande(Demande C){
	get_Demande();
	int l=len_Demande();
	Demande R=get_Demande_by_nbr(C.nbr);
		Demandes[l]=C;
		set_Demande();
		Service S=get_Service_by_id(C.nbr);
		printf("reserve le service : %s\nde : (%d-%d-%d)\njusqu'a : 
			(%d-%d-%d)\n\nle cout total : %d\n",S.Nom,
			C.start.jour,C.start.mois,C.start.annee,
			C.end.jour,C.end.mois,C.end.annee,C.price);  
}


void show_Demande(){
	get_Demande();
	int l = len_Demande();
	for (int i = 0; i < l; ++i)
	{
		Demande C=Demandes[i];
		printf("%d\t%d\t(%d-%d-%d)\t(%d-%d-%d)\t%d\n",C.nbr,C.id,C.start.jour,C.start.mois,C.start.annee,C.end.jour,C.end.mois,C.end.annee,C.price);
	}
}

// void main(){
// 	add_Demande(init_Demande(7,5,init_Date(11,12,2021),init_Date(14,12,2021)));
// 	show_Demande();
// 	printf("%d\n", compare(init_Date(17,10,2021),init_Date(11,10,2021)));
// }

// void main(){
// 	printf("done !!!!!\n");
// 	printf("hhhh\n");
// }

void main(int argc, char* argv[])
{	

    if (strcmp(argv[1], "-a")==0){
    	int id=get_Service_by_name(argv[2]).id;
    	add_Demande(init_Demande(id,atoi(argv[3])
    		,init_Date(atoi(argv[4]),atoi(argv[5]),atoi(argv[6]))
    		,init_Date(atoi(argv[7]),atoi(argv[8]),atoi(argv[9]))
    		));
    }

}


// Demande -a 2 6 20 12 2021 23 12 2021