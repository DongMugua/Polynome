/* Ce projet est de realiser un ensemble de fonctions 
 * per mettantant la manipulation de polynomes.
 *
 * Le menu d'utilisation est:
 *    --Initialisation;
 *    --Lecture et ecriture;
 *    --Evaluation de p(x) par la methode de Horner pour un x donne;
 *    --Addition;
 *    --Soustraction;
 *    --Multiplication;
 *    --Derivation;
 *    --Division euclidienne;
 *    --Factorisation par (x-α),α un entier donne;
 *    --plus grand commun diviseur de deux polynomes;
 *    --plus petit commun multiple de deux polynomes.
 *
 * Polytech-Sophia
 * Xidian University
 * 
 * auteur Qian Likun (15310116001)
 * @auteur  Charles-Qian@outlook.com
 *
 * auteur Sun Hao    (15310116005)
 * @auteur sh9339@163.com
 *
 * lundi 12 decembre 2016 —— mercredi 4 janvier 2017
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define CMONOME 100 /*Le maximum des monomes dans le polynome que vous ecrivez est 100. */
#define LMONOME 20  /*La longueur de chacun monome est 20.*/




/*Antecedent : COEFF_ORDONNE est le tableau coefficient.q est un variable.
 *
 *Consequent : COEFF_ORDONNE est le tableau coefficient dont vous avez besoin définitivement,
 *             et il est range par degre d'exponent ascen*dant.
 *             q determine la situation de la fonction dans ce polynome vous ecrivez.
 *
 *Role       : Cette fonction peux analyser et exprimer la matrice coefficient,
 *             cette matrice est homologue de cepolynome vous ecrivez d'abord.
 *             (Initialiser cette matrice comme les parametres effectifs dans le tableau COEFF_ORDONNE[])
 *             En plus: Quand vous calculez Division euclidienne,le resultat peut-etre est 
 *             fraction décimale,mais on ne peux pas exprimer par <int>,
 *             thus on le exprime par <double>.
 */
