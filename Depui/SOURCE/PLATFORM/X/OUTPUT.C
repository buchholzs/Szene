#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include "depui/support/mouse.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>

#warning Compiling DEPUI for X

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

Display *mx_x_display;
Window mx_x_window;
static int thescreen;
static Visual *thevisual;
static Colormap thecolormap;
static GC thecontext;
static GC thetextcontext;
static int thedepth;
static char windowname[50];

int mx_x_width;
int mx_x_height;

int mx_x_gfx_init(MxDriverOutput * driver, int width, int height, int c, const char *title)
{
	 int backColor;
	 XEvent anevent;
	 XTextProperty textproperty;
	 XColor color;
	 XFontStruct *font;
	 const int len = strlen(title);

	 (void) c;

	 strncpy(windowname, title, 50);
	 windowname[len] = '\0';

	 mx_x_display = XOpenDisplay(NULL);
	 thescreen = DefaultScreen(mx_x_display);
	 thecolormap = DefaultColormap(mx_x_display, thescreen);
	 thedepth = DefaultDepth(mx_x_display, thescreen);
	 thevisual = DefaultVisual(mx_x_display, thescreen);

	 color.red = 0 << 8;
	 color.green = 0 << 8;
	 color.blue = 0 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxForeIndex] = color.pixel;
	 color.red = 174 << 8;
	 color.green = 174 << 8;
	 color.blue = 174 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxBackIndex] = color.pixel;

	 color.red = 0 << 8;
	 color.green = 0 << 8;
	 color.blue = 0 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxObjectForeIndex] = color.pixel;
	 color.red = 255 << 8;
	 color.green = 255 << 8;
	 color.blue = 255 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxObjectBackIndex] = color.pixel;

	 color.red = 255 << 8;
	 color.green = 255 << 8;
	 color.blue = 255 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxSelectedForeIndex] = color.pixel;
	 color.red = 84 << 8;
	 color.green = 124 << 8;
	 color.blue = 82 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxSelectedBackIndex] = color.pixel;

	 color.red = 215 << 8;
	 color.green = 215 << 8;
	 color.blue = 215 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxLightIndex] = color.pixel;
	 color.red = 154 << 8;
	 color.green = 154 << 8;
	 color.blue = 154 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxMedIndex] = color.pixel;
	 color.red = 114 << 8;
	 color.green = 114 << 8;
	 color.blue = 114 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxDarkIndex] = color.pixel;

	 color.red = 92 << 8;
	 color.green = 156 << 8;
	 color.blue = 69 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxDesktopIndex] = color.pixel;
	 backColor = color.pixel;

	 color.red = 0 << 8;
	 color.green = 255 << 8;
	 color.blue = 0 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxFocusIndex] = color.pixel;

	 color.red = 147 << 8;
	 color.green = 147 << 8;
	 color.blue = 147 << 8;
	 XAllocColor(mx_x_display, thecolormap, &color);
	 driver->colors[MxDisabledIndex] = color.pixel;

	 /* Create the window */
	 mx_x_window = XCreateSimpleWindow(mx_x_display, DefaultRootWindow(mx_x_display), 0, 0, width, height, 0, backColor, backColor);
	 XSelectInput(mx_x_display, mx_x_window, StructureNotifyMask);
	 XMapWindow(mx_x_display, mx_x_window);

	 /* Label the window */
	 XStringListToTextProperty(&windowname, 1, &textproperty);
	 XSetWMName(mx_x_display, mx_x_window, &textproperty);
	 XSetStandardProperties(mx_x_display, mx_x_window, windowname, windowname, None, NULL, 0, NULL);

	 /* Get the general context */
	 thecontext = XCreateGC(mx_x_display, mx_x_window, 0, NULL);
	 XSetBackground(mx_x_display, thecontext, backColor);
	 XSetForeground(mx_x_display, thecontext, backColor);
	 thetextcontext = XCreateGC(mx_x_display, mx_x_window, 0, NULL);

	 /* Wait for the MapNotify event */
	 for (;;) {
		  XNextEvent(mx_x_display, &anevent);
		  if (anevent.type == MapNotify)
				break;
	 }

	 /* Set event types */
	 XSelectInput(mx_x_display, mx_x_window,
					  ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | StructureNotifyMask);

	 /* Erase the display (In the background colour), bring to top */
	 XClearWindow(mx_x_display, mx_x_window);
	 XMapRaised(mx_x_display, mx_x_window);

	 /* Set the basic font to use */
	 font = XLoadQueryFont(mx_x_display, "fixed");
//  font = XLoadQueryFont(mx_x_display, "5x8");
	 XSetFont(mx_x_display, thetextcontext, font->fid);
	 driver->font = (struct MxFont *) font;

	 XSetLineAttributes(mx_x_display, thecontext, 1, LineSolid, CapButt, JoinRound);
	 XSetLineAttributes(mx_x_display, thetextcontext, 1, LineSolid, CapButt, JoinRound);

	 mx_x_width = DisplayWidth(mx_x_display, thescreen);
	 mx_x_height = DisplayHeight(mx_x_display, thescreen);

	 return 1;
}

void mx_x_gfx_exit(void)
{
	 XFreeGC(mx_x_display, thecontext);
	 XFreeGC(mx_x_display, thetextcontext);
	 XUnmapWindow(mx_x_display, mx_x_window);
	 XDestroyWindow(mx_x_display, mx_x_window);
	 XCloseDisplay(mx_x_display);
}

void mx_x_flush(void)
{
	 XFlush(mx_x_display);
}

