#include "depui/config.h"
#ifdef MX_NEED_FONT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/support/font.h"
#include "depui/graphics/clip.h"

static void _draw_pixmap_char(struct MxImage *image, int x, int y, int h, const unsigned char *data, MxColor color, MxColor back,
										int fill, MxImagePixelFunc pixel, const MxRect * const rect, MxPixelClipFunc dopixel)
{
	 int i, r;
	 const int w = *data;

	 unsigned int bpix;

	 for (r = y; r < y + h; r++) {

		  bpix = 0x100, ++data;

		  for (i = x; i < x + w; i++) {

				/* Go one pixel to right, and maybe to the next data byte */
				bpix >>= 1;
				if (!bpix) {
					 bpix = 0x80, ++data;
				}

				/* If bit is set draw color, otherwise background if necessary */
				if ((*data) & bpix)
					 dopixel(image, i, r, color, rect, pixel);
				else if (fill)
					 dopixel(image, i, r, back, rect, pixel);
		  }
	 }
}

void Mx_FontTextPixmapRender(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
									  MxColor back, const MxRect * const clip, MxImagePixelFunc pixel)
{
	 const int fill = (color == back) ? 0 : 1;
	 const int height = font->height;

	 const MxFontIndex *range = 0;
	 MxFontIndex *data = (MxFontIndex *) (font + 1);
	 const unsigned char *chardata = (const unsigned char *) (data + font->sections);

	 while (*text) {
		  const unsigned int c = *text;

		  /* Find the character in the range */
		  if ((!range) || (c < range->start) || (c >= (range->start + 128)))
				range = mx_font_range(font, c);

		  if (range) {
				const unsigned char *cdata = &chardata[range->index[c - range->start]];

				MxPixelClipFunc do_pixel = mx_pixel;

				MxRect intersect;
				MxRect charrect;

				charrect.x1 = x, charrect.y1 = y, charrect.x2 = x + *cdata, charrect.y2 = y + height;

				/* If left side of char farther than right side of clipping, we
				   are done */
				if (x > clip->x2)
					 return;

				MX_INTERSECT_RECTS(*clip, charrect, intersect);
				if (MX_VALID_RECT(intersect)) {

					 /* Use a fast pixel method if it is not even partially
					    clipped */
					 if ((intersect.x1 == charrect.x1)
						  && (intersect.y1 == charrect.y1)
						  && (intersect.x2 == charrect.x2)
						  && (intersect.y2 == charrect.y2))
						  do_pixel = mx_pixel_fast;

					 /* Don't draw the character if it is totally clipped */
					 _draw_pixmap_char(image, x, y, height, cdata, color, back, fill, pixel, clip, do_pixel);
				}
				x += *cdata;
		  }
		  ++text;
	 }
}

#else
extern int mx_ignore_this;

#endif
