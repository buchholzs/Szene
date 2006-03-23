#include "depui/config.h"

#if defined(MX_DRIVER_NONE)

#elif defined(MX_DRIVER_GENERIC)
#include "platform/generic/output.c"

#elif defined(MX_DRIVER_ALLEGRO)
#include "platform/allegro/output.c"

#elif defined(MX_DRIVER_SVGALIB)
#include "platform/svgalib/output.c"

#elif defined(MX_DRIVER_GRX)
#include "platform/grx/output.c"

#elif defined(MX_DRIVER_BORLAND_BGI)
#include "platform/borland/bgi/output.c"

#elif defined(MX_DRIVER_DJVESA2)
#include "platform/djvesa2/output.c"

#elif defined(MX_DRIVER_DJVESA1)
#include "platform/djvesa1/output.c"

#elif defined(MX_DRIVER_TINYPTC)
#include "platform/tiny_ptc/output.c"

#elif defined(MX_DRIVER_NANOX)
#include "platform/nanox/output.c"

#elif defined(MX_DRIVER_X)
#include "platform/x/output.c"

#elif defined(MX_DRIVER_OPENGUI)
#include "platform/opengui/output.c"

#elif defined(MX_DRIVER_VGA)
#include "platform/vga/output.c"

#elif defined(MX_DRIVER_PORT)
#include "platform/port/output.c"

#endif
