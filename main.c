#include<stdio.h>
#include<time.h>
#include<math.h>
#include"Structure.h"
#include<stdlib.h>
#include<string.h>
#define nalloc(n,t) (t*) malloc((n)*sizeof(t))
#define alloc(t) (t*)malloc(sizeof(t))

int comparerdates(date d1, date d2) {
    if (d1.tm_year != d2.tm_year) {
        return d1.tm_year - d2.tm_year;
    }
    if (d1.tm_mon != d2.tm_mon) {
        return d1.tm_mon - d2.tm_mon;
    }
    return d1.tm_mday - d2.tm_mday;
}

//les fonctions de saisir qui permettent d'entrer les donnes /////
/////////////////////////////////////////////////////////////////
date saisirdate() {
    date dt;

    printf("saisir le jour: \n");
    scanf("%d", &dt.tm_mday);

    printf("saisir le mois: \n");
    scanf("%d", &dt.tm_mon);

    printf("saisir l'annee: \n");
    scanf("%d", &dt.tm_year);

    return dt;
}


profil saisir_profil () {
    profil p;
    printf("saisir le nom: \n");

    scanf("%s",p.nom);


    printf("saisir le prenom: \n");
    scanf("%s",p.prenom);


    printf("saisir l'adresse mail: \n");
    scanf("%s",p.email);
    fflush(stdin);

    printf("saisir l'adresse: \n");
    gets(p.adr);
    //scanf("%s", p.adr);


    printf("saisir le numero d'inscription: \n");
    scanf("%ld", &p.num_inscrit);

    printf("saisir le numero de telephone: \n");
    scanf("%ld", &p.num_tele);

    printf("saisir la date de naissance\n");
    p.date_naissance = saisirdate();
    p.code=1920;
    return (p);
}

void ajouter_profil( pcell** tab_profil,profil prof );
auteur saisir_auteur(pcell** tab_profil ) {
    auteur a;


    printf("saisir le pseudo de l'auteur: \n");
    scanf("%s",a.pseudo);

    printf("saisir le nombre de messages de l'auteur: \n");
    scanf("%d", &a.nbr_msg);

    printf("sasir la date du premier message de l'auteur\n");
    a.date_premier_msg = saisirdate();

    printf("sasir la date du dernier message de l'auteur\n");
    a.date_dernier_msg = saisirdate();
    printf("si tu ne veut pas associser un profil a l'auteur taper 0 sinon taper n'importe quelle valeur!=0:\n");
    int arr;
    scanf("%d",&arr);
    if(arr==0){
        return a;
    }
    printf("<<sasir le num d'incription de profil de l'auteur si'il exist >>\n");
    long int x;
    scanf("%ld",&x);
    pcell* tmp;
	tmp=*tab_profil;
	while(tmp)
    {

		if(((tmp->elt).num_inscrit)==x){
			 a.aut_profil=(tmp->elt);
			 return(a);
		}

		tmp=tmp->succ;


    }


    if(tmp==NULL){
        printf("Le profile n'exist pas saisir un nouveau profile ");
        a.aut_profil=saisir_profil();
        a.aut_profil.num_inscrit=x;
        ajouter_profil(&(*tab_profil),a.aut_profil);

    }
	free(tmp);
    return (a);
}

rubrique saisir_rubrique() {
    rubrique r;

    printf("donnez le theme de la rubrique: \n");
    fflush(stdin);
    scanf("%s",r.theme);

    printf("donnez la date de creation de la rubrique\n");
    r.date_creation = saisirdate();

    printf("donnez l'adresse mail de l'animateur: \n");
    fflush(stdin);
    scanf("%s",r.adr_email_animateur);
    printf("donnez la liste des sites : \n");
    fflush(stdin);
    gets(r.liste_des_site);
    printf("donnez l'adresse internet de forum  : \n");
    fflush(stdin);
    scanf("%s",r.adr_int_forum);


    return (r);
}



reponse saisir_reponse() {
    reponse rp;

    printf("saisir le titre de la reponse: \n");
    fflush(stdin);
    scanf("%s",rp.titre);

    printf("saisir le texte de la reponse: \n");
    fflush(stdin);
    gets(rp.text);

    printf("saisir la date de publication de la reponse\n");
    rp.date_publication= saisirdate();

    printf("saisir le pseudo de l'auteur de la reponse: \n");
    fflush(stdin);
    scanf("%s",(rp.auteur));

    return (rp);
}

//entete de la fonction explicitee anterierement
void ajouter_auteur( acell **tab,auteur prof );
message saisir_message(acell** tab,pcell** tabp) {
    message m;
    fflush(stdin);
    printf("saisir le titre du message: \n");
    scanf("%s",m.titre);
    fflush(stdin);

    printf("saisir le texte du message: \n");
    gets(m.text);

    printf("saisir la date de publication du message\n");
    m.date_publications = saisirdate();
    char x[20];
    printf("saisir le pseudo de l'auteur du message: \n");
    fflush(stdin);
    scanf("%s",x);
    acell* tmp;
	tmp=*tab;
	while(tmp)
    {

		if(strcmp(((tmp->elt).pseudo),x)==0){
			 m.auteur=(tmp->elt);
			 break;
		}

		tmp=tmp->succ;


    }



    if(tmp==NULL){
        printf("L'auteur n'exist pas saisir un nouveau auteur ");
        m.auteur=saisir_auteur(&(*tabp));
        strcpy(m.auteur.pseudo,x);
        ajouter_auteur(&(*tab),m.auteur);
    }
	free(tmp);

    printf("saisir le theme de rubrique : \n");
    scanf("%s",(m.rubrique));


    //pour ajouter une reponse aucours de la creation de message
    //remarque on a une autre fonction dans le menue pour ajouter une reponse apres la creation de message
    int c,j=0;
    m.nbr_rp=0 ;
    while (1) {

        printf("donner 1 pour ajouter une reponce ou 0 pour quitter\n");
        scanf("%d" , &c);
        if (c==1){
            m.lst_rp[j]=saisir_reponse();
            j++ ;
            m.nbr_rp++;
        }
        else
				break ;

    }


    return (m);

}



forum saisir_forum(){
    forum f;
    printf("saisir laddresse internet\n");
    fflush(stdin);
    scanf("%s",f.adr_internet);
    printf("saisir courriel\n");
    fflush(stdin);
    scanf("%s",f.adr_courriel);
    return (f);
}
////les fonctions d'affichages ///////////////////
/////////////////////////////////////////////////

