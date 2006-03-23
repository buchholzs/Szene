#ifndef MX_CONFIG_H
#define MX_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
/* *INDENT-OFF* *//* Platform specific defines */
#include "depui/_config.h"
//#define MX_DRIVER_NONE
//#define MX_DRIVER_GENERIC
//#define MX_DRIVER_ALLEGRO
//#define MX_DRIVER_SVGALIB
//#define MX_DRIVER_GRX
//#define MX_DRIVER_BORLAND_BGI
//#define MX_DRIVER_DJVESA2
//#define MX_DRIVER_DJVESA1
//#define MX_DRIVER_TINYPTC
//#define MX_DRIVER_NANOX
//#define MX_DRIVER_OPENGUI
//#define MX_DRIVER_X
//#define MX_DRIVER_PORT

/* Some debugging helping defines */
//#define MX_DEBUG_MEM
//#define MX_DEBUG_EVENT
//#define MX_DEBUG_TRACE
//#define MX_DEBUG_EVENT_LOST
//#define MX_DEBUG_EVENT_QUEUE
//#define MX_DEBUG_EXPOSE_RECT
//#define MX_DEBUG_REGION_RECT
//#define MX_DEBUG_MODULES
//#define MX_DEBUG_IMAGE_AQUIRE
//#define MX_DEBUG_STREAM
//#define MX_DEBUG_REGION_CONSTRUCT
//#define MX_EVENT_NAMES
//#define MX_WINDOW_NAMES

/* Define how many gui idle cycles we will take before yielding to the system */
#define MX_IDLE_TO_YIELD    10

/* If the supporting libs uses the MxImage stuff, you can choose what color depths to support */
//#define MX_IMAGE_SUPPORT_1
//#define MX_IMAGE_SUPPORT_4
//#define MX_IMAGE_SUPPORT_8
//#define MX_IMAGE_SUPPORT_16
//#define MX_IMAGE_SUPPORT_24
//#define MX_IMAGE_SUPPORT_32
//#define MX_IMAGE_LOAD_PCX

//#define MX_IMAGE_LOAD_BMP

/* *INDENT-ON* */
/* Make sure the compiler/library choice is correct for the compiler in use */
#if defined(MX_DRIVER_NONE)
#define MX_PLATFORM "MxPlatformNone"
	 typedef unsigned char MxColor;

#define MX_MAX_PATH 1
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"

/* Check compiler for generic driver */
#elif defined(MX_DRIVER_GENERIC)

#define MX_PLATFORM "MxPlatformGeneric"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_16
//#define MX_NEED_FINDFIRST
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"

	 typedef unsigned long MxColor;

/* Allegro uses strange main macro, see <platform.c> */
#define main MxMain
	 int MxMain(int argc, char *argv[]);

/* Check compiler for allegro driver */
#elif defined(MX_DRIVER_ALLEGRO)

#define MX_PLATFORM "MxPlatformAllegro"
#define MX_MAX_PATH 1024

#ifdef __MSDOS__
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"
#else
#define MX_NEED_FINDFIRST
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"
#endif

	 typedef int MxColor;

//#define MxFont  FONT
//#define MxImage BITMAP

/* Allegro uses strange main macro, see <platform.c> */
#define main MxMain
	 int MxMain(int argc, char *argv[]);

/* Check compiler for GRX driver */
#elif defined(MX_DRIVER_GRX)

#define MX_PLATFORM "MxPlatformGRX"
#define MX_MAX_PATH 1024

#define MX_NEED_MOUSE
#ifdef __MSDOS__
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"
#else
#define MX_NEED_FINDFIRST
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"
#endif

	 typedef unsigned int MxColor;

#define MxFont  GrFont
#define MxImage GrContext

/* Check compiler for Svgalib driver */
#elif defined(MX_DRIVER_SVGALIB)

#define MX_PLATFORM "MxPlatformSvgalib"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_24
#define MX_NEED_FINDFIRST
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"

	 typedef unsigned int MxColor;

/* Check compiler for Borland BGI driver */
#elif defined(MX_DRIVER_BORLAND_BGI)
#if !defined(__BORLANDC__) || !defined(__MSDOS__)
#error "Borland BGI driver required Borland C in DOS"
#endif

#define MX_PLATFORM "MxPlatformBorlandBGI"
#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_IMAGE_SUPPORT_4
#define MX_NO_EMPTY_STRUCTS
#define MX_MAX_PATH 128
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"

	 typedef unsigned char MxColor;

/* Check compiler for generic (DJGPP/VESA2) driver */
#elif defined(MX_DRIVER_DJVESA2)

