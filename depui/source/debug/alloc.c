#include <stdlib.h>
#include <stdio.h>
#include "depui/config.h"
#include "depui/debug/alloc.h"

/* Show memory use on screen in real time */
#define SHOW_MEM_USE

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#ifdef MX_DEBUG_MEM

#ifdef SHOW_MEM_USE

#ifdef __DJGPP__
#include <allegro.h>
#endif

#ifdef __BORLANDC__
#include <graphics.h>
#endif

#endif

void *_mx_stack_base;
void *_mx_highest_stack;

typedef struct Mem {
	 void *mem;
	 int size;
	 const char *file;
	 int line;
} Mem;

static Mem *allmem = NULL;
static int num = 0;
static int maxnum = 0;
static int maxmem = 0;
static int summem = 0;

static int __sum_mem(void)
{
	 int i, sum = 0;

	 for (i = 0; i < num; i++)
		  sum += allmem[i].size;

#ifdef SHOW_MEM_USE
	 {
		  char string[500];

		  sprintf(string, "%5i[%4i]", summem, num);

#ifdef __DJGPP__
		  text_mode(makecol(0, 0, 0));
		  textout(screen, font, string, 0, 0, makecol(255, 255, 255));
#endif

#ifdef __BORLANDC__
		  setfillstyle(i, EGA_BLACK);
		  bar(0, 0, 100, 8);

		  setcolor(EGA_WHITE);
		  outtextxy(0, 0, string);
#endif
	 }
#endif

	 return sum;
}

static void _add_mem(void *mem, int size, const char *file, int line)
{
	 Mem newmem;

	 newmem.mem = mem;
	 newmem.size = size;
	 newmem.file = file;
	 newmem.line = line;

	 allmem = realloc(allmem, (num + 1) * sizeof(Mem));
	 allmem[num] = newmem;
	 ++num;

	 summem = __sum_mem();
	 if (summem > maxmem)
		  maxmem = summem;

	 if (num > maxnum)
		  maxnum = num;
}

static int _find_mem(void *mem)
{
	 int i;

	 for (i = 0; i < num; i++)
		  if (allmem[i].mem == mem)
				return i;

	 return -1;
}

static int _remove_mem(void *mem)
{
	 int i;
	 int index = _find_mem(mem);

	 if (index < 0)
		  return 0;

	 for (i = index; i < num - 1; i++)
		  allmem[i] = allmem[i + 1];

	 --num;
	 allmem = realloc(allmem, (num + 1) * sizeof(Mem));
	 summem = __sum_mem();

	 return 1;
}

static int init = 0;

static void _done(void)
{
	 int i;

	 for (i = 0; i < num; i++) {
		  fprintf(mx_stream, "!!!Unfreed %i bytes [%p] from %s : %i\n", allmem[i].size, allmem[i].mem, allmem[i].file, allmem[i].line);
		  fflush(mx_stream);
	 }

	 free(allmem);
}

#define HEADER_SIZE 32

static void _write_header(void *mem, unsigned int bytes)
{
	 int i;
	 char *start = (char *) mem - HEADER_SIZE;

	 srand((unsigned) mem);

	 for (i = 0; i < HEADER_SIZE; i++)
		  start[i] = rand() & 0xff;

	 start = (char *) mem + bytes;
	 for (i = 0; i < HEADER_SIZE; i++)
		  start[i] = rand() & 0xff;
}

static int _check_header(void *mem, unsigned int bytes, FILE * stream)
{
	 int i;
	 char *start = (char *) mem - HEADER_SIZE;

	 srand((unsigned) mem);

	 for (i = 0; i < HEADER_SIZE; i++) {
		  char dat = rand() & 0xff;

		  if (start[i] != dat) {
				fprintf(stream, "Pre Damage 0x%02x[0x%02x]\n", start[i], dat);
				return 1;
		  }
	 }

	 start = (char *) mem + bytes;

	 for (i = 0; i < HEADER_SIZE; i++) {
		  char dat = rand() & 0xff;

		  if (start[i] != dat) {
				fprintf(stream, "Post Damage 0x%02x[0x%02x]\n", start[i], dat);
				return 1;
		  }
	 }

	 return 0;
}

