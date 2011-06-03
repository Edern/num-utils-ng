/**
*
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
* This file is part of num-utils-ng project
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
* Contributor(s): Edern Hotte, Flavien Moullec, Reuven Benichou.
*
* ***** END GPL LICENSE BLOCK *****
*/



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

enum
{ TYPE_ERROR = 1, OPTION_ERROR, WRONG_FILE };


static int
skipWord (FILE * stream)
{				//this function tests if there is letters in the file.
  char c = 'a';
  if (stream == stdin)
    fprintf (stderr, "This is not a number!\n");
  while (!isdigit (c) && !isspace (c) && !(c == 46) && !(c == 45))
    {
      if (fscanf (stream, "%c", &c) != 1)
	{
	  perror ("num-utils-ng");
	  return EXIT_FAILURE;
	}
    }
  return EXIT_SUCCESS;
}


static void
afficher (double *tab, int count)
{
  int i = 0;
  for (i = 0; i < count - 1; i++)
    {
      printf ("%lf \n", tab[i]);
    }
}


static void
normalize (FILE * stream, int l, int h)
{				//this function normalize
  double *tab = NULL;
  double number = 0.;
  double sum = 0.;
  int count = 0, lengthTab = 1;
  int i;
  int test;

  if (!(tab = (double *) malloc (sizeof (double))))
    {
      perror ("num-utils-ng");
      return EXIT_FAILURE;
    }

  while (!feof (stream))
    {
      if ((test = fscanf (stream, "%lf", &number)) != EOF)
	if (!test)
	  skipWord (stream);
      sum += number;
      tab[count] = number;
      count++;
      if (count == lengthTab)
	{
	  lengthTab *= 2;
	  if (!
	      (tab = (double *) realloc (tab, (lengthTab) * sizeof (double))))
	    {
	      perror ("num-utils-ng");
	      return EXIT_FAILURE;
	    }
	}
    }
  sum -= number;
  for (i = 0; i < count; i++)
    {
      *(tab + i) = *(tab + i) * (h - l) / (double) sum + l;
    }
  afficher (tab, count);
  free (tab);
}


int
main (int argc, char *argv[])
{
  FILE *stream = stdin;
  int optch;
  int numberL = 0;
  int numberH = 1;

  while ((optch = getopt (argc, argv, "R:h")) != -1)
    {
      switch (optch)
	{
	case 'R':		//Specify a different normalization 
	  if (optarg)
	    {
	      if (!sscanf (optarg, "%d..%d", &numberL, &numberH))
		{
		  perror ("invalid argument\n");
		  return EXIT_FAILURE;
		}
	    }
	  break;

	case 'h':
	  if (execlp ("man", "man", "numnormalize", NULL) == -1)
	    {
	      perror ("num-utils-ng");
	      return EXIT_FAILURE;
	    }
	  return EXIT_SUCCESS;
	  break;

	default:		//option fail.
	  fprintf (stderr, "Invalid option\n");
	  return OPTION_ERROR;
	  break;
	}
    }

  if (argc > optind)
    {
      if (!(stream = fopen (argv[optind], "r")))
	{
	  perror ("num-utils-ng");
	  return WRONG_FILE;
	}
    }
  normalize (stream, numberL, numberH);
  fclose (stream);
  return EXIT_SUCCESS;
}