#define MX_PLATFORM "MxPlatformDJGPPVESA2"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_8
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"

	 typedef unsigned long MxColor;

/* Check compiler for generic (DJGPP/VESA1) driver */
#elif defined(MX_DRIVER_DJVESA1)

#define MX_PLATFORM "MxPlatformDJGPPVESA1"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_8
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"

	 typedef unsigned long MxColor;

/* Check compiler for TinyPTC driver */
#elif defined(MX_DRIVER_TINYPTC)

#define MX_PLATFORM "MxPlatformTinyPTC"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_32
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"

	 typedef unsigned long MxColor;

/* Check compiler for NANOX driver */
#elif defined(MX_DRIVER_NANOX)

#define MX_NEED_FINDFIRST
#define MX_PLATFORM "MxPlatformNanoX"
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"

	 typedef unsigned long MxColor;

#define MxFont  GrFont
#define MxImage GrContext

/* Check compiler for Opengui driver */
#elif defined(MX_DRIVER_OPENGUI)

#define MX_PLATFORM "MxPlatformOpengui"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_8
#define MX_MAX_PATH 1024

#ifdef __MSDOS__
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"
#else
#define MX_NEED_FINDFIRST
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"
#endif

	 typedef unsigned char MxColor;

/* Check compiler for X driver */
#elif defined(MX_DRIVER_X)

#define MX_PLATFORM "MxPlatformX"

#define MX_NEED_FINDFIRST
#define MX_NEED_GENERIC_DRAWING
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "r"
#define MX_FILE_WRITE "w"

	 typedef unsigned long MxColor;

/* Check compiler for testing new graphics port */
#elif defined(MX_DRIVER_PORT)

#define MX_PLATFORM "MxPlatformPort"

#define MX_NEED_FONT
#define MX_NEED_IMAGE
#define MX_NEED_MOUSE
#define MX_IMAGE_SUPPORT_24
#define MX_MAX_PATH 1024
#define MX_FILE_READ  "rb"
#define MX_FILE_WRITE "wb"

	 typedef unsigned long MxColor;

/* There seems to be no driver defined */
#else
#error "One of the drivers must be defined: depui/_config.h"
#endif
/* We cannot support any images depths or loading if we dont have MxImage */
#if !defined(MX_NEED_IMAGE)
#undef MX_IMAGE_SUPPORT_1
#undef MX_IMAGE_SUPPORT_4
#undef MX_IMAGE_SUPPORT_8
#undef MX_IMAGE_SUPPORT_16
#undef MX_IMAGE_SUPPORT_24
#undef MX_IMAGE_SUPPORT_32
#undef MX_IMAGE_LOAD_PCX
#undef MX_IMAGE_LOAD_BMP
#endif
/* Some handy defines to find out what version we have */
#define MX_DEPUI_VERSION                2
#define MX_DEPUI_SUB_VERSION            0
#define MX_DEPUI_VERSION_STRING         "2.0"
#ifdef MX_DEBUG_TRACE
#ifdef __BORLANDC__				  /* Simplified trace macro for Borland C */
#define MX_TRACE(A)				  do { fprintf(mx_stream,"%s \t%s\t%i\n",        \
																		 (A),__FILE__,__LINE__); \
																		 fflush(mx_stream); }    \
														while (0)
#else									  /* Use a better GNU C trace macro */
#define MX_TRACE(A)				  do { fprintf(mx_stream,"%s \t%s\t%i\n",            \
																		 (A),__FUNCTION__,__LINE__); \
																		 fflush(mx_stream); }        \
														while (0)
#endif
#else
#define MX_TRACE(A)
#endif
/* Just making the combination of debug defines meaningful */
#if defined(MX_NEED_IMAGE)
#define MX_NEED_GENERIC_DRAWING
#endif
#if defined(MX_DEBUG_EVENT_QUEUE) || defined(MX_DEBUG_EVENT_LOST)
#define MX_DEBUG_EVENT
#endif
#if defined(MX_DEBUG_EVENT) || defined(MX_DEBUG_TRACE)
#define MX_WINDOW_NAMES
#define MX_EVENT_NAMES
#endif
#if defined(MX_DEBUG_EVENT) || defined(MX_DEBUG_MEM) || defined (MX_DEBUG_EVENT_LOST)  || defined (MX_DEBUG_TRACE)
#define MX_DEBUG_STREAM
#endif
/* Send the event debugging stuff to a file */
#ifdef MX_DEBUG_STREAM
#include <stdio.h>
	 extern FILE *mx_stream;
#endif

#ifdef __cplusplus
}
#endif
#endif
