
#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Рабочий Проект :RGZ (Сетевая задача 'Задача о пути')
  Группа: 5ПМ-1  Преподаватель : Зверева Т.В.(кафедра ПМиИ)
  Авторы проекта Студенты: Cвириденко О.В., Родионова Е.А. */
/* Программа предназначена для нахождения минимального или максимального пути.
 На вход программы поступает матрица длин (размером N)
           |l(v[i],v[j]),если v[i]->v[j],
    r[i,j]=|0,v[i]<>v[j].*/

int MinMaxCalc(char  *FileIn,char  *FileOut,int FlagMinMax)
/*FlagMinMax=1-min ;2-max*/
/*-1:Cannot read data file;
  -2 :Cannot creat out file;
  -3:Table is not Matrix(n x n) Unknow Format date;
   0  :all normal   */
{

FILE *rf;FILE *hf;  /*double*/float Pr; int fl_Count;
int Count ;  /*╤ўхЄўшъ*/

if((hf = fopen(FileIn, "r"))==NULL) return(-1);

Count = 0; fl_Count=0;
while (fl_Count==0)  if (1== fscanf(hf, "%f",&Pr)) Count++;  else fl_Count=1;
if (Count>3)
{ Pr=sqrt((double)Count);
   if ((Pr!=floor(Pr)) || (Pr!=ceil(Pr)) || (floor(Pr)!=ceil(Pr))) { fclose(hf);return(-3);  }
  }
 else { fclose(hf);return(-3);  }

 if((rf=fopen(FileOut,"w"))==NULL) { fclose(hf);return(-2);  }

   int n; n=(int)Pr;  //n=14,  ўшёыю єчыют(тхЁ°шэ) /*число узлов(вершин)*/

/* allocate memory for the far pointer */
float  far *X;    //X[n][n+1];
X = (float far *) farmalloc(n*(n+1)*sizeof(float));
float  far *R;    //float R[n][n] тхёютр  ьрЄЁшЎр
R = (float far *) farmalloc(n*n*sizeof(float));

 int  i,j,k,p,fl; float VarMinMax;

/*Reading table..*/ rewind(hf); //fclose(hf);if((hf = fopen(FileIn, "r"))==NULL) {  fclose(rf);return(-1);}
if(FlagMinMax==1) VarMinMax=1e37; else VarMinMax=-1e37;
for(i=0;i<n;i++)
{ /*fprintf(rf,"\n");*/
  for(j=0;j<n;j++)
  { fscanf(hf,"%f",&Pr);
    if (Pr==0.00000000) R[i*n+j]=VarMinMax; else R[i*n+j]=Pr;
    /*fprintf(rf," %8.3f ",Pr);*/ }
 }
fclose(hf);

fprintf(rf,"\n╘рщы ╚ёїюфэ√ї ─рээ√ї= %s \n╥шя чрфрўш=%s \n",FileIn,((FlagMinMax==1)?"min":"max"));

for(i=0;i<(n*(n+1));i++) X[i]=0.0; //Обнуление

/*Начальный */ X[0*n+0]=0.0;for(i=n+1;i<(n*n);i+=(n+1)) X[i]=VarMinMax;

 /*Нахождение оптимального пути*/
for(k=0;k<n;k++)
 for(i=0;i<n;i++)
  switch(FlagMinMax)
   { case 1:{
      p=0;
      for(j=1;j<n;j++) if((X[j*(n+1)+k]+R[j*n+i])<(X[p*(n+1)+k]+R[p*n+i])) p=j;
      X[i*(n+1)+k+1]=X[p*(n+1)+k]+R[p*n+i];
      if (i==0) if(0.00000000<X[i*(n+1)+k+1]) X[i*(n+1)+k+1]=0.0;
      } break;
   case 2:{
      p=0;
      for(j=1;j<n;j++) if((X[j*(n+1)+k]+R[j*n+i])>(X[p*(n+1)+k]+R[p*n+i])) p=j;
      X[i*(n+1)+k+1]=X[p*(n+1)+k]+R[p*n+i];
      if (i==0) if(0.00000000>X[i*(n+1)+k+1]) X[i*(n+1)+k+1]=0.0;
      } break;
    }

/*Нахождение вершин оптимального пути и их вывод*/
if (X[n*(n+1)-1]==X[n*(n+1)-2])
 {
 k=n;
 while (X[n*n+k-1]==X[n*n+k-2])  k--;
 k++;
 fprintf(rf,"\n╬яЄшьры№эюх ёєььрЁэюх чэрўхэшх:=% 8.3g\n╫шёыю фєу:=%d\n═юьхЁр тхЁ°шэ=|%d",X[n*(n+1)-2],k,n);
 i=n-1;
 while (i!=-1)
  {
   fl=0;
   switch (FlagMinMax)
  { case 1:{
       p=0;
       for(j=1;j<n;j++) if ((X[j*(n+1)+k-1]+R[j*n+i])<(X[p*(n+1)+k-1]+R[p*n+i])) { p=j;fl=1; }
       } break;
  case  2:{
       p=0;
       for(j=1;j<n;j++) if ((X[j*(n+1)+k-1]+R[j*n+i])>(X[p*(n+1)+k-1]+R[p*n+i])) { p=j;fl=1; }
       } break;
     }
   if (fl!=0) fprintf(rf,"<-%d",p+1);
   if (i==p) i--; else i=p;
   }
   fprintf(rf,"<-1|.");
} else {  fprintf(rf,"\n╬яЄшьры№эюх ёєььрЁэюх чэрўхэшх:=NULL\n╫шёыю фєу:=NULL\n═юьхЁр тхЁ°шэ=|NULL"); } 

/* Вывод результатов */
 fprintf(rf,"\nTable of way:\n");
 for(i=0;i<n;i++)
{ fprintf(rf,"\n");
   for(j=0;j<(n+1);j++)  fprintf(rf," % 8.3g ",((X[i*(n+1)+j]==VarMinMax)?0.0:X[i*(n+1)+j]));
  }

 fclose(rf);
 return(0);
}

//int main()
//{ int i;
//i=MinMaxCalc("c:\\programs\\bc\\out\\netlen.prn","c:\\programs\\bc\\out\\_Dar.prn",1);
/*FlagMinMax=1-min ;2-max*/
/*-1:Cannot read data file;
  -2 :Cannot creat out file;
  -3:Table is not Matrix(n x n) Unknow Format date;
   0  :all normal   */
//printf("%d",i);
// return(0);
//}


