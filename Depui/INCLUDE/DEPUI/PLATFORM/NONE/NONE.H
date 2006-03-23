#ifndef MX_PLATFORM_NONE_H
#define MX_PLATFORM_NONE_H

#define MxDriverSystemNone                      \
    { 0 }

#define MxDriverOutputNone                      \
	 {0,                            \
	  0,                            \
	  0,                               \
                                                    \
	  0,                          \
                                                     \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     0,                               \
     0,                              \
                                                    \
	  0,                        \
	  0,                   \
	  0,                               \
                                                    \
	  /* The screen vtable */                        \
	  {0,                     \
		0,                      \
		0,                     \
                                                    \
		0,                       \
		0,                      \
		0,                       \
                                                    \
		0,                                \
		0,                             \
                                                    \
		0,                               \
		0,                               \
                                                    \
		0}                            \
	  ,                                              \
     /* The screen trans vtable */                  \
	  {0},                          \
                                                    \
	  /* The clipped screen vtable */                 \
	  {0,                     \
		0,                      \
		0,                     \
                                                    \
		0,                       \
		0,                      \
		0,                       \
                                                    \
		0,                       \
		0,                   \
                                                    \
		0,                       \
		0,                       \
                                                    \
		0}                    \
	  ,                                              \
     /* The clipped screen trans vtable */           \
	  {0},                \
                                                    \
	  0,                        \
	  0,                          \
                                                    \
	  {0,                              \
		0,                       \
		0,                      \
                                                    \
		0,                                \
		0,                               \
      0,                                \
                                                    \
		0,                          \
		0,                       \
                                                    \
		0,                        \
		0,                        \
                                                    \
		0},                    \
	  {0},                 \
                                                    \
	  0,                                \
	  0,                      \
	  0,                    \
	  0,                         \
                                                     \
     0,                            \
                                                    \
	  0,	 							   /* Default font */ \
	  0,                           \
	  0,                        \
                                                    \
	  0,                  \
	  0,                   \
                                                    \
	  0,                         \
	  0}

#define MxDriverInputNone                      \
                                                    \
	 {0,                            \
	  0,                            \
                                                    \
	  0,                         \
	  0,                                 \
                                                    \
	  0}

#define MxDriverSystemDefault MxDriverSystemNone
#define MxDriverOutputDefault MxDriverOutputNone
#define MxDriverInputDefault MxDriverInputNone

#endif
