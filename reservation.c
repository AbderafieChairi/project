#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// ###################### Chambre Class #############################

typedef struct 
{
	int nbr;	// le nombre de chambre
	int price;	// le couts de chambre
} Chambre;

Chambre init_Chambre(int a,int b){
	Chambre CH;
	CH.nbr=a;
	CH.price=b;
	return CH;
}

Chambre Chambres[100];
#define Empty_Chambre init_Chambre(0,0);

int len_Chambre(){
	for (int i = 0; i < sizeof(Chambres)/sizeof(Chambre); ++i)
	{
		if (Chambres[i].nbr==0){return i;}

	}
}

void get_Chambre(){
	FILE *CP=fopen("Chambre.txt","a+");
	int nbr,price;
	int i=0;
	do{	
		fscanf(CP,"%d\t%d\n",&nbr,&price);
		Chambres[i]=init_Chambre(nbr,price);i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Chambre(){
	FILE *CP=fopen("Chambre.txt","w+");
	int l=len_Chambre();
	for (int i = 0; i < l; ++i){
		Chambre C=Chambres[i];
		fprintf(CP,"%d\t%d\n",C.nbr,C.price);
	}
	fclose(CP);
}
Chambre get_Chambre_by_nbr(int nbr){
	get_Chambre();
	int l=len_Chambre();
	for (int i = 0; i < l; ++i){
		if (Chambres[i].nbr==nbr)	
		{
			return Chambres[i];
		}
	}	
	return Empty_Chambre;
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
	int cout=get_Chambre_by_nbr(a).price;
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

// ###################### Reservation Class ##############################

typedef struct 
{
	int nbr;    // nombre de chambre
	int id;		// id de client
	Date start;	// la date depart de reservation de chambre
	Date end;	// la date final de reservation de chambre
	int price;
} Reservation;

Reservation init_Reservation(int a,int b,Date s,Date e){
	Reservation B;
	B.nbr=a;
	B.id=b;
	B.start=s;
	B.end=e;
	B.price=calcul(a,s,e);
	return B;
}
Reservation empty(){
	Reservation B;
	B.nbr=0;
	B.id=0;
	B.start=init_Date(0,0,0);
	B.end=init_Date(0,0,0);
	B.price=0;
	return B;
}

Reservation Reservations[100];
#define Empty_Reservation empty()

int len_Reservation(){
	for (int i = 0; i < sizeof(Reservations)/sizeof(Reservation); ++i)
	{
		if (Reservations[i].id==0){return i;}

	}
}
void get_Reservation(){
	FILE *CP=fopen("Reservation.txt","a+");
	int nbr,id,price;
	Date s,e;
	int i=0;
	do{	
		fscanf(CP,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",&nbr,&id,&s.jour,&s.mois,&s.annee,&e.jour,&e.mois,&e.annee,&price);
		Reservations[i]=init_Reservation(nbr,id,s,e);
		// Reservations[i].start=s;
		// Reservations[i].end=e;
		// Reservations[i].price=price;
		;i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Reservation(){
	FILE *CP=fopen("Reservation.txt","w+");
	int l=len_Reservation();
	for (int i = 0; i < l; ++i){
		Reservation C=Reservations[i];
		fprintf(CP,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",C.nbr,C.id,C.start.jour,C.start.mois,C.start.annee,C.end.jour,C.end.mois,C.end.annee,C.price);
	}
	fclose(CP);
}

// ###################### Gestion des Reservations #############################



Reservation get_Reservation_by_nbr(int nbr){
	get_Reservation();
	int l=len_Reservation();
	// printf("%d\n", l);
	int k=0;
	Reservation R;
	for (int i = 0; i < l; ++i){
		// printf("%d : %d\n", Reservations[i].nbr,nbr);
		if (Reservations[i].nbr==nbr)	
		{
			R= Reservations[i];k=1;
		}
	}	
	if (k==1){
		return R;
	}
	return Empty_Reservation;
}





int get_free_chambre(){
	get_Reservation();
	get_Chambre();
	int ll=len_Reservation();
	int l=len_Chambre();
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime( &rawtime );
	Date start=init_Date(info->tm_mday,info->tm_mon+1,info->tm_year+1900);
	// printf("%d\t%d\t%d\n",start.jour,start.mois,start.annee);
	for (int i = 0; i < l; ++i){
		Reservation R=get_Reservation_by_nbr(Chambres[i].nbr);
		// printf("%d : %d\n",Chambres[i].nbr,R.id);
		// printf("(%d-%d-%d) %d\n",R.end.jour,R.end.mois,R.end.annee,compare(start,R.end));
		if (compare(start,R.end)==1){
			printf("%d\t%d\n",Chambres[i].nbr,Chambres[i].price);
		}
	}


}




void add_Reservation(Reservation C){
	get_Reservation();
	int l=len_Reservation();
	Reservation R=get_Reservation_by_nbr(C.nbr);
	if (compare(C.start,R.end)==1){
		Reservations[l]=C;
		set_Reservation();
		printf("reserve le Chambre : %d\nde : (%d-%d-%d)\njusqu'a : (%d-%d-%d)\n\nle cout total : %d\n",C.nbr,
			C.start.jour,C.start.mois,C.start.annee,
			C.end.jour,C.end.mois,C.end.annee,C.price);
	}
	else{
	printf("Le Chambre %d est deja reserve\n",R.nbr);
	}   
}


void show_Reservation(){
	get_Reservation();
	int l = len_Reservation();
	for (int i = 0; i < l; ++i)
	{
		Reservation C=Reservations[i];
		printf("%d\t%d\t(%d-%d-%d)\t(%d-%d-%d)\t%d\n",C.nbr,C.id,C.start.jour,C.start.mois,C.start.annee,C.end.jour,C.end.mois,C.end.annee,C.price);
	}
}

// void main(){
// 	add_Reservation(init_Reservation(7,5,init_Date(11,12,2021),init_Date(14,12,2021)));
// 	show_Reservation();
// 	printf("%d\n", compare(init_Date(17,10,2021),init_Date(11,10,2021)));
// }

// void main(){
// 	printf("done !!!!!\n");
// 	printf("hhhh\n");
// }

void main(int argc, char* argv[])
{	
	if (strcmp(argv[1], "-f")==0){
		get_free_chambre();
	}
    if (strcmp(argv[1], "-a")==0){
    	add_Reservation(init_Reservation(atoi(argv[2]),atoi(argv[3])
    		,init_Date(atoi(argv[4]),atoi(argv[5]),atoi(argv[6]))
    		,init_Date(atoi(argv[7]),atoi(argv[8]),atoi(argv[9]))
    		));
    }

}


// reservation -a 2 6 20 12 2021 23 12 2021