void lecture(double COEFF_ORDONNE[CMONOME],int q)
/*Le dernier ordonne tableau de coefficient.*//*Le maximum de degre du tableau on exporte.*/
{
  char CLASSI[CMONOME][LMONOME];          /*Le tableau <classification>.*/
  char OCCA[8000];                        /*Le tableau <occasionnel>.*/
  char ch;
  int i = 0;                              /*i est l'indice du tableau <occasionnel>.*/
  int L;                                  /*L est la longueur du tableau <occasionnel> .*/
  int j;                                  /*j est le premier indice  du tableau <classification>.*/
  int k;                                  /*k est le deuxieme indice du tableau <classification>.*/
  
  double COUNT[LMONOME];                  /*Compter la quantite des elements chacun ligne.*/
  int x;                                  /*x est l'indice du tableau<COUNT>.*/
  /*int nombre_de_monome;*/
  /*X est le nombre des valeurs effctifs dans le tableau<COUNT>,il est aussi le nombre des monomes effectifs.*/
  
  int PLUS_MOINS[CMONOME];                 /*Ce tableau met en reserve des signes positifs et négatifs dans chacun monome. */
  int pm;                                  /*pm est l'indice du tableau <PLUS_MOINS[CMONOME]>.*/

  char COEFF[CMONOME][LMONOME];            /*Le tableau <coefficients>.*/
  double COEFF2[CMONOME][LMONOME];
  int jcoe;                                /*Les indices du tableau <coefficients>.*/
  int kcoe;


  double REELCOEFF[CMONOME];               /*Le tableau <coefficient> reel.*/
  int reel;

  int J;                                   /*Le nombre des monomes reel.*/
  
  double COUNT_2[LMONOME];
  /*Ce sont des variables qu'on discute le degre.*/
  int INDICE[CMONOME];
  int ind;
  
  int trans;

  /*int COEFF_ORDONNE[CMONOME];*//*Le dernier ordonne tableau <coefficient>.*/
  for (x = 0; x < CMONOME; ++x) /*Initialiser le tableau.*/
    INDICE[x] = 0;
  
  for (x = 0; x < CMONOME; ++x)/*Initialiser le tableau.*/
    REELCOEFF[x] = 0;
  

  /*L'assignation du tableau.*/
  for(j=0;j<CMONOME;j++)
    for(k=0;k<LMONOME;k++)
      CLASSI[j][k] = '|';

  /*Initialiser <PLUS_MOINS[CMONOME]>.*/
  for(pm=0;pm<CMONOME;pm++)
    PLUS_MOINS[pm]=1;

  if(q==0)
    printf("P(x) = ");
  else
    printf("P%d(x) = ",q);
  
  if(q==1 || q==0)
    ch=getchar();

  for(x=0;x<100;x++)
    {
      if(x>0)
        {
	  if(q==0)
	    printf("P(x) = ");
	  else
	    printf("P%d(x) = ",q);
        
	    ch=' ';
	}

      i=0;
      while((ch = getchar()) != '\n')  /*Effacer l'espace.*/
    {
      if(ch != ' ')
	{  
	  OCCA[i]=ch;
	  i++;
	  L=i;
	}
    }
      /*Vérifier si il y a une erreur dans lecture.*/
      for(i=0;i<L;i++)
	{
	  if(OCCA[i]!='0' && OCCA[i]!='1' && OCCA[i]!='2' && OCCA[i]!='3' && OCCA[i]!='4' && OCCA[i]!='5' && OCCA[i]!='6' && OCCA[i]!='7' && OCCA[i]!='8' && OCCA[i]!='9' && OCCA[i]!='x' && OCCA[i]!='^' && OCCA[i]!='+' && OCCA[i]!='-')
	    {
	      printf("Erreur!Re-ecrivez s'il vous plait.\n");
	      L=0;
	    }
	  else
	    x=100;
	}
    }
  
  j=0;
  k=0;
  x=0;
  for(i=0;i<L;i=i)
    {
      if(OCCA[i]=='+'||OCCA[i]=='-')
	{
	  CLASSI[j][k]=OCCA[i];
	  i++;
	  k++;
	}
      else
	{
	  do{
	    CLASSI[j][k]=OCCA[i];
	    i++;
	    k++;
	  }
	  while((OCCA[i]!='+' && OCCA[i]!='-') && i<L);
	  
	  if((OCCA[i]=='+'||OCCA[i]=='-') && i<L)
	    {
	      j++;
	      /*---------------------------------------------------------------------------------*/
	      /*Donne le nombre des elements de ce ligne dans le tableau COUNT[x] quand il y a retour à la ligne.*/
	      COUNT[x] = k;
	      x++;
	      /*--------------------------------------------------------------------------------*/
	      k=0;
	      CLASSI[j][k]=OCCA[i];
	      k++;
	      i++;
	    }
  	}
    }
  
  COUNT[x]=k;/*Donne le nombre du dernier ligne dans x.*/

  pm=0;
  /*Separer chacun signe positif ou négatif par ligne.*/
  for(j=0;j<CMONOME;j++)
    {
      for(k=0;k<LMONOME;k++)
	{
	  switch(CLASSI[j][k])
	    {
	    case '-' :
	      {
		if(CLASSI[j][k+1]=='+')
		  PLUS_MOINS[pm]=-1;
		else if(CLASSI[j][k+1]=='-')
		  PLUS_MOINS[pm]=1;
		else
		  PLUS_MOINS[pm]=-1;
	      }
	      ; break;
	    case '+' :
	      {
		if(CLASSI[j][k+1]=='+')
		  PLUS_MOINS[pm]=1;
		else if(CLASSI[j][k+1]=='-')
		  PLUS_MOINS[pm]=-1;
		else
		  PLUS_MOINS[pm]=1;
	      }
	      ; break;
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
	    case '0':
	    case 'x': PLUS_MOINS[pm]=1 ;break;
	    }
	  pm++;
	  k=LMONOME;
	}
    }


  x=0;  
  jcoe=0;kcoe=0;  
  for(j=0;j<CMONOME;j++)
    {
      for(k=0;k<LMONOME;k++)
	{
	  if (CLASSI[j][k]=='|')
	    {
	      k=LMONOME;
	      jcoe--;}
	  else if((CLASSI[j][k]=='+' || CLASSI[j][k]=='-') && (CLASSI[j][k+1]!='+' && CLASSI[j][k+1]!='-'&&CLASSI[j][k+1]!='x'))
	    {
	      do
		{
		  COEFF[jcoe][kcoe] = CLASSI[j][k+1];
		  kcoe++;
		  COUNT_2[x]=kcoe;
		  k++;
		}
	      while(CLASSI[j][k+1]!='x'&& CLASSI[j][k+1]!='|');
	    }
	  else if((CLASSI[j][k]=='+' || CLASSI[j][k]=='-') && (CLASSI[j][k+1]=='+' || CLASSI[j][k+1]=='-')&&(CLASSI[j][k+2]!='x'))
	    {
	      do
		{
		  COEFF[jcoe][kcoe] = CLASSI[j][k+2];
		  kcoe++;
		  COUNT_2[x]=kcoe;
		  k++;
		}
	      while(CLASSI[j][k+2]!='x' && CLASSI[j][k+2]!='|');
	    }
	  else if(CLASSI[j][k]=='1'||CLASSI[j][k]=='2'||CLASSI[j][k]=='3'||CLASSI[j][k]=='4'||CLASSI[j][k]=='5'||CLASSI[j][k]=='6'||CLASSI[j][k]=='7'||CLASSI[j][k]=='8'||CLASSI[j][k]=='9'||CLASSI[j][k]=='0')
	    {
	      do
		{
		  COEFF[jcoe][kcoe] = CLASSI[j][k];
		  kcoe++;
		  COUNT_2[x]=kcoe;
		  k++;
		}
	      while(CLASSI[j][k]!='x'&&CLASSI[j][k]!='|');
	    }
	  else if((CLASSI[j][k]=='x')||(CLASSI[j][k]=='+'&&CLASSI[j][k+1]=='x')||(CLASSI[j][k]=='-'&&CLASSI[j][k+1]=='x')||(CLASSI[j][k]=='+'&&CLASSI[j][k+1]=='-'&&CLASSI[j][k+2]=='x')||(CLASSI[j][k]=='-'&&CLASSI[j][k+1]=='+'&&CLASSI[j][k+2]=='x')||(CLASSI[j][k]=='+'&&CLASSI[j][k+1]=='+'&&CLASSI[j][k+2]=='x')||(CLASSI[j][k]=='-'&&CLASSI[j][k+1]=='-'&&CLASSI[j][k+2]=='x'))
	    {
	      COEFF[jcoe][kcoe]='1';
	      COUNT_2[x]=1;
	    }
	  k=LMONOME;
	}
      jcoe++;
      kcoe=0;
      x++;
    }
  
  x=0;
  J=jcoe;
  for(jcoe=0;jcoe<J;jcoe++)     /*Vérifie le tableau "classification.*/
    {
	for(kcoe=0;kcoe<COUNT_2[x];kcoe++)
	  {
	    COEFF2[jcoe][kcoe]=COEFF[jcoe][kcoe];
	    COEFF2[jcoe][kcoe]=COEFF2[jcoe][kcoe]-48;
	  }
	x++;
    }
  x=0;

  /* Maintenant!
   * Le tableau PLUS_MOINS est le signe positif et négatif pour chacun monome.
   * Le tableau COUNT est le nombre des elements dans chacun ligne. 
   * Le tableau COEFF est le coefficient dans chacun monome par chacun ligne.(Il est type char)
   */
  
  reel=0;pm=0;x=0;
  
  for(reel=0;reel<J;reel++)
      {
	REELCOEFF[reel]=0;
      }
  
  reel=0;
  
  for(jcoe=0;jcoe<J;jcoe++)
    {
      for(kcoe=0;kcoe<COUNT_2[x];kcoe++)
	{
	  REELCOEFF[reel]=REELCOEFF[reel]+COEFF2[jcoe][kcoe]*pow(10,(COUNT_2[x]-kcoe-1));
	  
	}
      REELCOEFF[reel]=REELCOEFF[reel]*PLUS_MOINS[pm];
      pm++;
      reel++;
      x++;
    }

  /*REELCOEFF le tableau <coefficient> reel ,J est l'indice de REELCOEFF.*/
  for(ind=0;ind<LMONOME;ind++)
    INDICE[ind]=0;
  
  ind=0;x=0;

  for(j=0;j<J;j++)
    {
      for(k=0;k<LMONOME;k++)
	{
	  if(CLASSI[j][k]=='^')
	    {
	      while(k+1<COUNT[x])
		{
		  trans=CLASSI[j][k+1];
		  trans=trans-48;
		  INDICE[ind]=INDICE[ind]+trans*pow(10,(COUNT[x]-k-2));
		  k++;
		}
	      break;
	    }
	  else if(CLASSI[j][k]=='x' && CLASSI[j][k+1]== '|')
	    {
	      INDICE[ind]=1;
	      break;
	    }
	  else
	    INDICE[ind]=0;
	 
	}
      ind++;
      x++;
    }

  /*Maintenant, on a reussi a obtenir le tableau <degre> homologue.*/
  for(x=0;x<CMONOME;x++)
      COEFF_ORDONNE[x]=0;

  for(x=0;x<CMONOME;x++)
    COEFF_ORDONNE[INDICE[x]]=COEFF_ORDONNE[INDICE[x]]+REELCOEFF[x];
}




