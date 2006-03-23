#include "depui/config.h"

#if defined(MX_DRIVER_NONE)

#elif defined(MX_DRIVER_GENERIC)
#include "platform/generic/system.c"

#elif defined(MX_DRIVER_ALLEGRO)
#include "platform/allegro/system.c"

#elif defined(MX_DRIVER_SVGALIB)
#include "platform/svgalib/system.c"

#elif defined(MX_DRIVER_GRX)
#include "platform/grx/system.c"

#elif defined(MX_DRIVER_BORLAND_BGI)
#include "platform/borland/bgi/system.c"

#elif defined(MX_DRIVER_DJVESA2)
#include "platform/djvesa2/system.c"

#elif defined(MX_DRIVER_DJVESA1)
#include "platform/djvesa1/system.c"

#elif defined(MX_DRIVER_TINYPTC)
#include "platform/tiny_ptc/system.c"

#elif defined(MX_DRIVER_NANOX)
#include "platform/nanox/system.c"

#elif defined(MX_DRIVER_X)
#include "platform/x/system.c"

#elif defined(MX_DRIVER_OPENGUI)
#include "platform/opengui/system.c"

#elif defined(MX_DRIVER_VGA)
#include "platform/vga/system.c"

#elif defined(MX_DRIVER_PORT)
#include "platform/port/system.c"

#endif
