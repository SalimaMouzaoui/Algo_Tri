#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// on déclare des variables globales
char ch[], sh[];
int nbTab, nbTaille, pas, n;

// une procédure de lecture d'un fichier
void readFile(FILE* fichier, long *tab, int n)
{
    int i;
    for (i=0; i<n; i++)
        fscanf(fichier, "%ld", &tab[i]);
}
// une procédure de construction d'un fichier par des valeurs aléatoires
void constructFile1(FILE *fichier1, int nbTab, int nbTaille, int n)
{
int i, j, k;
   for (j=0; j<nbTaille; j++)
    {
   for (k=0; k<nbTab; k++)
    {
    for (i=0; i<n; i++)
    {
        fprintf(fichier1, "%ld ", rand() % n);
    }
        fprintf(fichier1, "\n");
    }
    fprintf(fichier1, "\n");
            n = n + pas;
    }
}
// une procédure de construction d'un fichier dans le sens inverse
void constructFile2(FILE *fichier1, int nbTaille, int n)
{
int i, j, k;
   for (j=0; j<nbTaille; j++)
    {
        for (k=0; k<nbTab; k++)
    {
    for (i=n; i>0; i--)
    {
        fprintf(fichier1, "%ld ", i);
    }
        fprintf(fichier1, "\n");
    }
    fprintf(fichier1, "\n");
            n = n + pas;
    }
}
// une procédure de permutation
void permutation(long *tab, int i, int j)
{
long temp;
    temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}
// Tri par sélection
void TriSelection (long *tab, int n)
{
int i, j, min, pmin;
long temp;
for (i=0; i<=n-1; i++)
{
    pmin = i;
    for (j=i+1; j<=n; j++)
    {
        if (tab[pmin] > tab[j])  pmin = j;
    }
    if (pmin != i)  permutation(tab, pmin, i);
}
}
// Tri par insertion
void TriInsertion (long *tab, int n)
{
int i, j;
long temp;
for (i=1; i<n; i++)
{
   temp = tab[i];
   j = i;
   while (( j > 0) && (tab[j-1] > temp))
   {
       tab[j] = tab[j-1];
       j--;
   }
   tab[j] = temp;
}
}
// Tri à bulle
void TriBulle (long *tab, int n)
{
int i, j;
long temp;
for (i=n-1; i>=0; i--)
{
   for (j=1; j<=i; j++)
    {
       if (tab[j-1] > tab[j]) permutation(tab, j-1, j);
    }
}
}
// le pivot c'est l'element premier
int partitionnment1 (long *tab,int gauche, int droit)
{
int i, j, pivot;
i = gauche  ; j = droit;
pivot = tab[droit];
do{
while (tab[i] < pivot) i++;
while (tab[j] > pivot) j--;
if (i < j)
permutation(tab, i, j);
}while (i > j);
return i;
}

// le pivot c'est le milieu
int partitionnment2 (long *tab,int gauche, int droit)
{
int i, j, pivot;
i = gauche  ; j = droit;
pivot = tab[(i+j)/2];
do{
while (tab[i] < pivot) i++;
while (tab[j] > pivot) j--;
if (i < j)
permutation(tab, i, j);
}while (i > j);
return i;
}
// le pivot c'est le dernier element
int partitionnment3 (long *tab, int gauche, int droit)
{
    int i, j, pivot;
i = gauche  ; j = droit;
pivot = tab[droit];
do{
while (tab[i] < pivot) i++;
while (tab[j] > pivot) j--;
if (i < j)
permutation(tab, i, j);
}while (i > j);
return i;
}
// Tri rapide
void TriRapide(long *tab, int gauche, int droit, int i)
    {
        int pivot;
        if (gauche < droit)
        {
            switch (i)
                  {
                    case 1 : pivot = partitionnment1 (tab, gauche, droit);
                            break;
                    case 2 : pivot = partitionnment2 (tab, gauche, droit);
                            break;
                    case 3 : pivot = partitionnment3 (tab, gauche, droit);
                            break;
                  }
         TriRapide(tab, gauche, pivot-1, i);
         TriRapide(tab, pivot+1, droit, i);
        }
}
// Tri par fusion
void TriFusion (long *tab, int debut, int fin)
{
    long *tab2 = NULL; int i, j;
    tab2 = (long*) malloc (((fin-debut)+1) * sizeof(long));
    int milieu = (debut + fin) / 2;
if (debut != fin)
{
    if (debut < fin-1){
    TriFusion(tab, debut, milieu);
    TriFusion(tab, milieu+1, fin);}

    i=debut; j=milieu+1; int k=0;
    while ((i<=milieu) && (j<=fin))
    {
        if (tab[i] < tab[j]) {tab2[k]=tab[i]; k++; i++; }
        else {tab2[k]=tab[j]; k++; j++;}
    }
    while (i<=milieu) {tab2[k]=tab[i]; k++; i++; }
    while (j<=fin) {tab2[k]=tab[j]; k++; j++; }
    int l=0; i=debut;
    while (l<k)
    {
        tab[i] = tab2[l]; l++; i++;
    }
    free(tab2);
}
}
// la procédure de la construction d'un tas
void Construction_Tas(long *tab, int n)
{
    int i;
    for (i = n/2; i >= 0; i--)
        Inserer_dans_Tas(tab, i, n - 1);
}
// la procédure d'insertion d'un élément dans un tas
void Inserer_dans_Tas(long *tas, long racine, long bas)
{
    int i;
    long fils_max = racine * 2 + 1;
    if(fils_max < bas) {
    int autre_fils = fils_max + 1;
    if (tas[autre_fils] > tas[fils_max]) fils_max = autre_fils;
    } else { if(fils_max > bas) return; }
    if(tas[racine] >= tas[fils_max]) return;
    permutation(tas, racine, fils_max);
    Inserer_dans_Tas(tas, fils_max, bas);
 }
