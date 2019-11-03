#include <ALLOC.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

const n=4;  //n=14,  ўшёыю єчыют(тхЁ°шэ) /*число узлов(вершин)*/
FILE *rf;

int main()
{
if((rf=fopen("c:\\programs\\bc\\out\\___nmb.prn","w"))==NULL) { return(-2);  }
 int  i,j; float VarMinMax; VarMinMax=1e37;
/* allocate memory for the far pointer */
float  far *X;    //X[n][n+1];
X = (float far *) farmalloc(n*(n+1)*sizeof(float));

//for(i=0;i<n;i++) for(j=0;j<(n+1);j++) X[i*n+j]=0.0; //Обнуление
//X[0*n+0]=0.0;
//for(i=1;i<n;i++) X[i*(n-1)+1]=-2; /*Начальный */

for(i=0;i<(n*(n+1));i++) X[i]=i;

fprintf(rf,"\n1->");
 for(i=0;i<n;i++)
{ fprintf(rf,"\n");
   for(j=0;j<(n+1);j++)  fprintf(rf,"  % 3.2g ",X[i*(n+1)+j]);  }

fprintf(rf,"\n2->\n"); for(i=0;i<(n*(n+1));i++) fprintf(rf," [%d]%3.2g ",i,X[i]);

  fclose(rf);  puts("End");  return(0);
}