void mx_x_mouse_show(const int show)
{
	 (void) show;
}

MxColor mx_x_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_x_encode(int index, int r, int g, int b)
{
	 XColor color;

	 (void) index;

	 color.red = r << 8;
	 color.green = g << 8;
	 color.blue = b << 8;

	 XAllocColor(mx_x_display, thecolormap, &color);
	 return color.pixel;
}

void mx_x_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
}

void mx_x_done_drawing_area(void)
{
}

void mx_x_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_x_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_x_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_x_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_x_screen_width(struct MxImage *image)
{
	 (void) image;
	 return mx_x_width;
}

int mx_x_screen_height(struct MxImage *image)
{
	 (void) image;
	 return mx_x_height;
}

int mx_x_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return thedepth;
}

void mx_x_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 XSetForeground(mx_x_display, thecontext, color);
	 XDrawPoint(mx_x_display, mx_x_window, thecontext, x1, y1);
}

MxColor mx_x_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;

	 /* Not supported yet */
	 assert(0);

//  return XGetPixel(theimage, x1, y1);
	 return 0;
}

void mx_x_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 XSetForeground(mx_x_display, thecontext, color);
	 XDrawLine(mx_x_display, mx_x_window, thecontext, x1, y1, x2 + 1, y1);
}

void mx_x_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 XSetForeground(mx_x_display, thecontext, color);
	 XDrawLine(mx_x_display, mx_x_window, thecontext, x1, y1, x1, y2 + 1);
}

void mx_x_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 XSetForeground(mx_x_display, thecontext, color);
	 XFillRectangle(mx_x_display, mx_x_window, thecontext, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

void mx_x_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
	 mx_x_screen_pixel(image, x1, y1, mx_x_blend(color, mx_x_screen_get_pixel(image, x1, y1), alpha));
}

struct MxImage *mx_x_image_create(int w, int h)
{
	 /* This should really call XCreateImage to me fast (what I have here is
	    slow) but I don't really know how to fill in all the arguments in the
	    correct way.  This way works, but should be improved at some point */
	 return (struct MxImage *) XGetImage(mx_x_display, mx_x_window, 0, 0, w, h, AllPlanes, XYPixmap);
}

void mx_x_image_destroy(struct MxImage *image)
{
	 if (image)
		  XDestroyImage((XImage *) image);
}

struct MxImage *mx_x_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_x_image_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_x_image_release(struct MxImage *image)
{
	 (void) image;
}

int mx_x_image_height(struct MxImage *image)
{
	 return ((XImage *) image)->width;
}

int mx_x_image_width(struct MxImage *image)
{
	 return ((XImage *) image)->height;
}

int mx_x_image_depth(struct MxImage *image)
{
	 return ((XImage *) image)->depth;
}

void mx_x_image_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 XPutPixel((XImage *) image, x1, y1, color);
}

MxColor mx_x_image_get_pixel(struct MxImage *image, int x1, int y1)
{
	 return XGetPixel((XImage *) image, x1, y1);
}

void mx_x_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 Mx_ImageHLineFast(image, x1, y1, x2, color, mx_x_image_pixel);
}

void mx_x_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 Mx_ImageVLineFast(image, x1, y1, y2, color, mx_x_image_pixel);
}

void mx_x_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_x_image_pixel);
}

void mx_x_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 XPutPixel((XImage *) image, x1, y1, mx_x_blend(color, XGetPixel((XImage *) image, x1, y1), alpha));
}

void mx_x_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 /* No suport for this yet */
	 assert(0);
}

void mx_x_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) dest;
	 XPutImage(mx_x_display, mx_x_window, thecontext, (XImage *) src, sx, sy, dx, dy, w, h);
}

void mx_x_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 XGetSubImage(mx_x_display, mx_x_window, sx, sy, w, h, AllPlanes, XYPixmap, (XImage *) dest, dx, dy);
}

void mx_x_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 /* No support for this yet */
	 assert(0);
}

void mx_x_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_x_screen_pixel);
}

struct MxFont *mx_x_font_load(const char *name, int points, MxFontFlag flags)
{
	 return 0;
}

void mx_x_font_destroy(struct MxFont *font)
{
	 (void) font;
}

void mx_x_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
									  MxColor back)
{
	 unsigned int i;

	 /* Copy the regions over to X style and but it on the GC */
	 XRectangle rect;
	 Region xregion = XCreateRegion();

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  rect.x = s->x1;
		  rect.y = s->y1;
		  rect.width = s->x2 - s->x1 + 1;
		  rect.height = s->y2 - s->y1 + 1;
		  XUnionRectWithRegion(&rect, xregion, xregion);
	 }

	 /* Set the proper text clipping regions */
	 XSetRegion(mx_x_display, thetextcontext, xregion);
	 XDestroyRegion(xregion);

	 /* Find the correct baseline of the text */
	 y += ((XFontStruct *) font)->ascent;

	 /* Actually get X to draw the text */
	 XSetForeground(mx_x_display, thetextcontext, color);
	 XSetBackground(mx_x_display, thetextcontext, back);
	 XDrawImageString(mx_x_display, mx_x_window, thetextcontext, x, y, text, strlen(text));
}

void mx_x_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
									 int y, MxColor color, MxColor back)
{
}

unsigned int mx_x_font_length(const struct MxFont *font, const char *text)
{
	 return XTextWidth((XFontStruct *) font, text, strlen(text));
}

unsigned int mx_x_font_height(const struct MxFont *font)
{
	 return ((XFontStruct *) font)->ascent + ((XFontStruct *) font)->descent;
}
