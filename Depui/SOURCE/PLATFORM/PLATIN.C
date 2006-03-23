#include "depui/config.h"

#if defined(MX_DRIVER_NONE)

#elif defined(MX_DRIVER_GENERIC)
#include "platform/generic/input.c"

#elif defined(MX_DRIVER_ALLEGRO)
#include "platform/allegro/input.c"

#elif defined(MX_DRIVER_BORLAND_BGI)
#include "platform/borland/bgi/input.c"

#elif defined(MX_DRIVER_SVGALIB)
#include "platform/svgalib/input.c"

#elif defined(MX_DRIVER_GRX)
#include "platform/grx/input.c"

#elif defined(MX_DRIVER_DJVESA2)
#include "platform/djvesa2/input.c"

#elif defined(MX_DRIVER_DJVESA1)
#include "platform/djvesa1/input.c"

#elif defined(MX_DRIVER_TINYPTC)
#include "platform/tiny_ptc/input.c"

#elif defined(MX_DRIVER_NANOX)
#include "platform/nanox/input.c"

#elif defined(MX_DRIVER_X)
#include "platform/x/input.c"

#elif defined(MX_DRIVER_OPENGUI)
#include "platform/opengui/input.c"

#elif defined(MX_DRIVER_VGA)
#include "platform/vga/input.c"

#elif defined(MX_DRIVER_PORT)
#include "platform/port/input.c"

#endif
