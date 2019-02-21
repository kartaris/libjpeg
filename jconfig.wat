/* jconfig.wat --- jconfig.h for Watcom C/C++ on MS-DOS or OS/2. */
/* see jconfig.txt for explanations */

#define HAVE_PROTOTYPES
#define HAVE_UNSIGNED_CHAR
#define HAVE_UNSIGNED_SHORT
/* #define void char */
/* #define const */
#define CHAR_IS_UNSIGNED
#define HAVE_STDDEF_H
#define HAVE_STDLIB_H
#undef NEED_BSD_STRINGS
#undef NEED_SYS_TYPES_H
#undef NEED_FAR_POINTERS	/* Watcom uses flat 32-bit addressing */
#undef LJPEG9_NEED_SHORT_EXTERNAL_NAMES
#undef INCOMPLETE_TYPES_BROKEN

#ifdef JPEG_INTERNALS

#undef RIGHT_SHIFT_IS_UNSIGNED

#endif /* JPEG_INTERNALS */

#ifdef JPEG_CJPEG_DJPEG

#define LJPEG9_BMP_SUPPORTED		/* BMP image file format */
#define LJPEG9_GIF_SUPPORTED		/* GIF image file format */
#define LJPEG9_PPM_SUPPORTED		/* PBMPLUS PPM/PGM image file format */
#undef LJPEG9_RLE_SUPPORTED		/* Utah RLE image file format */
#define LJPEG9_TARGA_SUPPORTED		/* Targa image file format */

#undef TWO_FILE_COMMANDLINE	/* optional */
#define LJPEG9_USE_SETMODE		/* Needed to make one-file style work in Watcom */
#undef LJPEG9_NEED_SIGNAL_CATCHER	/* Define this if you use jmemname.c */
#undef DONT_USE_B_MODE
#undef LJPEG9_PROGRESS_REPORT		/* optional */

#endif /* JPEG_CJPEG_DJPEG */
