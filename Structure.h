
#include<stdio.h>
#include<time.h>


typedef struct
{
    char adr_internet[64];
    char adr_courriel[266];

}forum;

typedef struct tm  date;
typedef struct
{   long int num_inscrit;
    char nom[20];
    char prenom[15];
    char adr[100];
    date date_naissance;
    char email[64];
    long int num_tele;
    int code;
}profil;



typedef struct
{
    char theme[20];
    date date_creation;
    char adr_email_animateur[266];
    char liste_des_site[266];
    char adr_int_forum[64];

}rubrique;

typedef struct
{
	char pseudo[20];
	date date_premier_msg;
	date date_dernier_msg;
    long int nbr_msg;
    profil aut_profil;
}auteur;
typedef struct
{
   char titre[15];
    char auteur[20];
	char text[266];
	date date_publication ;

}reponse;


typedef struct
{
	char titre[15];
    auteur auteur;
	char text[266];//dynamique
	date date_publications;
    reponse lst_rp[100];//dynamique
    int nbr_rp;
    char rubrique[20];

} message;

typedef struct scell
{
    profil elt;
    struct scell* succ;
}pcell;
typedef struct aut
{
    auteur elt;
    struct aut* succ;
}acell;
typedef struct rb
{
    rubrique elt;
    struct rb* succ;
}rcell;
typedef struct rpe
{
    reponse elt;
    struct rpe* succ;
}rpcell;
typedef struct msgg
{
    message elt;
    struct msgg* succ;
}mcell;
typedef struct frm
{
    forum elt;
    struct frm* succ;
}fcell;
