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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

enum {
	ERROR_1=1,
	ERROR_2,
     };

int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char d;
  while(!feof(stream)){
    fscanf(stream, "%c",&d);
    if ((d>57) || ((d<48) && (d>32) && (d!=46))) { 
      fprintf(stderr,"The type of the file is wrong\n");
      return 1;
    }
  }
  rewind(stream);
  return 0;
}


int interval(FILE* stream){ 	
  double o,n;
  double *tab=NULL;
  int i,l=0;
  fscanf(stream,"%lf",&o);
  if(!(tab=(double*) malloc(sizeof(double)))){
    perror("memory allocation"); 
    exit(EXIT_FAILURE);
  }
  while(fscanf(stream,"%lf",&n)!=EOF){
    if(!(tab=(double*) realloc(tab,(l+2)*sizeof(double)))){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
    tab[l]=n-o;
    o=n;
    l++;
  }
  for(i=0;i<l;i++){
  fprintf(stdout,"%lf\n",tab[i]);
  }
  free(tab);
  return 0;
}

int main(int argc,char *argv[]){
  int opt;
  FILE* stream = stdin;
  while((opt=getopt(argc,argv,"iIMmlh"))!=-1){
    switch(opt) {
      case 'h':
        printf("Sorry, the help page is not available yet.\n");
        return 0;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return ERROR_2;
      break;
    }
  }
  if(argc>optind){
    if (!(stream = fopen(argv[optind], "r"))){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
    if (typeIsWrong(stream))
      return ERROR_1;
  }
  interval(stream);
  if(argc>optind){
    if (fclose(stream)!=0){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
