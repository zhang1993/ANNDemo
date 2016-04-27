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

#define TARGET_ANGRY 1
#define TARGET_HAPPY 0.75
#define TARGET_NEUTRAL 0.5
#define TARGET_SAD 0.25
/*** This is the target output encoding for a network with one output unit.
     It scans the image name, and if it's an image of me (js) then
     it sets the target unit to HIGH; otherwise it sets it to LOW.
     Remember, units are indexed starting at 1, so target unit 1
     is the one to change....  ***/
void init_target(BPNN *net, char *userid){
	//if (!strcmp(p, "glickman")) {
	char *username[20] = { "an2i"
		, "at33"
		, "boland"
		, "bpm"
		, "ch4f"
		, "cheyer"
		, "choon"
		, "danieln"
		, "glickman"
		, "karyadi"
		, "kawamura"
		, "kk49"
		, "megak"
		, "mitchell"
		, "night"
		, "phoebe"
		, "saavik"
		, "steffi"
		, "sz24"
		, "tammo"
	};
	for (int i = 0; i < 20; i++){
		if (!strcmp(userid, username[i])){
			net->target[i+1] = 1;
		}
		else{
			net->target[i+1] = 0;
		}

	}
}
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
  char username[40];
  username[0] = '\0';
  int index = 0;
  for (int i=0; i <sizeof(userid); i++){
	  if (userid[i] == '\\'){
		  index = i;
	  }
  }
  int count = 0;
  for (int i = index+1; i < sizeof(userid); i++){
	  username[count] = userid[i];
	  count++;
  }
  username[count] = '\0';
  //printf("%s", username);
  init_target(net, username);
 
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
