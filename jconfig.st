/* jconfig.st --- jconfig.h for Atari ST/STE/TT using Pure C or Turbo C. */
/* see jconfig.txt for explanations */

#define HAVE_PROTOTYPES
#define HAVE_UNSIGNED_CHAR
#define HAVE_UNSIGNED_SHORT
/* #define void char */
/* #define const */
#undef CHAR_IS_UNSIGNED
#define HAVE_STDDEF_H
#define HAVE_STDLIB_H
#undef NEED_BSD_STRINGS
#undef NEED_SYS_TYPES_H
#undef NEED_FAR_POINTERS
#undef LJPEG9_NEED_SHORT_EXTERNAL_NAMES
#define INCOMPLETE_TYPES_BROKEN	/* suppress undefined-structure warnings */

#ifdef JPEG_INTERNALS

#undef RIGHT_SHIFT_IS_UNSIGNED

#define ALIGN_TYPE  long	/* apparently double is a weird size? */

#endif /* JPEG_INTERNALS */

#ifdef JPEG_CJPEG_DJPEG

#define LJPEG9_BMP_SUPPORTED		/* BMP image file format */
#define LJPEG9_GIF_SUPPORTED		/* GIF image file format */
#define LJPEG9_PPM_SUPPORTED		/* PBMPLUS PPM/PGM image file format */
#undef LJPEG9_RLE_SUPPORTED		/* Utah RLE image file format */
#define LJPEG9_TARGA_SUPPORTED		/* Targa image file format */

#define TWO_FILE_COMMANDLINE	/* optional -- undef if you like Unix style */
/* Note: if you undef TWO_FILE_COMMANDLINE, you may need to define
 * LJPEG9_USE_SETMODE.  Some Atari compilers require it, some do not.
 */
#define LJPEG9_NEED_SIGNAL_CATCHER	/* needed if you use jmemname.c */
#undef DONT_USE_B_MODE
#undef LJPEG9_PROGRESS_REPORT		/* optional */

#endif /* JPEG_CJPEG_DJPEG */
