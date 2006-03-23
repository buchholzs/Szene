#include "depui/platform/platform.h"
#include "depui/platform/empty.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_empty_kbd_init(void)
{
	 return 1;
}

void mx_empty_kbd_exit(void)
{
}

void mx_empty_mouse(int *x, int *y, int *b)
{
	 *x = 0;
	 *y = 0;
	 *b = 0;
}

int mx_empty_key_pressed(void)
{
	 return 0;
}

void mx_empty_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 *raw = 0;
	 *key = MxKeyNone;
	 *code = 0;
}