/*Antecedent: coeff1 et coeff2 sont les tableaux <coefficients> des polynomes, result est le tableau <sommation>.
 *
 *Consequent: coeff1 et coeff2 sont deux tableaux <coefficients> des polynomes par la routine <lecture> dans <main>.             .
 *            result est le tableau <coefficient> apres calculer dans la routine <lecture>.
 *Role      : Cette routine additionne les elements homologues dans tous les deux tableaux,et donne la valeur dans <resultat>.
 */
void addition(double coeff1[CMONOME],double coeff2[CMONOME],double result[CMONOME])
{
  int x=0;
  
  for(x=0;x<CMONOME;x++)
    result[x]=0;

  /*L'addition des elements homologues.*/
  for(x=0;x<CMONOME;x++)
    result[x]=coeff1[x]+coeff2[x]; 
}




/*Antecedent: coeff1 et coeff2 sont les tableaux <coefficients> des polynomes,result est le tableau <soustraction>.
 * 
 *Consequent: coeff1 et coeff2 sont deux tableaux <coefficients> des polynomes par la routine <lecture> dans <main>.             .
 *            result est le tableau <coefficient> apres calculer dans la routine <lecture>.
 *Role      : Cette routine soustrait les elements homologues dans tous les deux tableaux,et donne la valeur dans <resultat>.
 */
void soustraction(double coeff1[CMONOME],double coeff2[CMONOME],double result[CMONOME])
{
  int x=0;
  
  for(x=0;x<CMONOME;x++)
    result[x]=0;

  /*La soustraction des elements homologues.*/
  for(x=0;x<CMONOME;x++)
    result[x]=coeff1[x]-coeff2[x];
}





/*Antecedent : coeff1 et coeff2 sont les tableaux <coefficients> des polynomes,result est le tableau <multiplication>.
 *
 *Consequent:  coeff1 et coeff2 sont deux tableaux <coefficients> des polynomes par la routine <lecture> dans <main>.             .
 *             result est le tableau <coefficient> apres calculer dans la routine <lecture>.
 *
 *Role       : Cette routine multiplie les elements homologues un par un dans tous les deux tableaux,
 *             et donne la valeur dans <resultat>.
 */
