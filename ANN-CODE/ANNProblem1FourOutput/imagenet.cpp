/*
 ******************************************************************
 * HISTORY
 * 15-Oct-94  Jeff Shufelt (js), Carnegie Mellon University
 *      Prepared for 15-681, Fall 1994.
 *
 ******************************************************************
 */

#include "stdafx.h"

#include <stdio.h>
#include "pgmimage.h"
#include "backprop.h"

extern void exit();


/*** This is the target output encoding for a network with one output unit.
     It scans the image name, and if it's an image of me (js) then
     it sets the target unit to HIGH; otherwise it sets it to LOW.
     Remember, units are indexed starting at 1, so target unit 1
     is the one to change....  ***/

void load_target(IMAGE *img,BPNN *net)
{
  int scale;
  char userid[40], head[40], expression[40], eyes[40], photo[40];

  userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

  /*** scan in the image features ***/
  sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^_]_%d.%[^_]",
    userid, head, expression, eyes, &scale, photo);

  char *p=NULL;
  p = strrchr(eyes,'.');
  if(p!=NULL)
  {
	    userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

	    sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^.].%[^_]",
    userid, head, expression, eyes, photo);
		scale = 1;
  }

  p = strrchr(userid,'\\');
  if(p!=NULL)
	  p++;

  //if (!strcmp(p, "glickman")) {
  if (!strcmp(expression, "angry")) {
    net->target[1] = 1;  
	net->target[2] = 0;
	net->target[3] = 0;  
	net->target[4] = 0;
  } 
  if (!strcmp(expression, "happy")) {
	  net->target[1] = 0;  
	  net->target[2] = 1;
	  net->target[3] = 0;  
	  net->target[4] = 0;
  }
  if (!strcmp(expression, "neutral")) {
	  net->target[1] = 0;  
	  net->target[2] = 0;
	  net->target[3] = 1;  
	  net->target[4] = 0;
  }
  if (!strcmp(expression, "sad")) {
	  net->target[1] = 0;  
	  net->target[2] = 0;
	  net->target[3] = 0;  
	  net->target[4] = 1;
  }
}


/***********************************************************************/
/********* You shouldn't need to change any of the code below.   *******/
/***********************************************************************/

void load_input_with_image(IMAGE *img,BPNN *net)
{
  double *units;
  int nr, nc, imgsize, i, j, k;

  nr = ROWS(img);
  nc = COLS(img);
  imgsize = nr * nc;;
  if (imgsize != net->input_n) {
    printf("LOAD_INPUT_WITH_IMAGE: This image has %d pixels,\n", imgsize);
    printf("   but your net has %d input units.  I give up.\n", net->input_n);
    exit (-1);
  }

  units = net->input_units;
  k = 1;
  for (i = 0; i < nr; i++) {
    for (j = 0; j < nc; j++) {
      units[k] = ((double) img_getpixel(img, i, j)) / 255.0;
      k++;
    }
  }
}
