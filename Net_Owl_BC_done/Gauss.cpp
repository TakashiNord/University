
#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int GaussCalc(char  *FileIn,char  *FileOut)
/*-1:Cannot read data file;
  -2 :Cannot creat out file;
  -3:Table is not Matrix [(n x n) (n x 1)]  Unknow Format date;
  -4:Low far Memory;
   0  :all normal   */
{
 int  i,j,k,fl;   float Pr; 
int n; // ����� �����(������)
FILE *rf;FILE *hf;
int fl_Count; int Count ;  /*�������*/

if((hf = fopen(FileIn, "r"))==NULL) return(-1);

Count = 0; fl_Count=0;
while (fl_Count==0)  if (1== fscanf(hf, "%f",&Pr)) Count++;  else fl_Count=1;

if (Count>=6)
{  Pr=(double)Count;   Pr=sqrt(fabs(Pr));   n=(int)Pr;
   if ((n*n+n)!=Count)  { fclose(hf);return(-3);  }
  }
 else { fclose(hf);return(-3);  }
     
 if((rf=fopen(FileOut,"w"))==NULL) { fclose(hf);return(-2);  }

/* allocate memory for the far pointer */
float  far *A;    //float A[n][n];
if ((A = (float far *) farmalloc(n*n*sizeof(float)))==NULL) {fclose(rf); fclose(hf);return(-4); } 
float  far *B,*X; //float  B[n],X[n];
if ((B = (float far *) farmalloc(n*sizeof(float)))==NULL) {farfree(A);fclose(rf); fclose(hf);return(-4); }
if ((X = (float far *) farmalloc(n*sizeof(float)))==NULL) {farfree(A);farfree(B); fclose(rf); fclose(hf);return(-4);  }

/*Reading table..*/ rewind(hf); //fclose(hf);if((hf = fopen(FileIn, "r"))==NULL) {  fclose(rf);return(-1);}
for(i=0;i<n;i++) 
{ /*fprintf(rf,"\n");*/
   for(j=0;j<(n+1);j++)  
{ fscanf(hf,"%f",&Pr);
   if (j==n) B[i]=Pr; else A[i*n+j]=Pr;
 /* fprintf(rf," %8.3g ",Pr);*/ }
 }  
fclose(hf);

fl=0;
  for(j=0;(j<(n-1));j++)
   { /* max */k=j;for(i=k+1;i<n;i++) if ((fabs(A[i*n+j]))>(fabs(A[k*n+j]))) k=i;
      for(i=0;i<n;i++){ Pr=A[k*n+i];A[k*n+i]=A[j*n+i];A[j*n+i]=Pr; }
      Pr=B[k];B[k]=B[j];B[j]=Pr;
      if (A[j*n+j]!=0.0)
       for (i=j+1;i<n;i++)
        { Pr=-A[i*n+j]/A[j*n+j];
           for(k=j;k<n;k++) A[i*n+k]+=Pr*A[j*n+k];
           B[i]+=Pr*B[j];  }
       else { ; } /*fl=1;*/
    }
  if (fl==0)
   for(i=n-1;(i>=0);i--)
    { Pr=B[i];
      for(j=i+1;j<n;j++) Pr-=A[i*n+j]*X[j];
      if (A[i*n+i]==0.0) fl=1; else X[i]=Pr/A[i*n+i];
    }

 fprintf(rf,"\n���� �������� ������= %s \n",FileIn);
if (fl==0) 
{ fprintf(rf,"\nMethods Gauss : A*X=B \n X=A^-1*B= -->\n\n");
  for(i=0;i<n;i++)  fprintf(rf," % 8.3g \n",X[i]); }
 else 
{ fprintf(rf,"\nMethods Gauss : A*X=B\n��������!������� A ��������� \n����� ��������������-> \nA | B->\n");
   for(i=0;i<n;i++)
   { fprintf(rf,"\n");
     for(j=0;j<(n+1);j++) { if (j==n) Pr=B[i]; else Pr=A[i*n+j]; fprintf(rf," % 8.3g ",Pr); }
    }
 }  
       
 /* free the memory */  farfree(X);farfree(A);farfree(B);
 fclose(rf);
return (0);
}
