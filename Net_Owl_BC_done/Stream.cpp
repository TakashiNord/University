   
#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int StreamCalc(char  *FileIn,char  *FileOut)
/*-1:Cannot read data file;
  -2 :Cannot creat out file;
  -3:Table is not Matrix(n x n) Unknow Format date;
   0  :all normal   */
{

FILE *rf;FILE *hf;  /*double*/float Pr; int fl_Count;
int Count ;  /*Счетчик*/

if((hf = fopen(FileIn, "r"))==NULL) return(-1);

Count = 0; fl_Count=0;
while (fl_Count==0)  if (1== fscanf(hf, "%f",&Pr)) Count++;  else fl_Count=1;
if (Count>3)
{ Pr=sqrt((double)Count); 
   if ((Pr!=floor(Pr)) || (Pr!=ceil(Pr)) || (floor(Pr)!=ceil(Pr))) { fclose(hf);return(-3);  }
  }
 else { fclose(hf);return(-3);  }
     
 if((rf=fopen(FileOut,"w"))==NULL) { fclose(hf);return(-2);  }

   int n; n=(int)Pr;  //n=12,  число узлов(вершин)

float  /*double*/ far *X,*R; /* allocate memory for the far pointer */   //float R[n][n],X[n][n];  //весовая матрица и потока
X = (float far *) farmalloc(n*n*sizeof(float));   R = (float far *) farmalloc(n*n*sizeof(float));
//   X = (double far *) farmalloc(n*n*sizeof(double));   R = (double far *) farmalloc(n*n*sizeof(double));
   int far *nN,*Spot; //int  nN[n],Spot[n]; //матрица индексов
   nN = (int far *) farmalloc(n*sizeof(int));   Spot = (int far *) farmalloc(n*sizeof(int));
float  /*double*/ far *nQ; //float  nQ[n]; //матрица индексов
nQ = (float far *) farmalloc(n*sizeof(float));  //   nQ = (double far *) farmalloc(n*sizeof(double));

float  maxV; /*Поток*/   int  i,j,k,l,p,fl,fl1,Step;

/*Reading table..*/ rewind(hf); //fclose(hf);if((hf = fopen(FileIn, "r"))==NULL) {  fclose(rf);return(-1);}
for(i=0;i<n;i++) 
{ /*fprintf(rf,"\n");*/
   for(j=0;j<n;j++)  { fscanf(hf,"%f",&Pr);R[i*n+j]=Pr; /* fprintf(rf," %8.3f ",Pr);*/ }
 }  
fclose(hf);

//Основной блок
maxV=0;for(i=0;i<n;i++)for(j=0;j<n;j++)X[i*n+j]=0; //Начальный поток
fl=0;//флажок для завершения решения
Step=0;//Подсчет числа итераций необходимых для решения
while(fl==0)
{ //Step 1.Стирание пометок
  for(i=0;i<n;i++){nN[i]=0;nQ[i]=0;Spot[i]=0;}
  //Step 2.Расстанова пометок
  //Начальные условия
  i=0; nN[i]=0; nQ[i]=1e37; //very large number
  Spot[i]=1;//Пометка вершины для просмотра
  l=1;//счетчик помеченных и просмотренных вершин
  k=1;//счетчик помеченных вершин
  p=i;//максимальный номер помеченных(просмотренных) вершин
fl1=0;//флажок для завершения процесса расстановки пометок
while(fl1==0)
{ for(j=0;j<n;j++)
  if(nN[j]==0)
   if(R[i*n+j]!=0)
  {
  if(X[j*n+i]>0){ nN[j]=-i-1;nQ[j]=(nQ[i]<X[j*n+i])?nQ[i]:X[j*n+i]; k++; if (j>p) p=j; }
  if(nN[j]==0)
   if((R[i*n+j]-X[i*n+j])>0){nN[j]=i+1;nQ[j]=(nQ[i]<(R[i*n+j]-X[i*n+j]))?nQ[i]:R[i*n+j]-X[i*n+j];k++; if (j>p) p=j;}
   }
//Проверка - дошли ли до вершины-t
 if(nN[n-1]!=0) fl1=1;
  else
   if(k==l) {fl1=1;fl=1;}//Нельзя сделать дальнейших пометок
    else
    { //Выбор помеченной вершины для просмотра случ. образом
     randomize();
     while (!((Spot[i]==0)&&(nN[i]!=0)))  {  /*i=rand()%p+1;*/  i=random(p+1); }
     Spot[i]=1;l++;
   }
}
 if(fl==0) //Step3.
  { i=n-1;maxV+=nQ[n-1];
   while (i!=0)
   { if(nN[i]>0) X[abs(nN[i]-1)*n+i]+=nQ[n-1]; 
      if(nN[i]<0) X[i*n+abs(nN[i]+1)]-=nQ[n-1];
      if (nN[i]>0)  i=nN[i]-1; else if (nN[i]<0)  i=nN[i]+1; //i=nN[i];
       }
  }
Step++; }

 fprintf(rf,"\nStream:\nNumber Iter=%d         Max(Stream)=%8.4f\n",Step,maxV);
 for(i=0;i<n;i++) { fprintf(rf,"\n"); for(j=0;j<n;j++) fprintf(rf," % 8.3g ",X[i*n+j]);}
       
 /* free the memory */  farfree(X);farfree(R);farfree(nN);farfree(Spot);farfree(nQ);
 fclose(rf);
return (0);
}