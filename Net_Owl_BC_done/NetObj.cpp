
/* ������� ������ :�������� ������� ������
  ������������� : ������� �.�.(������� ����)
  ���������� : ���� �.,��������� �. ������ � ����� . "���",�.,1966. */

#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**************************************************************/
int TNetWindow::NetCalc(char *nameLength_R,char *namePrice_C,char *nameIntense_D,
             char *nameOut, int n,
            int FlagMinMax ,int FlagCase,int FlagSpot,int FlagCalc,int MaxStep,RTMessage )
/*-1:Cannot read data files;
  -2 :Cannot creat out file;
  -3 : Low memory;
   0  :all normal   */
/*  FlagMinMax=1;{1- min ; 2- max ; (<-��� ������� ������)}
  nameLength_R {������������ �������(���������� ������������)r[i,j] �� �����}
  namePrice_C {������������ �������(���������)c[i,j] �� �����}
  nameIntense_D {������������ �������(��������������)D[i] �� �����}
  nameOut {�������� ���� ������������ ������=����������� ����� x[i,j] }
  FlagCase=2;{1- � ������� �����������;2- � ������� ��������;3- ��. ������� (<-����� �������)}
  FlagSpot=1;{1- � ������;2- � �����(<-����������� �������)}
  FlagCalc=1;{1-On;0-Off (���������� �������� ������)}
 MaxStep=500;{(��������� ���������)������������ ����� �������� ��� ���������� ������}
*/

 /*�������� ����*/
{
//char *strEdit="\0";
//MessageBox(GetFocus(),"Begin","NetCalc",MB_OK);
//wsprintf(strEdit,"%d\n%d",Count,n3);_fstrcat(strEdit,"\0");
//MessageBox(GetFocus(),(LPCSTR)strEdit,(LPCSTR )nameIntense_D,MB_OK|MB_ICONSTOP);

/*��������������� ����������*/
int  kDelta1,kDelta2,kDeltai;
float minC,SumPr,nQmin,kDeltaMin,Delta2,Delta1,DeltaMin,SumStr;
int i,j,k,l,p,e,Step;
int  fl,fl1,fl2,fl3;/*������ ��� ������*/

 float Pr; FILE *rf,*hr;

/* allocate memory for the far pointer */     /*�������� ����������*/
float far *R;float far *C;float far *X;    //float R[n][n],C[n][n],X[n][n];
if((R = (float far *) farmalloc(n*n*sizeof(float)))==NULL) { return(-3); }/*� ����  ���������� ������������*/
if((C = (float far *) farmalloc(n*n*sizeof(float)))==NULL) { farfree(R);return(-3); }/*� ����  ���������*/
if((X = (float far *) farmalloc(n*n*sizeof(float)))==NULL) { farfree(C);farfree(R); return(-3); }/*� ����  ����� ������ ����� }*/
float far *D;float far *nQ; //float  D[n],nQ[n];
if((D = (float far *) farmalloc(n*sizeof(float)))==NULL) { farfree(X);farfree(C);farfree(R);return(-3); } /*� ����  ��������������*/
if((nQ = (float far *) farmalloc(n*sizeof(float)))==NULL) { farfree(X);farfree(C);farfree(D);farfree(R);farfree(D); return(-3); } /*� ����  ��������� */
int far *nN;int far*Spot;
if((nN = (int far *) farmalloc(n*sizeof(int)))==NULL) { farfree(X);farfree(C);farfree(D);farfree(R);farfree(nQ);return(-3); }/*� ����  ������� ������*/
if((Spot= (int far *) farmalloc(n*sizeof(int)))==NULL) { farfree(X);farfree(C);farfree(D);farfree(R);farfree(nN);farfree(nQ); return(-3); }/*� ����  �������� � ����������� ������*/


/*Reading table..*/ 
if((rf = fopen(nameLength_R, "r"))==NULL) return(-1);/*������������ ������� r[i,j] �� ����� */
if((hr = fopen(nameIntense_D, "r"))==NULL){ fclose(rf);return(-1); } /*�������� ��� � ����� D[i] �� � �� */
for(i=0;i<n;i++)
{ fscanf(hr,"%f",&Pr);D[i]=Pr;
  for(j=0;j<n;j++){ fscanf(rf,"%f",&Pr);R[i*n+j]=Pr; }
 }
fclose(rf);fclose(hr);

if((rf = fopen(namePrice_C, "r"))==NULL) return(-1); /*������������ ������� �[i,j] �� ����� */
fl=0;
for(i=0;i<n;i++)
 for(j=0;j<n;j++)
   { fscanf(rf,"%f",&Pr);C[i*n+j]=Pr; if (Pr<0) fl=1;   }
fclose(rf);

strEdit[0]='\0';
if (fl!=0) if (FlagMinMax==1)
 { _fstrcat(strEdit,"Status:  [���������]->C[i,j]<=0........\n�����:��� ������ �� MIN [���������] ������ ���� C[i,j]>=0\n\t.......������ ������?");
     if (IDNO==MessageBox(GetFocus(),strEdit," ? ������ ������������ ������",MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION) )
       { farfree(X);farfree(C);farfree(D);farfree(R);farfree(nN);farfree(nQ);farfree(Spot); return(-23); } 
  }
if (fl==0) if (FlagMinMax==2) 
 { _fstrcat(strEdit,"Status:  [���������]->C[i,j]>=0........\n�����:��� ������ �� MAX [���������] ������ ���� C[i,j]<=0\n\t......������ ������?");
    if (IDNO==MessageBox(GetFocus(),strEdit," ? ������ ������������ ������",MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION)) 
      { farfree(X);farfree(C);farfree(D);farfree(R);farfree(nN);farfree(nQ);farfree(Spot); return(-23); } 
} 
strEdit[0]='\0';

if((rf = fopen(nameOut, "w"))==NULL) return(-2);

/*������(������ �������� ������ ���������).�����(���� ������..*/

/*��������� �����:*/for(i=0;i<n;i++) for(j=0;j<n;j++) X[i*n+j]=0.0;

/*��� 0.(��������������� ���) */
/*fl=0; for(i=0;i<n;i++) for(j=0;j<n;j++) if (C[i*n+j]<0.0) fl=1;*/
if (fl==0) { /*��� ������ �� ������� (C[i,j]>=0)*/
 for(i=0;i<n;i++)
  if (D[i]>0.00000000)
   { /*����� �������� */
       k=0; for(j=1;j<n;j++) if (C[i*n+k]>C[i*n+j]) k=j;
       minC=C[i*n+k];
       if (minC!=0.0000000) {
         for(j=0;j<n;j++) /*����������->*/
          { if (R[i*n+j]!=0.0) C[i*n+j]-=minC;
            if (R[j*n+i]!=0.0) C[j*n+i]+=minC; }
        }
   }
 }

randomize();
Step=0;/*������� ����� �������� ����������� ��� �������*/
fl=0;/*������ ��� ���������� �������*/
while (0==fl) /*���������� ������*/
{
  l=0;/*������� ���������� � ������������� ������*/
  k=0;/*������� ���������� ������*/
/*��� 1.����������� �������(���������� ������������� ������ � ��������� �����)*/
/*��������� �������.�������� ������� � ����������� ������� ��� ����������*/
 for(j=0;j<n;j++)
 { nN[j]=0;nQ[j]=0;Spot[j]=0;
   if (D[j]>0)
   { nN[j]=0;nQ[j]=D[j];Spot[j]=0;k++;
     /*������� ������� ��� ���������*/
     if (k==1) { i=j;l++;Spot[j]=1; } else  {;}
     p=j;/*������������ ����� ����������(�������������) �������*/
    }
 }
//***********************
 if (k==0) { /* free the memory */
   farfree(X);farfree(C);farfree(D);farfree(R);farfree(nN);farfree(nQ);farfree(Spot);
   fprintf(rf,"\n!������ ������������ ������ : ��� ����������!\n(D[i]>0- ���������,D[i]<0-�����");
   fclose(rf); return(0);
  }
//*************************
  fl2=0;fl3=0;/*������ ��� ���������� �������� ����������� �������*/
  while (0==(fl2+fl3)) /*����������� �������*/
  { 
     /***********************/     Yield();

    switch (FlagSpot)
    { case 1: j=0; break; case  2: j=n-1;break; default :break; }

    fl1=0;
    while (fl1==0)
     {
      if ((nN[j]==0)&&(nQ[j]==0.0)) /*������� �� ��������*/
      {
	if ((X[j*n+i]>0)&&(C[j*n+i]==0.0))
	{ nN[j]=-i-1;nQ[j]=(nQ[i]<X[j*n+i])?nQ[i]:X[j*n+i];
	  k++; if (j>p) p=j; else { ; }
          if (D[j]<0.0) { fl2=1;fl1=1;e=j; } else { ; }
	 } else { ; }

	if ((nN[j]==0) && (nQ[j]==0.0))
	 if((R[i*n+j]>0)&&(C[i*n+j]==0.0))
	  { nN[j]=i+1;nQ[j]=(nQ[i]<R[i*n+j])?nQ[i]:R[i*n+j];
            k++; if (j>p) p=j;else { ; }
	    if (D[j]<0.0) { fl2=1;fl1=1;e=j; } else { ; }
	   } else { ; } else { ; }
       } else { ; }
      switch (FlagSpot)
       { case 1: if (j==(n-1)) fl1=1; else j++; break;
         case 2: if (j==0) fl1=1; else j--;break;
         default :break; }

     }  /*���������� ������� �������*/

    if (fl2==0)
      if (k==l)  fl3=1; /*������ ������� ���������� �������*/
       else /*����� ���������� ������� ��� ���������*/
        switch (FlagCase){
          case 1: /*����� ������� � ������� �����������*/
                 i=-1;fl1=0;j=0;
                 while(0==fl1)
	         { if((Spot[j]==0)&&((nN[j]!=0)||(nQ[j]!=0)))
                     { i=j;Spot[j]=1;l++;fl1=1; } else { ; }
                   if (j==p)  fl1=1; else j++;
	          }
	         if (i<0) fl3=1; else { ; }
                 break;
          case 2: /*����� ������� � ������� ��������*/
                 i=-1;fl1=0;j=p;
                 while(0==fl1)
                 { if((Spot[j]==0)&&((nN[j]!=0)||(nQ[j]!=0)))
                     { i=j;Spot[j]=1;l++;fl1=1; } else { ; }
                   if (j==0)  fl1=1; else j--;
                  }
                 if (i<0) fl3=1; else  {;}
	         break;
          case 3:/*����� ������� ��. �������*/
	         i=-1;fl1=0;randomize();
	         while (fl1==0)
                             { j=random(p+1);
	             if (Spot[j]==0) if ((nN[j]!=0) || (nQ[j]!=0))
                                      { fl1=1;i=j;Spot[j]=1;l++; } 
                              }
	         break;
          default:break;
                }

   } /*���������� �������� ����������� �������*/


  if (fl2!=0) /*��� 2.������������� ������� (���������� ��������� ������)*/
  { 
 for(i=0;i<n;i++) if (nN[i]<0) nN[i]++;else if (nN[i]>0)  nN[i]--; else { ; }
    nQmin=(nQ[e]<fabs(D[e]))?(nQ[e]):(fabs(D[e]));   
    i=abs(nN[e]);
    D[e]+=nQmin;   X[i*n+e]+=nQmin;   R[i*n+e]-=nQmin;
    while (nN[i]!=0)
     {
/***********************/     Yield(); 
      e=abs(nN[i]);
      if (nN[i]<0) { X[i*n+e]-=nQmin; R[i*n+e]+=nQmin; }
      if (nN[i]>0) { X[e*n+i]+=nQmin; R[e*n+i]-=nQmin; }
      i=abs(nN[i]);
      }
    D[i]-=nQmin;
 for(i=0;i<n;i++) if (nN[i]<0) nN[i]--;else if (nN[i]>0)  nN[i]++; else { ; }
    /*�������� �� ������������� ����������� ������*/
    SumPr=0.0; for(j=0;j<n;j++) if (D[j]>0) SumPr+=D[j];else { ; }
    if (SumPr==0.0000000000)  fl=1;
   } /*����� ��� 2.������������� �������*/

/****************************************************************************/

  if (fl3!=0)  /*��� 3.��������� ����������� ��� ������������� ��������������*/
  { 
   kDeltai=0;DeltaMin=0;kDeltaMin=0; /*�������� �������,� �������� �������� ���� ������*/

   for(i=0;i<=p;i++) /*�������� ���������� i �������*/
    if ((nN[i]!=0)||(nQ[i]!=0.0)) 
     {
      kDelta1=0;   kDelta2=0;/*�������� �������� ������*/

      for(j=0;j<n;j++)
       if ((nN[j]==0) && (nQ[j]==0.0))
        {
          if (C[i*n+j]>0)  /*����� min(j,C[i,j]>0) C[i,j]=Delta1 */
           { kDelta1++;
              if (kDelta1==1)  Delta1=C[i*n+j];
                else if (Delta1>C[i*n+j]) Delta1=C[i*n+j];  }
          if (C[j*n+i]<0)  /*����� min(j,C[j,i]<0) |C[j,i]|=Delta2 */
           { kDelta2++;
              if (kDelta2==1) Delta2=fabs(C[j*n+i]);
                else if (Delta2>fabs(C[j*n+i])) Delta2=fabs(C[j*n+i]); }
         }

      if ((kDelta1!=0) || (kDelta2!=0)) 
      { kDeltai++; /*������� ���������� ������*/
        if (kDelta1==0) kDeltaMin=Delta2;
         else if (kDelta2==0) kDeltaMin=Delta1;
           else kDeltaMin=(Delta1<Delta2)?(Delta1):(Delta2);
        if (kDeltai==1) DeltaMin=kDeltaMin;
         else if (DeltaMin>=kDeltaMin) DeltaMin=kDeltaMin;
        }

       }

  if (kDeltai!=0)
   if (DeltaMin!=0)
    for(i=0;i<=p;i++)   /*���������� ���������� ������*/
     if ((nN[i]!=0)||(nQ[i]!=0.0)) /*�������� ���������� i �������*/
      for(j=0;j<n;j++)
      { if (C[i*n+j]>0) C[i*n+j]-=DeltaMin;
         if (C[j*n+i]<0) C[j*n+i]+=DeltaMin; }

    if (DeltaMin==0) 
    if (FlagMinMax==1) fl=1; /*����� �� ��������� ��� �������������� ��������������*/
     else /*������� ������ �� ��������*/
     {
      kDeltai=0;DeltaMin=0;kDeltaMin=0; /*�������� �������,� �������� ������������ ���� ������*/
      for(i=0;i<=p;i++) /*�������� ���������� i �������*/
       if ((nN[i]!=0) || (nQ[i]!=0.0))
        {
	  kDelta1=0;   kDelta2=0;/*�������� �������� ������*/
         for(j=0;j<n;j++)
	  if ((nN[j]==0)&&(nQ[j]==0))
	   {
	     if (C[i*n+j]<0) /*����� max(j,|C[i,j]|<0) |C[i,j]|=Delta1 */
	     { kDelta1++;
	        if (kDelta1==1) Delta1=fabs(C[i*n+j]);
	           else if (Delta1<fabs(C[i,j])) Delta1=fabs(C[i*n+j]); }
	     if (C[j*n+i]>0) /*����� max(j,C[j,i]>0) C[j,i]=Delta2 */
	     { kDelta2++;
	        if (kDelta2==1) Delta2=(C[j*n+i]);
                            else if (Delta2<(C[j*n+i])) Delta2=(C[j*n+i]); }
	    }
	  if ((kDelta1!=0) || (kDelta2!=0))
	   { kDeltai++; /*������� ���������� ������*/
	     if (kDelta1==0) kDeltaMin=Delta2;
		  else if (kDelta2==0) kDeltaMin=Delta1;
			  else if (Delta1>=Delta2) kDeltaMin=Delta1;
				 else  kDeltaMin=Delta2;
	     if (kDeltai==1) DeltaMin=kDeltaMin;
		   else if (DeltaMin<=kDeltaMin) DeltaMin=kDeltaMin;
	    }
	   }
      if (kDeltai!=0)
	 if (DeltaMin!=0)
	  for(i=0;i<=p;i++)  /*���������� ���������� ������*/
	   if ((nN[i]!=0)||(nQ[i]!=0)) /*�������� ���������� i �������*/
            for(j=0;j<n;j++) { if (C[i*n+j]<0) C[i*n+j]+=DeltaMin; if (C[j*n+i]>0) C[j*n+i]-=DeltaMin; }
     } /*������� ������ �� ��������*/

  }/*����� ��� 3.��������� �����������*/

Step++;/*������� ����� �������� ���������*/

strEdit[0]='\0';sprintf( strEdit,"[%d ]",Step);
    Static4->SetText((LPSTR)strEdit);  
strEdit[0]='\0';

if (Step>=MaxStep) fl=1;/*��������� ��������� ����������*/

} /*����� ���������� ������*/

/* free the memory */ farfree(R);farfree(nN);farfree(nQ);farfree(Spot);farfree(C);
/* ����� ����������� */
SumStr=0.0;
if (FlagCalc!=0) 
{ if((hr = fopen(namePrice_C, "r"))==NULL) return(-1); /*������������ ������� �[i,j] �� ����� */
  for(i=0;i<n;i++) 
   for(j=0;j<n;j++){ fscanf(hr,"%f",&Pr);SumStr=SumStr+Pr*X[(i*n+j)];  }
  fclose(hr);
}

fprintf(rf,"\n������������ ������ �� ������:\n(���������� ������������)R[i,j] = %s \n",  nameLength_R);
fprintf(rf,"(���������) C[i,j] = %s \n(��������������)D[i]  = %s \n",namePrice_C, nameIntense_D);
fprintf(rf,"��� ������= %s ",(( FlagMinMax==1)?"min":"max"));

fprintf(rf,"\n������������������ (%d) , ������������(%d)\n",FlagSpot,FlagCase);
if (SumPr==0.0000000000) { fprintf(rf,"\n����� ����������� , �.�. ~D[i]=0, i=1..%d\n",n); }
 else  { fprintf(rf,"\n����� �� ����������� , �.�. ~D[i]<>0,i=1..%d\n�������������:D[i]\n",n);
             for(j=0;j<n;j++)  fprintf(rf,"% 8.3g\n",D[j]);
            }
fprintf(rf,"\n NumberIter(�������������)=%d : �������� �����{Stream}=% 8.3g\n",Step,SumStr);
fprintf(rf,"\n�����(X[1..%d,1..%d]):=",n,n);
for(i=0;i<n;i++){ fprintf(rf,"\n"); for(j=0;j<n;j++) fprintf(rf," % 8.3g ",X[i*n+j]); }
 
/* free the memory */  farfree(X);farfree(D);
fclose(rf); 
return (0);
}

/*������: 5��-1(������� ����)
 ������ ������� ��������: C��������� �.�., ��������� �.�.
 ��� 2000*/