void multiplication(double coeff1[CMONOME],double coeff2[CMONOME],double result[CMONOME])
{
  int x1=0;
  int x2=0;
  int x;
  
  for(x=0;x<CMONOME;x++)
    result[x]=0;
  
  for(x1=0;x1<CMONOME;x1++)
    {
      for(x2=0;x2<CMONOME;x2++)
	result[x1+x2]=result[x1+x2]+coeff1[x1]*coeff2[x2];
    }  
}




/*Antecedent : coeff1 et coeff2 sont les tableaux <coefficients> des polynomes,result est le tableau <dérivation>.
 *
*Consequent : coeff1 et coeff2 sont deux tableaux <coefficients> des polynomes par la routine <lecture> dans <main>.             .
 *            result est le tableau <coefficient> apres calculer dans la routine <lecture>.
 *
 *Role      : Cette routine donne chacun coefficient du tableau que vous ecrivez dans chacun coefficient 
 *            qui a le degre inférieur 1 à lui,
 *            et multiplie le degre de ce terme pour la dérivation.
 */
void derivation(double coeff[CMONOME],double result[CMONOME])
{
  int x=0;
  for(x=0;x<CMONOME;x++)
    result[x]=0+coeff[x+1]*(x+1);
  
  /*Le tableau resultat apres le calcule dernier, le dernier terme n'est pas initialise.*/
  result[CMONOME-1]=0;

  printf("p'(x) = ");
}



/*Antecedent: coeff est le tableau <coefficient> des polynomes.
 *
 *Consequent: coeff est le tableau <coefficient> des polynomes qui n'est pas encore donne la valeur.
 *
 *Role      : Cette routine calcule le resultat par <L'axiome de Horner> en utilisant la valeur que vous donnez.
 *            
 */
void evaluation(double coeff[CMONOME])
{
  int x=0;
  int t=0;
  int max=0;  
  int result=0;

  
  printf("Veuillez ecrire un entier:\n");/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  printf("x = ");
  scanf("%d",&t);

  /*Donne le maximal exponent de <coeff> dans <max>.*/
  for(x=0;x<CMONOME;x++)
    {
      if(coeff[x]!=0)
	  max=x;
    }

  /*Par le maximal exponent,multiplie et additionne de l'intérieur vers l'extérieur.*/
  x=max;
  if(max>0)
    {
      result=coeff[x]*t+coeff[x-1];
      for(x=max-1;x>=1;x--)
	result=result*t+coeff[x-1];
      printf("p(%d) = %d",t,result);
    }

  /*Si l'entrée est une constante, exporte directement.*/
  else if(max==0)
    {
      result=coeff[0];
      printf("p(%d) = %d",t,result);
    }
}




/*Antecedent : coeff1, coeff2 ,result et reste sont les tableaux <double>.
 *
 *Consequent : coeff1 et coeff2 sont respectivement dividendei et diviseur.
 *             result est quotient, reste est residu.
 *
 *Role       : f(x)=p(x)*g(x)+r(x),selon la formule, dans le division euclidienne,remplace f(x) par g(x), 
 *             et remplace g(x) par r(x) jusqu'au maximal exponent de r(x) est inférieur a le premier.
 */
void division_euclidienne(double coeff1[CMONOME],double coeff2[CMONOME],double result[CMONOME],double reste[CMONOME])
{
  int max1;
  int max2;
  int x;

  double centre[CMONOME];                 /*Ce tableau est comme le compteur additif. */
  double quotient[CMONOME];               /*Quotient(diviseur)*/
  
  double mu[CMONOME];                     /*Le produit*/
  double dividende[CMONOME];              /*Dividendei*/


  
  for(x=0;x<CMONOME;x++)
    {
      result[x]=0;
      reste[x]=0;
    }
  
  
  /*Trouve le maximal exponent respectivement dans <coeff1> et <coeff2>.*/
  for(x=0;x<CMONOME;x++)
    {
      if(coeff1[x]!=0)
	max1=x;
    }
  for(x=0;x<CMONOME;x++)
    {
      if(coeff2[x]!=0)
	max2=x;
    }
  /*Maintenant, on a le division par 2 pour 1 selon la demande.*/
  /*------------------------------------------*/   

  for(x=0;x<CMONOME;x++)
    {
      /*Initialiser le tableau.*/
      centre[x]=0;
      quotient[x]=0;

      /*D'abord, <coeff1> est comme residu et dividendei.*/
      dividende[x]=coeff1[x];
      reste[x]=coeff1[x];

      /*<coeff2> est comme quotient.*/
      quotient[x]=coeff2[x];
    }
  
  
  /*Avec le division euclidienne ,max1 baissera juequ'a il est inférieur a max2*/
  while(max1>max2)
    {
      /*Le dividendei divise par le diviseur font le quotient.*/
      centre[max1-max2]=centre[max1-max2]+reste[max1]/quotient[max2];

      /*Cumule le quotient pour obtenir le resultat.*/
      result[max1-max2]=result[max1-max2]+centre[max1-max2];

      /*On a obtenu le dividendei pour la circulation la prochaine fois.*/
      multiplication(result,quotient,mu);
      soustraction(dividende,mu,reste);

      /*Déterminer si le residu est égale à zéro.*/
      max1=0;
      for(x=0;x<CMONOME;x++)
	{
	  centre[x]=0;
	  
	  /*--------------------------------------------------*/
	  /*Cette étape est afin d'éviter des erreurs en langage C.
	   *L'erreur moyenne est inférieur a 0.00000000001.  
	   *Cette situation sera apparaît dans l'autres routines.
	   */
	  if(reste[x]<0.00000000001 && reste[x]>-0.0000000000)
	    reste[x]=0;
	  /*--------------------------------------------------*/
	  
 	  if(reste[x]!=0)
	    max1=x;
	}
    }
  /*
   * Ce objectif garantit qu’on progresse seulement une fois dans le cas du même coefficient.
   * C’est pour éviter le cas de mort de circulation en raison de la division entre les constantes.
   * C’est le même énoncé qu’on a momifié précédent.
   */
    if(max1==max2)
    {
      centre[max1-max2]=centre[max1-max2]+reste[max1]/quotient[max2];

      result[max1-max2]=result[max1-max2]+centre[max1-max2];

      multiplication(result,quotient,mu);
      soustraction(dividende,mu,reste);

      max1=0;
      for(x=0;x<CMONOME;x++)
	{
	  centre[x]=0;

	  if(reste[x]<0.00000000001 && reste[x]>-0.0000000000)
	    reste[x]=0;
	  
 	  if(reste[x]!=0)
	    max1=x;
	}
    }
}