static void _print_header(FILE * stream, void *mem, unsigned int bytes)
{
	 int i;
	 char *start = (char *) mem - HEADER_SIZE;

	 srand((unsigned) mem);

	 fprintf(stream, "Pre: ");

	 for (i = 0; i < HEADER_SIZE; i++)
		  fprintf(stream, "0x%02x[0x%02x] ", start[i] & 0xff, rand() & 0xff);

	 fprintf(stream, "Post: ");

	 start = (char *) mem + bytes;
	 for (i = 0; i < HEADER_SIZE; i++)
		  fprintf(stream, "0x%02x[0x%02x] ", start[i] & 0xff, rand() & 0xff);

	 fprintf(stream, "\n");
}

void *_MxMalloc(unsigned int bytes, const char *file, const int line)
{
	 void *mem = malloc(bytes + (HEADER_SIZE * 2));

	 if (!init) {
		  atexit(_done);
		  init = 1;
	 }

	 if (bytes == 0) {
		  fprintf(mx_stream, "!!!Malloc of zero %s : %i [%p]\n", file, line, mem);
		  fflush(mx_stream);
		  exit(9);
	 }

	 mem = (char *) mem + HEADER_SIZE;

	 fprintf(mx_stream, "%p %i %s %i malloc\n", mem, bytes, file, line);

	 _add_mem(mem, bytes, file, line);
	 fprintf(mx_stream, "malloc \t%5i\t%8i\t%8i\t[%i] %s : %i\n", bytes, summem, maxmem, num, file, line);
	 fflush(mx_stream);

	 _write_header(mem, bytes);
	 return mem;
}

void *_MxRealloc(void *oldmem, unsigned int bytes, const char *file, const int line)
{
	 void *mem;

	 if (!init) {
		  atexit(_done);
		  init = 1;
	 }

	 if (bytes == 0) {
		  fprintf(mx_stream, "!!!Realloc to zero %s : %i [%p]\n", file, line, oldmem);
		  fflush(mx_stream);
		  exit(10);
	 }

	 if (oldmem)
		  mem = realloc((char *) oldmem - HEADER_SIZE, bytes + (HEADER_SIZE * 2));
	 else
		  mem = realloc(oldmem, bytes + (HEADER_SIZE * 2));
	 mem = (char *) mem + HEADER_SIZE;

	 fprintf(mx_stream, "%p %i %s %i realloc %p\n", mem, bytes, file, line, oldmem);

	 if (oldmem) {
		  if (!_remove_mem(oldmem)) {
				fprintf(mx_stream, "!!!Realloc of unallocatd %s : %i\n", file, line);
				fflush(mx_stream);
				exit(11);
		  }
	 }

	 _add_mem(mem, bytes, file, line);

	 if (oldmem != mem) {
		  fprintf(mx_stream, "realloc\t%5i\t%8i\t%8i\t[%i] %s : %i\n", bytes, summem, maxmem, num, file, line);
		  fflush(mx_stream);
	 }

	 _write_header(mem, bytes);
	 return mem;
}

void _MxFree(void *mem, const char *file, const int line)
{
	 int index = _find_mem(mem);

	 if (!init) {
		  atexit(_done);
		  init = 1;
	 }

	 fprintf(mx_stream, "%p %i %s %i free\n", mem, -1, file, line);

	 if (index < 0) {
		  fprintf(mx_stream, "!!!Free of unallocated %s : %i [%p]\n", file, line, mem);
		  fflush(mx_stream);
		  exit(13);

	 } else {

		  if (_check_header(mem, allmem[index].size, mx_stream)) {
				fprintf(mx_stream, "!!! Header damaged\n");
				_print_header(mx_stream, mem, allmem[index].size);
				exit(14);
		  }

		  fprintf(mx_stream, "free    \t%5i\t%8i\t%8i\t[%i] %s : %i\n", allmem[index].size, summem, maxmem, num, file, line);
		  fflush(mx_stream);

		  _remove_mem(mem);

		  /* Set freed data to zero */
//        memset(mem, 0, 1);
//        memset(mem, 0, allmem[index].size);
//        memset((char *) mem - HEADER_SIZE, 0, allmem[index].size);
	 }
	 free((char *) mem - HEADER_SIZE);
}

void _MxCheckStack(void *ptr, const char *file, const int line)
{
	 long diff = (long) _mx_stack_base - (long) ptr;
	 long most = (long) _mx_stack_base - (long) _mx_highest_stack;

	 if (!init) {
		  atexit(_done);
		  init = 1;
	 }

	 if (diff > most) {
		  _mx_highest_stack = ptr;
		  fprintf(mx_stream, "%9li at %s : %i\n", diff, file, line);
	 }
}

#else
/* Keep ANSI happy about empty files */
extern int mx_do_not_use_this_name;

#endif
