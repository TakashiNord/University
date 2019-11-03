

#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int NetFileCalc(char *nameLength_R,char *namePrice_C,char *nameIntense_D,
                            int FlagMinMax )
/*-1:Cannot read data file[nameLength_R];
   -11:Table is not Matrix [(n x n)]  Unknow Format date;
  -2 :Cannot read data file[namePrice_C];
   -22:Table is not Matrix [(n x n)]  Unknow Format date;
   -23:������ ������������ ������ :��������� ������ C[i,j]>=0 (C[i,j]<=0);
  -3 :Cannot read data file[nameIntense_D];
  -33:Table is not Matrix [(n x n)]  Unknow Format date;
  -4: Tables is not Matrix [(n x n)],Matrix [(n x n)],,Matrix [(n x 1)],  Unknow Format date;
   n  :all normal   */
/*  FlagMinMax=1;{1- min ; 2- max ; (<-��� ������� ������)}
  nameLength_R {������������ �������(���������� ������������)r[i,j] �� �����}
  namePrice_C {������������ �������(���������)c[i,j] �� �����}
  nameIntense_D {������������ �������(��������������)D[i] �� �����}
*/
{ 
float Pr; int fl,fl_Count,n1,n2,n3; int Count ;  /*�������*/    FILE *rf;

/*Reading table..*/ 
if((rf = fopen(nameLength_R, "r"))==NULL) return(-1);/*������������ ������� r[i,j] �� ����� */
Count = 0; fl_Count=0;
while (fl_Count==0)  if (1== fscanf(rf, "%f",&Pr)) Count++;  else fl_Count=1;
if (Count>3)
{  Pr=(float)Count;   Pr=sqrt((double)fabs(Pr));   n1=(int)Pr;
   if ((n1*n1)!=Count)  { fclose(rf);return(-11);  }
  }
 else { fclose(rf);return(-11);  }
fclose(rf);

if((rf = fopen(namePrice_C, "r"))==NULL) return(-2); /*������������ ������� �[i,j] �� ����� */
Count = 0; fl_Count=0;fl=0;
while (fl_Count==0) 
  if (1== fscanf(rf, "%f",&Pr))  { Count++; if (Pr<0)fl=1;}  else fl_Count=1;
if (Count>3)
{  Pr=(float)Count;   Pr=sqrt((double)fabs(Pr));   n2=(int)Pr;
   if ((n2*n2)!=Count)  { fclose(rf);return(-22);  }
  }
 else { fclose(rf);return(-22);  }
fclose(rf);

/*!�������� ������� ������*/
//if (fl!=0)  if (FlagMinMax==1)   return(-23); 
//if (fl==0) if (FlagMinMax==2)   return(-23); 

if((rf = fopen(nameIntense_D, "r"))==NULL){return(-3);} /*������������ ������� D[i] �� ����� */
Count = 0; fl_Count=0;
while (fl_Count==0) 
  if (1== fscanf(rf, "%f",&Pr)) {Count++;}  else fl_Count=1;
if (Count>0) {  n3=Count;  }
 else { fclose(rf);return(-33);  }
fclose(rf);

if ((n1==n2)&&(n1==n3)) return(n1);
return(-4);
}


int NetFileTest(char *nameFile,int Flag, int *Num)
/*-1:Cannot read data file
   -2:Table is not Matrix [(n x n)]  Unknow Format date;
   -3:Table is not Matrix [(n x 1)]  Unknow Format date;
   n  :all normal   */
{ 
float Pr; int fl,Count ;  /*�������*/    FILE *rf;

/*Reading table..*/ 
if((rf = fopen(nameFile, "r"))==NULL) return(-1);
Count = 0; fl=0;
while (fl==0)  if (1== fscanf(rf, "%f",&Pr)) Count++;  else fl=1;
fclose(rf);

if (Flag==1)
  if (Count>3)
    {  Pr=(float)Count;   Pr=sqrt((double)fabs(Pr));   fl=(int)Pr;
        if ((fl*fl)!=Count) { *Num=Count; return(-2);}
    }

*Num=Count;
if (Flag==2)  if (Count==0)  return(-3); else  fl=Count;

return(fl);
}