/*Antecedent : coeff1, coeff2, et reste sont les tableaux <double>.
 *
 *Consequent : coeff1 et coeff2 sont deux les tableaux <coefficients> des polynomes pour <pgcd>
 *             result est le tableau <resultat>.
 *
 *Role       : Cette routine peux calculer le plus grand commun diviseur de deux polynomes par le division euclidienne
 *             Comme l'axiome :f(x)=p1(x)*g(x)+r(x),f(x) et g(x) ont le commun diviseur avec g(x) et r(x).
 */
void pgcd(double coeff1[CMONOME],double coeff2[CMONOME], double result[CMONOME])
{
  int x=0;
  int va=0;
  int i=0;

  double reste2[CMONOME];
  double reste[CMONOME];
  double quotient2[CMONOME];
  double quotient[CMONOME];
  
  int max1=0;
  int max2=0;

  /*Initialiser tous les tableaux.*/
  for(x=0;x<CMONOME;x++)
    {  
      quotient[x]=0;
      reste2[x]=0;
      quotient2[x]=0;
      result[x]=0;
    }

  /*D'abord,détermine les maximal exponents dans les deux polunomes.*/ 
    for(x=0;x<CMONOME;x++)
    {
      if(coeff1[x]!=0)
	max1=x;
    }
  for(x=0;x<CMONOME;x++)
    {
      if(coeff2[x]!=0)
	max2=x;
    }                                   

  /*Donne le polynome qui a un supérieur degre dans <reste> comme le dividende.*/ 
  if(max1>=max2)
    {
      for(x=0;x<CMONOME;x++)
	{
	  reste[x]=coeff1[x];
	  quotient[x]=coeff2[x];
	}      
    }
  else
    {
      for(x=0;x<CMONOME;x++)
	{
	  reste[x]=coeff2[x];
	  quotient[x]=coeff1[x];
	}      
    }

  
  for(x=0;x<CMONOME;x++)
    reste2[x]=reste[x];
  while(va==0)
    {
      for(x=0;x<CMONOME;x++)
	result[x]=quotient[x];
  
      division_euclidienne(reste,quotient,quotient2,reste2); 

      /*----------------------------------------------------------*/
      /*Ici,on detemine si chacun element dans <reste2> est tout egale a 0.*/
      i=0;
      for(x=0;x<CMONOME;x++)
	{
	  if(reste2[x]<0.00000000001 && reste2[x]>-0.00000000001)
	    reste2[x]=0;
	}	  
      for(x=0;x<CMONOME;x++)
	{
	  if(reste2[x]!=0)
	    i=i;
	  else
	    i++;
	  
	  if(i==CMONOME)
	    va=1;
	}
      i=0;
      /*------------------------------------------------------------*/

      /*Quand il y a une valeur qui n'est pas egale a 0,on donne un nouveau valeur et fait un circulation <while> à nouveau.*/
      if(va==0)
	{
	  for(x=0;x<CMONOME;x++)
	    {
	      reste[x]=quotient[x];
	      quotient[x]=reste2[x];
	    }
	}      
    }
}





/*Antecedent: coeff1, coeff2, et reste sont les tableaux <double>.
 *
 *Consequent: coeff1 et coeff2 sont deux les tableaux <coefficients> des polynomes pour <ppcm>
 *             result est le tableau <resultat>.
 *
 *Role      : Cette routine utilise l'axiome: le plus petit commun multipe est egale a le quotient entre 
 *            le produit de deux polynomes et le plus grand commun diviseur.
 */
void ppcm(double coeff1[CMONOME],double coeff2[CMONOME],double result[CMONOME])
{
  double mu[CMONOME];
  double pgcd12[CMONOME];
  double reste[CMONOME];

  /*Calcule le plus grand commun multipe de deux polynomes.*/
  pgcd(coeff1,coeff2,pgcd12);

  /*Calcule le produit de deux polynomes.*/
  multiplication(coeff1,coeff2,mu);

  /*Le produit divise par le plus grand commun multipe.*/
  division_euclidienne(mu,pgcd12,result,reste);  /*Ici, le residu <reste> doit etre 0.*/
}




