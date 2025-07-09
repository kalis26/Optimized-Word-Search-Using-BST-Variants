/**--------------------------------------------------------**/
/**       C o n v e r s i o n   Z vers C (Standard)        **/
/**             Realisee par Pr D.E ZEGOUR                 **/
/**             E S I - Alger                              **/
/**             Copywrite 2014                             **/
/**--------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef int bool;
typedef char *string255;
typedef char *string2;

#define True 1
#define False 0

/** Terminal **/

#define RED 12	 // Code pour la couleur rouge (Terminal)
#define GRAY 8	 // Code pour la couleur grise
#define BLUE 9	 // Code pour la couleur bleue
#define GREEN 10 // Code pour la couleur verte
#define WHITE 15 // Code pour la couleur blanche
#define CYAN 11	 // Code pour la couleur cyan

/* Renitialiser l'ecran */

void clearScreen()
{
	system("cls");
}

void setColor(int ForgeC)
{ // Choisir la couleur du texte affiché
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, ForgeC);
}

/** Implementation **\: FICHIER **/

/* Traitement des fichiers ouverts */

struct _Noeud
{
	FILE *Var_fich;
	char *Nom_fich;
	int Sauv_pos;
	struct _Noeud *Suiv;
};

typedef struct _Noeud *_Ptr_Noeud;

_Ptr_Noeud _Pile_ouverts = NULL;

/* Teste si un fichier est ouvert */
_Ptr_Noeud _Ouvert(char *Fp)
{
	_Ptr_Noeud P;
	bool Trouv;
	P = _Pile_ouverts;
	Trouv = False;
	while ((P != NULL) && !Trouv)
		if (strcmp(P->Nom_fich, Fp) == 0)
			Trouv = True;
		else
			P = P->Suiv;
	return P;
}

/* Ajouter un fichier ouvert */
void _Empiler_ouvert(char *Fp, FILE *Fl)
{
	_Ptr_Noeud P;
	P = (_Ptr_Noeud)malloc(sizeof(struct _Noeud));
	P->Nom_fich = Fp;
	P->Var_fich = Fl;
	P->Suiv = _Pile_ouverts;
	_Pile_ouverts = P;
}

/* Supprimer un fichier ouvert et rendre son nom*/
char *_Depiler_ouvert(FILE *Fl)
{
	char *Fp = malloc(100);
	_Ptr_Noeud P, Prec;
	P = _Pile_ouverts;
	Prec = NULL;
	while (P->Var_fich != Fl)
	{
		Prec = P;
		P = P->Suiv;
	}
	strcpy(Fp, P->Nom_fich);
	if (Prec != NULL)
		Prec->Suiv = P->Suiv;
	else
		_Pile_ouverts = P->Suiv;
	free(P);
	return Fp;
}

/** Fichiers **/

typedef char _Tx[255];
typedef string255 Typestruct1_s;
typedef _Tx Typestruct1_s_Buf;

/** Machine abstaite sur les fichiers **/

void Ouvrir_s(FILE **s, char *Fp, char *Mode)
{
	_Ptr_Noeud P = _Ouvert(Fp);
	if (P != NULL)
	/* Le fichier est deja ouvert */
	{
		P->Sauv_pos = ftell(P->Var_fich);
		fclose(P->Var_fich);
	}
	/* Le fichier est non ouvert */
	if (strcmp(Mode, "A") == 0)
		*s = fopen(Fp, "r+b");
	else
		*s = fopen(Fp, "w+b");
	_Empiler_ouvert(Fp, *s);
}

void Fermer_s(FILE *s)
{
	char *Fp = malloc(100);
	_Ptr_Noeud P;
	strcpy(Fp, _Depiler_ouvert(s));
	fclose(s);
	/* Ya-til un fichier ouvert avec le m�me nom ?  */
	/* Si Oui, le Reouvrir a la position sauvegardee */
	P = _Ouvert(Fp);
	if (P != NULL)
	{
		s = fopen(P->Nom_fich, "r+b");
		fseek(s, P->Sauv_pos, 0);
	}
}

void Ecrireseq_s(FILE *s, Typestruct1_s Buf)
{
	Typestruct1_s_Buf Buffer;
	int I, J;
	for (J = 0; J <= strlen(Buf); ++J)
		Buffer[J] = Buf[J];
	fwrite(&Buffer, sizeof(Typestruct1_s_Buf), 1, s);
}

void Ecriredir_s(FILE *s, Typestruct1_s Buf, int N)
{
	Typestruct1_s_Buf Buffer;
	int I, J;
	for (J = 0; J <= strlen(Buf); ++J)
		Buffer[J] = Buf[J];
	fseek(s, (long)(N - 1) * sizeof(Typestruct1_s_Buf), 0);
	fwrite(&Buffer, sizeof(Typestruct1_s_Buf), 1, s);
}

void Lireseq_s(FILE *s, Typestruct1_s Buf)
{
	Typestruct1_s_Buf Buffer;
	int I, J;
	if (fread(&Buffer, sizeof(Typestruct1_s_Buf), 1, s) != 0)
	{
		for (J = 0; J <= strlen(Buffer); ++J)
			Buf[J] = Buffer[J];
	}
}

void Liredir_s(FILE *s, Typestruct1_s Buf, int N)
{
	Typestruct1_s_Buf Buffer;
	int I, J;
	fseek(s, (long)(N - 1) * sizeof(Typestruct1_s_Buf), 0);
	fread(&Buffer, sizeof(Typestruct1_s_Buf), 1, s);
	for (J = 0; J <= strlen(Buffer); ++J)
		Buf[J] = Buffer[J];
}

void Rajouter_s(FILE *s, Typestruct1_s Buf)
{
	Typestruct1_s_Buf Buffer;
	int I, J;
	for (J = 0; J <= strlen(Buf); ++J)
		Buffer[J] = Buf[J];
	fseek(s, 0, 2); /* Fin du fichier */
	fwrite(&Buffer, sizeof(Typestruct1_s_Buf), 1, s);
}

bool Finfich_s(FILE *s)
{
	long K = ftell(s);
	fseek(s, 0, 2);		/* Fin du fichier */
	long K2 = ftell(s); /* position a partir du debut */
	if (K == K2)
	{
		fseek(s, K, 0);
		return 1;
	}
	else
	{
		fseek(s, K, 0);
		return 0;
	}
}

int Alloc_bloc_s(FILE *s)
{
	long K;
	fseek(s, 0, 2); /* Fin du fichier */
	K = ftell(s);	/* position a partir du debut */
	K = K / sizeof(Typestruct1_s_Buf);
	K++;
	return (K);
}

/** Implementation **\: ARBRE BINAIRE DE CHAINES DE CARACTERES**/

/** Arbres de recherche binaire **/

typedef string255 Typeelem_As;
typedef struct Noeud_As *Pointeur_As;

struct Noeud_As
{
	Typeelem_As Val;
	Pointeur_As Fg;
	Pointeur_As Fd;
	Pointeur_As Pere;
};

Typeelem_As Info_As(Pointeur_As P)
{
	return P->Val;
}

Pointeur_As Fg_As(Pointeur_As P)
{
	return P->Fg;
}

Pointeur_As Fd_As(Pointeur_As P)
{
	return P->Fd;
}

Pointeur_As Pere_As(Pointeur_As P)
{
	return P->Pere;
}

void Aff_info_As(Pointeur_As P, Typeelem_As Val)
{
	strcpy(P->Val, Val);
}

void Aff_fg_As(Pointeur_As P, Pointeur_As Q)
{
	P->Fg = Q;
}

void Aff_fd_As(Pointeur_As P, Pointeur_As Q)
{
	P->Fd = Q;
}

void Aff_pere_As(Pointeur_As P, Pointeur_As Q)
{
	P->Pere = Q;
}

