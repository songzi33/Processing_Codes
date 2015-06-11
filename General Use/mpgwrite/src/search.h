/*===========================================================================*
 * search.h								     *
 *									     *
 *	stuff dealing with the motion search				     *
 *									     *
 *===========================================================================*/

/*
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

/*  
 *  $Header: /home/daf/mpeg/mpgwrite/RCS/search.h,v 1.1 1994/01/07 17:05:21 daf Exp $
 *  $Log: search.h,v $
 * Revision 1.1  1994/01/07  17:05:21  daf
 * Initial revision
 *
 * Revision 1.2  1993/07/22  22:24:23  keving
 * nothing
 *
 * Revision 1.1  1993/07/09  00:17:23  keving
 * nothing
 *
 */


/*==============*
 * HEADER FILES *
 *==============*/

#include "ansi.h"


/*===========*
 * CONSTANTS *
 *===========*/

#define PSEARCH_SUBSAMPLE   0
#define PSEARCH_EXHAUSTIVE  1
#define	PSEARCH_LOGARITHMIC 2
#define	PSEARCH_TWOLEVEL    3

#define BSEARCH_EXHAUSTIVE  0
#define BSEARCH_CROSS2	    1
#define BSEARCH_SIMPLE	    2


/*========*
 * MACROS *
 *========*/

#define COMPUTE_MOTION_BOUNDARY(by,bx,stepSize,leftMY,leftMX,rightMY,rightMX)\
    leftMY = -2*DCTSIZE*by;	/* these are valid motion vectors */	     \
    leftMX = -2*DCTSIZE*bx;						     \
			    	/* these are invalid motion vectors */	     \
    rightMY = 2*(Fsize_y - (by+2)*DCTSIZE + 1) - 1;			     \
    rightMX = 2*(Fsize_x - (bx+2)*DCTSIZE + 1) - 1;			     \
									     \
    if ( stepSize == 2 ) {						     \
	rightMY++;							     \
	rightMX++;							     \
    }
    
#define VALID_MOTION(y,x)	\
    (((y) >= leftMY) && ((y) < rightMY) &&   \
     ((x) >= leftMX) && ((x) < rightMX) )


/*===============================*
 * EXTERNAL PROCEDURE prototypes *
 *===============================*/

void	SetPSearchAlg _ANSI_ARGS_((char *alg));
void	SetBSearchAlg _ANSI_ARGS_((char *alg));
char	*BSearchName _ANSI_ARGS_((void));
char	*PSearchName _ANSI_ARGS_((void));
int32	PLogarithmicSearch _ANSI_ARGS_((LumBlock currentBlock,
					MpegFrame *prev,
					int by, int bx,
					int *motionY, int *motionX));
int32	PSubSampleSearch _ANSI_ARGS_((LumBlock currentBlock,
					      MpegFrame *prev, int by, int bx,
					      int *motionY, int *motionX));
int32	PLocalSearch _ANSI_ARGS_((LumBlock currentBlock,
					  MpegFrame *prev, int by, int bx,
					  int *motionY, int *motionX,
					  int32 bestSoFar));
int32	PTwoLevelSearch _ANSI_ARGS_((LumBlock currentBlock,
				     MpegFrame *prev, int by, int bx,
				     int *motionY, int *motionX,
				     int32 bestSoFar));


/*==================*
 * GLOBAL VARIABLES *
 *==================*/

extern int psearchAlg;

