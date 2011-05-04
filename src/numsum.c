/**
*
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
* This file is part of num-utils-nv project
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program If not, see <http://www.gnu.org/licenses/>.
*
* The Original Code is Copyright (C) 2011 by num-utils-nv project.
* All rights reserved.
*
* The Original Code is: all of this file.
*
* Contributor(s): none yet.
*
* ***** END GPL LICENSE BLOCK *****
*/


# include <stdlib.h>
# include <stdio.h>
#include  <unistd.h>
#include <ctype.h>


enum {TYPE_ERROR=1, OPTION_ERROR };

static double sum ( FILE* stream){		//this function calculates the sum of numbers from a file or stdin.
  double sum=0.;
  double number=0.;
  while (!feof(stream)){
    sum = sum + number ;					
    if(fscanf (stream,"%lf",&number)!=EOF);
  }
 return sum;
}


static int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char c;
  while(fscanf(stream, "%c",&c)!=EOF){
    if (!isdigit(c) && !isspace(c) && !(c==46)) { 
    fprintf(stderr,"The type of the file is wrong.\n");
    fprintf(stderr,"the programm has detected an unexpected char : %c\n",c);
    return 1;
    }
  }
  rewind(stream);
  return 0;
}


static double column(FILE* stream){     // this function print out the sum of each column.
	int l=0,i,I,J;  
	int C=0;
	int car; 
	if (stream){
	while ( (car= getc(stream)) != EOF){
		if (car == '\n')
		++l;	
		if (car == ' ' && l==0)
		++C;
	    }
	int tableau[l][C+1];
	int* tab=NULL;
	tab=malloc(C*sizeof(int));
	rewind(stream);
	for(i=0; i<l*(C+1); i++){
		if(fscanf(stream,"%d",&tableau[i/(C+1)][i % (C+1)])!=EOF);
	    }
	for (J=0;J<C+1;J++){
		for (I=0;I<l;I++){
			tab[J]=tab[J]+tableau[I][J];
		}
	      printf("The sum of column %d is %d \n",J+1,tab[J]);
	}
	fclose(stream);
	}
	return 0;
}

static double row(FILE* stream){                  // this function print ou the sum of each row.
	char ligne[1024], *p, *e;
	long v, somme = 0;
	while (fgets(ligne, sizeof(ligne), stream)) {
		p = ligne;
		for (p = ligne; ; p = e) {
	        v = strtol(p, &e, 10);
			if (p == e){
				printf("%ld \n", somme); 
				somme = 0; 
				break; 
			}
			else 
				somme += v;
	    }
	}
	return 0;
}


static double decimalPortion(FILE* stream){     //this function calculates the decimal portion of the final sum 
	double d = sum(stream);
	int i = (int)d;
	double res = d - (double)i;
	return res;
}

int main(int argc,char *argv[]){
	FILE*stream = stdin;
	int opt;
	double res=0;
	int m=0;				// for options (column, row).
	int s=0;				// for options (normal, integer portion and decimal portion).;
	while((opt = getopt(argc,argv,"iIcrh"))!=-1){
		switch(opt) {

		case 'i':			// option "-i" (integer portion of the final sum)
		s=1;     
		break;
		
		case 'I':			//option "-I" (decimal portion of the final sum)
        	s=2;
		break;

		case 'c':			//option "-c" (Print out the sum of each column.)
		m=1;
		break;
	
		case 'r':			//option "-r" (Print out the sum of each row.)
		m=2;
		break;

			
		case 'h':
		printf ( " sorry, the help page is not yet available.\n");
		return 0;
		break;
					
		default :				//option fail.
        	fprintf(stderr, "Invalid option\n");
        	return OPTION_ERROR;
		break;
	
    		}
  	}
	
	if (argc>optind){
		if (!(stream = fopen(argv[optind], "r"))){
			perror("num-utils-ng"); 
			exit(EXIT_FAILURE);
		}
    		if (typeIsWrong(stream))
			return TYPE_ERROR;
	}  
	
	if (m==0)
		res = sum(stream);
	if (m==1)
		res = column(stream);
	if (m==2)
		res = row(stream);

  if (argc>1){
    if (fclose(stream)!=0){
      perror("num-utils-ng"); 
      exit(EXIT_FAILURE);
    }
  }

		
  if (s==0)
  	printf("result : %lf\n",sum(stream));
  if (s==1)
  	printf("result : %d\n",(int)sum(stream));
  if (s==2)
  	printf("result : %lf\n",decimalPortion(stream));
  return EXIT_SUCCESS;

}
