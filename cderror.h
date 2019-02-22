/*
 * cderror.h
 *
 * Copyright (C) 1994-1997, Thomas G. Lane.
 * Modified 2009 by Guido Vollbeding.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file defines the error and message codes for the cjpeg/djpeg
 * applications.  These strings are not needed as part of the JPEG library
 * proper.
 * Edit this file to add new codes, or to translate the message strings to
 * some other language.
 */

/*
 * To define the enum list of message codes, include this file without
 * defining macro LJPEG9_JMESSAGE.  To create a message string table, include it
 * again with a suitable LJPEG9_JMESSAGE definition (see jerror.c for an example).
 */
#ifndef LJPEG9_JMESSAGE
#ifndef LJPEG9_CDERROR_H
#define LJPEG9_CDERROR_H
/* First time through, define the enum list */
#define LJPEG9_JMAKE_ENUM_LIST
#else
/* Repeated inclusions of this file are no-ops unless LJPEG9_JMESSAGE is defined */
#define LJPEG9_JMESSAGE(code,string)
#endif /* LJPEG9_CDERROR_H */
#endif /* LJPEG9_JMESSAGE */

#ifdef LJPEG9_JMAKE_ENUM_LIST

typedef enum {

#define LJPEG9_JMESSAGE(code,string)	code ,

#endif /* LJPEG9_JMAKE_ENUM_LIST */

LJPEG9_JMESSAGE(JMSG_FIRSTADDONCODE=1000, NULL) /* Must be first entry! */

#ifdef LJPEG9_BMP_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_BADCMAP, "Unsupported BMP colormap format")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_BADDEPTH, "Only 8- and 24-bit BMP files are supported")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_BADHEADER, "Invalid BMP file: bad header length")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_BADPLANES, "Invalid BMP file: biPlanes not equal to 1")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_COLORSPACE, "BMP output must be grayscale or RGB")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_COMPRESSED, "Sorry, compressed BMPs not yet supported")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_EMPTY, "Empty BMP image")
LJPEG9_JMESSAGE(LJPEG9_JERR_BMP_NOT, "Not a BMP file - does not start with BM")
LJPEG9_JMESSAGE(LJPEG9_JTRC_BMP, "%ux%u 24-bit BMP image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_BMP_MAPPED, "%ux%u 8-bit colormapped BMP image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_BMP_OS2, "%ux%u 24-bit OS2 BMP image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_BMP_OS2_MAPPED, "%ux%u 8-bit colormapped OS2 BMP image")
#endif /* LJPEG9_BMP_SUPPORTED */

#ifdef LJPEG9_GIF_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_GIF_BUG, "GIF output got confused")
LJPEG9_JMESSAGE(LJPEG9_JERR_GIF_CODESIZE, "Bogus GIF codesize %d")
LJPEG9_JMESSAGE(LJPEG9_JERR_GIF_COLORSPACE, "GIF output must be grayscale or RGB")
LJPEG9_JMESSAGE(LJPEG9_JERR_GIF_IMAGENOTFOUND, "Too few images in GIF file")
LJPEG9_JMESSAGE(LJPEG9_JERR_GIF_NOT, "Not a GIF file")
LJPEG9_JMESSAGE(LJPEG9_JTRC_GIF, "%ux%ux%d GIF image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_GIF_BADVERSION,
	 "Warning: unexpected GIF version number '%c%c%c'")
LJPEG9_JMESSAGE(LJPEG9_JTRC_GIF_EXTENSION, "Ignoring GIF extension block of type 0x%02x")
LJPEG9_JMESSAGE(LJPEG9_JTRC_GIF_NONSQUARE, "Caution: nonsquare pixels in input")
LJPEG9_JMESSAGE(LJPEG9_JWRN_GIF_BADDATA, "Corrupt data in GIF file")
LJPEG9_JMESSAGE(LJPEG9_JWRN_GIF_CHAR, "Bogus char 0x%02x in GIF file, ignoring")
LJPEG9_JMESSAGE(LJPEG9_JWRN_GIF_ENDCODE, "Premature end of GIF image")
LJPEG9_JMESSAGE(LJPEG9_JWRN_GIF_NOMOREDATA, "Ran out of GIF bits")
#endif /* LJPEG9_GIF_SUPPORTED */

#ifdef LJPEG9_PPM_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_PPM_COLORSPACE, "PPM output must be grayscale or RGB")
LJPEG9_JMESSAGE(LJPEG9_JERR_PPM_NONNUMERIC, "Nonnumeric data in PPM file")
LJPEG9_JMESSAGE(LJPEG9_JERR_PPM_NOT, "Not a PPM/PGM file")
LJPEG9_JMESSAGE(LJPEG9_JTRC_PGM, "%ux%u PGM image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_PGM_TEXT, "%ux%u text PGM image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_PPM, "%ux%u PPM image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_PPM_TEXT, "%ux%u text PPM image")
#endif /* LJPEG9_PPM_SUPPORTED */

#ifdef LJPEG9_RLE_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_BADERROR, "Bogus error code from RLE library")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_COLORSPACE, "RLE output must be grayscale or RGB")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_DIMENSIONS, "Image dimensions (%ux%u) too large for RLE")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_EMPTY, "Empty RLE file")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_EOF, "Premature EOF in RLE header")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_MEM, "Insufficient memory for RLE header")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_NOT, "Not an RLE file")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_TOOMANYCHANNELS, "Cannot handle %d output channels for RLE")
LJPEG9_JMESSAGE(LJPEG9_JERR_RLE_UNSUPPORTED, "Cannot handle this RLE setup")
LJPEG9_JMESSAGE(LJPEG9_JTRC_RLE, "%ux%u full-color RLE file")
LJPEG9_JMESSAGE(LJPEG9_JTRC_RLE_FULLMAP, "%ux%u full-color RLE file with map of length %d")
LJPEG9_JMESSAGE(LJPEG9_JTRC_RLE_GRAY, "%ux%u grayscale RLE file")
LJPEG9_JMESSAGE(LJPEG9_JTRC_RLE_MAPGRAY, "%ux%u grayscale RLE file with map of length %d")
LJPEG9_JMESSAGE(LJPEG9_JTRC_RLE_MAPPED, "%ux%u colormapped RLE file with map of length %d")
#endif /* LJPEG9_RLE_SUPPORTED */

#ifdef LJPEG9_TARGA_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_TGA_BADCMAP, "Unsupported Targa colormap format")
LJPEG9_JMESSAGE(LJPEG9_JERR_TGA_BADPARMS, "Invalid or unsupported Targa file")
LJPEG9_JMESSAGE(LJPEG9_JERR_TGA_COLORSPACE, "Targa output must be grayscale or RGB")
LJPEG9_JMESSAGE(LJPEG9_JTRC_TGA, "%ux%u RGB Targa image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_TGA_GRAY, "%ux%u grayscale Targa image")
LJPEG9_JMESSAGE(LJPEG9_JTRC_TGA_MAPPED, "%ux%u colormapped Targa image")
#else
LJPEG9_JMESSAGE(LJPEG9_JERR_TGA_NOTCOMP, "Targa support was not compiled")
#endif /* LJPEG9_TARGA_SUPPORTED */

LJPEG9_JMESSAGE(LJPEG9_JERR_BAD_CMAP_FILE,
	 "Color map file is invalid or of unsupported format")
LJPEG9_JMESSAGE(LJPEG9_JERR_TOO_MANY_COLORS,
	 "Output file format cannot handle %d colormap entries")
LJPEG9_JMESSAGE(LJPEG9_JERR_UNGETC_FAILED, "ungetc failed")
#ifdef LJPEG9_TARGA_SUPPORTED
LJPEG9_JMESSAGE(LJPEG9_JERR_UNKNOWN_FORMAT,
	 "Unrecognized input file format --- perhaps you need -targa")
#else
LJPEG9_JMESSAGE(LJPEG9_JERR_UNKNOWN_FORMAT, "Unrecognized input file format")
#endif
LJPEG9_JMESSAGE(JERR_UNSUPPORTED_FORMAT, "Unsupported output file format")

#ifdef LJPEG9_JMAKE_ENUM_LIST

  LJPEG9_JMSG_LASTADDONCODE
} LJPEG9_ADDON_MESSAGE_CODE;

#undef LJPEG9_JMAKE_ENUM_LIST
#endif /* LJPEG9_JMAKE_ENUM_LIST */

/* Zap LJPEG9_JMESSAGE macro so that future re-inclusions do nothing by default */
#undef LJPEG9_JMESSAGE
