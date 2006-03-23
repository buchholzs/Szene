#include "depui/config.h"
#include "depui/macros.h"
#include "depui/debug/alloc.h"
#include "depui/draw/region.h"
#include "depui/desktop/desktop.h"
#include "depui/object/object.h"
#include "depui/graphics/clip.h"
#include <stdlib.h>
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#if defined(MX_DEBUG_EXPOSE_RECT) || defined(MX_DEBUG_REGION_RECT)
#include "depui/graphics/frame.h"
extern MxObject *MxDesk;
#endif

/* If we are not debugging the regions, we use a macro */
#ifdef MX_DEBUG_REGION_CONSTRUCT
unsigned int MxRegionEmpty(const MxRegion * const region)
{
	 assert(region);
	 assert(region->constructed);

	 return region->reg ? MxFalse : MxTrue;
}
#endif

void MxRegionAddRect(MxRegion * region, const MxRect * const rect)
{	
	 MxRegionData *newreg;
	 MxRect *newrect;
	 const int num = MxRegionNumber(*region);

	 assert(region);
	 assert(rect);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

//  MX_TRACE("");

	 if (!MX_VALID_RECT(*rect))
		  return;

	 /* Allocate memory for the rect */
     newreg = MxMalloc(Mx_RegionMem(num + 1));
	 if (region->reg != NULL) {
		 unsigned i;
		 newreg->num = region->reg->num;
		 for (i=0; i<newreg->num; i++) {
			newreg->r[i] = region->reg->r[i];
		 }
		 MxFree(region->reg);
		 region->reg = NULL;
	 }
     region->reg = newreg;
	 region->reg->num = num + 1;

	 /* Put the new rect on the end */
	 newrect = MxRegionRect(*region, num);
	 *newrect = *rect;
}

void MxRegionRemoveRect(MxRegion * region, const int index)
{
	 int i;
	 const int num = MxRegionNumber(*region);

	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

//  MX_TRACE("");

	 for (i = index; i < num - 1; i++) {
		  MxRect *r = MxRegionRect(*region, i);

		  *r = *MxRegionRect(*region, i + 1);
	 }

	 /* Make room for 1 less rect in the region */
	 if (num > 1) {
		  region->reg->num = num - 1;

		  /* Maybe we can free it if there are no rects */
	 } else {
		  MxFree(region->reg);
		  region->reg = NULL;
	 }
}

void MxRegionConstruct(MxRegion * region)
{
	 assert(region);
//  MX_TRACE("");

	 region->reg = 0;

#ifdef MX_DEBUG_REGION_CONSTRUCT
	 region->constructed = MxTrue;
#endif
}

void MxRegionDestruct(MxRegion * region)
{
	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

//  MX_TRACE("");

#ifndef NDEBUG
#ifdef MX_DEBUG_MEM
	 if (region->reg)
		  assert(MxRegionNumber(*region) != 0);
#endif
#endif

	 if (region->reg) {
		  MxFree(region->reg);
		  region->reg = NULL;
	 }

//    memset(region, 0, sizeof(MxRegion));

#ifdef MX_DEBUG_REGION_CONSTRUCT
	 region->constructed = MxFalse;
#endif
}

static int _rect_sort(const void *one, const void *two)
{
	 MxRect *first = (MxRect *) one;
	 MxRect *second = (MxRect *) two;

	 if (first->y1 < second->y1)
		  return 1;

	 if (first->y1 == second->y1)
		  if (first->x1 < second->x1)
				return 1;

	 return -1;
}

void MxRegionSort(MxRegion * region)
{
	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

	 /* Sort the rectangles from X and then Y direction so rects are less
	    likely to cause bank switching when drawn */
	 qsort(MxRegionRect(*region, 0), MxRegionNumber(*region), sizeof(MxRect), _rect_sort);
}