/*Antecedent : reesultd est le tableau <double>.
 *
 *Consequent : resultd est le polynome qui sera <printf>.
 *
 *Role       : Cette routine <printf> le tableau <entier> dans le terminal,comprendu
 *             "+" "-" "*" "d".
 */
void ecriture(double resultd[CMONOME])
{
  
  int x=0;
  int max=0;
  int result[CMONOME];

  /*Changer le type <int> par <double>.*/
  for(x=0;x<CMONOME;x++)
    result[x]=resultd[x];

  /*Calcule le terme qui a le maximal exponent.*/
  for(x=0;x<CMONOME;x++)
    {
      if(result[x]!=0)
	max=x;
    }

  /*Analyser de <max=0,max=1> a <max>1>.*/
  if(max==0)
    printf("%d",result[0]);
  else if(max==1)
    {
      if(result[1]==1)
	printf("x");
      else if(result[1]==-1)
	printf("-x");
      else
	printf("%dx",result[1]);

      if(result[0]>0)
	printf("+%d",result[0]);
      else if(result[0]<0)
	printf("%d",result[0]);
    }
  else if(max>1)
    {
      if(result[max]==1)
	printf("x^%d",max);
      else if(result[max]==-1)
	printf("-x^%d",max);
      else
	  printf("%dx^%d",result[max],max);
      
      for(x=max-1;x>=2;x--)
	{
	  if(result[x]==1)
	    printf("+x^%d",x);
	  else if(result[x]==-1)
	    printf("-x^%d",x);
	  else
	    {
	      if(result[x]>0)
		printf("+%dx^%d",result[x],x);
	      else if(result[x]<0)
		printf("%dx^%d",result[x],x);
	    }
	}
      if(result[1]==1)
	printf("+x");
      else if(result[1]==-1)
	printf("-x");
      else
	{
	  if(result[1]>0)
	    printf("+%dx",result[1]);
	  else if(result[1]<0)
	    printf("%dx",result[1]);
	}

      if(result[0]>0)
	printf("+%d",result[0]);
      else if(result[0]<0)
	printf("%d",result[0]);
    }
}





/*Antecedent : result est le tableau <double>.
 * 
 *Consequent : result est le polynome qui sera <printf>.
 *
 *Role       : Cette routine <printf> le tableau <double> dans le terminal,comprendu
 *             "/" "g" "p" "f".
 */
void double_ecriture(double result[CMONOME])
{
  
  int x=0;
  int max=0;

  /*Il est le meme chose que la fontion derniere , sauf les variables.*/
  for(x=0;x<CMONOME;x++)
    {
      if(result[x]<0.000000001 && result[x]>-0.000000001)
	result[x]=0;
    }
  for(x=0;x<CMONOME;x++)
    {
      if(result[x]!=0)
	max=x;
    }
  
  if(max==0)
    printf("%.2f",result[0]);
  else if(max==1)
    {
      if(result[1]==1)
	printf("x");
      else if(result[1]==-1)
	printf("-x");
      else
	printf("%.2fx",result[1]);

      if(result[0]>0)
	printf("+%.2f",result[0]);
      else if(result[0]<0)
	printf("%.2f",result[0]);
    }

  else if(max>1)
    {
      if(result[max]==1)
	printf("x^%d",max);
      else if(result[max]==-1)
	printf("-x^%d",max);
      else
	  printf("%.2fx^%d",result[max],max);
      
      for(x=max-1;x>=2;x--)
	{
	  if(result[x]==1)
	    printf("+x^%d",x);
	  else if(result[x]==-1)
	    printf("-x^%d",x);
	  else
	    {
	      if(result[x]>0)
		printf("+%.2fx^%d",result[x],x);
	      else if(result[x]<0)
		printf("%.2fx^%d",result[x],x);
	    }
	}
      if(result[1]==1)
	printf("+x");
      else if(result[1]==-1)
	printf("-x");
      else
	{
	  if(result[1]>0)
	    printf("+%.2fx",result[1]);
	  else if(result[1]<0)
	    printf("%.2fx",result[1]);
	}

      if(result[0]>0)
	printf("+%.2f",result[0]);
      else if(result[0]<0)
	printf("%.2f",result[0]);
    }
}





/*Antecedent : coeff est le tableau <double>.
 *
 *Consequent : coeff est le polynome qui sera factorise.
 *
 *Role       : Cette routine factorise le polynome que vous ecrivez par calculer 
 *             le diviseur du terme qui a le maximal exponent et le diviseur du terme qui a le minimum exponent
 *             pour trouver les racines possibles, ensuite crible 
 *             les racines reels(comprendu les racines binaires,triplex......)        
 */