void afficher_date(date d) {

    printf("%d/%d/%d \n",d.tm_mday,d.tm_mon,d.tm_year);


}


int afficher_profil (profil p) {
    if(p.code!=1920){
        printf("le profil est vide ");
        return 1;
    }


    printf("le nom est: %s \n",p.nom);

    printf("le prenom est: %s\n",p.prenom);


    printf("l'adresse mail est : %s \n",p.email);


    printf("l'adresse est: %s \n",p.adr);

    printf("le numero d'inscription est : %d \n",p.num_inscrit);


    printf("le numero de telephone est: %d \n",p.num_tele);


    printf("la date de naissance : \n");
    afficher_date(p.date_naissance);
    return 1;

}



void afficher_auteur(auteur a) {


    printf("le pseudo de l'auteur est: %s \n",a.pseudo);


    printf("le nombre de messages de l'auteur est: %d \n",a. nbr_msg);


    printf("la date du premier message de l'auteur : \n");
    afficher_date(a.date_premier_msg);


    printf("la date du dernier message de l'auteur : \n");
    afficher_date(a.date_dernier_msg);
    printf("le profil de l'auteur est:\n ");
    afficher_profil(a.aut_profil);


}



void afficher_rubrique(rubrique r) {


    printf("le theme de la rubrique est: %s \n",r.theme);


    printf("la date de creation de la rubrique est \n");
    afficher_date(r.date_creation);

    printf("l'adresse mail de l'animateur est : %s \n",r.adr_email_animateur);

    printf("la liste de site est :\n");
    puts(r.liste_des_site);
    printf("l'adress de forum est:\n");
    fflush(stdout);
    puts(r.adr_int_forum);


}


void afficher_reponse(reponse rp) {


    printf("le titre de la reponse est: %s \n",rp.titre);


    printf("le texte de la reponse est: %s \n",rp.text);


    printf("la date de publication de la reponse est : \n");
    afficher_date(rp.date_publication);
    printf("voisi le  pseudo de l'auteur :%s \n",rp.auteur);



}


void afficher_message(message m) {


    printf("le titre du message est: %s \n",m.titre);


    printf("le texte du message est: %s \n",m.text);


    printf("la date de publication du message est : \n");
    afficher_date(m.date_publications);

    printf("le pseudo de l'auteur du message est: %s \n ", m.auteur.pseudo);
    printf("le message appartient a la rubriquede theme : %s \n ", m.rubrique);

    /*int i ;
    for (i=0;i<m.nbr_rp;i++) {


        printf("la reponce %d est : \n ",i);

        afficher_reponse(m.lst_rp[i]);


    }*/

}
void afficher_messagev2(message m) {


    printf("le titre du message est: %s \n",m.titre);


    printf("le texte du message est: %s \n",m.text);


    printf("la date de publication du message est : \n");
    afficher_date(m.date_publications);

    printf("le pseudo de l'auteur du message est: %s \n ", m.auteur.pseudo);
    printf("le message appartient a la rubriquede theme : %s \n ", m.rubrique);

    int i ;
    for (i=0;i<m.nbr_rp;i++) {


        printf("la reponce %d est : \n ",i);

        afficher_reponse(m.lst_rp[i]);


    }

}

void afficher_forum(forum f){
	printf("laddresse internet est %s \n",f.adr_internet);

    printf("courriel %s \n",f.adr_courriel);

}


//***-*-*-*-*---*-*-*-*-***--*-**-*-*-*--**-*-*-**--**-
////////////////stockage des doones dans une liste chainee ///////////////////
/////////////////////////////////////////////////////////////////////////////
void ajouter_profil( pcell** tab_profil,profil prof )
{
   if(*tab_profil==NULL)
   {
       *tab_profil=alloc(pcell);
       (*tab_profil)->elt=prof;
       (*tab_profil)->succ=NULL;
   }else
   {
       pcell* newcell;
       newcell=alloc(pcell);
       newcell->elt=prof;
       newcell->succ=*tab_profil;
       *tab_profil=newcell;



   }

}

void ajouter_auteur( acell **tab,auteur prof )
{
   if(*tab==NULL)
   {
       (*tab)=alloc(acell);
       (*tab)->elt=prof;
       (*tab)->succ=NULL;
   }else
   {
       acell* newcell;
       newcell=alloc(acell);
       newcell->elt=prof;
       newcell->succ=*tab;
       *tab=newcell;



   }

}


void ajouter_message( mcell** tab,message prof )
{
   if(*tab==NULL)
   {
       *tab=alloc(mcell);
       (*tab)->elt=prof;
       (*tab)->succ=NULL;
   }else
   {
       mcell* newcell;
       newcell=alloc(mcell);
       newcell->elt=prof;
       newcell->succ=*tab;
       *tab=newcell;

   }

}


void ajouter_forum( fcell** tab,forum prof )
{
   if(*tab==NULL)
   {
       *tab=alloc(fcell);
       (*tab)->elt=prof;
       (*tab)->succ=NULL;
   }else
   {
       fcell* newcell;
       newcell=alloc(fcell);
       newcell->elt=prof;
       newcell->succ=*tab;
       *tab=newcell;



   }

}


void ajouter_rubrique( rcell** tab,rubrique prof )
{
   if(*tab==NULL)
   {
       *tab=alloc(rcell);
       (*tab)->elt=prof;
       (*tab)->succ=NULL;
   }else
   {
       rcell* newcell;
       newcell=alloc(rcell);
       newcell->elt=prof;
       newcell->succ=*tab;
       *tab=newcell;



   }

}


void ajouter_reponse( rpcell** tab,reponse prof )
{
   if(*tab==NULL)
   {
       *tab=alloc(rpcell);
       (*tab)->elt=prof;
       (*tab)->succ=NULL;
   }else
   {
       rpcell* newcell;
       newcell=alloc(rpcell);
       newcell->elt=prof;
       newcell->succ=*tab;
       *tab=newcell;



   }

}
//////////////////////////////////////////////////////////
//////////////affichage des donnés stockee //////////////
////////////////////////////////////////////////////////
void affichage_tab_profil(pcell* tab_profil){



	int i=0 ;
	pcell* tmp;
	tmp=tab_profil;
	while(tmp)
    {
        i++;
        printf("le profil %d \n",i);
		afficher_profil(tmp->elt);
		tmp=tmp->succ;

    }


}
void affichage_tab_auteur(acell* tab){


	int i=0 ;
	acell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("l'auteur %d \n",i);
		afficher_auteur(tmp->elt);
		tmp=tmp->succ;

    }


}
void affichage_tab_message(mcell* tab){


	int i=0 ;
	mcell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("le message %d \n",i);
		afficher_message(tmp->elt);
		tmp=tmp->succ;

    }


}
void affichage_tab_messagev2(mcell* tab){


	int i=0 ;
	mcell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("le message %d \n",i);
		afficher_messagev2(tmp->elt);
		tmp=tmp->succ;

    }


}
void affichage_tab_forum(fcell* tab){


	int i=0 ;
	fcell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("le forum %d \n",i);
		afficher_forum(tmp->elt);
		tmp=tmp->succ;

    }
}