void Creernoeud_As(Pointeur_As *P)
{
	*P = (struct Noeud_As *)malloc(sizeof(struct Noeud_As));
	(*P)->Val = malloc(255 * sizeof(string255));
	(*P)->Fg = NULL;
	(*P)->Fd = NULL;
	(*P)->Pere = NULL;
}

void Liberernoeud_As(Pointeur_As P)
{
	free(P);
}

/** Implementation **\: FILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
/** Files d'attente **/

typedef Pointeur_As Typeelem_FAs;
typedef struct Filedattente_FAs *Pointeur_FAs;
typedef struct Maillon_FAs *Ptliste_FAs;

struct Maillon_FAs
{
	Typeelem_FAs Val;
	Ptliste_FAs Suiv;
};

struct Filedattente_FAs
{
	Ptliste_FAs Tete, Queue;
};

void Creerfile_FAs(Pointeur_FAs *Fil)
{
	*Fil = (struct Filedattente_FAs *)malloc(sizeof(struct Filedattente_FAs));
	(*Fil)->Tete = NULL;
	(*Fil)->Queue = NULL;
}

bool Filevide_FAs(Pointeur_FAs Fil)
{
	return Fil->Tete == NULL;
}

void Enfiler_FAs(Pointeur_FAs Fil, Typeelem_FAs Val)
{
	Ptliste_FAs Q;

	Q = (struct Maillon_FAs *)malloc(sizeof(struct Maillon_FAs));
	Q->Val = Val;
	Q->Suiv = NULL;
	if (!Filevide_FAs(Fil))
		Fil->Queue->Suiv = Q;
	else
		Fil->Tete = Q;
	Fil->Queue = Q;
}

void Defiler_FAs(Pointeur_FAs Fil, Typeelem_FAs *Val)
{
	if (!Filevide_FAs(Fil))
	{
		*Val = Fil->Tete->Val;
		Fil->Tete = Fil->Tete->Suiv;
	}
	else
		printf("%s \n", "File d'attente vide");
}

typedef struct
{
	string255 Mot1;
	string255 Mot2;
} Intervalle;

/** Variables du programme principal **/
int Nombremots;
int Prof;
int Nombremotspec;
int Choix1;
int Choix2;
int Choix3;
int M;
int Searchlength;
int Total_search_success_BST0;
int Total_search_success_Triplet;
int Total_search_fail_BST0;
int Total_search_fail_Triplet;
int Total_search_all_BST0;
int Total_search_all_Triplet;
int Total_range_BST0;
int Total_range_Triplet;
string255 X;
string255 Y;
string255 Z;
string255 Motarech;
string255 Mot1;
string255 Mot2;
FILE *F1;
Typestruct1_s Bf1;
FILE *F2;
Typestruct1_s Bf2;
Pointeur_As Bst0 = NULL;
Pointeur_As Bst1 = NULL;
Pointeur_As Bst2 = NULL;
Pointeur_As Bst3 = NULL;
Pointeur_As Resultat = NULL;
bool Ver1;
bool Ver2;
bool Ver3;
bool Quitter1;
bool Quitter2;
bool Quitter3;

/** Fonctions standards **/

int Aleanombre(int N)
{
	return (rand() % N);
}

char *Aleachaine(int N)
{
	int k;
	char *Chaine = malloc(N + 1);

	char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
	char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (k = 0; k < N; k++)
		switch (rand() % 2)
		{
		case 0:
			*(Chaine + k) = Chr1[rand() % 26];
			break;
		case 1:
			*(Chaine + k) = Chr2[rand() % 26];
			break;
		}
	Chaine[k] = '\0';

	return (Chaine);
}

char *Caract(string255 Ch, int I)
{
	char *s = malloc(2);
	s[0] = Ch[I - 1];
	s[1] = '\0';
	return s;
}

int Max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

/** Prototypes des fonctions **/

void Generer_mot(string255 *Ch, string255 *X, string255 *Y, string255 *Z);
void Generer_fichier(int *N, string255 *X, string255 *Y, string255 *Z);
void Creer_bst1(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z);
void Creer_bst2(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z);
void Creer_bst3(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z);
int Profondeur(Pointeur_As *P);
void Inordre(Pointeur_As *P);
void Compte_mots(Pointeur_As *P, int *C, string255 *X, string255 *Y, string255 *Z);
void Compte_mots_par_niv(Pointeur_As *P, string255 *X, string255 *Y, string255 *Z);
void Inserer_bst(Pointeur_As *P, Pointeur_As *Q);
void Rotation_gauche(Pointeur_As *P);
void Rotation_droite(Pointeur_As *P);
void Rotation_bst(Pointeur_As *P);
void Recherche(string255 *V, Pointeur_As *P, Pointeur_As *R, int *Searchlength);
void Recherche_bst(string255 *V, Pointeur_As *A, int *Mode, Pointeur_As *P, string255 *X, string255 *Y, string255 *Z, int *Searchlength);
bool Recherche_triplet(string255 *Word, string255 *X, string255 *Y, string255 *Z, int *Searchlength);
Pointeur_As Prochain_inordre(Pointeur_As *P, int *Searchlength);
void Recherche_intervalle(string255 *Mot1, string255 *Mot2, Pointeur_As *Arbre, int *Searchlength, int check);
void Recherche_intervalle_triplet(string255 *X, string255 *Y, string255 *Z, int *Searchlength, int check);
void Creer_bst0(Pointeur_As *P, int *N);
void Generer_fichier_sim(int *N, string255 *X, string255 *Y, string255 *Z, char *Fich);
void Generer_fichier_range_sim(int *N, string255 *X, string255 *Y, string255 *Z);
void Recherche_intervalle_triplet_sim(string255 *Mot1, string255 *Mot2, string255 *X, string255 *Y, string255 *Z, int *Searchlength, int check);