/* optimizes a region */
void MxRegionOptimize(MxRegion * region)
{
	 unsigned int i, j;

	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

	 /* Remove any invalid rectangles */
	 for (i = 0; i < MxRegionNumber(*region); i++)
		  if (!MX_VALID_RECT(*MxRegionRect(*region, i)))
				MxRegionRemoveRect(region, i);

	 /* Combine rectangles that are attached */
	 for (i = 0; i < MxRegionNumber(*region); i++) {
		  MxRect *s = MxRegionRect(*region, i);

		  for (j = i; j < MxRegionNumber(*region); j++) {
				MxRect *f = MxRegionRect(*region, j);

				if ((s->x1 == f->x1) && (s->x2 == f->x2)) {
					 if (s->y2 == f->y1 - 1) {
						  s->y2 = f->y2;
						  MxRegionRemoveRect(region, j);
					 } else if (s->y1 == f->y2 + 1) {
						  s->y1 = f->y1;
						  MxRegionRemoveRect(region, j);
					 }

				} else if ((s->y1 == f->y1) && (s->y2 == f->y2)) {
					 if (s->x2 == f->x1 - 1) {
						  s->x2 = f->x2;
						  MxRegionRemoveRect(region, j);
					 } else if (s->x1 == f->x2 + 1) {
						  s->x1 = f->x1;
						  MxRegionRemoveRect(region, j);
					 }
				}
		  }
	 }
}

void MxRegionClipRect(MxRegion * region, const MxRect * const rect)
{
	 unsigned int i;
	 MxRegion clipped;

	 assert(region);
	 assert(rect);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

	 MxRegionConstruct(&clipped);

	 if (!MX_VALID_RECT(*rect))
		  return;

	 /* Make a list of intersecting rectangles */
	 for (i = 0; i < MxRegionNumber(*region); i++) {
		  MxRect s = *MxRegionRect(*region, i);
		  MxRect trial;

		  MX_INTERSECT_RECTS(s, *rect, trial);
		  if (MX_VALID_RECT(trial)) {

				/* Remove the intersecting rectangles */
				MxRegionRemoveRect(region, i);
				--i;

				/* Add to a temp list of the clipped rectangles */
				MX_TOP_RECTS(s, *rect, trial);
				MxRegionAddRect(&clipped, &trial);

				MX_LEFT_RECTS(s, *rect, trial);
				MxRegionAddRect(&clipped, &trial);

				MX_RIGHT_RECTS(s, *rect, trial);
				MxRegionAddRect(&clipped, &trial);

				MX_BOT_RECTS(s, *rect, trial);
				MxRegionAddRect(&clipped, &trial);
		  }
	 }

	 /* Add the temp list back into the region list */
	 for (i = 0; i < MxRegionNumber(clipped); i++)
		  MxRegionAddRect(region, MxRegionRect(clipped, i));

	 MxRegionDestruct(&clipped);
}

void MxRegionClipRegion(MxRegion * region, const MxRegion * const reg)
{
	 unsigned int i;

	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

	 for (i = 0; i < MxRegionNumber(*reg); i++)
		  MxRegionClipRect(region, MxRegionRect(*reg, i));
}

/* Ask an object to mask it's region so it does not have to occupy the
   entire rectangular area under itself */
static void region_mask(MxObject * const object, MxRegion * region)
{
	 MxEvent maskevent;

//  MX_TRACE("");

	 maskevent.type = MxEventRegionMask, maskevent.region.region = region;

	 /* Ask the object to mask it's region */
	 MxEventSend(object, &maskevent);
}