void affichage_tab_rubrique(rcell* tab){


	int i=0 ;
	rcell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("le rubrique %d \n",i);
		afficher_rubrique(tmp->elt);
		tmp=tmp->succ;

    }


}
void affichage_tab_reponse(rpcell *tab){


	int i=0 ;
	rpcell* tmp;
	tmp=tab;
	while(tmp)
    {
        i++;
        printf("la reponse %d \n",i);
		afficher_reponse(tmp->elt);
		tmp=tmp->succ;

    }

}

////fonction pour ajouter une reponse au message //////
//////////////////////////////////////////////////////
void ajouter_reponse_msg(mcell **tab_message,char ch[])
{
    /*printf("choisir le titre de message qui vous souhaite repondre ");
    char ch[15];

    scanf("%s",ch);*/
    reponse rp;
    mcell *tmp=*tab_message;
    while(strcmp(((tmp->elt).titre), ch) != 0 && tmp)
        tmp=tmp->succ;
    rp=saisir_reponse();
    ((tmp->elt).lst_rp)[(tmp->elt).nbr_rp]=rp;
    ((tmp->elt).nbr_rp)++;

}
//////////////////////////////////////////////////////////////////////////////////////
//////////////fonction pour afficher les reponses d'un messages ////////////////////////
void afficher_reponse_msg(mcell *tab_message)
{
    char titre[15];
    printf("choisir le titre de message qui vous souhaite  afficher les reponses:\n ");
    scanf("%s",titre);
    mcell *tmp=tab_message;
    while((strcmp(((tmp->elt).titre),titre)!=0) && tmp)
        tmp=tmp->succ;
    int i ;
    for (i=0;i<((tmp->elt).nbr_rp);i++) {


        printf("la reponce %d est : \n ",i);

        afficher_reponse(((tmp->elt).lst_rp)[i]);


    }


}
////////////////////////////////////////////////////////////////////////////////
///////////fonction pour afficher les messages d'une rubrique///////////////////
void afficher_msg_rubrique(mcell *tab_message)
{
    char themee[20];
    printf("donnee le theme de rubrique que vous shouaitez afficher les messages:\n ");
    scanf("%s",themee );
    mcell *tmp=tab_message;
    while(tmp)
    {
        if (strcmp(((tmp->elt).rubrique),themee)==0 ){
            afficher_message(tmp->elt);
        }
        tmp=tmp->succ;

    }
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///////////////////////////////////////////////////////////+++++++++++++++++++++
//Ecrire un  dans un fichier
int ecrire (FILE * fp,profil m)
{

    if (fp == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un message dans le fichier


    if (fprintf(fp,"%ld\n%s\n%s\n%s\n%s\n%ld\n%d/%d/%d\n%d\n",m.num_inscrit,m.nom, m.prenom, m.adr,m.email,m.num_tele,m.date_naissance.tm_mday,m.date_naissance.tm_mon,m.date_naissance.tm_year,m.code) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }


    return 0;
}
//Ecrire une liste de message dans un fichier
void ecriref_liste_profil(FILE* fp,pcell * pr_head){

    pcell * courant = (pcell*)malloc(sizeof(pcell));
    courant=pr_head;
    while(courant!=NULL){
        ecrire(fp,courant->elt);
        courant=courant->succ;
    }
    free(courant);


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////stockage les donnes de liste chainee de rubrique dans un fichier//////////////////////////////////////////

//Ecrire un profil dans un fichier
int ecrirer(FILE * fp,rubrique m)
{

    if (fp == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un message dans le fichier


    if (fprintf(fp,"%s\n%s\n%s\n%d/%d/%d\n%s\n",m.theme,m.adr_email_animateur,m.liste_des_site,m.date_creation.tm_mday,m.date_creation.tm_mon,m.date_creation.tm_year,m.adr_int_forum) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }


    return 0;
}
//Ecrire une liste de message dans un fichier
void ecriref_liste_rubrique(FILE* fp,rcell * pr_head){

    rcell * courant = (rcell*)malloc(sizeof(rcell));
    courant=pr_head;
    while(courant!=NULL){
        ecrirer(fp,courant->elt);
        courant=courant->succ;
    }
    free(courant);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////stockage les donnes de liste chainee de forum dans un fichier//////////////////////////////////////////

//Ecrire un forum dans un fichier
int ecrirer_forum(FILE * fm,forum f)
{

    if (fm == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un message dans le fichier


    if (fprintf(fm,"%s\n%s\n",f.adr_internet,f.adr_courriel) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }


    return 0;
}
//Ecrire une liste de forum dans un fichier
void ecriref_liste_forum(FILE* fm,fcell * pr_head){

    fcell * courant = (fcell*)malloc(sizeof(fcell));
    courant=pr_head;
    while(courant!=NULL){
        ecrirer_forum(fm,courant->elt);
        courant=courant->succ;
    }
    free(courant);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////stockage les donnes de liste chainee de message dans un fichier//////////////////////////////////////////

//Ecrire un reponse  dans un fichier
int ecrirer_reponse(FILE * fm,reponse f)
{

    if (fm == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un reponse dans le fichier


    if (fprintf(fm,"%s\n%s\n%s\n%d/%d/%d\n",f.titre,f.auteur,f.text,f.date_publication.tm_mday,f.date_publication.tm_mon,f.date_publication.tm_year) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }


    return 0;
}


//Ecrire un message  dans un fichier
int ecrirer_message(FILE * fp,message m)
{
	int i;
    if (fp == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un message dans le fichier

    if (fprintf(fp,"\n%s\n%s\n%s\n%s\n%d/%d/%d\n%d\n\n",m.titre,m.auteur.pseudo,m.text,m.rubrique,m.nbr_rp,m.date_publications.tm_mday,m.date_publications.tm_mon,m.date_publications.tm_year) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }

	for(i=0;i<m.nbr_rp;i++)
	{
		ecrirer_reponse(fp,m.lst_rp[i]);
	}

    return 0;
}
//Ecrire une liste de message dans un fichier
void ecrire_liste_message(FILE* fp,mcell * pr_head){

    mcell * courant = (mcell*)malloc(sizeof(mcell));
    courant=pr_head;
    while(courant!=NULL){
    	ecrirer_message(fp,courant->elt);
        courant=courant->succ;
    }
    free(courant);


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////stockage les donnes de liste chainee d'auteur dans un fichier//////////////////////////////////////////

//Ecrire un auteur dans un fichier
int ecrira (FILE * fp,auteur m)
{

    if (fp == NULL)
    {
        fputs("Le fichier n'a pas pu être ouvert\n",stderr);
        return EXIT_FAILURE;
    }

    //Ecriture des données d'un message dans le fichier


    if (fprintf(fp,"%s\n%d/%d/%d\n%d/%d/%d\n\%ld\n%ld\n",m.pseudo,m.date_dernier_msg.tm_mday,m.date_dernier_msg.tm_mon,m.date_dernier_msg.tm_year,m.date_premier_msg.tm_mday,m.date_premier_msg.tm_mon,m.date_premier_msg.tm_year,m.nbr_msg,m.aut_profil.num_inscrit) == EOF)
    {
        fputs("Erreur lors de l'écriture dans le fichier\n",stderr);
        return EXIT_FAILURE;
    }


    return 0;
}
//Ecrire une liste de message dans un fichier
void ecriref_liste_auteur(FILE* fp,acell * pr_head){

    acell * courant = (acell*)malloc(sizeof(acell));
    courant=pr_head;
    while(courant!=NULL){
        ecrira(fp,courant->elt);
        courant=courant->succ;
    }
    free(courant);


}
////*****+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////////////////////////////////////////////////////////////
///////////////////////lecture apartir d'un fichier ////////////////////
///////////////PROFIL////////////////////////////////////
void lireProfils(pcell** tab) {
    FILE*fp = fopen("profil.txt", "r");


    // Déclaration d'une variable de type Profile
    profil m;



    // Utilisation d'une boucle pour lire chaque profil du fichier
    while (fscanf(fp, "%ld\n%s\n%s\n%[^\n]\n%s\n%ld\n%d/%d/%d\n%d\n",&m.num_inscrit,m.nom, m.prenom, m.adr,m.email,&m.num_tele,&m.date_naissance.tm_mday,&m.date_naissance.tm_mon,&m.date_naissance.tm_year,&m.code) !=EOF) {
            ajouter_profil(&(*tab),m);



    }


    fclose(fp);

}

/////////////////////////////RUBRIQUE//////////////////////////////////
void lirerubrique(rcell** tab) {
    FILE*fp = fopen("rubrique.txt", "r");


    // Déclaration d'une variable de type Profile
    rubrique m;



    // Utilisation d'une boucle pour lire chaque profil du fichier
    while (fscanf(fp, "%s\n%s\n%[^\n]\n%d/%d/%d\n%s\n",m.theme,m.adr_email_animateur,m.liste_des_site,&m.date_creation.tm_mday,&m.date_creation.tm_mon,&m.date_creation.tm_year,m.adr_int_forum)!=EOF) {
            ajouter_rubrique(&(*tab),m);




    }


    fclose(fp);

}
//////////////////////////////auteur//////////////////////////////////
void lireauteur(acell** tab,pcell* p) {
    FILE*fp = fopen("auteur.txt", "r");


    // Déclaration d'une variable de type Profile
    auteur m;



    // Utilisation d'une boucle pour lire chaque profil du fichier
    while (fscanf(fp, "%s\n%d/%d/%d\n%d/%d/%d\n\%ld\n%ld\n",m.pseudo,&m.date_dernier_msg.tm_mday,&m.date_dernier_msg.tm_mon,&m.date_dernier_msg.tm_year,&m.date_premier_msg.tm_mday,&m.date_premier_msg.tm_mon,&m.date_premier_msg.tm_year,&m.nbr_msg,&m.aut_profil.num_inscrit) != EOF) {
            while(p){
                    if(((p->elt).num_inscrit)==m.aut_profil.num_inscrit){
                            m.aut_profil=(p->elt);

                    }
                    p=p->succ;


            }
            ajouter_auteur(&(*tab),m);




    }


    fclose(fp);

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////forum//////////////////////////////////////////
void lireforum(fcell** tab) {
    FILE*fp = fopen("forum.txt", "r");


    // Déclaration d'une variable de type Profile
    forum m;



    // Utilisation d'une boucle pour lire chaque profil du fichier
    while (fscanf(fp, "%[^\n]\n%[^\n]\n",m.adr_internet,m.adr_courriel) != EOF) {
            ajouter_forum(&(*tab),m);




    }


    fclose(fp);

}
//////////////////////////////////////////////////////////////////////
///////////////////////////mesaages//////////////////////////////////
void liremessage(mcell** tab,acell* p) {
    FILE*fp = fopen("message.txt", "r");


    // Déclaration d'une variable de type Profile
    message m;



    // Utilisation d'une boucle pour lire chaque profil du fichier
    while (fscanf(fp, "\n%s\n%s\n%[^\n]\n%s\n%d/%d/%d\n%d\n\n",m.titre,m.auteur.pseudo,m.text,m.rubrique,&m.nbr_rp,&m.date_publications.tm_mday,&m.date_publications.tm_mon,&m.date_publications.tm_year) != EOF) {
            reponse r;
            for(int i=0;i<m.nbr_rp;i++){
                    if(fscanf(fp,"%s\n%s\n%[^\n]\n%d/%d/%d\n",r.titre,r.auteur,r.text,&r.date_publication.tm_mday,&r.date_publication.tm_mon,&r.date_publication.tm_year)!=EOF){
                        m.lst_rp[i]=r;
                    }




            }
             while(p){
                    if(((p->elt).pseudo)==m.auteur.pseudo){
                            m.auteur=(p->elt);

                    }
                    p=p->succ;


            }


            ajouter_message(&(*tab),m);




    }


    fclose(fp);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////fonction tri par date et affichage de messages des rubriques /////////////////
void fusion(message arr[], int l, int m, int r);
void trifussion(message arr[], int l, int r) {
    if (l < r) {
        // Trouver le point milieu pour diviser le tableau en deux moitiés
        int m = l + (r - l) / 2;

        // Appel récursif sur la première moitié
        trifussion(arr, l, m);
        // Appel récursif sur la deuxième moitié
        trifussion(arr, m + 1, r);

        // Fusionner les deux moitiés triées
        fusion(arr, l, m, r);
    }
}


void fusion(message arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Créer des tableaux temporaires
    message L[n1], R[n2];

    // Copier les données dans les tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionner les tableaux temporaires dans arr[l..r]
    i = 0; // Indexe du premier sous-tableau
    j = 0; // Indexe du deuxième sous-tableau
    k = l; // Indexe du sous-tableau fusionné
    while (i < n1 && j < n2) {
        if (comparerdates(L[i].date_publications,R[j].date_publications)<=0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copier les éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copier les éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void affichage_tri_rubrique(mcell* tab ){
    char themee[20];

    int i=0;
    printf("donnee le theme de rubrique que vous shouaitez afficher les messages:\n ");
    scanf("%s",themee );
    mcell *tmp=tab;
    message t[10];
    while(tmp)
    {
        if (strcmp(((tmp->elt).rubrique),themee)==0 ){

                t[i++]=(tmp->elt);


        }
        tmp=tmp->succ;

    }
    trifussion(t,0,i);
    for(int j=1;j<=i;j++){
        afficher_message(t[j]);
    }



}
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////reponse de reponse////////////////////////////////////
void ajouter_reponse_rp(mcell **tab_message,char titre[15],char titrerp [15])
{
    /*printf("choisir le titre de reponse qui vous souhaite repondre ");
    char ch[15];
    reponse rp;
    scanf("%s",ch);*/
    mcell *tmp=*tab_message;
    while(strcmp(((tmp->elt).titre), titre) != 0 && tmp){
             tmp=tmp->succ;

    }
    for(int i=0;i<=(tmp->elt).nbr_rp;i++){
        if(strcmp(((((tmp->elt).lst_rp)[i]).titre),titrerp)==0){
            ajouter_reponse_msg(&(*tab_message),titre);


        }
    }


}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
int recherche_message_aut(mcell* tab,char pseudoo[],int p){
    int i=0;
    while(tab ){
        if( strcmp((tab->elt).auteur.pseudo,pseudoo)==0){
                i++;
                if(p==0){
                        afficher_message((tab->elt));

                }

        }
        tab=tab->succ;
    }
     if(p==1){
            printf("le nembre totale des messages de l'auteur %s est: %d \n  ",pseudoo,i);
        }

    // dans le cas ou p =0 on utilise cette fonction pour afficher les messages d'un auteur par son pseudo
    // dans le cas ou p!=0 cette finction est utiliser pour effectuer des statistiques sur le nembre des messages d'un auteur
    return i;
}
/////////////////////////////////////////////////////////////////////////
void recherche_message_prof(mcell* tab,int id){

    while(tab ){
        if((tab->elt).auteur.aut_profil.num_inscrit==id){


                afficher_message((tab->elt));



        }
        tab=tab->succ;
    }


}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void fusiond(date arr[], int l, int m, int r);
void trifussiond(date arr[], int l, int r) {
    if (l < r) {
        // Trouver le point milieu pour diviser le tableau en deux moitiés
        int m = l + (r - l) / 2;

        // Appel récursif sur la première moitié
        trifussiond(arr, l, m);
        // Appel récursif sur la deuxième moitié
        trifussiond(arr, m + 1, r);

        // Fusionner les deux moitiés triées
        fusiond(arr, l, m, r);
    }
}


void fusiond(date arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Créer des tableaux temporaires
    date L[n1], R[n2];

    // Copier les données dans les tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionner les tableaux temporaires dans arr[l..r]
    i = 0; // Indexe du premier sous-tableau
    j = 0; // Indexe du deuxième sous-tableau
    k = l; // Indexe du sous-tableau fusionné
    while (i < n1 && j < n2) {
        if (comparerdates(L[i],R[j])<=0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copier les éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copier les éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
//---------------------------------------------------///
float stat_nbr_msg_jour(mcell* tab,char pseudo[]){

    int x=recherche_message_aut(tab,pseudo,20);//le nbr des messages d'un auteur (recherche par pseudo)
    date* t=nalloc(x,date);
    int i=0;
    while(tab)
    {
        if (strcmp(((tab->elt).auteur.pseudo),pseudo)==0 ){

                t[i++]=(tab->elt).date_publications;


        }
        tab=tab->succ;

    }
    trifussiond(t,0,x-1);
    int s=0;
    if(x<1){
        printf("x<1");
        return 0;
    }
    for(int j=1;j<=x;j++){
            s=s+abs(t[j].tm_year-t[j-1].tm_year)*365-abs(t[j].tm_mon-t[j-1].tm_mon)*30-abs(t[j].tm_mday-t[j-1].tm_mday);

    }
    return x/s;






}
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++-
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//cette fonction a pour but de determiner le date le plus frequent
date element_Plus_Frequent(date tableau[], int taille) {
    date elementCourant = tableau[0];
    int occurrenceCourante = 1;

    for (int i = 0; i < taille - 1; i++) {
        date elementActuel = tableau[i];
        int occurrenceActuelle = 1;
        /// j=i+1
        for (int j = 0; j < taille; j++) {
            if (comparerdates(tableau[j],elementActuel)==0) {
                occurrenceActuelle++;
            }
        }

        if (occurrenceActuelle>occurrenceCourante) {
            occurrenceCourante = occurrenceActuelle;
            elementCourant = elementActuel;
        }
    }

    return elementCourant;
}
//cette fonction affiche la date la plus frequente .
void stat_freq_jour(mcell* tab){
    int i=0;
    mcell* tmp=tab;
    while(tmp){
            i++;
            tmp=tmp->succ;


    }


    date* t=nalloc(i,date);
    i=0;
    while(tab)
    {
        t[i++]=(tab->elt).date_publications;
        tab=tab->succ;
    }
    date d=element_Plus_Frequent(t,i);
    afficher_date(d);









}
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////suppression////////////////////////////////////////
void supprimer_profil(pcell** tab,long int num){
    int i=0;
    pcell* tmp=*tab,*t;
    while((tmp->succ)!=NULL){
            if((tmp->elt.num_inscrit)==num){
                    if(i==0){
                        t=*tab;
                        *tab=(*tab)->succ;
                        free(t);
                        i++;

                        break;
                    }
                    if(((tmp->succ)->succ)==NULL){

                        t=tmp->succ;
                        tmp->succ=NULL;
                        free(t);
                        i++;
                        break;

                    }



        }
        if(((tmp->succ))->elt.num_inscrit==num){
            t=tmp->succ;
            tmp->succ=t->succ;
            free(t);
            i++;
            break;
        }

    i++;
    tmp=tmp->succ;
    }
    if(i==0){
            (*tab)=NULL;


    }


}



void supprimer_rubrique(rcell** tab,char th[]){
    int i=0;
    rcell* tmp=*tab,*t;
    while((tmp->succ)!=NULL){
            if(strcmp((tmp->elt.theme),th)==0){
                    if(i==0){
                        t=*tab;
                        *tab=(*tab)->succ;
                        free(tmp);
                        i++;

                        break;
                    }
                    if(((tmp->succ)->succ)==NULL){

                        t=tmp->succ;
                        tmp->succ=NULL;
                        free(t);
                        i++;
                        break;

                    }



        }
        if(strcmp(((tmp->succ)->elt.theme),th)==0){
            t=tmp->succ;
            tmp->succ=t->succ;
            free(t);
            i++;
            break;
        }
    i++;
    tmp=tmp->succ;
    }
    if(i==0){
            (*tab)=NULL;


    }


}

void supprimer_forum(fcell** tab,char th[]){
    int i=0;
    fcell* tmp=*tab,*t;
    while((tmp->succ)!=NULL){
            if(strcmp((tmp->elt.adr_internet),th)==0){
                    if(i==0){
                        t=*tab;
                        *tab=(*tab)->succ;
                        free(tmp);
                        i++;

                        break;
                    }
                    if(((tmp->succ)->succ)==NULL){

                        t=tmp->succ;
                        tmp->succ=NULL;
                        free(t);
                        i++;
                        break;

                    }



        }
        if(strcmp(((tmp->succ)->elt.adr_internet),th)==0){
            t=tmp->succ;
            tmp->succ=t->succ;
            free(t);
            i++;
            break;
        }
    i++;
    tmp=tmp->succ;
    }
    if(i==0){
            (*tab)=NULL;


    }

}
void supprimer_auteur(acell** tab,char pseudoo[]){
    int i=0;
    acell * tmp= * tab, *t;
    while((tmp->succ)!=NULL){
            if(strcmp((tmp->elt.pseudo),pseudoo)==0){
                    if(i==0){
                        t=*tab;
                        *tab=(*tab)->succ;
                        free(tmp);
                        i++;

                        break;
                    }
                    if(((tmp->succ)->succ)==NULL){

                        t=tmp->succ;
                        tmp->succ=NULL;
                        free(t);
                        i++;
                        break;

                    }



        }
        if(strcmp((tmp->succ)->elt.pseudo,pseudoo)==0){
            t=tmp->succ;
            tmp->succ=t->succ;
            free(t);
            i++;
            break;
        }
    i++;
    tmp=tmp->succ;
    }
    if(i==0){
            (*tab)=NULL;


    }

}
void supprimer_message(mcell** tab,char titree[]){
    int i=0;
    mcell * tmp=*tab,* t;
    while((tmp->succ)!=NULL){
            if(strcmp((tmp->elt.titre),titree)==0){
                    if(i==0){
                        t=*tab;
                        *tab=(*tab)->succ;
                        free(tmp);
                        i++;

                        break;
                    }
                    if(((tmp->succ)->succ)==NULL){

                        t=tmp->succ;
                        tmp->succ=NULL;
                        free(t);
                        i++;
                        break;

                    }



        }
        if(strcmp((tmp->succ)->elt.titre,titree)==0){
            t=tmp->succ;
            tmp->succ=t->succ;
            free(t);
            i++;
            break;
        }
    i++;
    tmp=tmp->succ;
    }
    if(i==0){
            (*tab)=NULL;


    }

}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int nbr_msg_par_rubrique(mcell * tab,char theme[]){
    mcell* tmp=tab;
    int i=0;
    while(tmp){
        if(strcmp(tmp->elt.rubrique,theme)==0){
            i++;

        }
        tmp=tmp->succ;
    }
    return i;
}
///////////////////////////////////////////////////////////////////////////
///////////////////////modifications//////////////////////////////////////
void modifier_profil(pcell** tab,long int id){
    pcell* tmp=*tab;
    while(tmp && (tmp->elt.num_inscrit)!=id)
        tmp=tmp->succ;
    tmp->elt=saisir_profil();

}
void modifier_rubrique(rcell** tab,char id[]){
    rcell* tmp=*tab;
    while(tmp && strcmp((tmp->elt.theme),id)!=0)
        tmp=tmp->succ;
    tmp->elt=saisir_rubrique();

}
void modifier_forum(fcell** tab,char id[]){
    fcell* tmp=*tab;
    while(tmp && strcmp((tmp->elt.adr_internet),id)!=0)
        tmp=tmp->succ;
    tmp->elt=saisir_forum();

}
void modifier_auteur(acell** tab,char id[],pcell** tp){
    acell* tmp=*tab;
    while(tmp && strcmp((tmp->elt.pseudo),id)!=0)
        tmp=tmp->succ;
    tmp->elt=saisir_auteur(&(*tp));

}
void modifier_message(mcell** tab,char id[]){
    mcell* tmp=*tab;
    while(tmp && strcmp((tmp->elt.titre),id)!=0)
        tmp=tmp->succ;
    //tu ne peut modifier que le text pour ne pas perdre les messages
    printf(" saisir le text:\n ");
    scanf("%s",tmp->elt.text);

}
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//fonction de recherche de mot dans un text de message
int recherche_mot(mcell* tab,char titree[],char mot[]){
    mcell *tmp=tab;
    while(tmp && (strcmp((tmp->elt).titre,titree)!=0)){
    tmp=tmp->succ;

    }
    int longueurChaine = strlen(tmp->elt.text);
    int longueurMot = strlen(mot);
    int i;
    for (i = 0; i <= longueurChaine - longueurMot; ++i) {
            int j;
            for (j = 0; j < longueurMot; ++j) {
                if ((tmp->elt.text)[i + j] != mot[j]) {
                    break;
                }
            }

        if (j == longueurMot) {
            // Le mot a été trouvé
            printf("le texte contient le mot %s a la position %d ",mot,i);
            return 0;

        }
    }

    // Le mot n'a pas été trouvé
    if (i == longueurChaine - longueurMot){
            printf("le texte ne contient le mot %s  ",mot);
            return 0;


    }

}
////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void affichage_profil_rubrique(mcell* tab,char themee[]){
    mcell* tmp =tab;
    while(tmp){
            if(strcmp(tmp->elt.rubrique,themee)==0){
                afficher_profil(tmp->elt.auteur.aut_profil);
            }
            tmp=tmp->succ;

    }
}
///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void afficher_mesg_jour(mcell*tab ,date dt){
    mcell * tmp=tab;
    while(tmp){
        if(comparerdates((tmp->elt).date_publications,dt)==0){
        afficher_message(tmp->elt);
        }
    tmp=tmp->succ;
    }
}
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
float taille_moyenne_msg(mcell* tab){
    mcell* tmp =tab;
    int s=0,i=0;
    while(tmp){
        s+=strlen(tmp->elt.text);
        i++;
        tmp=tmp->succ;
    }
    return s/i;

}







///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int main() {

    int menu;
    int sw=1;
    profil p ;
    pcell *tab_profil;
    auteur a;
	acell *tab_auteur;
    reponse rp;
    rpcell* tab_reponse;
    message m;
    mcell* tab_message;
    forum f;
    fcell* tab_forum;
    rubrique r;
    rcell* tab_rubrique;
	printf("						+------------------+\n");
	printf("						|    mini-projet   |\n");
    printf("						+------------------+\n\n");
    lireProfils(&tab_profil);
    lirerubrique(&tab_rubrique);
    lireauteur(&tab_auteur,tab_profil);
    lireforum(&tab_forum);
    liremessage(&tab_message,tab_auteur);


    do {

        printf("\n*************************************************Menu Principal************************************\n\n");
        printf("1>>  Saisir un profil.\n\n");
        printf("2>>  saisir un auteur.\n\n");
        printf("3>>  Saisir une reponse. \n\n");
        printf("7>>  Saisir un message.\n\n");
        printf("9>>  Saisir un forum.\n\n");
        printf("11>> saisir rubrique. \n\n");
        printf("----------------------------------\n");
		printf("4>>  Afficher les profils. \n\n");
        printf("5>>  Afficher les auteurs.\n\n");
        printf("6>>  Afficher les reponses pour un message donne.\n \n");
        printf("8>>  Afficher les messages. \n\n");
        printf("10>> Afficher les forums.\n\n");
        printf("12>> Afficher les rubriques.\n\n");
        printf("13>> Afficher les messages d'une rubrique.\n\n");
        printf("14>> Afficher les messages de rubrique triee \n\n ");
        printf("15>> Afficher les messages d'un auteur par son pseudo.\n\n");
        printf("16>> Afficher les messages d'un auteur par son numero d'inscription.\n\n\n");
        printf("-----------------------------------\n\n");
        printf("17>> Effecutuer des statistiques.\n\n\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("18>> Supprimer profil.\n\n");
        printf("19>> Supprimer rubrique.\n\n");
        printf("20>> Supprimer forum.\n\n");
        printf("21>> Supprimer message.\n\n");
        printf("22>> Supprimer auteur.\n\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("23>> Modifier profil.\n\n");
        printf("24>> Modifier rubrique.\n\n");
        printf("25>> Modifier forum.\n\n");
        printf("26>> Modifier message.\n\n");
        printf("27>> Modifier auteur.\n\n");
        printf("------------------------------------------------------------------------------\n");
        printf("28>> Recherche d'une mot dans un texte de message\n\n");
        printf("29>> Profil des persones qui postent dans une rubrique donne\n\n ");
        printf("30>> Afficher les messages d'un jour donnee\n\n ");

        printf("0>>  Quitter.\n\n");
        printf("Choisir  :\n ");
        printf("-----------------------------------------------------------------------------------------------\n");
        scanf("%d", &menu);





        switch (menu) {
        	case 0 :
        		printf("vous avez quittez \n");
        		break;
        	case 1 :
				p=saisir_profil ();
        		ajouter_profil(&tab_profil,p);


                break;

        	case 2 :
        		a=saisir_auteur(&tab_profil);
        		ajouter_auteur(&tab_auteur,a) ;


        		break ;
        	case 3 :
        	    printf("veillez vous repondre a un message saisit 1\n");
        	    printf("veillez vous repondre a une reponse saisit 0\n");
        	    int x;
        	    scanf("%d",&x);
        	    switch(x){
                case 1:
                    ;
                    char ch[15];
                    affichage_tab_message(tab_message);
                    printf("choisir le titre de message qui vous souhaite repondre ");
                    fflush(stdin);
                    scanf("%s",ch);
                    ajouter_reponse_msg(&tab_message,ch);
                    break;
                case 0:
                    ;
                    char titre[15],titrerp[15];
                    affichage_tab_messagev2(tab_message);
                    fflush(stdin);
                    printf("saisr le titre de message de reponse  que vous souhaitez repondre\n");
                    gets(titre);
                    fflush(stdin);
                    printf("saisr le titre de reponse  que vous souhaitez repondre\n");
                    gets(titrerp);
                    ajouter_reponse_rp(&tab_message,titre,titrerp);
                    break;



        	    }

        		break;

        	case 4 :
        		affichage_tab_profil(tab_profil);
        		break;

        	case 5 :

        		affichage_tab_auteur(tab_auteur);
        		break;

        	case 6 :
        	    affichage_tab_message(tab_message);
        		afficher_reponse_msg(tab_message);
        		break;

        	case 7 :
        		m =saisir_message(&tab_auteur,&tab_profil);
        		ajouter_message(&tab_message,m);

        		break;

        	case 8 :
        		printf("les messages stocke  :\n");
        		affichage_tab_message(tab_message);
        		break;

        	case 9 :

        		f=saisir_forum();
        		ajouter_forum(&tab_forum,f);


                break;
        	case 10 :
        		affichage_tab_forum(tab_forum);
        		break;

        	case 11 :
        		r = saisir_rubrique();
        		ajouter_rubrique(&tab_rubrique,r);


                break;


        	case 12 :
        		affichage_tab_rubrique(tab_rubrique);
        		break;
            case 13:
                affichage_tab_rubrique(tab_rubrique);
                afficher_msg_rubrique(tab_message);
                break;
            case 14:
                printf("voici les rubriques existantes :\n");
                affichage_tab_rubrique(tab_rubrique);
                printf("////////////////\n");

                affichage_tri_rubrique(tab_message);

                break;
            case 15:
                fflush(stdout);
                affichage_tab_auteur(tab_auteur);
                printf("donner le pseudo de l'auteur qui vous voullez afficher les messages:\n ");
                char ch [20];
                fflush(stdin);
                gets(ch);
                recherche_message_aut(tab_message,ch,0);
                break;
            case 16 :
                affichage_tab_profil(tab_profil);
                printf("saisir le numero d'inscription de profil \n");
                int id;
                scanf("%d",&id);
                recherche_message_prof(tab_message,id);

                break;
            case 17:
                printf("1>> le nombre de messages postés par jour et en moyenne par un même auteur.\n\n");
                printf("2>> le nombre de messages d'un même auteur.\n\n");
                printf("3>> la date la plus frequente est.\n\n");
                printf("4>> afficher le nbr de messages par rubrique\n\n");
                printf("5>> Afficher la taille moyenne des textes\n\n ");

                printf("choisir\n");
                int choix;
                scanf("%d",&choix);
                switch(choix){
                    case 1:
                        affichage_tab_auteur(tab_auteur);
                        printf("choisir le pseudo ");
                        char raed[20];
                        fflush(stdin);
                        gets(raed);
                        printf(" le nombre de messages postés par jour et en moyenne par %s.%f\n",raed,stat_nbr_msg_jour(tab_message,raed));
                        break;
                    case 2:
                        affichage_tab_auteur(tab_auteur);
                        printf("choisir le pseudo ;\n");
                        char ahmed[20];
                        fflush(stdin);
                        gets(ahmed);
                        recherche_message_aut(tab_message,ahmed,1);
                        break;
                    case 3:
                        stat_freq_jour(tab_message);
                        break;
                    case 4:
                        affichage_tab_rubrique(tab_rubrique);
                        printf("saisir le theme de rubrique:\n  ");
                        char o[20];
                        fflush(stdin);
                        scanf("%s",o);
                        printf("le nbr de messages par rubrique donne est:%d\n",nbr_msg_par_rubrique(tab_message,o));
                        break;
                    case 5:
                        ;
                        float enit=taille_moyenne_msg(tab_message);
                        printf(" la taille moyenne des text est:%f\n",enit);
                        break;




                }
                break;
            case 18 :
                affichage_tab_profil(tab_profil);
                printf("choisir le num d'inscription de profil a supprimer \n");
                long int par;
                scanf("%ld",&par);
                supprimer_profil(&tab_profil,par);
                break;
            case 19 :
                affichage_tab_rubrique(tab_rubrique);
                printf("choisir le theme de rubrique a supprimer\n ");
                char chv[20];
                fflush(stdin);
                gets(chv);
                supprimer_rubrique(&tab_rubrique,chv);
                break;
            case 20 :
                affichage_tab_forum(tab_forum);
                printf("choisir l'addresse internet de forum a supprimer\n ");
                char chvv[64];
                fflush(stdin);
                gets(chvv);
                supprimer_forum(&tab_forum,chvv);
                break;
            case 21 :
                affichage_tab_message(tab_message);
                printf("choisir le titre de message a supprimer \n");
                char chp[64];
                fflush(stdin);
                gets(chp);
                supprimer_message(&tab_message,chp);

                break;
            case 22 :
                affichage_tab_auteur(tab_auteur);
                printf("choisir le pseudo de l'auteur a supprimer\n ");
                char chrr[20];
                fflush(stdin);
                gets(chrr);
                supprimer_auteur(&tab_auteur,chrr);
                break;
            case 23:
                affichage_tab_profil(tab_profil);
                printf("saisir le num d'inscription de profil a modifier\n ");
                long int nn;
                scanf("%ld",&nn);
                modifier_profil(&tab_profil,nn);
                break;
            case 24:
                affichage_tab_rubrique(tab_rubrique);
                printf("saisir le theme de rubrique a modifier\n ");
                char nnn[20];
                fflush(stdin);
                gets(nnn);
                modifier_rubrique(&tab_rubrique,nnn);

                break;
            case 25:
                affichage_tab_forum(tab_forum);
                printf("saisir l'adr internet de forum a modifier \n");
                char uu[65];
                fflush(stdin);
                gets(uu);
                modifier_forum(&tab_forum,uu);


                break;
            case 26:
                affichage_tab_message(tab_message);
                printf("saisir le titre de message a modifier\n ");
                char unu[20];
                fflush(stdin);
                gets(unu);
                modifier_message(&tab_message,unu);

                break;
            case 27:
                affichage_tab_auteur(tab_auteur);
                printf("saisir le pseudo de l'auteur a modifier \n");
                char oop[20];
                fflush(stdin);
                gets(oop);
                modifier_auteur(&tab_auteur,oop,&tab_profil);

                break;
            case 28:
                affichage_tab_message(tab_message);
                printf("saisir le titre de message \n ");
                char oopp[20];
                fflush(stdin);
                gets(oopp);
                printf("saisir le mot :\n ");
                char mot[20];
                fflush(stdin);
                gets(mot);
                recherche_mot(tab_message,oopp,mot);
                break;
            case 29:
                affichage_tab_rubrique(tab_rubrique);
                printf("saisir le theme de rubrique\n  ");
                char caynwa[20];
                fflush(stdin);
                gets(caynwa);
                affichage_profil_rubrique(tab_message,caynwa);

               break;
            case 30:
                printf("Saisir le date que jour que vous allez afficher les message\n ");
                date datee;
                datee=saisirdate();
                afficher_mesg_jour(tab_message,datee);
                break;
        	default:
                printf("Choix invalide. Veuillez réessayer.\n");
		}


    } while (menu != 0);
   FILE *fp= fopen("profil.txt","w");
         ecriref_liste_profil(fp,tab_profil);
          if (fclose(fp) == EOF){
                printf("Erreur lors de la fermeture du flux\n");
                return EXIT_FAILURE;}
  FILE *fpa = fopen("auteur.txt","w");
         ecriref_liste_auteur(fpa,tab_auteur);
          if (fclose(fpa) == EOF){
                 printf("Erreur lors de la fermeture du flux\n");
                 return EXIT_FAILURE;}
  FILE *fme =fopen("message.txt","w");
         ecrire_liste_message(fme,tab_message);
          if (fclose(fme) == EOF){
                 printf("Erreur lors de la fermeture du flux\n");
                 return EXIT_FAILURE;

          }
  FILE *fm = fopen("forum.txt","w");
         ecriref_liste_forum(fm,tab_forum);

                if (fclose(fm) == EOF)
                    {
                        printf("Erreur lors de la fermeture du flux\n");
                        return EXIT_FAILURE;
					}
  FILE *fpr = fopen("rubrique.txt","w");
        		ecriref_liste_rubrique(fpr,tab_rubrique);
        		 if (fclose(fpr) == EOF)
                    {
                        printf("Erreur lors de la fermeture du flux\n");
                        return EXIT_FAILURE;
                    }



    return 0;
}