// Tri par tas
void TriTas (long *tab, int n)
{
    int i;
    Construction_Tas(tab, n);
    for (i = n-1; i>=0; i--)
    {
        permutation(tab, 0, i);
        Inserer_dans_Tas(tab, 0, i-1);
    }
}

int main ()
{
    FILE* fichier1 = NULL;
    FILE *fichier2 = NULL;
    int i, j, k=0;
    clock_t dbt, fin;
    double moy_tps_exe;
    long *tab = NULL;
    tab = (long*) malloc (n * sizeof(long));
    int choix1, choix2, choix3, choix;
    int c;
       printf (" Veuillez construire un benchmark tapper 1 pour Oui | 2 pour Sortir \n");
       scanf ("%d", &c);
                switch (c)
                  {
                    case 1 :
                                printf (" *********** VEUILLEZ CONSTRUIRE UN BENCHMARK *********** \n");
                                printf (" ******************************************************** \n");
                                printf (" * 1 ****************** ALEATOIRE *********************** \n");
                                printf (" * 2 **************** SENS INVERSE ********************** \n");
                                printf (" * 3 ******************* QUITTER ************************ \n");
                                printf (" ******************************************************** \n");
                                printf ("veuillez tapper votre choix SVP:\n ");
                                scanf ("%d", &choix);
                                 switch (choix)
                                 {
                                   case 1 :
                                            printf("donner le mode de création \"moyen\" : \n");
                                            scanf("%s", sh);
                                            printf("donner le nom du fichier à créer : \n");
                                            scanf("%s", ch);
                                            fichier1 = fopen(ch, "w");
                                            printf ("donner la taille du tableau : \n");
                                            scanf("%d", &n);
                                            printf ("donner le nombre de tableau à générer : \n");
                                            scanf ("%d", &nbTab);
                                            printf ("donner le nombre de taille de tableau à générer : \n");
                                            scanf ("%d", &nbTaille);
                                            printf ("donner le pas entre les tableaux  :\n");
                                            scanf ("%d", &pas);
                                            constructFile1(fichier1, nbTab, nbTaille, n);
                                            fclose(fichier1);

                                            break;
                                   case 2 :
                                            printf("donner le mode de création \"pire\" : \n");
                                            scanf("%s", sh);
                                            printf("donner le nom du fichier à créer : \n");
                                            scanf("%s", ch);
                                            fichier1 = fopen(ch, "w");
                                            printf ("donner la taille du tableau :\n");
                                            scanf("%d", &n);
                                            printf ("donner le nombre de tableau à générer :\n");
                                            scanf ("%d", &nbTab);
                                            printf ("donner le nombre de taille de tableau à générer :\n");
                                            scanf ("%d", &nbTaille);
                                            printf ("donner le pas entre les tableaux  :\n");
                                            scanf ("%d", &pas);
                                            constructFile2(fichier1, nbTaille, n);
                                            fclose(fichier2);
                                            break;
                                    default : return 0;
                                 }
                            break;
                    case 2 : return 0;
                  }
                                printf (" ** VOULEZ VOUS PRENDRE UN ECHANTILLON DE DONNEES DANS ** \n");
                                printf (" ******************************************************** \n");
                                printf (" * 1 ****************** PIRE CAS ************************ \n");
                                printf (" * 2 ****************** MOYEN CAS *********************** \n");
                                printf (" * 3 ******************* QUITTER ************************ \n");
                                printf (" ******************************************************** \n");
                                printf ("veuillez tapper votre choix SVP:\n ");
                                scanf ("%d", &choix);
                                 switch (choix)
                                 {
                                   case 1 :
                                            fichier1 = fopen(ch, "r");
                                            break;
                                   case 2 :
                                            fichier1 = fopen(ch, "r");
                                            break;
                                   default : break;
                                 }


printf (" *********************** MENU *************************** \n");
printf (" ******************************************************** \n");
printf (" * 1 ************* TRI PAR SELECTION ******************** \n");
printf (" * 2 ************* TRI PAR INSERTION ******************** \n");
printf (" * 3 ************* TRI A BULLE ************************** \n");
printf (" * 4 ************* TRI RAPIDE *************************** \n");
printf (" ****************** CHOIX DU PIVOT : ******************** \n");
printf (" ******************************************************** \n");
printf (" **************** 4.1 * PIVOT DEBUT ********************* \n");
printf (" **************** 4.2 * PIVOT MILIEU ******************** \n");
printf (" **************** 4.3 * PIVOT FIN *********************** \n");
printf (" **************** 4.4 * QUITTER ************************* \n");
printf (" ******************************************************** \n");
printf (" * 5 ************* TRI PAR FUSION *********************** \n");
printf (" * 6 ************* TRI PAR TAS ************************** \n");
printf (" * 7 ************* QUITTER ******************************* \n");

printf ("veuillez tapper votre choix SVP:\n ");
scanf ("%d", &choix1);
do {
    switch (choix1)
    {
        case 1 :
                if (fichier1 != NULL)
                {
        if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriSelectionMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriSelectionPireCas.txt", "a");

    while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriSelection(tab, n);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI PAR SELECTION \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                 break;
        case 2 :
                 if (fichier1 != NULL)
                {
                 moy_tps_exe = 0;
    if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriInsertionMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriInsertionPireCas.txt", "a");
                 while ( k < nbTaille)
   {
    for (j = 0;  j < nbTab ; j++ )
    {moy_tps_exe=0;
    readFile(fichier1, tab, n);
    dbt = clock();
    TriInsertion(tab, n);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI PAR INSERTION \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                 break;
        case 3 :
                 if (fichier1 != NULL)
                {
                 moy_tps_exe = 0;
    if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriBulleMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriBullePireCas.txt", "a");
                 while ( k < nbTaille)
   {
    for (j = 0;  j < nbTab ; j++ )
    {moy_tps_exe=0;
    readFile(fichier1, tab, n);
    dbt = clock();
    TriBulle(tab, n);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI A BULLE \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                 break;
        case 4 :
               do {
                   printf (" ****************** CHOIX DU PIVOT : ******************** \n");
                   printf (" ******************************************************** \n");
                   printf (" **************** 4.1 * PIVOT DEBUT ********************* \n");
                   printf (" **************** 4.2 * PIVOT MILIEU ******************** \n");
                   printf (" **************** 4.3 * PIVOT FIN *********************** \n");
                   printf (" **************** 4.3 * PIVOT FIN *********************** \n");
                   printf (" **************** 4.4 * QUITTER ************************* \n");
                   printf ("veuillez tapper votre choix SVP:\n ");
                   scanf ("%d", &choix2);
                switch (choix2)
                  {
                    case 1 :
                if (fichier1 != NULL)
                {
                    if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriRapideMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriSelectionPireCas.txt", "a");
                 fprintf(fichier2, " PIVOT = PREMIER ELEMENT \n");
    while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriRapide(tab, 0, n-1, 1);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI RAPIDE \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                            break;
                    case 2 :
                            if (fichier1 != NULL)
                {
                     if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriRapideMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriSelectionPireCas.txt", "a");
                 fprintf(fichier2, " PIVOT = ELEMENT DU MILIEU \n");
     while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriRapide(tab,0 , n-1, 2);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI RAPIDE \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                            break;
                    case 3 :
                            if (fichier1 != NULL)
                {
                     if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriRapideMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriSelectionPireCas.txt", "a");
                 fprintf(fichier2, " PIVOT = DERNIER ELEMENT \n");
    while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriRapide(tab, 0, n-1, 3);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI RAPIDE \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                            break;
                    default :
                            break;
                  }
                  } while (choix3 != 4);
                 break;
        case 5 :
        if (fichier1 != NULL)
                {
    if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriFusionMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriFusionPireCas.txt", "a");
    while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriFusion(tab, 0, n-1);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI PAR FUSION \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    }
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                 break;
        case 6 :
        if (fichier1 != NULL)
    {
    if (strcmp(sh, "moyen") == 0)
                 fichier2 = fopen("results//Result_TriTasMoyenCas.txt", "a");
                 else fichier2 = fopen("results//Result_TriTasPireCas.txt", "a");
   while ( k < nbTaille)
   {moy_tps_exe=0;
    for (j = 0;  j < nbTab ; j++ )
    {
    readFile(fichier1, tab, n);
    dbt = clock();
    TriTas(tab, n);
    fin = clock();
    moy_tps_exe += fin - dbt;
    printf(" TRI PAR TAS \n");
    printf(" la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));
    }
    if (fichier2 != NULL){
    fprintf(fichier2, " la taille = %d       la moyenne d'executions = %f \n\n", n, (float)(moy_tps_exe) / (CLOCKS_PER_SEC*nbTab));}
    else printf("Impossible d'ouvrir le fichier2 ");
    n = n + pas; k++;
    }}
    else printf("Impossible d'ouvrir le fichier1 ");
                 break;
        default :
                 break;
    }

} while (choix1 != 7);

    fclose(fichier2);
    fclose(fichier1);
    return ;
}
