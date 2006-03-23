#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int calls;

/* Start them off at the same portion of the clock */
static clock_t clock_sync(void)
{
	 clock_t ret;
	 const clock_t start = clock();

	 /* Wait for a switch */
	 ret = clock();
	 while (start == ret)
		  ret = clock();

	 return ret;
}

/* Simulate a C++ vtable virtual member function */
static int vtable_handler(void)
{
	 ++calls;
	 return 0;
}

typedef int (*func) (void);

typedef struct vtable {
	 func handle;
} vtable;

typedef struct vobject {
	 vtable *table;
} vobject;

vtable table = { vtable_handler };

static int time_virtual(vobject * object, const int seconds)
{
	 const clock_t start = clock_sync();
	 const clock_t end = start + CLOCKS_PER_SEC * seconds;

	 calls = 0;

	 while (end > clock())
		  object->table->handle();

	 return calls;
}

/* Event handling like in DEPUI */
static int event_handler(int data)
{
	 switch (data) {

	 case 0:
		  ++calls;
		  break;

	 case 1:
		  break;

	 default:
		  break;
	 }

	 return 0;
}

static int second_event_handler(int data)
{
	 switch (data) {

	 case 1:
		  break;

		  /* Call a first level handler */
	 default:
		  return event_handler(data);
	 }

	 return 0;
}

static int third_event_handler(int data)
{
	 switch (data) {

	 case 1:
		  break;

		  /* Call a first level handler */
	 default:
		  return second_event_handler(data);
	 }

	 return 0;
}

static int fourth_event_handler(int data)
{
	 switch (data) {

	 case 1:
		  break;

		  /* Call a first level handler */
	 default:
		  return third_event_handler(data);
	 }

	 return 0;
}

typedef int (*handler) (int);

typedef struct hobject {
	 handler handle;
} hobject;

static int time_event_handler(hobject * obj, const int seconds)
{
	 const clock_t start = clock_sync();
	 const clock_t end = start + CLOCKS_PER_SEC * seconds;

	 calls = 0;

	 while (end > clock())
		  obj->handle(0);

	 return calls;
}

int main(void)
{
	 int virt;
	 int event1;
	 int event2;
	 int event3;
	 int event4;

	 vobject obj = { &table };
	 hobject obj1 = { event_handler };
	 hobject obj2 = { second_event_handler };
	 hobject obj3 = { third_event_handler };
	 hobject obj4 = { fourth_event_handler };

	 /* Call them once to get stuff into the cache */
	 time_virtual(&obj, 1);
	 virt = time_virtual(&obj, 2);

	 time_event_handler(&obj1, 1);
	 event1 = time_event_handler(&obj1, 2);

	 time_event_handler(&obj2, 1);
	 event2 = time_event_handler(&obj2, 2);

	 time_event_handler(&obj3, 1);
	 event3 = time_event_handler(&obj3, 2);

	 time_event_handler(&obj4, 1);
	 event4 = time_event_handler(&obj4, 2);

	 /* Output real results */
	 printf("Virtual              func = %i calls\n", virt);
	 printf("Event Handler        func = %i calls\n", event1);
	 printf("Second Event Handler func = %i calls\n", event2);
	 printf("Third  Event Handler func = %i calls\n", event3);
	 printf("Fourth Event Handler func = %i calls\n", event4);

	 return 0;
}