void factorisation(double coeff[CMONOME])
{
  int x;
  int i,j;
  int a=0;
  int L;
  int y;
  
  int max=0;
  int min=0;

  /*Le tableau ammasant les diviseurs de coefficient.*/
  int maxresoudre[100]={0};
  int minresoudre[100]={0};

  int coeffint[CMONOME];

  /*La longeur de <maxresoudre[100]> et <minresoudre[100]>.*/
  int lmax=0;
  int lmin=0;

  double racine_pro[100];/*Les racines possibles*/

  double m[100]={0};
  double n[100]={0};

  double reel[100]={0};

  /*reel2 est le tableau <reel> qui a efface les racines réitératifs.*/
  double reel2[100]={0};
  
  double result=0;

  /*La quantité intermédiaire dans le dérivation.*/
  double deriva[CMONOME]={0};

  double final[100];

  double ecri[CMONOME]={0};
  double rest[CMONOME];
  double mu[CMONOME];

  double f[CMONOME]={0};


  /*Changer <coeff> pour le tableau <int>, car il faut etre <entier> pour le reste.*/
  for(x=0;x<CMONOME;x++)
    coeffint[x]=coeff[x];

  /*Calculer le maximal exponent et le minimum exponent.*/
  for(x=0;x<CMONOME;x++)
    {
      if(coeffint[x]!=0)
	{
	  min=x;
	  x=CMONOME;
	}
    }

  for(x=0;x<CMONOME;x++)
    {
      if(coeffint[x]!=0)
	{
	  max=x;
	}
    }


  /*Calculer tous les diviseurs et donne le valeur.*/
  i=0;
  for(x=0;x<abs(coeffint[max]);x++)
    {
      if((coeffint[max]%(x+1))==0)
	{
	  maxresoudre[i]=abs(coeffint[max]/(x+1));
	  i++;
	}
    }
  i=0;
  for(x=0;x<abs(coeffint[min]);x++)
    {
      if((coeffint[min]%(x+1))==0)
	{
	  minresoudre[i]=abs(coeffint[min]/(x+1));
	  i++;
	}
    }

  /*Efface 0 dans le tableau de diviseurs.*/
  i=0; 
  for(x=0;x<CMONOME;x++)
    {
      if(maxresoudre[x]!=0)
	{
	  maxresoudre[i]=maxresoudre[x];
	  if(i!=x)
	    maxresoudre[x]=0;
	  i++;
	}
    }
  j=0;  
  for(x=0;x<CMONOME;x++)
    {
      if(minresoudre[x]!=0)
	{
	  minresoudre[j]=minresoudre[x];
	  if(j!=x)
	    minresoudre[x]=0;
	  j++;
	}
    }
  /*Trouve la valeur de l'évaluation de la maximal longeur.*/
  lmax=i;
  lmin=j;
  
  /*m,n sont les deux tableux <double> pour le division.*/
  for(x=0;x<100;x++)
    {
      m[x]=maxresoudre[x];
      n[x]=minresoudre[x];
    }

  /*Divise les diviseurs pour obtenir les racines possibles.*/
  x=0; 
  for(i=0;i<lmax;i++)
    {
      for(j=0;j<lmin;j++)
	{
	  racine_pro[x]=n[j]/m[i];/*Ce tableau est le tableau qui a tous les racines possibles.*/
	  x++;
	}    
    }
  L=x;
  
  /*Trouve les racines reels.*/  
  i=0;a=0;
  for(x=0;x<L;x++)
    {
      for(a=0;a<CMONOME;a++)
	result=result+coeff[a]*pow(racine_pro[x],a);

      /*Donne les termes qui a ete estime 0 dans le tableau <reel>.*/	    
      if(result> -0.00000000001 && result< 0.00000000001)
	result=0;   
      if(result==0)
	{
	  reel[i]=racine_pro[x];
	  i++;
	}
      result=0;
      
    }
  /*Repete le meme travail.*/
  
  for(x=0;x<L;x++)
    {
      for(a=0;a<CMONOME;a++)
	result=result+coeff[a]*pow(-racine_pro[x],a);

      if(result> -0.00000000001 && result< 0.00000000001)
	result=0;      
      if(result==0)
	{
	  reel[i]=-racine_pro[x];
	  i++;
	}
      result=0;
      
    }
  L=i;

  /*Donne les racines qui a ete efface les réitératifs de <reel> dans le tableau <reel2>.*/
  y=0;i=0;
  for(x=0;x<L;x++)
    { 
      for(a=0;a<i;a++)
	{	  
	  if(reel[x]!=reel2[a])
	    {
	      y++;
	    }
	}    
      if(y==i)
	{
	  reel2[i]=reel[x];
	  i++;
	}
      y=0;
    }  
  /*L est la longeur de <reel2>.*/
  L=i;  

  /*Donne <coeff> dans <dervia> pour le debut du dérivation.*/
  for(x=0;x<CMONOME;x++)
    deriva[x]=coeff[x];

  /*Donne une nouvelle valeur par un derivation, jusqu'a tous les racines ne pourent pas faire f(x)=0.*/ 
  result=0;y=1;i=0;  
  while(y!=0)
    {
      /*Donne y=0 quand la circulation commence,quand ne donne pas, y ne augment pas, ensuite la circulation sera cesse.*/
      y=0;
      
      for(x=0;x<L;x++)
	{
	  for(a=0;a<CMONOME;a++)
	    result=result + deriva[a]*pow(reel2[x],a);
	  
	  if(result> -0.00000000001 && result< 0.00000000001)
	    {
	      final[i]=reel2[x];
	      i++;
	      y++;
	    }
	  result=0;
	}

      /*Faire le derivation et donne les racines dans le tableau.*/
      for(a=0;a<CMONOME;a++)
	deriva[a]=deriva[a+1]*(a+1);
      deriva[CMONOME-1]=0;
    }
  
  /*
   *On peux trouver tous les racines qui ne sont pas 0 par les mesures.
   *Puis,on determine le nombre de 0.
   */
  result=0; y=1;/*Ici, i n'est pas initialise, car <final> a besoin de donner les valeurs ensuite.*/
  for(x=0;x<CMONOME;x++)
    deriva[x]=coeff[x];
  while(y!=0)
    {
      y=0;
      
      for(a=0;a<CMONOME;a++)
	result =result + deriva[a]*pow(0,a);
      
      if(result> -0.00000000001 && result< 0.00000000001)
	{
	  final[i]=0;
	  i++;
	  y++;
	}
 
      for(a=0;a<CMONOME;a++)
	deriva[a]=deriva[a+1]*(a+1);
      deriva[CMONOME-1]=0;
    }
  L=i;

  /*On doit montrer par (x-α) ,donc le coefficient de <x> egale a 1.*/
  ecri[1]=1;
  if(L==0)
    {
      printf("Ce polynome est non-factorisation: ");
      ecriture(coeff);
    }
  else
    {
      printf("le polynome par factorisation est: \n");

      for(x=0;x<L;x++)
	{
	  ecri[0]=-final[x];
	  
	  printf("(");
	  double_ecriture(ecri);
	  printf(")*");
	}

      /*Trouve les termes restants apres choisir les termes cartésiens.*/
      for(x=0;x<CMONOME;x++)
	f[x]=coeff[x];
      
      for(x=0;x<L;x++)
	{
	  ecri[0]=-final[x];
	  division_euclidienne(f,ecri,mu,rest);

	  for(a=0;a<CMONOME;a++)
	    f[a]=mu[a];
	}
      /*Printf les termes restants.*/
      printf("(");
      double_ecriture(mu);
      printf(")");
    }
}

