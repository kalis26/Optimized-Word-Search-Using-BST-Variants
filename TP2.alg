
   SOIT
       Nombremots , Prof , Nombremotspec , Choix1 , Choix2 DES ENTIERS ;
       X , Y , Z , Motarech DES CHAINES ;
       F1 UN FICHIER DE CHAINES BUFFER Bf1 ;
       Bst1 , Bst2 , Bst3 DES ARB DE CHAINES ;
       Ver1 , Ver2 , Quitter1 , Quitter2 DES BOOLEENS ;
      /*****             Actions et Fonctions *****/
       Generer_mot UNE ACTION ;
       Generer_fichier UNE ACTION ;
       Creer_bst1 UNE ACTION ;
       Creer_bst2 UNE ACTION ;
       Creer_bst3 UNE ACTION ;
       Inserer_bst UNE ACTION ;
       Rotation_gauche UNE ACTION ;
       Rotation_droite UNE ACTION ;
       Rotation_bst UNE ACTION ;
       Inordre UNE ACTION ;
       Compte_mots UNE ACTION ;
       Compte_mots_par_niv UNE ACTION ;
       Profondeur UNE FONCTION ( ENTIER ) ;
       Recherche UNE ACTION ;
       Recherche_bst UNE ACTION ;
       Recherche_triplet UNE FONCTION ( BOOLEEN ) ;
       Prochain_inordre UNE FONCTION ( ARB DE CHAINE ) ;
       Recherche_intervalle UNE ACTION ;
       Recherche_intervalle_triplet UNE ACTION ;
      /*********************************/
   DEBUT
       Ver1 := FAUX ;
       Ver2 := FAUX ;
       Quitter1 := FAUX ;
       Quitter2 := FAUX ;
      /********************/
       TQ ( NON Quitter1 )
           ECRIRE ( ' TP2 Realise par : Rachid Mustapha Amine' ) ;
           ECRIRE ( ' Section : C | Groupe : 12' ) ;
           ECRIRE ( ' _______________________________________' ) ;
           ECRIRE ( ' ' ) ;
           ECRIRE ( ' 1. Generer le fichier' ) ;
           ECRIRE ( ' 2. Construire le triplet BST1, BST2 et BST3' ) ;
           ECRIRE ( ' 3. Tester le triplet' ) ;
           ECRIRE ( ' 4. Single Word Search' ) ;
           ECRIRE ( ' 5. Range Search' ) ;
           ECRIRE ( ' 6. Quitter' ) ;
           ECRIRE ( ' _______________________________________' ) ;
           ECRIRE ( ' ' ) ;
           ECRIRE ( ' Choisissez l''option : ' ) ;
           LIRE ( Choix1 ) ;
          /********************/
           SI Choix1 = 1
               APPEL Generer_fichier ( Nombremots , X , Y , Z ) ;
               Ver1 := VRAI ;
           FSI ;
          /********************/
           SI Choix1 = 2
               SI ( Ver1 )
                   APPEL Creer_bst1 ( Bst1 , Nombremots , X , Y , Z ) ;
                   APPEL Creer_bst2 ( Bst2 , Nombremots , X , Y , Z ) ;
                   APPEL Creer_bst3 ( Bst3 , Nombremots , X , Y , Z ) ;
                   Ver2 := VRAI ;
               SINON
                   ECRIRE ( ' Generez d''abord le fichier. ' ) ;
               FSI ;
           FSI ;
          /********************/
           SI Choix1 = 3
               SI ( Ver2 )
                   TQ ( NON Quitter2 )
                       ECRIRE ( ' 1. Compter le nombre de mots commençant par X, Y et Z' ) ;
                       ECRIRE ( ' 2. Calculer la profondeur de chaque arbre' ) ;
                       ECRIRE ( ' 3. Navigation en inordre' ) ;
                       ECRIRE ( ' 4. Compter le nombre de mots par niveau pour chaque arbre' ) ;
                       ECRIRE ( ' 5. Quitter' ) ;
                       ECRIRE ( ' _______________________________________' ) ;
                       ECRIRE ( ' ' ) ;
                       ECRIRE ( ' Choisir l''option : ' ) ;
                       LIRE ( Choix2 ) ;
                      /********************/
                       SI Choix2 = 1
                           Nombremotspec := 0 ;
                           APPEL Compte_mots ( Bst1 , Nombremotspec , X , Y , Z ) ;
                           ECRIRE ( 'Nombre de mots dans BST1 : ' , Nombremotspec ) ;
                           Nombremotspec := 0 ;
                           APPEL Compte_mots ( Bst2 , Nombremotspec , X , Y , Z ) ;
                           ECRIRE ( 'Nombre de mots dans BST2 : ' , Nombremotspec ) ;
                           Nombremotspec := 0 ;
                           APPEL Compte_mots ( Bst3 , Nombremotspec , X , Y , Z ) ;
                           ECRIRE ( 'Nombre de mots dans BST3 : ' , Nombremotspec ) ;
                       FSI ;
                      /********************/
                       SI Choix2 = 2
                           Prof := Profondeur ( Bst1 ) ;
                           ECRIRE ( 'Profondeur de BST1 :' , Prof ) ;
                           Prof := Profondeur ( Bst2 ) ;
                           ECRIRE ( 'Profondeur de BST2 :' , Prof ) ;
                           Prof := Profondeur ( Bst3 ) ;
                           ECRIRE ( 'Profondeur de BST3 :' , Prof ) ;
                       FSI ;
                      /********************/
                       SI Choix2 = 3
                           ECRIRE ( ' Inordre BST1: ' ) ;
                           APPEL Inordre ( Bst1 ) ;
                           ECRIRE ( ' Inordre BST2: ' ) ;
                           APPEL Inordre ( Bst2 ) ;
                           ECRIRE ( ' Inordre BST3: ' ) ;
                           APPEL Inordre ( Bst3 ) ;
                       FSI ;
                      /********************/
                       SI Choix2 = 4
                           ECRIRE ( ' BST1 : ' ) ;
                           APPEL Compte_mots_par_niv ( Bst1 , X , Y , Z ) ;
                           ECRIRE ( ' BST2 : ' ) ;
                           APPEL Compte_mots_par_niv ( Bst2 , X , Y , Z ) ;
                           ECRIRE ( ' BST3 : ' ) ;
                           APPEL Compte_mots_par_niv ( Bst3 , X , Y , Z ) ;
                       FSI ;
                      /********************/
                       SI Choix2 = 5
                           Quitter2 := VRAI ;
                       FSI ;
                      /********************/
                       SI ( Choix2 <> 1 ) ET ( Choix2 <> 2 ) ET ( Choix2 <> 3 ) ET ( Choix2 <> 4 ) ET ( Choix2 <> 5 )
                           ECRIRE ( ' Choisissez une option correcte.' ) ;
                       FSI ;
                   FTQ ;
               SINON
                   ECRIRE ( ' Construire d''abord le triplet. ' ) ;
               FSI ;
           FSI ;
          /********************/
           SI Choix1 = 4
               SI ( Ver2 )
                   ECRIRE ( 'Entrez le mot a rechercher : ' ) ;
                   LIRE ( Motarech ) ;
                   SI Recherche_triplet ( Motarech , X , Y , Z )
                       ECRIRE ( 'le mot a ete trouve.' ) ;
                   SINON
                       ECRIRE ( 'le mot n''a pas ete trouve.' ) ;
                   FSI ;
               SINON
                   ECRIRE ( ' Construire d''abord le triplet. ' ) ;
               FSI ;
           FSI ;
          /********************/
           SI Choix1 = 5
               SI ( Ver2 )
                   APPEL Recherche_intervalle_triplet ( X , Y , Z ) ;
               SINON
                   ECRIRE ( ' Construire d''abord le triplet. ' ) ;
               FSI ;
           FSI ;
          /********************/
           SI Choix1 = 6
               Quitter1 := VRAI ;
           FSI ;
          /********************/
           SI ( Choix1 <> 1 ) ET ( Choix1 <> 2 ) ET ( Choix1 <> 3 ) ET ( Choix1 <> 4 ) ET ( Choix1 <> 5 ) ET ( Choix1
           <> 6 )
               ECRIRE ( ' Choisissez une option correcte.' ) ;
           FSI ;
       FTQ ;
      /********************/
   FIN
  /************************************************************/
   ACTION Generer_mot ( Ch , X , Y , Z )
   SOIT
       Ch UNE CHAINE ;
       X , Y , Z DES CHAINES ;
       I UN ENTIER ;
   DEBUT
       I := ALEANOMBRE ( 10 ) ;
       SI I = 0
           Ch := X + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
       SINON
           SI I = 1
               Ch := Y + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
           SINON
               SI I = 3
                   Ch := Z + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
               SINON
                   Ch := ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /************************************************************/
   ACTION Generer_fichier ( N , X , Y , Z ) ;
   SOIT
       N , I DES ENTIERS ;
       X , Y , Z DES CHAINES ;
       Ver UN BOOLEEN ;
   DEBUT
       ECRIRE ( 'Entrez le nombre de mots a generer : ' ) ;
       LIRE ( N ) ;
       ECRIRE ( 'Choisissez les caracteres speciaux X, Y et Z.' ) ;
       ECRIRE ( 'X = ' ) ;
       LIRE ( X ) ;
       Ver := FAUX ;
       ECRIRE ( 'Y = ' ) ;
       TQ ( NON Ver )
           LIRE ( Y ) ;
           SI Y = X
               ECRIRE ( 'Choisissez des caracteres differents : ' ) ;
           SINON
               Ver := VRAI ;
           FSI ;
       FTQ ;
       Ver := FAUX ;
       ECRIRE ( 'Z = ' ) ;
       TQ ( NON Ver )
           LIRE ( Z ) ;
           SI ( Z = X ) OU ( Z = Y )
               ECRIRE ( 'Choisissez des caracteres differents : ' ) ;
           SINON
               Ver := VRAI ;
           FSI ;
       FTQ ;
       OUVRIR ( F1 , 'words.txt' , 'N' ) ;
       POUR I := 1 , N
           APPEL Generer_mot ( Bf1 , X , Y , Z ) ;
           ECRIRESEQ ( F1 , Bf1 ) ;
       FPOUR ;
       FERMER ( F1 ) ;
   FIN
  /************************************************************/
   ACTION Creer_bst1 ( P , N , X , Y , Z ) ;
   SOIT
       P , Q DES POINTEURS VERS DES ARB DE CHAINES ;
       N , I DES ENTIERS ;
       X , Y , Z DES CHAINES ;
       Debutstring UN CARACTERE ;
   DEBUT
       OUVRIR ( F1 , 'words.txt' , 'A' ) ;
       POUR I := 1 , N
           LIREDIR ( F1 , Bf1 , I ) ;
           APPEL Recherche ( Bf1 , P , Q ) ;
           SI Q = NIL
               CREERNOEUD ( Q ) ;
               AFF_INFO ( Q , Bf1 ) ;
               APPEL Inserer_bst ( P , Q ) ;
               Debutstring := CARACT ( INFO ( Q ) , 1 ) ;
               SI ( Debutstring = X ) OU ( Debutstring = Y ) OU ( Debutstring = Z )
                   TQ ( PERE ( Q ) <> NIL )
                       APPEL Rotation_bst ( Q ) ;
                   FTQ ;
                   P := Q ;
               FSI ;
           FSI ;
       FPOUR ;
       FERMER ( F1 ) ;
   FIN
  /************************************************************/
   ACTION Creer_bst2 ( P , N , X , Y , Z ) ;
   SOIT
       P , Q , Qtemp DES POINTEURS VERS DES ARB DE CHAINES ;
       N , I , Compteur , J DES ENTIERS ;
       X , Y , Z DES CHAINES ;
       Finrot UN BOOLEEN ;
       Debutstring , Debutpere UN CARACTERE ;
   DEBUT
       OUVRIR ( F1 , 'words.txt' , 'A' ) ;
       POUR I := 1 , N
           LIREDIR ( F1 , Bf1 , I ) ;
           APPEL Recherche ( Bf1 , P , Q ) ;
           SI Q = NIL
               CREERNOEUD ( Q ) ;
               AFF_INFO ( Q , Bf1 ) ;
               APPEL Inserer_bst ( P , Q ) ;
               Debutstring := CARACT ( INFO ( Q ) , 1 ) ;
               SI ( Debutstring = X ) OU ( Debutstring = Y ) OU ( Debutstring = Z )
                   Qtemp := Q ;
                   Compteur := 0 ;
                   TQ ( PERE ( Qtemp ) <> NIL )
                       Qtemp := PERE ( Qtemp ) ;
                       Compteur := Compteur + 1 ;
                   FTQ ;
                   SI Compteur >= 2
                       Finrot := FAUX ;
                       POUR J := 1 , ( Compteur / 2 )
                           SI ( PERE ( Q ) <> NIL )
                               Debutpere := CARACT ( INFO ( PERE ( Q ) ) , 1 ) ;
                               SI ( Debutpere > X ) OU ( Debutpere > Y ) OU ( Debutpere > Z )
                                   Finrot := VRAI ;
                               FSI ;
                           FSI ;
                           SI ( NON Finrot )
                               APPEL Rotation_bst ( Q ) ;
                           FSI ;
                       FPOUR ;
                       SI PERE ( Q ) = NIL
                           P := Q ;
                       FSI ;
                   FSI ;
               SINON
                   SI ( Debutstring > X ) OU ( Debutstring > Y ) OU ( Debutstring > Z )
                       TQ ( PERE ( Q ) <> NIL )
                           APPEL Rotation_bst ( Q ) ;
                       FTQ ;
                       P := Q ;
                   FSI ;
               FSI ;
           FSI ;
       FPOUR ;
       FERMER ( F1 ) ;
   FIN
  /************************************************************/
   ACTION Creer_bst3 ( P , N , X , Y , Z ) ;
   SOIT
       P , Q DES POINTEUR VERS DES ARB DE CHAINES ;
       N , I DES ENTIERS ;
       X , Y , Z DES CHAINES ;
       Debutstring UN CARACTERE ;
   DEBUT
       OUVRIR ( F1 , 'words.txt' , 'A' ) ;
       POUR I := 1 , N
           LIREDIR ( F1 , Bf1 , I ) ;
           APPEL Recherche ( Bf1 , P , Q ) ;
           SI Q = NIL
               CREERNOEUD ( Q ) ;
               AFF_INFO ( Q , Bf1 ) ;
               APPEL Inserer_bst ( P , Q ) ;
               Debutstring := CARACT ( INFO ( Q ) , 1 ) ;
               SI ( Debutstring <> X ) ET ( Debutstring <> Y ) ET ( Debutstring <> Z )
                   TQ ( PERE ( Q ) <> NIL )
                       APPEL Rotation_bst ( Q ) ;
                   FTQ ;
                   P := Q ;
               FSI ;
           FSI ;
       FPOUR ;
       FERMER ( F1 ) ;
   FIN
  /************************************************************/
   FONCTION Profondeur ( P ) : ENTIER ;
   SOIT
       P UN POINTEUR VERS UN ARB DE CHAINE ;
   DEBUT
       SI P = NIL
           Profondeur := - 1
       SINON
           Profondeur := 1 + MAX ( Profondeur ( FG ( P ) ) , Profondeur ( FD ( P ) ) ) ;
       FSI
   FIN
  /************************************************************/
   ACTION Inordre ( P ) ;
   SOIT
       P UN POINTEUR VERS UN ARB DE CHAINE ;
   DEBUT
       SI P <> NIL
           APPEL Inordre ( FG ( P ) ) ;
           ECRIRE ( INFO ( P ) ) ;
           APPEL Inordre ( FD ( P ) ) ;
       FSI
   FIN
  /************************************************************/
   ACTION Compte_mots ( P , C , X , Y , Z ) ;
   SOIT
       P UN POINTEUR VERS UN ARB DE CHAINE ;
       X , Y , Z DES CHAINES ;
       C UN ENTIER ;
   DEBUT
       SI P <> NIL
           APPEL Compte_mots ( FG ( P ) , C , X , Y , Z ) ;
           SI ( ( CARACT ( INFO ( P ) , 1 ) = X ) OU ( CARACT ( INFO ( P ) , 1 ) = Y ) OU ( CARACT ( INFO ( P ) , 1 )
           = Z ) )
               C := C + 1 ;
           FSI ;
           APPEL Compte_mots ( FD ( P ) , C , X , Y , Z ) ;
       FSI
   FIN
  /************************************************************/
   ACTION Compte_mots_par_niv ( P , X , Y , Z ) ;
   SOIT
       P , Ptemp , Pnil UN POINTEUR VERS UN ARB DE CHAINE ;
       X , Y , Z DES CHAINES ;
       F UNE FILE DE ARB DE CHAINES ;
       Count , Level UN ENTIER ;
       Debutstring UN CARACTERE ;
   DEBUT
       Ptemp := P ;
       Pnil := NIL ;
       Count := 0 ;
       Level := 0 ;
       CREERFILE ( F ) ;
       SI P <> NIL
           ENFILER ( F , Ptemp ) ;
           ENFILER ( F , Pnil ) ;
       FSI ;
       TQ ( NON FILEVIDE ( F ) )
           DEFILER ( F , Ptemp ) ;
           SI Ptemp = NIL
               ECRIRE ( 'Niveau : ' , Level , ', Nombre de noeuds : ' , Count ) ;
               Level := Level + 1 ;
               Count := 0 ;
               SI ( NON FILEVIDE ( F ) )
                   ENFILER ( F , Pnil ) ;
               FSI ;
           SINON
               Debutstring := CARACT ( INFO ( Ptemp ) , 1 ) ;
               SI ( Debutstring = X ) OU ( Debutstring = Y ) OU ( Debutstring = Z )
                   Count := Count + 1 ;
               FSI ;
               SI FG ( Ptemp ) <> NIL
                   ENFILER ( F , FG ( Ptemp ) ) ;
               FSI ;
               SI FD ( Ptemp ) <> NIL
                   ENFILER ( F , FD ( Ptemp ) ) ;
               FSI ;
           FSI ;
       FTQ ;
   FIN
  /************************************************************/
   ACTION Inserer_bst ( P , Q ) ;
   SOIT
       P , Ptemp , Q DES POINTEURS VERS DES ARB DE CHAINES ;
       I DES ENTIERS ;
       Sorstq DES BOOLEENS ;
   DEBUT
       SI P = NIL
           P := Q ;
       SINON
           Ptemp := P ;
           Sorstq := FAUX ;
           TQ ( NON Sorstq )
               SI INFO ( Ptemp ) > INFO ( Q )
                   SI FG ( Ptemp ) <> NIL
                       Ptemp := FG ( Ptemp ) ;
                   SINON
                       Sorstq := VRAI ;
                   FSI ;
               SINON
                   SI FD ( Ptemp ) <> NIL
                       Ptemp := FD ( Ptemp ) ;
                   SINON
                       Sorstq := VRAI ;
                   FSI ;
               FSI ;
           FTQ ;
           AFF_PERE ( Q , Ptemp ) ;
           SI INFO ( Ptemp ) > INFO ( Q )
               AFF_FG ( Ptemp , Q ) ;
           SINON
               AFF_FD ( Ptemp , Q ) ;
           FSI ;
       FSI ;
   FIN
  /************************************************************/
   ACTION Rotation_gauche ( P )
   SOIT
       P , Q , Fgarot , Pereorg DES POINTEURS VERS DES ARB DE CHAINES ;
   DEBUT
       Pereorg := PERE ( PERE ( P ) ) ;
       Q := PERE ( P ) ;
       Fgarot := FG ( P ) ;
       SI ( Pereorg <> NIL )
           SI ( FG ( Pereorg ) = Q )
               AFF_FG ( Pereorg , P ) ;
           SINON
               AFF_FD ( Pereorg , P ) ;
           FSI ;
       FSI ;
       SI ( Fgarot <> NIL )
           AFF_PERE ( Fgarot , Q ) ;
           AFF_FD ( Q , Fgarot ) ;
       SINON
           AFF_FD ( Q , NIL ) ;
       FSI ;
       AFF_FG ( P , Q ) ;
       AFF_PERE ( P , Pereorg ) ;
       AFF_PERE ( Q , P ) ;
   FIN
  /************************************************************/
   ACTION Rotation_droite ( P )
   SOIT
       P , Q , Fdarot , Pereorg DES POINTEURS VERS DES ARB DE CHAINES ;
   DEBUT
       Pereorg := PERE ( PERE ( P ) ) ;
       Q := PERE ( P ) ;
       Fdarot := FD ( P ) ;
       SI ( Pereorg <> NIL )
           SI ( FG ( Pereorg ) = Q )
               AFF_FG ( Pereorg , P ) ;
           SINON
               AFF_FD ( Pereorg , P ) ;
           FSI ;
       FSI ;
       SI ( Fdarot <> NIL )
           AFF_PERE ( Fdarot , Q ) ;
           AFF_FG ( Q , Fdarot ) ;
       SINON
           AFF_FG ( Q , NIL ) ;
       FSI ;
       AFF_FD ( P , Q ) ;
       AFF_PERE ( P , Pereorg ) ;
       AFF_PERE ( Q , P ) ;
   FIN
  /************************************************************/
   ACTION Rotation_bst ( P )
   SOIT
       P UN POINTEUR VERS UN ARB DE CHAINE ;
   DEBUT
       SI FG ( PERE ( P ) ) = P
           APPEL Rotation_droite ( P ) ;
       SINON
           APPEL Rotation_gauche ( P ) ;
       FSI
   FIN
  /************************************************************/
   ACTION Recherche ( V , P , R )
   SOIT
       P , Trav , R DES POINTEURS VERS UN ARB DE CHAINE ;
       V UNE CHAINE ;
       Finrech UN BOOLEEN ;
   DEBUT
       R := NIL ;
       SI P <> NIL
           Trav := P ;
           Finrech := FAUX ;
           TQ ( Trav <> NIL ) ET ( NON Finrech )
               SI V = INFO ( Trav )
                   R := Trav ;
                   Finrech := VRAI ;
               SINON
                   SI V < INFO ( Trav )
                       Trav := FG ( Trav ) ;
                   SINON
                       Trav := FD ( Trav ) ;
                   FSI ;
               FSI ;
           FTQ ;
       FSI ;
   FIN
  /************************************************************/
   ACTION Recherche_bst ( V , A , Mode , P , X , Y , Z )
   SOIT
       P , A , Trav UN POINTEUR VERS UN ARB DE CHAINE ;
       X , Y , Z DES CHAINES ;
       V UNE CHAINE ;
       Mode UN ENTIER ;
       Finrech UN BOOLEEN ;
       Debutstring UN CARACTERE ;
   DEBUT
       SI ( Mode = 1 ) OU ( Mode = 3 )
           P := NIL ;
           Trav := A ;
           Finrech := FAUX ;
           TQ ( Trav <> NIL ) ET ( NON Finrech )
               SI INFO ( Trav ) = V
                   P := Trav ;
                   Finrech := VRAI ;
               SINON
                   Debutstring := CARACT ( INFO ( Trav ) , 1 ) ;
                   SI ( Mode = 1 )
                       SI ( Debutstring <> X ) ET ( Debutstring <> Y ) ET ( Debutstring <> Z )
                           Finrech := VRAI ;
                       FSI ;
                   SINON
                       SI ( Debutstring = X ) OU ( Debutstring = Y ) OU ( Debutstring = Z )
                           Finrech := VRAI ;
                       FSI ;
                   FSI ;
                   SI ( NON Finrech )
                       SI V < INFO ( Trav )
                           Trav := FG ( Trav ) ;
                       SINON
                           Trav := FD ( Trav ) ;
                       FSI ;
                   FSI ;
               FSI ;
           FTQ ;
       SINON
           APPEL Recherche ( V , A , P ) ;
       FSI ;
   FIN
  /************************************************************/
   FONCTION Recherche_triplet ( Word , X , Y , Z ) : BOOLEEN ;
   SOIT
       Word , X , Y , Z DES CHAINES ;
       Debutword UN CARACTERE ;
       P UN POINTEUR VERS UN ARB DE CHAINE ;
   DEBUT
       Debutword := CARACT ( Word , 1 ) ;
       SI ( Debutword = X ) OU ( Debutword = Y ) OU ( Debutword = Z )
           APPEL Recherche_bst ( Word , Bst1 , 1 , P , X , Y , Z ) ;
           SI P <> NIL
               Recherche_triplet := VRAI ;
           SINON
               Recherche_triplet := FAUX ;
           FSI ;
       SINON
           SI ( Debutword > X ) OU ( Debutword > Y ) OU ( Debutword > Z )
               APPEL Recherche_bst ( Word , Bst2 , 2 , P , X , Y , Z ) ;
               SI P <> NIL
                   Recherche_triplet := VRAI ;
               SINON
                   Recherche_triplet := FAUX ;
               FSI ;
           SINON
               APPEL Recherche_bst ( Word , Bst3 , 3 , P , X , Y , Z ) ;
               SI P <> NIL
                   Recherche_triplet := VRAI ;
               SINON
                   Recherche_triplet := FAUX ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /************************************************************/
   FONCTION Prochain_inordre ( P ) : ARB DE CHAINE ;
   SOIT
       P , Prochain DES POINTEURS VERS UN ARB DE CHAINE ;
       Finpro UN BOOLEEN ;
   DEBUT
       SI P <> NIL
           SI ( FD ( P ) <> NIL )
               Prochain := FD ( P ) ;
               TQ ( FG ( Prochain ) <> NIL )
                   Prochain := FG ( Prochain ) ;
               FTQ ;
           SINON
               SI PERE ( P ) <> NIL
                   SI ( FD ( PERE ( P ) ) = P )
                       Prochain := P ;
                       Finpro := FAUX ;
                       TQ ( FD ( PERE ( Prochain ) ) = Prochain ) ET ( NON Finpro )
                           SI ( PERE ( Prochain ) = NIL )
                               Prochain := NIL ;
                               Finpro := VRAI ;
                           SINON
                               Prochain := PERE ( Prochain ) ;
                           FSI ;
                       FTQ ;
                       SI Prochain <> NIL
                           Prochain := PERE ( Prochain ) ;
                       FSI ;
                   SINON
                       Prochain := PERE ( P ) ;
                   FSI ;
               SINON
                   Prochain := NIL ;
               FSI ;
           FSI ;
           Prochain_inordre := Prochain ;
       SINON
           Prochain_inordre := NIL ;
       FSI ;
   FIN
  /************************************************************/
   ACTION Recherche_intervalle ( Mot1 , Mot2 , Arbre )
   SOIT
       Mot1 , Mot2 DES CHAINES ;
       Arbre , Deb , Trav DES ARB DE CHAINE ;
   DEBUT
       SI Arbre <> NIL
           Trav := Arbre ;
           Deb := NIL ;
           TQ Trav <> NIL
               SI INFO ( Trav ) >= Mot1
                   Deb := Trav ;
                   Trav := FG ( Trav ) ;
               SINON
                   Trav := FD ( Trav ) ;
               FSI ;
           FTQ ;
           TQ ( Deb <> NIL ) ET ( INFO ( Deb ) <= Mot2 )
               ECRIRE ( INFO ( Deb ) ) ;
               Deb := Prochain_inordre ( Deb ) ;
           FTQ ;
       FSI ;
   FIN
  /************************************************************/
   ACTION Recherche_intervalle_triplet ( X , Y , Z )
   SOIT
       Mot1 , Mot2 , X , Y , Z DES CHAINES ;
       Ver UN BOOLEEN ;
       Debutmot1 , Debutmot2 UN CARACTERE ;
   DEBUT
       Ver := FAUX ;
       ECRIRE ( 'Veuillez entrer l''intervalle [ Mot1, Mot2 ] avec Mot1 < Mot2 : ' ) ;
       TQ ( NON Ver )
           ECRIRE ( 'Mot1 : ' ) ;
           LIRE ( Mot1 ) ;
           ECRIRE ( 'Mot2 : ' ) ;
           LIRE ( Mot2 ) ;
           SI Mot1 > Mot2
               ECRIRE ( 'Entrez un intervalle correct.' ) ;
           SINON
               Ver := VRAI ;
           FSI ;
       FTQ ;
       Debutmot1 := CARACT ( Mot1 , 1 ) ;
       Debutmot2 := CARACT ( Mot2 , 1 ) ;
       SI ( Debutmot1 = X ) OU ( Debutmot1 = Y ) OU ( Debutmot1 = Z )
           APPEL Recherche_intervalle ( Mot1 , Mot2 , Bst1 ) ;
       SINON
           SI ( Debutmot1 > X ) OU ( Debutmot1 > Y ) OU ( Debutmot1 > Z )
               APPEL Recherche_intervalle ( Mot1 , Mot2 , Bst2 ) ;
           SINON
               APPEL Recherche_intervalle ( Mot1 , Mot2 , Bst3 ) ;
           FSI ;
       FSI ;
   FIN
