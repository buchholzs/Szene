#include "depui/config.h"
#ifdef MX_NEED_FONT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/graphics/clip.h"
#include "depui/support/font.h"

/*Static antialiasing table for filled text background speeds things up */
static unsigned int _aa_setup = MxFalse;
static MxColor _aa_color;
static MxColor _aa_back;
static MxColor _aa_table[16];

static void _setup_aa_table(const MxColor color, const MxColor back, const MxBlendFunc blend)
{
	 int i;

	 for (i = 0; i < 16; i++)
		  _aa_table[i] = blend(color, back, i << 4);

	 _aa_color = color, _aa_back = back, _aa_setup = MxTrue;
}

static void _draw_filled_antialiased_char(struct MxImage *image, int x, int y, int h, const unsigned char *data,
														const MxImagePixelFunc pixel, const MxRect * const rect, const MxPixelClipFunc dopixel)
{
	 int i, r;
	 const int w = *data;

	 data++;

	 for (r = y; r < y + h; r++) {
		  for (i = x; i < x + w; i++) {
				dopixel(image, i, r, _aa_table[(*data) >> 4], rect, pixel);
				++data;
		  }
	 }
}

static void _draw_unfilled_antialiased_char(struct MxImage *image, int x, int y, int h, const unsigned char *data, MxColor color,
														  const MxRect * const rect, const MxImagePixelFunc pixel, const MxImagePixelTransFunc trans,
														  const MxPixelClipFunc dopixel, const MxPixelTransClipFunc dotrans)
{
	 int i, r;
	 const int w = *data;

	 data++;

	 for (r = y; r < y + h; r++) {
		  for (i = x; i < x + w; i++) {

				const int alpha = *data;

				++data;

				if (alpha == 255)
					 dopixel(image, i, r, color, rect, pixel);
				else
					 dotrans(image, i, r, color, alpha, rect, trans);
		  }
	 }
}

void Mx_FontTextAntialiasedRender(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											 MxColor back, MxBlendFunc blend, const MxRect * const clip, MxImagePixelFunc pixel,
											 MxImagePixelTransFunc trans)
{
	 const int fill = (color == back) ? 0 : 1;
	 const int height = font->height;

	 const MxFontIndex *range = 0;
	 MxFontIndex *data = (MxFontIndex *) (font + 1);
	 const unsigned char *chardata = (const unsigned char *) (data + font->sections);

	 /* 
	  * Setup the antialiasing table for fast drawing of filled characters 
	  */
	 if (fill) {
		  if ((color != _aa_color) || (back != _aa_back) || (!_aa_setup))
				_setup_aa_table(color, back, blend);
	 }

	 while (*text) {
		  const unsigned int c = *text;

		  if ((!range) || (c < range->start) || (c >= (range->start + 128)))
				range = mx_font_range(font, c);

		  if (range) {
				const unsigned char *cdata = &chardata[range->index[c - range->start]];

				MxPixelClipFunc do_pixel = mx_pixel;
				MxPixelTransClipFunc do_trans = mx_pixel_trans;

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
						  && (intersect.y2 == charrect.y2)) {
						  do_pixel = mx_pixel_fast, do_trans = mx_pixel_trans_fast;
					 }

					 if (fill)
						  _draw_filled_antialiased_char(image, x, y, height, cdata, pixel, clip, do_pixel);
					 else
						  _draw_unfilled_antialiased_char(image, x, y, height, cdata, color, clip, pixel, trans, do_pixel, do_trans);
				}
				x += *cdata;
		  }
		  ++text;
	 }
}

#else
extern int mx_ignore_this;

#endif