/************************************************************************************************************************************/
int main(void)
{
  char a;

  double result[CMONOME];
  int x;
  
  double p1[CMONOME];
  double p2[CMONOME];

  double r1[CMONOME];
  double r2[CMONOME];
  
  /*int max;*/

  for(x=0;x<CMONOME;x++)
    result[x]=0;
  printf("Instructions d’utilization:\n");
  printf("1 Donnez les polynômes dont la variable est lettre minuscule x , les coefficients sont tout entiers.\n");
  printf("2 Donnezle terme degré par ^ .\n");
  printf("3 Arrêtez par Enter .\n");
  printf("4  Ne pas ajoutez de parenthèses.\n");
  printf("5  Le maximal exponent des polynômes est inférieur à 100, la longueur par un monôme est inférieur à 20.(On peux modifier cette longueur par #define )\n");
  printf("6 Utilisant la division euclidienne, on utilise P(1)diviser P(2)tacitement.\n");
  printf("7 Il n’y a que deux fractions décimale dans la division euclidienne et le plus grand commun diviseur.\n");
  printf("8 Donnez les signes dans le menu que nous vous offrons.\n");
  printf("9 Donnez q pour quitter.\n");
  printf("********************************************************************\n\n");
  printf("\t+ : addition\n");
  printf("\t- : soustraction\n");
  printf("\t* : multiplication\n");
  printf("\t/ : division\n");
  printf("\td : derivation\n");
  printf("\te : evaluation\n");
  printf("\tf : factorisation par (x-a)\n");
  printf("\tg : plus grand commun divisieur\n");
  printf("\tp : plus petit commun multiple\n");
  printf("\tq : quit\n");
  
  
  
  while(a!='q')
    {
      printf("\nEcrivez le signe de l'opération que vous voulez:");
      scanf("%c",&a);

      switch(a)
	{
	case '+':{lecture(p1,1);lecture(p2,2);addition(p1,p2,result);
	    printf("p1(x) + p2(x) = ");ecriture(result);}                         break;
	  
	case '-':{lecture(p1,1);lecture(p2,2);soustraction(p1,p2,result); 
	    printf("p1(x) - p2(x) = ");ecriture(result);}                         break;
	  
	case '*':{lecture(p1,1);lecture(p2,2);multiplication(p1,p2,result); 
	    printf("p1(x) * p2(x) = ");ecriture(result);}                         break;
	  
	case 'd':{lecture(p1,0);derivation(p1,result);ecriture(result);}          break;
	  
	case 'e':{lecture(p1,0);evaluation(p1);}                                  break;

	case '/':{lecture(p1,1);lecture(p2,2);division_euclidienne(p1,p2,r1,r2);
	    printf("AN: p1(x) = (");double_ecriture(r1);
	    printf(")*p2(x) + (");double_ecriture(r2);printf(")");}               break;

	case 'g':{lecture(p1,1);lecture(p2,2);pgcd(p1,p2,result);
	    printf("Le plus grand commun diviseur est:");double_ecriture(result);}break;
	  
	case 'p':{lecture(p1,1);lecture(p2,2);ppcm(p1,p2,result);
	    printf("Le plus petit commun mutiple est:");double_ecriture(result);} break;

	case 'f':{lecture(p1,0);factorisation(p1);}                               break;
	  
	case 'q':                                                                 break;
	}

    }     


  return EXIT_SUCCESS;
}

 

