#ifndef MX_MACROS_H
#define MX_MACROS_H

#include "depui/config.h"

#define MX_MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MX_MAX(x,y)     (((x) > (y)) ? (x) : (y))

#define MX_TOP_RECTS(A, B, R)\
   (R).x1 = (A).x1;\
   (R).y1 = (A).y1;\
   (R).x2 = (A).x2;\
   (R).y2 = MX_MIN( (B).y1-1, (A).y2 )

#define MX_LEFT_RECTS(A, B, R)\
   (R).x1 = (A).x1;\
   (R).y1 = MX_MAX( (B).y1, (A).y1 );\
   (R).x2 = MX_MIN( (B).x1-1, (A).x2 );\
   (R).y2 = MX_MIN( (B).y2, (A).y2 )

#define MX_RIGHT_RECTS(A, B, R)\
   (R).x1 = MX_MAX( (B).x2+1, (A).x1 );\
   (R).y1 = MX_MAX( (B).y1, (A).y1 );\
   (R).x2 = (A).x2;\
   (R).y2 = MX_MIN( (B).y2, (A).y2 )

#define MX_BOT_RECTS(A, B, R)\
   (R).x1 = (A).x1;\
   (R).y1 = MX_MAX( (B).y2+1, (A).y1 );\
   (R).x2 = (A).x2;\
   (R).y2 = (A).y2

#define MX_VALID_RECT(A)\
	 (((A).x2 >= (A).x1)&&\
    ((A).y2 >= (A).y1))

#define MX_POINT_IN_RECT(R, X, Y)\
   ((X >= (R).x1) &&\
    (X <= (R).x2) &&\
    (Y >= (R).y1) &&\
    (Y <= (R).y2))

#define MX_INTERSECT_RECTS(A, B, R)\
   (R).x1 = MX_MAX((A).x1, (B).x1);\
   (R).y1 = MX_MAX((A).y1, (B).y1);\
   (R).x2 = MX_MIN((A).x2, (B).x2);\
   (R).y2 = MX_MIN((A).y2, (B).y2)

#define MX_UNION_RECTS(A, B, R)\
   (R).x1 = MX_MIN((A).x1, (B).x1);\
   (R).y1 = MX_MIN((A).y1, (B).y1);\
   (R).x2 = MX_MAX((A).x2, (B).x2);\
   (R).y2 = MX_MAX((A).y2, (B).y2)

#define MX_RECTS_OVERLAP(A, B)\
   (!(((B).x1 > (A).x2) ||\
      ((B).y1 > (A).y2) ||\
      ((B).x2 < (A).x1) ||\
      ((B).y2 < (A).y1)))

#define MX_AREA_RECT(A)\
   (((A).y2 - (A).y1) * ((A).x2 - (A).x1))

#endif