/************************************************************/
void Generer_mot(string255 *Ch, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	int I;
	string255 _Sx;

	/** Corps du module **/
	_Sx = malloc(255 * sizeof(char));
	I = Aleanombre(10);
	if (I == 0)
	{
		strcpy(_Sx, *X);
		strcpy(*Ch, strcat(_Sx, Aleachaine(Aleanombre(5) + 3)));
	}
	else
	{
		if (I == 1)
		{
			strcpy(_Sx, *Y);
			strcpy(*Ch, strcat(_Sx, Aleachaine(Aleanombre(5) + 3)));
		}
		else
		{
			if (I == 2)
			{
				strcpy(_Sx, *Z);
				strcpy(*Ch, strcat(_Sx, Aleachaine(Aleanombre(5) + 3)));
			}
			else
			{
				strcpy(*Ch, Aleachaine(Aleanombre(5) + 3));
			};
		};
	};
	free(_Sx);
}
/************************************************************/
void Generer_fichier(int *N, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	int I;
	bool Ver;

	/** Corps du module **/
	printf(" %s", "\n Entrez le nombre de mots a generer: ");
	do
	{
		scanf(" %d", &*N);
		if (*N < 100)
		{
			printf("\n Veuillez entrer un nombre de mots superieur ou egal a 100: ");
		}
	} while (*N < 100);
	printf(" %s", "\n Choisissez les lettres cibles X, Y et Z.");
	setColor(BLUE);
	printf(" %s", "\n X = ");
	setColor(WHITE);
	scanf(" %[^\n]", *X);
	Ver = False;
	setColor(BLUE);
	printf(" %s", "Y = ");
	setColor(WHITE);
	while ((!Ver))
	{
		scanf(" %[^\n]", *Y);
		if (strcmp(*Y, *X) == 0)
		{
			printf(" %s", "\n Choisissez des lettres differentes: ");
		}
		else
		{
			Ver = True;
		};
	};
	Ver = False;
	setColor(BLUE);
	printf(" %s", "Z = ");
	setColor(WHITE);
	while ((!Ver))
	{
		scanf(" %[^\n]", *Z);
		if ((strcmp(*Z, *X) == 0) || (strcmp(*Z, *Y) == 0))
		{
			printf(" %s", "\n Choisissez des lettres differentes: ");
		}
		else
		{
			Ver = True;
		};
	};
	Ouvrir_s(&F1, "F.z", "N");
	for (I = 1; I <= *N; ++I)
	{
		Generer_mot(&Bf1, &*X, &*Y, &*Z);
		Ecrireseq_s(F1, Bf1);
	};
	Fermer_s(F1);
}
/************************************************************/
void Creer_bst1(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	int I;
	string2 Debutstring;

	/** Corps du module **/
	Debutstring = malloc(2 * sizeof(char));
	Ouvrir_s(&F1, "F.z", "A");
	for (I = 1; I <= *N; ++I)
	{
		Liredir_s(F1, Bf1, I);
		Recherche(&Bf1, &*P, &Q, NULL);
		if (Q == NULL)
		{
			Creernoeud_As(&Q);
			Aff_info_As(Q, Bf1);
			Inserer_bst(&*P, &Q);
			strcpy(Debutstring, Caract(Info_As(Q), 1));
			if ((strcmp(Debutstring, *X) == 0) || (strcmp(Debutstring, *Y) == 0) || (strcmp(Debutstring, *Z) == 0))
			{
				while ((Pere_As(Q) != NULL))
				{
					Rotation_bst(&Q);
				};
				*P = Q;
			};
		};
	};
	Fermer_s(F1);
	free(Debutstring);
}
/************************************************************/
void Creer_bst2(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	Pointeur_As Qtemp = NULL;
	int I;
	int Compteur;
	int J;
	string2 Debutstring;

	/** Corps du module **/
	Debutstring = malloc(2 * sizeof(char));
	Ouvrir_s(&F1, "F.z", "A");
	for (I = 1; I <= *N; ++I)
	{
		Liredir_s(F1, Bf1, I);
		Recherche(&Bf1, &*P, &Q, NULL);
		if (Q == NULL)
		{
			Creernoeud_As(&Q);
			Aff_info_As(Q, Bf1);
			Inserer_bst(&*P, &Q);
			strcpy(Debutstring, Caract(Info_As(Q), 1));
			if ((strcmp(Debutstring, *X) == 0) || (strcmp(Debutstring, *Y) == 0) || (strcmp(Debutstring, *Z) == 0))
			{
				Qtemp = Q;
				Compteur = 0;
				while ((Pere_As(Qtemp) != NULL))
				{
					Qtemp = Pere_As(Qtemp);
					Compteur = Compteur + 1;
				};
				if (Compteur >= 2)
				{
					int J = 1;
					bool Finrot = False;
					while (J <= (Compteur / 2) && !Finrot)
					{
						if (Pere_As(Q) != NULL)
						{
							if ((Caract(Info_As(Pere_As(Q)), 1) > *X) || (Caract(Info_As(Pere_As(Q)), 1) > *Y) || (Caract(Info_As(Pere_As(Q)), 1) > *Z))
							{
								Finrot = True;
							}
						};
						if (!Finrot)
						{
							Rotation_bst(&Q);
						}
						J++;
					}
					if (Pere_As(Q) == NULL)
					{
						*P = Q;
					};
				};
			}
			else if ((strcmp(Debutstring, *X) > 0) || (strcmp(Debutstring, *Y) > 0) || (strcmp(Debutstring, *Z) > 0))
			{
				while ((Pere_As(Q) != NULL))
				{
					Rotation_bst(&Q);
				};
				*P = Q;
			}
		};
	};
	Fermer_s(F1);
	free(Debutstring);
}
/************************************************************/
void Creer_bst3(Pointeur_As *P, int *N, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	int I;
	string2 Debutstring;

	/** Corps du module **/
	Debutstring = malloc(2 * sizeof(char));
	Ouvrir_s(&F1, "F.z", "A");
	for (I = 1; I <= *N; ++I)
	{
		Liredir_s(F1, Bf1, I);
		Recherche(&Bf1, &*P, &Q, NULL);
		if (Q == NULL)
		{
			Creernoeud_As(&Q);
			Aff_info_As(Q, Bf1);
			Inserer_bst(&*P, &Q);
			strcpy(Debutstring, Caract(Info_As(Q), 1));
			if ((strcmp(Debutstring, *X) != 0) && (strcmp(Debutstring, *Y) != 0) && (strcmp(Debutstring, *Z) != 0))
			{
				while ((Pere_As(Q) != NULL))
				{
					Rotation_bst(&Q);
				};
				*P = Q;
			};
		};
	};
	Fermer_s(F1);
	free(Debutstring);
}
/************************************************************/
int Profondeur(Pointeur_As *P)
{
	/** Variables locales **/
	int Profondeur2;
	Pointeur_As _Px1 = NULL;
	Pointeur_As _Px2 = NULL;

	/** Corps du module **/
	if (*P == NULL)
	{
		Profondeur2 = -1;
	}
	else
	{
		_Px1 = Fg_As(*P);
		_Px2 = Fd_As(*P);
		Profondeur2 = 1 + Max(Profondeur(&_Px1), Profondeur(&_Px2));
	}
	return Profondeur2;
}
/************************************************************/
void Inordre(Pointeur_As *P)
{
	/** Variables locales **/
	Pointeur_As _Px1 = NULL;
	Pointeur_As _Px2 = NULL;

	/** Corps du module **/
	if (*P != NULL)
	{
		_Px1 = Fg_As(*P);
		Inordre(&_Px1);
		setColor(WHITE);
		printf(" %s ", Info_As(*P));
		setColor(BLUE);
		printf("/");
		setColor(WHITE);
		_Px2 = Fd_As(*P);
		Inordre(&_Px2);
	}
}
/************************************************************/
void Compte_mots(Pointeur_As *P, int *C, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	Pointeur_As _Px1 = NULL;
	Pointeur_As _Px2 = NULL;

	/** Corps du module **/
	if (*P != NULL)
	{
		_Px1 = Fg_As(*P);
		Compte_mots(&_Px1, &*C, &*X, &*Y, &*Z);
		if (((strcmp(Caract(Info_As(*P), 1), *X) == 0) || (strcmp(Caract(Info_As(*P), 1), *Y) == 0) || (strcmp(Caract(Info_As(*P), 1), *Z) == 0)))
		{
			*C = *C + 1;
		};
		_Px2 = Fd_As(*P);
		Compte_mots(&_Px2, &*C, &*X, &*Y, &*Z);
	}
}
/************************************************************/
void Compte_mots_par_niv(Pointeur_As *P, string255 *X, string255 *Y, string255 *Z)
{
	/** Variables locales **/
	Pointeur_As Ptemp = NULL;
	Pointeur_As Pnil = NULL;
	Pointeur_FAs F = NULL;
	int Count;
	int Level;
	string2 Debutstring;

	/** Corps du module **/
	Debutstring = malloc(2 * sizeof(char));
	Ptemp = *P;
	Pnil = NULL;
	Count = 0;
	Level = 0;
	Creerfile_FAs(&F);
	if (*P != NULL)
	{
		Enfiler_FAs(F, Ptemp);
		Enfiler_FAs(F, Pnil);
	};
	while ((!Filevide_FAs(F)))
	{
		Defiler_FAs(F, &Ptemp);
		if (Ptemp == NULL)
		{
			setColor(BLUE);
			printf(" %s", "\n Niveau: ");
			setColor(WHITE);
			printf(" %d", Level);
			setColor(BLUE);
			printf(" %s", ", Nombre de noeuds: ");
			setColor(WHITE);
			printf(" %d", Count);
			Level = Level + 1;
			Count = 0;
			if ((!Filevide_FAs(F)))
			{
				Enfiler_FAs(F, Pnil);
			};
		}
		else
		{
			strcpy(Debutstring, Caract(Info_As(Ptemp), 1));
			if ((strcmp(Debutstring, *X) == 0) || (strcmp(Debutstring, *Y) == 0) || (strcmp(Debutstring, *Z) == 0))
			{
				Count = Count + 1;
			};
			if (Fg_As(Ptemp) != NULL)
			{
				Enfiler_FAs(F, Fg_As(Ptemp));
			};
			if (Fd_As(Ptemp) != NULL)
			{
				Enfiler_FAs(F, Fd_As(Ptemp));
			};
		};
	};
	free(Debutstring);
	free(F);
}
/************************************************************/
void Inserer_bst(Pointeur_As *P, Pointeur_As *Q)
{
	/** Variables locales **/
	Pointeur_As Ptemp = NULL;
	int I;
	bool Sorstq;

	/** Corps du module **/
	if (*P == NULL)
	{
		*P = *Q;
	}
	else
	{
		Ptemp = *P;
		Sorstq = False;
		while ((!Sorstq))
		{
			if (strcmp(Info_As(Ptemp), Info_As(*Q)) > 0)
			{
				if (Fg_As(Ptemp) != NULL)
				{
					Ptemp = Fg_As(Ptemp);
				}
				else
				{
					Sorstq = True;
				};
			}
			else
			{
				if (Fd_As(Ptemp) != NULL)
				{
					Ptemp = Fd_As(Ptemp);
				}
				else
				{
					Sorstq = True;
				};
			};
		};
		Aff_pere_As(*Q, Ptemp);
		if (strcmp(Info_As(Ptemp), Info_As(*Q)) > 0)
		{
			Aff_fg_As(Ptemp, *Q);
		}
		else
		{
			Aff_fd_As(Ptemp, *Q);
		};
	};
}
/************************************************************/
void Rotation_gauche(Pointeur_As *P)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	Pointeur_As Fgarot = NULL;
	Pointeur_As Pereorg = NULL;

	/** Corps du module **/
	Pereorg = Pere_As(Pere_As(*P));
	Q = Pere_As(*P);
	Fgarot = Fg_As(*P);
	if ((Pereorg != NULL))
	{
		if ((Fg_As(Pereorg) == Q))
		{
			Aff_fg_As(Pereorg, *P);
		}
		else
		{
			Aff_fd_As(Pereorg, *P);
		};
	};
	if ((Fgarot != NULL))
	{
		Aff_pere_As(Fgarot, Q);
		Aff_fd_As(Q, Fgarot);
	}
	else
	{
		Aff_fd_As(Q, NULL);
	};
	Aff_fg_As(*P, Q);
	Aff_pere_As(*P, Pereorg);
	Aff_pere_As(Q, *P);
}
/************************************************************/
void Rotation_droite(Pointeur_As *P)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	Pointeur_As Fdarot = NULL;
	Pointeur_As Pereorg = NULL;

	/** Corps du module **/
	Pereorg = Pere_As(Pere_As(*P));
	Q = Pere_As(*P);
	Fdarot = Fd_As(*P);
	if ((Pereorg != NULL))
	{
		if ((Fg_As(Pereorg) == Q))
		{
			Aff_fg_As(Pereorg, *P);
		}
		else
		{
			Aff_fd_As(Pereorg, *P);
		};
	};
	if ((Fdarot != NULL))
	{
		Aff_pere_As(Fdarot, Q);
		Aff_fg_As(Q, Fdarot);
	}
	else
	{
		Aff_fg_As(Q, NULL);
	};
	Aff_fd_As(*P, Q);
	Aff_pere_As(*P, Pereorg);
	Aff_pere_As(Q, *P);
}
/************************************************************/
void Rotation_bst(Pointeur_As *P)
{

	/** Corps du module **/
	if (Fg_As(Pere_As(*P)) == *P)
	{
		Rotation_droite(&*P);
	}
	else
	{
		Rotation_gauche(&*P);
	}
}
/************************************************************/
void Recherche(string255 *V, Pointeur_As *P, Pointeur_As *R, int *Searchlength)
{
	/** Variables locales **/
	Pointeur_As Trav = NULL;
	bool Finrech;

	/** Corps du module **/
	*R = NULL;
	if (Searchlength != NULL)
		*Searchlength = 0;
	if (*P != NULL)
	{
		Trav = *P;
		Finrech = False;
		while ((Trav != NULL) && (!Finrech))
		{
			if (strcmp(*V, Info_As(Trav)) == 0)
			{
				*R = Trav;
				if (Searchlength != NULL)
					*Searchlength = *Searchlength + 1;
				Finrech = True;
			}
			else
			{
				if (strcmp(*V, Info_As(Trav)) < 0)
				{
					Trav = Fg_As(Trav);
				}
				else
				{
					Trav = Fd_As(Trav);
				};
			};
			if (!Finrech)
				if (Searchlength != NULL)
					*Searchlength = *Searchlength + 1;
		};
	};
}
/************************************************************/
void Recherche_bst(string255 *V, Pointeur_As *A, int *Mode, Pointeur_As *P, string255 *X, string255 *Y, string255 *Z, int *Searchlength)
{
	/** Variables locales **/
	Pointeur_As Trav = NULL;
	bool Finrech;
	string2 Debutstring;

	/** Corps du module **/
	Debutstring = malloc(2 * sizeof(char));
	*Searchlength = 0;
	*P = NULL;
	Trav = *A;
	Finrech = False;

	while ((Trav != NULL) && (!Finrech))
	{
		if (strcmp(Info_As(Trav), *V) == 0)
		{
			*P = Trav;
			*Searchlength = *Searchlength + 1;
			Finrech = True;
		}
		else
		{
			strcpy(Debutstring, Caract(Info_As(Trav), 1));
			if ((*Mode == 1))
			{
				if ((strcmp(Debutstring, *X) != 0) && (strcmp(Debutstring, *Y) != 0) && (strcmp(Debutstring, *Z) != 0))
				{
					Finrech = True;
				};
			}
			else
			{
				if ((*Mode == 2))
				{
					if ((strcmp(Debutstring, *X) < 0) || (strcmp(Debutstring, *Y) < 0) || (strcmp(Debutstring, *Z) < 0))
					{
						Finrech = True;
					};
				}
				else
				{
					if ((strcmp(Debutstring, *X) == 0) || (strcmp(Debutstring, *Y) == 0) || (strcmp(Debutstring, *Z) == 0))
					{
						Finrech = True;
					};
				}
			};
			if ((!Finrech))
			{
				if (strcmp(*V, Info_As(Trav)) < 0)
				{
					Trav = Fg_As(Trav);
				}
				else
				{
					Trav = Fd_As(Trav);
				};
			};
		};
		if (!Finrech)
			*Searchlength = *Searchlength + 1;
	};
	free(Debutstring);
}
/************************************************************/
bool Recherche_triplet(string255 *Word, string255 *X, string255 *Y, string255 *Z, int *Searchlength)
{
	/** Variables locales **/
	bool Recherche_triplet2;
	string2 Debutword;
	Pointeur_As P = NULL;
	int _Px1;
	int _Px2;
	int _Px3;
	int Searchlengthtemp;

	/** Corps du module **/
	Debutword = malloc(2 * sizeof(char));
	Searchlengthtemp = 0;
	strcpy(Debutword, Caract(*Word, 1));
	if ((strcmp(Debutword, *X) == 0) || (strcmp(Debutword, *Y) == 0) || (strcmp(Debutword, *Z) == 0))
	{
		_Px1 = 1;
		Recherche_bst(&*Word, &Bst1, &_Px1, &P, &*X, &*Y, &*Z, &Searchlengthtemp);
		if (P != NULL)
		{
			Recherche_triplet2 = True;
		}
		else
		{
			Recherche_triplet2 = False;
		};
	}
	else
	{
		if ((strcmp(Debutword, *X) > 0) || (strcmp(Debutword, *Y) > 0) || (strcmp(Debutword, *Z) > 0))
		{
			_Px2 = 2;
			Recherche_bst(&*Word, &Bst2, &_Px2, &P, &*X, &*Y, &*Z, &Searchlengthtemp);
			if (P != NULL)
			{
				Recherche_triplet2 = True;
			}
			else
			{
				Recherche_triplet2 = False;
			};
		}
		else
		{
			_Px3 = 3;
			Recherche_bst(&*Word, &Bst3, &_Px3, &P, &*X, &*Y, &*Z, &Searchlengthtemp);
			if (P != NULL)
			{
				Recherche_triplet2 = True;
			}
			else
			{
				Recherche_triplet2 = False;
			};
		};
	};

	*Searchlength = Searchlengthtemp;
	free(Debutword);

	return Recherche_triplet2;
}
/************************************************************/
Pointeur_As Prochain_inordre(Pointeur_As *P, int *Searchlength)
{
	Pointeur_As node = *P;
	if (Searchlength)
		*Searchlength = 0;
	if (node == NULL)
		return NULL;

	if (Fd_As(node) != NULL)
	{
		node = Fd_As(node);
		if (Searchlength)
			(*Searchlength)++;
		while (Fg_As(node) != NULL)
		{
			node = Fg_As(node);
			if (Searchlength)
				(*Searchlength)++;
		}
		return node;
	}

	Pointeur_As parent = Pere_As(node);
	while (parent != NULL && node == Fd_As(parent))
	{
		node = parent;
		parent = Pere_As(parent);
		if (Searchlength)
			(*Searchlength)++;
	}
	if (Searchlength && parent != NULL)
		(*Searchlength)++;
	return parent;
}
/************************************************************/
void Recherche_intervalle(string255 *Mot1, string255 *Mot2, Pointeur_As *Arbre, int *Searchlength, int check)
{
	/** Variables locales **/
	Pointeur_As Deb = NULL;
	Pointeur_As Trav = NULL;

	/** Corps du module **/
	if (Searchlength != NULL)
		*Searchlength = 0;
	if (*Arbre != NULL)
	{
		if (!check)
		{
			setColor(WHITE);
			printf("\n Les mots contenus dans l'intervalle sont: \n");
		}
		Trav = *Arbre;
		Deb = NULL;
		while (Trav != NULL)
		{
			if (strcmp(Info_As(Trav), *Mot1) >= 0)
			{
				Deb = Trav;
				Trav = Fg_As(Trav);
			}
			else
			{
				Trav = Fd_As(Trav);
			};
			if (Searchlength != NULL)
				if (Trav != NULL)
					*Searchlength = *Searchlength + 1;
		};
		while ((Deb != NULL) && (strcmp(Info_As(Deb), *Mot2) <= 0))
		{
			if (!check)
			{
				if (strcmp(Info_As(Deb), *Mot1) >= 0)
				{
					setColor(WHITE);
					printf(" %s ", Info_As(Deb));
					setColor(BLUE);
					printf("/");
				};
			}
			Deb = Prochain_inordre(&Deb, Searchlength);
		};
	};
}
/************************************************************/
void Recherche_intervalle_triplet(string255 *X, string255 *Y, string255 *Z, int *Searchlength, int check)
{
	/** Variables locales **/
	string255 Mot1;
	string255 Mot2;
	bool Ver;
	string2 Debutmot1;

	/** Corps du module **/
	if (Searchlength != NULL)
		*Searchlength = 0;
	Mot1 = malloc(255 * sizeof(char));
	Mot2 = malloc(255 * sizeof(char));
	Debutmot1 = malloc(2 * sizeof(char));
	Ver = False;
	printf(" %s", "\n Veuillez entrer l'intervalle [ Mot1, Mot2 ] avec Mot1 < Mot2: ");
	while ((!Ver))
	{
		printf(" %s", "\n Mot1: ");
		scanf(" %[^\n]", Mot1);
		printf(" %s", "Mot2: ");
		scanf(" %[^\n]", Mot2);
		if (strcmp(Mot1, Mot2) > 0)
		{
			setColor(RED);
			printf(" %s", "\n Entrez un intervalle correct.");
			setColor(WHITE);
		}
		else
		{
			Ver = True;
		};
	};
	strcpy(Debutmot1, Caract(Mot1, 1));
	if ((strcmp(Debutmot1, *X) == 0) || (strcmp(Debutmot1, *Y) == 0) || (strcmp(Debutmot1, *Z) == 0))
	{
		Recherche_intervalle(&Mot1, &Mot2, &Bst1, Searchlength, check);
	}
	else
	{
		if ((strcmp(Debutmot1, *X) > 0) || (strcmp(Debutmot1, *Y) > 0) || (strcmp(Debutmot1, *Z) > 0))
		{
			Recherche_intervalle(&Mot1, &Mot2, &Bst2, Searchlength, check);
		}
		else
		{
			Recherche_intervalle(&Mot1, &Mot2, &Bst3, Searchlength, check);
		};
	};
	free(Debutmot1);
	free(Mot1);
	free(Mot2);
}
/************************************************************/
void Creer_bst0(Pointeur_As *P, int *N)
{
	/** Variables locales **/
	Pointeur_As Q = NULL;
	int I;

	/** Corps du module **/
	Ouvrir_s(&F1, "F.z", "A");
	for (I = 1; I <= *N; ++I)
	{
		Liredir_s(F1, Bf1, I);
		Recherche(&Bf1, &*P, &Q, NULL);
		if (Q == NULL)
		{
			Creernoeud_As(&Q);
			Aff_info_As(Q, Bf1);
			Inserer_bst(&*P, &Q);
		};
	};
	Fermer_s(F1);
}
/************************************************************/
void Generer_fichier_sim(int *N, string255 *X, string255 *Y, string255 *Z, char *Fich)
{
	/** Variables locales **/
	int I;
	bool Ver;

	/** Corps du module **/
	if (strcmp(Fich, "F.z") == 0)
	{
		Ouvrir_s(&F1, Fich, "N");
		for (I = 1; I <= *N; ++I)
		{
			Generer_mot(&Bf1, &*X, &*Y, &*Z);
			Ecrireseq_s(F1, Bf1);
		};
		Fermer_s(F1);
	}
	else
	{
		Ouvrir_s(&F2, Fich, "N");
		for (I = 1; I <= *N; ++I)
		{
			Generer_mot(&Bf2, &*X, &*Y, &*Z);
			Ecrireseq_s(F2, Bf2);
		};
		Fermer_s(F2);
	}
}
/************************************************************/
void Generer_fichier_range_sim(int *N, string255 *X, string255 *Y, string255 *Z)
{

	Ouvrir_s(&F2, "F2.z", "N");
	for (int i = 1; i <= (*N / 2); i++)
	{
		Generer_mot(&Bf1, &*X, &*Y, &*Z);
		Generer_mot(&Bf2, &*X, &*Y, &*Z);
		if (strcmp(Bf1, Bf2) > 0)
		{
			// swap
			char tmp[255];
			strcpy(tmp, Bf1);
			strcpy(Bf1, Bf2);
			strcpy(Bf2, tmp);
		}
		Intervalle interval;
		interval.Mot1 = malloc(255 * sizeof(char));
		interval.Mot2 = malloc(255 * sizeof(char));
		strcpy(interval.Mot1, Bf1);
		strcpy(interval.Mot2, Bf2);
		fwrite(&interval, sizeof(Intervalle), 1, F2);
		free(interval.Mot1);
		free(interval.Mot2);
	};
	Fermer_s(F2);
}
/************************************************************/
void Recherche_intervalle_triplet_sim(string255 *Mot1, string255 *Mot2, string255 *X, string255 *Y, string255 *Z, int *Searchlength, int check)
{
	/** Variables locales **/
	bool Ver;
	string2 Debutmot1;

	/** Corps du module **/
	*Searchlength = 0;
	Debutmot1 = malloc(2 * sizeof(char));
	strcpy(Debutmot1, Caract(*Mot1, 1));
	Ver = False;
	if ((strcmp(Debutmot1, *X) == 0) || (strcmp(Debutmot1, *Y) == 0) || (strcmp(Debutmot1, *Z) == 0))
	{
		Recherche_intervalle(Mot1, Mot2, &Bst1, Searchlength, check);
	}
	else
	{
		if ((strcmp(Debutmot1, *X) > 0) || (strcmp(Debutmot1, *Y) > 0) || (strcmp(Debutmot1, *Z) > 0))
		{
			Recherche_intervalle(Mot1, Mot2, &Bst2, Searchlength, check);
		}
		else
		{
			Recherche_intervalle(Mot1, Mot2, &Bst3, Searchlength, check);
		};
	};
	free(Debutmot1);
}
/************************************************************/
void Liberer_arbre(Pointeur_As *P)
{
	/** Variables locales **/
	Pointeur_As _Px1 = NULL;
	Pointeur_As _Px2 = NULL;

	/** Corps du module **/
	if (*P != NULL)
	{
		_Px1 = Fg_As(*P);
		Liberer_arbre(&_Px1);
		_Px2 = Fd_As(*P);
		Liberer_arbre(&_Px2);
		free((*P)->Val);
		free(*P);
		*P = NULL;
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	Intervalle interval;
	interval.Mot1 = malloc(255 * sizeof(char));
	interval.Mot2 = malloc(255 * sizeof(char));
	X = malloc(255 * sizeof(char));
	Y = malloc(255 * sizeof(char));
	Z = malloc(255 * sizeof(char));
	Motarech = malloc(255 * sizeof(char));
	Mot1 = malloc(255 * sizeof(char));
	Mot2 = malloc(255 * sizeof(char));
	Bf1 = malloc(255 * sizeof(char));
	Bf2 = malloc(255 * sizeof(char));
	Ver1 = False;
	Ver2 = False;
	Ver3 = False;
	Quitter1 = False;
	Quitter2 = False;
	Quitter3 = False;
	/********************/
	while ((!Quitter1))
	{
		clearScreen();
		setColor(BLUE);
		printf(" %s", "\n TP2 realise par: ");
		setColor(WHITE);
		printf("Rachid Mustapha Amine");
		setColor(BLUE);
		printf(" %s", "\n Section: ");
		setColor(WHITE);
		printf("C ");
		setColor(BLUE);
		printf("   | Groupe: ");
		setColor(WHITE);
		printf("12");
		setColor(BLUE);
		printf("\n Module: ");
		setColor(WHITE);
		printf("ALSDD ");
		setColor(BLUE);
		printf("| Niveau: ");
		setColor(WHITE);
		printf("1ere Annee Cycle Preparatoire ");
		setColor(BLUE);
		printf("| ");
		setColor(WHITE);
		printf("2025");
		setColor(BLUE);
		printf(" %s", "\n _____________________________________________________________");
		printf(" %s", "\n");
		printf(" %s", "\n 1. ");
		setColor(WHITE);
		printf("Generer le fichier");
		setColor(BLUE);
		printf(" %s", "\n 2. ");
		setColor(WHITE);
		printf("Construire le triplet BST1, BST2 et BST3");
		setColor(BLUE);
		printf(" %s", "\n 3. ");
		setColor(WHITE);
		printf("Tester le triplet");
		setColor(BLUE);
		printf(" %s", "\n 4. ");
		setColor(WHITE);
		printf("Recherche d'un mot singulier");
		setColor(BLUE);
		printf(" %s", "\n 5. ");
		setColor(WHITE);
		printf("Recherche par intervalle de mots");
		setColor(BLUE);
		printf(" %s", "\n 6. ");
		setColor(WHITE);
		printf("Simulation");
		setColor(BLUE);
		printf(" %s", "\n 7. ");
		setColor(WHITE);
		printf("Quitter");
		setColor(BLUE);
		printf(" %s", "\n _____________________________________________________________");
		printf(" %s", "\n");
		setColor(WHITE);
		printf(" %s", "\n Choisissez l'option: ");
		scanf(" %d", &Choix1);
		/********************/
		if (Choix1 == 1)
		{
			printf("\n Le programme va generer un fichier contenant des mots aleatoires. Vous devrez choisir les lettres specifiques X, Y et Z dont on veut");
			printf("\n optimiser la recherche des mots commencant avec, ainsi que le nombre de mots N du fichier (N >= 100).\n");
			Generer_fichier(&Nombremots, &X, &Y, &Z);
			Ver1 = True;
		};
		/********************/
		if (Choix1 == 2)
		{
			if ((Ver1))
			{
				printf("\n Le programme va construire les arbres de recherches binaires BST1, BST2 et BST3 a partir du fichier genere precedemment, tel que: ");
				printf("\n");
				setColor(BLUE);
				printf("\n     BST1: ");
				setColor(WHITE);
				printf("Les mots commencant par X, Y ou Z seront mis en haut de l'arbre grace a des rotations.");
				setColor(BLUE);
				printf("\n     BST2: ");
				setColor(WHITE);
				printf("Les mots commencant par X, Y ou Z seront mis au milieu de l'arbre, et ceux commencant par des lettres superieures a X, Y ou Z");
				printf("\n           seront mis en haut de l'arbre, grace a des rotations.");
				setColor(BLUE);
				printf("\n     BST3: ");
				setColor(WHITE);
				printf("Les mots ne commencant pas par X, Y ou Z seront mis en haut de l'arbre grace a des rotations.");
				Creer_bst1(&Bst1, &Nombremots, &X, &Y, &Z);
				Creer_bst2(&Bst2, &Nombremots, &X, &Y, &Z);
				Creer_bst3(&Bst3, &Nombremots, &X, &Y, &Z);
				Ver2 = True;
			}
			else
			{
				setColor(RED);
				printf(" %s", "\n Generez d'abord le fichier. ");
				setColor(WHITE);
			};
		};
		/********************/
		if (Choix1 == 3)
		{
			if ((Ver2))
			{
				while ((!Quitter2))
				{
					clearScreen();
					setColor(BLUE);
					printf(" %s", "\n __________________________________________________________");
					printf(" %s", "\n");
					setColor(BLUE);
					printf(" %s", "\n 1. ");
					setColor(WHITE);
					printf("Compter le nombre de mots commencant par X, Y et Z");
					setColor(BLUE);
					printf(" %s", "\n 2. ");
					setColor(WHITE);
					printf("Calculer la profondeur de chaque arbre");
					setColor(BLUE);
					printf(" %s", "\n 3. ");
					setColor(WHITE);
					printf("Navigation en inordre");
					setColor(BLUE);
					printf(" %s", "\n 4. ");
					setColor(WHITE);
					printf("Compter le nombre de mots par niveau pour chaque arbre");
					setColor(BLUE);
					printf(" %s", "\n 5. ");
					setColor(WHITE);
					printf("Quitter");
					setColor(BLUE);
					printf(" %s", "\n __________________________________________________________");
					printf(" %s", "\n");
					setColor(WHITE);
					printf(" %s", "\n Choisir l'option: ");
					scanf(" %d", &Choix2);
					/********************/
					if (Choix2 == 1)
					{
						Nombremotspec = 0;
						Compte_mots(&Bst1, &Nombremotspec, &X, &Y, &Z);
						setColor(BLUE);
						printf(" %s", "\n Nombre de mots dans BST1: ");
						setColor(WHITE);
						printf(" %d", Nombremotspec);
						Nombremotspec = 0;
						Compte_mots(&Bst2, &Nombremotspec, &X, &Y, &Z);
						setColor(BLUE);
						printf(" %s", "\n Nombre de mots dans BST2: ");
						setColor(WHITE);
						printf(" %d", Nombremotspec);
						Nombremotspec = 0;
						Compte_mots(&Bst3, &Nombremotspec, &X, &Y, &Z);
						setColor(BLUE);
						printf(" %s", "\n Nombre de mots dans BST3: ");
						setColor(WHITE);
						printf(" %d", Nombremotspec);
					};
					/********************/
					if (Choix2 == 2)
					{
						Prof = Profondeur(&Bst1);
						setColor(BLUE);
						printf(" %s", "\n Profondeur de BST1:");
						setColor(WHITE);
						printf(" %d", Prof);
						Prof = Profondeur(&Bst2);
						setColor(BLUE);
						printf(" %s", "\n Profondeur de BST2:");
						setColor(WHITE);
						printf(" %d", Prof);
						Prof = Profondeur(&Bst3);
						setColor(BLUE);
						printf(" %s", "\n Profondeur de BST3:");
						setColor(WHITE);
						printf(" %d", Prof);
					};
					/********************/
					if (Choix2 == 3)
					{
						setColor(BLUE);
						printf(" %s", "\n\n Inordre BST1: \n\n");
						setColor(WHITE);
						Inordre(&Bst1);
						setColor(BLUE);
						printf(" %s", "\n\n Inordre BST2: \n\n");
						setColor(WHITE);
						Inordre(&Bst2);
						setColor(BLUE);
						printf(" %s", "\n\n Inordre BST3: \n\n");
						setColor(WHITE);
						Inordre(&Bst3);
					};
					/********************/
					if (Choix2 == 4)
					{
						setColor(BLUE);
						printf(" %s", "\n\n BST1: \n");
						setColor(WHITE);
						Compte_mots_par_niv(&Bst1, &X, &Y, &Z);
						setColor(BLUE);
						printf(" %s", "\n\n BST2: \n");
						setColor(WHITE);
						Compte_mots_par_niv(&Bst2, &X, &Y, &Z);
						setColor(BLUE);
						printf(" %s", "\n\n BST3: \n");
						setColor(WHITE);
						Compte_mots_par_niv(&Bst3, &X, &Y, &Z);
					};
					/********************/
					if (Choix2 == 5)
					{
						Quitter2 = True;
					};
					/********************/
					if ((Choix2 != 1) && (Choix2 != 2) && (Choix2 != 3) && (Choix2 != 4) && (Choix2 != 5))
					{
						setColor(RED);
						printf(" %s", "\n Choisissez une option correcte.");
						setColor(WHITE);
					};
					/********************/
					if (Choix2 != 5)
					{
						printf("\n");
						printf("\n");
						system("PAUSE");
					};
				};
				Quitter2 = !Quitter2;
			}
			else
			{
				setColor(RED);
				printf(" %s", "\n Construire d'abord le triplet. ");
				setColor(WHITE);
			};
		};
		/********************/
		if (Choix1 == 4)
		{
			if ((Ver2))
			{
				printf(" %s", "\n Entrez le mot a rechercher: ");
				scanf(" %[^\n]", Motarech);
				if (Recherche_triplet(&Motarech, &X, &Y, &Z, &Searchlength))
				{
					setColor(GREEN);
					printf(" %s", "\n Le mot a ete trouve.");
					setColor(WHITE);
				}
				else
				{
					setColor(RED);
					printf(" %s", "\n Le mot n'a pas ete trouve.");
					setColor(WHITE);
				};
			}
			else
			{
				setColor(RED);
				printf(" %s", "\n Construire d'abord le triplet. ");
				setColor(WHITE);
			};
		};
		/********************/
		if (Choix1 == 5)
		{
			if ((Ver2))
			{
				Recherche_intervalle_triplet(&X, &Y, &Z, NULL, 0);
			}
			else
			{
				setColor(RED);
				printf(" %s", "\n Construire d'abord le triplet. ");
				setColor(WHITE);
			};
		};
		/********************/
		if (Choix1 == 6)
		{
			while (!Quitter3)
			{
				clearScreen();
				setColor(BLUE);
				printf(" %s", "\n _________________________________________________________");
				printf(" %s", "\n");
				setColor(BLUE);
				printf(" %s", "\n 1. ");
				setColor(WHITE);
				printf("Simuler et evaluer l'efficacite du Single Word Search");
				setColor(BLUE);
				printf(" %s", "\n 2. ");
				setColor(WHITE);
				printf("Simuler et evaluer l'efficacite du Range Search");
				setColor(BLUE);
				printf(" %s", "\n 3. ");
				setColor(WHITE);
				printf("Quitter");
				setColor(BLUE);
				printf(" %s", "\n _________________________________________________________");
				printf(" %s", "\n");
				setColor(WHITE);
				printf(" %s", "\n Choisir l'option: ");
				scanf(" %d", &Choix3);
				/********************/
				if (Choix3 == 1)
				{
					setColor(BLUE);
					printf("\n N.B. ");
					setColor(WHITE);
					printf("E designe le nombre total de noeuds trouves, a cote le nombre total de noeuds visites pour des elements qui existent dans les arbres.");
					printf("\n      !E designe le nombre total de noeuds non trouves, a cote le nombre total de noeuds visites pour des elements qui n'existent pas dans les arbres.");
					printf("\n      All designe le nombre total de noeuds, a cote le nombre total de noeuds visites en considerant l'ensemble des cas de succes et d'echec.");
					printf(" %s", "\n\n Choisissez un nombre de simulations M (M >= 10): ");
					do
					{
						scanf(" %d", &M);
						if (M < 10) {
							printf("\n Choisissez un nombre de simulations superieur ou egal a 10: ");
						}
					} while (M < 10);
					strcpy(X, "Y");
					strcpy(Y, "Z");
					strcpy(Z, "a");
					setColor(BLUE);
					printf("\n\t _____________________________________________________________________");
					printf("\n\t|      "); setColor(WHITE); printf("Simulation      "); setColor(BLUE); printf("|       "); setColor(WHITE); printf("BST0       "); setColor(BLUE); printf("| "); setColor(WHITE); printf("BST1, BST2, BST3 "); setColor(BLUE); printf("| "); setColor(WHITE); printf(" Gain "); setColor(BLUE); printf(" |");
					printf("\n\t|______________________|__________________|__________________|________|");
					for (int I = 1; I <= M; ++I)
					{
						Total_search_success_BST0 = 0;
						Total_search_success_Triplet = 0;
						Total_search_fail_BST0 = 0;
						Total_search_fail_Triplet = 0;
						Nombremots = Aleanombre(10000) + 10000;
						Generer_fichier_sim(&Nombremots, &X, &Y, &Z, "F.z");
						Creer_bst0(&Bst0, &Nombremots);
						Creer_bst1(&Bst1, &Nombremots, &X, &Y, &Z);
						Creer_bst2(&Bst2, &Nombremots, &X, &Y, &Z);
						Creer_bst3(&Bst3, &Nombremots, &X, &Y, &Z);
						Generer_fichier_sim(&Nombremots, &X, &Y, &Z, "F2.z");
						Ouvrir_s(&F1, "F.z", "A");
						int Exist = 0;
						int NotExist = 0;
						float Gain = 0;
						for (int J = 1; J <= Nombremots; ++J)
						{
							Liredir_s(F1, Bf1, J);
							Recherche(&Bf1, &Bst0, &Resultat, &Searchlength);
							if (Resultat == NULL)
							{
								NotExist++;
								Total_search_fail_BST0 = Total_search_fail_BST0 + Searchlength;
							}
							else
							{
								Exist++;
								Total_search_success_BST0 = Total_search_success_BST0 + Searchlength;
							}
							if (Recherche_triplet(&Bf1, &X, &Y, &Z, &Searchlength))
							{
								Exist++;
								Total_search_success_Triplet = Total_search_success_Triplet + Searchlength;
							}
							else
							{
								NotExist++;
								Total_search_fail_Triplet = Total_search_fail_Triplet + Searchlength;
							}
						};
						Fermer_s(F1);
						Ouvrir_s(&F2, "F2.z", "A");
						for (int F = 1; F <= Nombremots; ++F)
						{
							Liredir_s(F2, Bf2, F);
							Recherche(&Bf2, &Bst0, &Resultat, &Searchlength);
							if (Resultat == NULL)
							{
								NotExist++;
								Total_search_fail_BST0 = Total_search_fail_BST0 + Searchlength;
							}
							else
							{
								Exist++;
								Total_search_success_BST0 = Total_search_success_BST0 + Searchlength;
							}
							if (Recherche_triplet(&Bf2, &X, &Y, &Z, &Searchlength))
							{
								Exist++;
								Total_search_success_Triplet = Total_search_success_Triplet + Searchlength;
							}
							else
							{
								NotExist++;
								Total_search_fail_Triplet = Total_search_fail_Triplet + Searchlength;
							}
						}
						Fermer_s(F2);
						Total_search_all_BST0 = Total_search_fail_BST0 + Total_search_success_BST0;
						Total_search_all_Triplet = Total_search_fail_Triplet + Total_search_success_Triplet;
						Gain = (((float)Total_search_all_BST0 - Total_search_all_Triplet) / Total_search_all_BST0) * 100;
						setColor(BLUE);
						printf("\n\t| S"); setColor(WHITE); printf(" %-2d ", I); setColor(BLUE); printf("|"); setColor(GREEN); printf("  E   = %-6d ", Exist); setColor(BLUE); printf("|"); setColor(WHITE); printf("    %8d      ", Total_search_success_BST0); setColor(BLUE); printf("|"); setColor(WHITE); printf("    %8d      ", Total_search_success_Triplet); setColor(BLUE); printf("|        |");
						printf("\n\t|      |---------------|------------------|------------------|        |");
						printf("\n\t|      |"); setColor(RED); printf("  !E  = %-6d ", NotExist); setColor(BLUE); printf("|"); setColor(WHITE); printf("    %8d      ", Total_search_fail_BST0); setColor(BLUE); printf("|"); setColor(WHITE); printf("    %8d      ", Total_search_fail_Triplet); setColor(BLUE); printf("| "); if (Gain >= 0) setColor(GREEN); else setColor(RED); printf("%05.2f%%", Gain); setColor(BLUE); printf(" |");
						printf("\n\t|      |---------------|------------------|------------------|        |");
						printf("\n\t|      |  All = %-6d |    ", Exist + NotExist); setColor(WHITE); printf("%8d      ", Total_search_all_BST0); setColor(BLUE); printf("|    "); setColor(WHITE); printf("%8d      ", Total_search_all_Triplet); setColor(BLUE); printf("|        |");
						printf("\n\t|------|---------------|------------------|------------------|--------|");
						Liberer_arbre(&Bst0);
						Liberer_arbre(&Bst1);
						Liberer_arbre(&Bst2);
						Liberer_arbre(&Bst3);
						setColor(WHITE);
					}
					setColor(BLUE);
					printf("\n\t|______|_______________|__________________|__________________|________|");
					setColor(WHITE);
				};
				/********************/
				if (Choix3 == 2)
				{
					setColor(BLUE);
					printf("\n N.B. ");
					setColor(WHITE);
					printf("Les donnees du tableau designent le nombre total de noeuds visites par arbre pour chaque simulation de recherche par intervalle.");
					printf(" %s", "\n\n Choisissez un nombre de simulations M (M >= 10): ");
					do
					{
						scanf(" %d", &M);
						if (M < 10) {
							printf("\n Choisissez un nombre de simulations superieur ou egal a 10: ");
						}
					} while (M < 10);
					
					
					strcpy(X, "Y");
					strcpy(Y, "Z");
					strcpy(Z, "a");
					setColor(BLUE);
					printf("\n\t ____________________________________________________________");
					printf("\n\t| "); setColor(WHITE); printf("Simulation "); setColor(BLUE); printf("|      "); setColor(WHITE); printf(" BST0       "); setColor(BLUE); printf("| "); setColor(WHITE); printf("BST1, BST2, BST3 "); setColor(BLUE); printf("| "); setColor(WHITE); printf(" Gain  "); setColor(BLUE); printf(" |");
					printf("\n\t|____________|__________________|__________________|_________|");
					for (int I = 1; I <= M; ++I)
					{
						Total_range_BST0 = 0;
						Total_range_Triplet = 0;
						Nombremots = Aleanombre(10000) + 10000;
						Generer_fichier_sim(&Nombremots, &X, &Y, &Z, "F.z");
						Creer_bst0(&Bst0, &Nombremots);
						Creer_bst1(&Bst1, &Nombremots, &X, &Y, &Z);
						Creer_bst2(&Bst2, &Nombremots, &X, &Y, &Z);
						Creer_bst3(&Bst3, &Nombremots, &X, &Y, &Z);
						Generer_fichier_range_sim(&Nombremots, &X, &Y, &Z);
						Ouvrir_s(&F2, "F2.z", "A");
						for (int J = 1; J <= (Nombremots / 2); J++)
						{

							fread(&interval, sizeof(Intervalle), 1, F2);
							Recherche_intervalle(&(interval.Mot1), &(interval.Mot2), &Bst0, &Searchlength, 1);
							Total_range_BST0 += Searchlength;
							Recherche_intervalle_triplet_sim(&(interval.Mot1), &(interval.Mot2), &X, &Y, &Z, &Searchlength, 1);
							Total_range_Triplet += Searchlength;
						};
						float Gain = (((float)Total_range_BST0 - Total_range_Triplet) / Total_range_BST0) * 100;
						fclose(F2);
						setColor(BLUE);
						printf("\n\t|    S"); setColor(WHITE); printf(" %-2d", I); setColor(BLUE); printf("    |      "); setColor(WHITE); printf("%6d      ", Total_range_BST0); setColor(BLUE); printf("|      "); setColor(WHITE); printf("%6d      ", Total_range_Triplet); setColor(BLUE); if (Gain > -10) printf("|  "); else printf("| "); if (Gain >= 0) setColor(GREEN); else setColor(RED); printf("%05.2f%%", Gain); setColor(BLUE); printf(" |");
						printf("\n\t|------------|------------------|------------------|---------|");
						Liberer_arbre(&Bst0);
						Liberer_arbre(&Bst1);
						Liberer_arbre(&Bst2);
						Liberer_arbre(&Bst3);
						setColor(WHITE);
					}
					setColor(BLUE);
					printf("\n\t|____________|__________________|__________________|_________|");
					setColor(WHITE);
				};
				/********************/
				if (Choix3 == 3)
				{
					Quitter3 = True;
				};
				/********************/
				if ((Choix3 != 1) && (Choix3 != 2) && (Choix3 != 3))
				{
					setColor(RED);
					printf(" %s", "\n Choisissez une option correcte.");
					setColor(WHITE);
				};
				/********************/
				if (Choix3 != 3)
				{
					printf("\n");
					printf("\n");
					system("PAUSE");
				};
			};
			Quitter3 = !Quitter3;
		};
		/********************/
		if (Choix1 == 7)
		{
			Quitter1 = True;
		};
		/********************/
		if ((Choix1 != 1) && (Choix1 != 2) && (Choix1 != 3) && (Choix1 != 4) && (Choix1 != 5) && (Choix1 != 6) && (Choix1 != 7))
		{
			setColor(RED);
			printf(" %s", "\n Choisissez une option correcte.");
			setColor(WHITE);
		};
		printf("\n");
		printf("\n");
		system("PAUSE");
	};
	/********************/
	free(interval.Mot1);
	free(interval.Mot2);
	free(X);
	free(Y);
	free(Z);
	free(Motarech);
	free(Mot1);
	free(Mot2);
	free(Bf1);
	free(Bf2);
	return 0;
}
