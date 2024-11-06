#include "depui/config.h"
#include "depui/object/object.h"
#include <assert.h>
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* How much memory do we need to store children array */
#define CHILDMEM(i) (sizeof(MxChildData) + (i - 1) * sizeof(MxObject*))

void mx_free_child(MxObject * object)
{
	 assert(object);

	 if (object->children.data)
		  MxFree(object->children.data);

	 object->children.data = 0;
}

void mx_add(MxObject * object, MxObject * parent)
{
	 /* Are we adding the first child */
	 if (!parent->children.data) {

		  parent->children.data = (MxChildData *) MxMalloc(CHILDMEM(1));
		  parent->children.data->num = 1;

		  /* We already have child, add this one to the lowest index */
	 } else {
		  int i;
		  const int num = parent->children.data->num;

		  assert(num > 0);

		  /* Reallocate the memory */
		  parent->children.data = (MxChildData *) MxRealloc(parent->children.data, CHILDMEM(num + 1));

		  /* Make room for the one at the start */
		  for (i = num - 1; i >= 0; i--) {

				/* Move the object farther down the array */
				parent->children.data->child[i]->index += 1;
				parent->children.data->child[i + 1] = parent->children.data->child[i];
		  }
		  ++parent->children.data->num;
	 }
	 /* Note that we actually added the object */
	 parent->children.data->child[0] = object;
	 object->parent = parent;
	 object->index = 0;
}

void mx_remove(MxObject * const object)
{
	 int i;
	 const int num = MxNumChild(object->parent);

	 assert(object->parent);
	 assert(object->parent->children.data->child[object->index] == object);

	 /* Move the higher windows down */
	 for (i = object->index; i < num - 1; i++) {
		  object->parent->children.data->child[i] = object->parent->children.data->child[i + 1];
		  object->parent->children.data->child[i]->index -= 1;
	 }

	 /* Are we deleting our last child */
	 if (num <= 1) {
		  mx_free_child(object->parent);

		  /* we still have some child */
	 } else {
		  object->parent->children.data->num = num - 1;

		  /* Reallocate the array of the child with less room for child */
		  object->parent->children.data = (MxChildData *) MxRealloc(object->parent->children.data, CHILDMEM(num - 1));
	 }
	 object->parent = 0;
	 object->index = 0;
}

unsigned int mx_zorder(MxObject * const object, int *neworder)
{
	 int i;
	 const MxObject *parent = object->parent;

	 const int index = object->index;
	 const int parchild = MxNumChild(parent);
	 int newindex = *neworder;

	 unsigned int changed = MxFalse;

	 /* We have no order if we have no parent */
	 assert(object);
	 assert(object->parent);

	 if (!object->parent)
		  return MxFalse;

	 /* Set some limits on the new index of the object */
	 if (newindex < 0)
		  newindex = 0;
	 if (newindex > parchild - 1)
		  newindex = parchild - 1;

	 /* Ask if we can change places */
	 if (index != newindex) {
		  void *ret = MxEventSendObject(parent->children.data->child[newindex],
												  MxEventZOrderRequest,
												  parent->children.data->child[newindex]);

		  /* The object said no */
		  if (ret)
				return MxFalse;
	 }

	 /* Do we move the object to higher index */
	 if (index < newindex) {

		  for (i = index; i < newindex; i++) {
				parent->children.data->child[i] = parent->children.data->child[i + 1];
				parent->children.data->child[i]->index -= 1;
		  }

		  parent->children.data->child[newindex] = object;
		  parent->children.data->child[newindex]->index = newindex;

		  /* Do we move the object to lower index */
	 } else if (index > newindex) {
		  for (i = index; i > newindex; i--) {
				parent->children.data->child[i] = parent->children.data->child[i - 1];
				parent->children.data->child[i]->index += 1;
		  }

		  parent->children.data->child[newindex] = object;
		  parent->children.data->child[newindex]->index = newindex;
	 }
	 *neworder = newindex;

	 /* Has the index changed */
	 if (index != newindex) {
		  changed = MxTrue;

		  /* Tell the simlings that the oder has changed */
		  MxEventSendSimpleToChildren(parent, MxEventZOrderInform, object);
	 }

	 return changed;
}

void mx_adjust_geometry(MxObject * object, MxRect * rect, const unsigned int add)
{
	 assert(object);
	 assert(rect);

	 if (!MxParent(object))
		  return;

	 if (add) {
		  object->position.x1 += rect->x1, object->position.y1 += rect->y1, object->position.x2 += rect->x1, object->position.y2 +=
				rect->y1;

		  for (object = MxFirstChild(object); object; object = MxNext(object))
				mx_adjust_geometry(object, rect, add);

	 } else {

		  for (object = MxFirstChild(object); object; object = MxNext(object))
				mx_adjust_geometry(object, rect, add);

		  object->position.x1 -= rect->x1, object->position.y1 -= rect->y1, object->position.x2 -= rect->x1, object->position.y2 -=
				rect->y1;
	 }
}

unsigned int MxIndex(const MxObject * const object)
{
	 assert(object);
	 return object->index;
}

MxObject *MxParent(const MxObject * const object)
{
	 assert(object);
	 return object->parent;
}

unsigned int MxNumChild(const MxObject * const object)
{
	 assert(object);

	 if (!object->children.data)
		  return 0;

	 return object->children.data->num;
}

MxObject *MxNext(const MxObject * const object)
{
	 assert(object);

	 if (object->parent) {
		  const int num = MxNumChild(object->parent);

		  if (object->index + 1 < num)
				return object->parent->children.data->child[object->index + 1];
	 }

	 return 0;
}

MxObject *MxPrev(const MxObject * const object)
{
	 assert(object);

	 if ((object->parent) && (object->index))
		  return object->parent->children.data->child[object->index - 1];

	 return 0;
}

MxObject *MxFirst(const MxObject * const object)
{
	 assert(object);
	 if (object->parent)
		  return MxFirstChild(object->parent);

	 return 0;
}

MxObject *MxLast(const MxObject * const object)
{
	 assert(object);
	 if (object->parent)
		  return MxLastChild(object->parent);

	 return 0;
}

MxObject *MxLastChild(const MxObject * const object)
{
	 assert(object);
	 if (object->children.data)
		  return object->children.data->child[object->children.data->num - 1];

	 return 0;
}

MxObject *MxFirstChild(const MxObject * const object)
{
	 assert(object);
	 if (object->children.data)
		  return object->children.data->child[0];

	 return 0;
}

typedef int (*qsortfunc) (const void *one, const void *two);

void mx_child_sort(MxObject * const object, MxChildSortFunc sort)
{
	 int i;

	 /* A little cast to a temporary variable to avoid a warning */
	 const qsortfunc func = (qsortfunc) sort;

	 assert(object);
	 assert(sort);

	 /* Don't sort if there are no children */
	 if (!object->children.data)
		  return;

	 /* Sort the children pointers */
	 qsort(object->children.data->child, object->children.data->num, sizeof(MxObject *), func);

	 /* Correct the object indexes */
	 for (i = 0; i < object->children.data->num; i++)
		  object->children.data->child[i]->index = i;
}