unsigned int MxRegionVisibleConstruct(MxRegion * region, MxObject * const object, const unsigned int children)
{
	 MxObject *parent, *ptr;
	 MxRect overlap = object->position;

	 assert(region);
	 assert(object);

//  MX_TRACE("");
	 MX_CHECKSTACK(object);

	 /* We start out with no region for the object */
	 MxRegionConstruct(region);

	 /* Make sure we have a valid object here */
	 if (!object->init)
		  return MxFalse;

	 /* If the object is hidden or a parent is hidden it does not have a
	    screen region */
	 parent = object;
	 while (parent) {

		  if (parent->hidden)
				return MxFalse;

		  parent = MxParent(parent);
	 }

	 /* Go up the parent list to reduce the area */
	 parent = MxParent(object);
	 while (parent) {

		  MX_INTERSECT_RECTS(parent->position, overlap, overlap);
		  parent = MxParent(parent);
	 }

	 /* The parents occlude the object */
	 if (!MX_VALID_RECT(overlap))
		  return MxFalse;

	 /* Start with the region of the basic area */
	 MxRegionAddRect(region, &overlap);
	 if (object->Hasmask)
		  region_mask(object, region);

	 /* Look at objects higher than the parent */
	 parent = MxParent(object);
	 while (parent) {

		  /* Looking for objects higher than the parent */
		  ptr = MxPrev(parent);
		  while ((ptr) && (MxRegionNumber(*region))) {

				if ((!ptr->Transparent)
					 && (!ptr->hidden)
					 && (MX_RECTS_OVERLAP(overlap, ptr->position))) {

					 /* Get the basic object region for the object that will
					    obscure the current object */
					 MxRegion clip;

					 MxRegionConstruct(&clip);
					 MxRegionAddRect(&clip, &ptr->position);

					 /* Ask the object if they need to mask some of thier region */
					 region_mask(ptr, &clip);

					 /* Now clip our visible region wit what the higher object
					    says they will use */
					 MxRegionClipRegion(region, &clip);
					 MxRegionDestruct(&clip);

					 if (MxRegionEmpty(region))
						  return MxFalse;
				}
				ptr = MxPrev(ptr);
		  }
		  parent = MxParent(parent);
	 }

	 /* Look for obscuring by higher objects */
	 ptr = MxPrev(object);
	 while ((ptr) && (MxRegionNumber(*region))) {

		  if ((!ptr->Transparent)
				&& (!ptr->hidden)
				&& (MX_RECTS_OVERLAP(overlap, ptr->position))) {

				/* Get the basic object region for the object that will obscure
				   the current object */
				MxRegion clip;

				MxRegionConstruct(&clip);
				MxRegionAddRect(&clip, &ptr->position);

				/* Ask the object if they need to mask some of thier region */
				region_mask(ptr, &clip);

				/* Now clip our visible region wit what the higher object says
				   they will use */
				MxRegionClipRegion(region, &clip);
				MxRegionDestruct(&clip);

				if (MxRegionEmpty(region))
					 return MxFalse;
		  }
		  ptr = MxPrev(ptr);
	 }

	 /* Look for obscuring by it's children */
	 if (children) {

		  ptr = MxFirstChild(object);
		  while ((ptr) && (MxRegionNumber(*region))) {

				if ((!ptr->Transparent)
					 && (!ptr->hidden)
					 && (MX_RECTS_OVERLAP(overlap, ptr->position))) {

					 /* Get the basic object region for the object that will
					    obscure the current object */
					 MxRegion clip;

					 MxRegionConstruct(&clip);
					 MxRegionAddRect(&clip, &ptr->position);

					 /* Ask the object if they need to mask some of thier region */
					 region_mask(ptr, &clip);

					 /* Now clip our visible region wit what the higher object
					    says they will use */
					 MxRegionClipRegion(region, &clip);
					 MxRegionDestruct(&clip);

					 if (MxRegionEmpty(region))
						  return MxFalse;
				}
				ptr = MxNext(ptr);
		  }
	 }

	 /* At least some part of the object is visible */
	 return MxTrue;
}

unsigned int MxRegionContainsPoint(const MxRegion * const region, const int x, const int y)
{
	 unsigned int i;

	 assert(region);
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 assert(region->constructed);
#endif

	 for (i = 0; i < MxRegionNumber(*region); i++)
		  if (MX_POINT_IN_RECT(*MxRegionRect(*region, i), x, y))
				return MxTrue;

	 return MxFalse;
}
