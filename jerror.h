/*
 * jerror.h
 *
 * Copyright (C) 1994-1997, Thomas G. Lane.
 * Modified 1997-2012 by Guido Vollbeding.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file defines the error and message codes for the JPEG library.
 * Edit this file to add new codes, or to translate the message strings to
 * some other language.
 * A set of error-reporting macros are defined too.  Some applications using
 * the JPEG library may wish to include this file to get the error codes
 * and/or the macros.
 */

/*
 * To define the enum list of message codes, include this file without
 * defining macro LJPEG9_JMESSAGE.  To create a message string table, include it
 * again with a suitable LJPEG9_JMESSAGE definition (see jerror.c for an example).
 */
#ifndef LJPEG9_JMESSAGE
#ifndef JERROR_H
/* First time through, define the enum list */
#define LJPEG9_JMAKE_ENUM_LIST
#else
/* Repeated inclusions of this file are no-ops unless LJPEG9_JMESSAGE is defined */
#define LJPEG9_JMESSAGE(code,string)
#endif /* JERROR_H */
#endif /* LJPEG9_JMESSAGE */

#ifdef LJPEG9_JMAKE_ENUM_LIST

typedef enum {

#define LJPEG9_JMESSAGE(code,string)	code ,

#endif /* LJPEG9_JMAKE_ENUM_LIST */

LJPEG9_JMESSAGE(JMSG_NOMESSAGE, "Bogus message code %d") /* Must be first entry! */

/* For maintenance convenience, list is alphabetical by message code name */
LJPEG9_JMESSAGE(JERR_BAD_ALIGN_TYPE, "ALIGN_TYPE is wrong, please fix")
LJPEG9_JMESSAGE(JERR_BAD_ALLOC_CHUNK, "MAX_ALLOC_CHUNK is wrong, please fix")
LJPEG9_JMESSAGE(JERR_BAD_BUFFER_MODE, "Bogus buffer control mode")
LJPEG9_JMESSAGE(JERR_BAD_COMPONENT_ID, "Invalid component ID %d in SOS")
LJPEG9_JMESSAGE(JERR_BAD_CROP_SPEC, "Invalid crop request")
LJPEG9_JMESSAGE(JERR_BAD_DCT_COEF, "DCT coefficient out of range")
LJPEG9_JMESSAGE(JERR_BAD_DCTSIZE, "DCT scaled block size %dx%d not supported")
LJPEG9_JMESSAGE(JERR_BAD_DROP_SAMPLING,
	 "Component index %d: mismatching sampling ratio %d:%d, %d:%d, %c")
LJPEG9_JMESSAGE(JERR_BAD_HUFF_TABLE, "Bogus Huffman table definition")
LJPEG9_JMESSAGE(JERR_BAD_IN_COLORSPACE, "Bogus input colorspace")
LJPEG9_JMESSAGE(JERR_BAD_J_COLORSPACE, "Bogus JPEG colorspace")
LJPEG9_JMESSAGE(JERR_BAD_LENGTH, "Bogus marker length")
LJPEG9_JMESSAGE(JERR_BAD_LIB_VERSION,
	 "Wrong JPEG library version: library is %d, caller expects %d")
LJPEG9_JMESSAGE(JERR_BAD_MCU_SIZE, "Sampling factors too large for interleaved scan")
LJPEG9_JMESSAGE(JERR_BAD_POOL_ID, "Invalid memory pool code %d")
LJPEG9_JMESSAGE(JERR_BAD_PRECISION, "Unsupported JPEG data precision %d")
LJPEG9_JMESSAGE(JERR_BAD_PROGRESSION,
	 "Invalid progressive parameters Ss=%d Se=%d Ah=%d Al=%d")
LJPEG9_JMESSAGE(JERR_BAD_PROG_SCRIPT,
	 "Invalid progressive parameters at scan script entry %d")
LJPEG9_JMESSAGE(JERR_BAD_SAMPLING, "Bogus sampling factors")
LJPEG9_JMESSAGE(JERR_BAD_SCAN_SCRIPT, "Invalid scan script at entry %d")
LJPEG9_JMESSAGE(JERR_BAD_STATE, "Improper call to JPEG library in state %d")
LJPEG9_JMESSAGE(JERR_BAD_STRUCT_SIZE,
	 "JPEG parameter struct mismatch: library thinks size is %u, caller expects %u")
LJPEG9_JMESSAGE(JERR_BAD_VIRTUAL_ACCESS, "Bogus virtual array access")
LJPEG9_JMESSAGE(JERR_BUFFER_SIZE, "Buffer passed to JPEG library is too small")
LJPEG9_JMESSAGE(JERR_CANT_SUSPEND, "Suspension not allowed here")
LJPEG9_JMESSAGE(JERR_CCIR601_NOTIMPL, "CCIR601 sampling not implemented yet")
LJPEG9_JMESSAGE(JERR_COMPONENT_COUNT, "Too many color components: %d, max %d")
LJPEG9_JMESSAGE(JERR_CONVERSION_NOTIMPL, "Unsupported color conversion request")
LJPEG9_JMESSAGE(JERR_DAC_INDEX, "Bogus DAC index %d")
LJPEG9_JMESSAGE(JERR_DAC_VALUE, "Bogus DAC value 0x%x")
LJPEG9_JMESSAGE(JERR_DHT_INDEX, "Bogus DHT index %d")
LJPEG9_JMESSAGE(JERR_DQT_INDEX, "Bogus DQT index %d")
LJPEG9_JMESSAGE(JERR_EMPTY_IMAGE, "Empty JPEG image (DNL not supported)")
LJPEG9_JMESSAGE(JERR_EMS_READ, "Read from EMS failed")
LJPEG9_JMESSAGE(JERR_EMS_WRITE, "Write to EMS failed")
LJPEG9_JMESSAGE(JERR_EOI_EXPECTED, "Didn't expect more than one scan")
LJPEG9_JMESSAGE(JERR_FILE_READ, "Input file read error")
LJPEG9_JMESSAGE(JERR_FILE_WRITE, "Output file write error --- out of disk space?")
LJPEG9_JMESSAGE(JERR_FRACT_SAMPLE_NOTIMPL, "Fractional sampling not implemented yet")
LJPEG9_JMESSAGE(JERR_HUFF_CLEN_OVERFLOW, "Huffman code size table overflow")
LJPEG9_JMESSAGE(JERR_HUFF_MISSING_CODE, "Missing Huffman code table entry")
LJPEG9_JMESSAGE(JERR_IMAGE_TOO_BIG, "Maximum supported image dimension is %u pixels")
LJPEG9_JMESSAGE(JERR_INPUT_EMPTY, "Empty input file")
LJPEG9_JMESSAGE(JERR_INPUT_EOF, "Premature end of input file")
LJPEG9_JMESSAGE(JERR_MISMATCHED_QUANT_TABLE,
	 "Cannot transcode due to multiple use of quantization table %d")
LJPEG9_JMESSAGE(JERR_MISSING_DATA, "Scan script does not transmit all data")
LJPEG9_JMESSAGE(JERR_MODE_CHANGE, "Invalid color quantization mode change")
LJPEG9_JMESSAGE(JERR_NOTIMPL, "Not implemented yet")
LJPEG9_JMESSAGE(JERR_NOT_COMPILED, "Requested feature was omitted at compile time")
LJPEG9_JMESSAGE(JERR_NO_ARITH_TABLE, "Arithmetic table 0x%02x was not defined")
LJPEG9_JMESSAGE(JERR_NO_BACKING_STORE, "Backing store not supported")
LJPEG9_JMESSAGE(JERR_NO_HUFF_TABLE, "Huffman table 0x%02x was not defined")
LJPEG9_JMESSAGE(JERR_NO_IMAGE, "JPEG datastream contains no image")
LJPEG9_JMESSAGE(JERR_NO_QUANT_TABLE, "Quantization table 0x%02x was not defined")
LJPEG9_JMESSAGE(JERR_NO_SOI, "Not a JPEG file: starts with 0x%02x 0x%02x")
LJPEG9_JMESSAGE(JERR_OUT_OF_MEMORY, "Insufficient memory (case %d)")
LJPEG9_JMESSAGE(JERR_QUANT_COMPONENTS,
	 "Cannot quantize more than %d color components")
LJPEG9_JMESSAGE(JERR_QUANT_FEW_COLORS, "Cannot quantize to fewer than %d colors")
LJPEG9_JMESSAGE(JERR_QUANT_MANY_COLORS, "Cannot quantize to more than %d colors")
LJPEG9_JMESSAGE(JERR_SOF_BEFORE, "Invalid JPEG file structure: %s before SOF")
LJPEG9_JMESSAGE(JERR_SOF_DUPLICATE, "Invalid JPEG file structure: two SOF markers")
LJPEG9_JMESSAGE(JERR_SOF_NO_SOS, "Invalid JPEG file structure: missing SOS marker")
LJPEG9_JMESSAGE(JERR_SOF_UNSUPPORTED, "Unsupported JPEG process: SOF type 0x%02x")
LJPEG9_JMESSAGE(JERR_SOI_DUPLICATE, "Invalid JPEG file structure: two SOI markers")
LJPEG9_JMESSAGE(JERR_TFILE_CREATE, "Failed to create temporary file %s")
LJPEG9_JMESSAGE(JERR_TFILE_READ, "Read failed on temporary file")
LJPEG9_JMESSAGE(JERR_TFILE_SEEK, "Seek failed on temporary file")
LJPEG9_JMESSAGE(JERR_TFILE_WRITE,
	 "Write failed on temporary file --- out of disk space?")
LJPEG9_JMESSAGE(JERR_TOO_LITTLE_DATA, "Application transferred too few scanlines")
LJPEG9_JMESSAGE(JERR_UNKNOWN_MARKER, "Unsupported marker type 0x%02x")
LJPEG9_JMESSAGE(JERR_VIRTUAL_BUG, "Virtual array controller messed up")
LJPEG9_JMESSAGE(JERR_WIDTH_OVERFLOW, "Image too wide for this implementation")
LJPEG9_JMESSAGE(JERR_XMS_READ, "Read from XMS failed")
LJPEG9_JMESSAGE(JERR_XMS_WRITE, "Write to XMS failed")
LJPEG9_JMESSAGE(JMSG_COPYRIGHT, JCOPYRIGHT)
LJPEG9_JMESSAGE(JMSG_VERSION, JVERSION)
LJPEG9_JMESSAGE(JTRC_16BIT_TABLES,
	 "Caution: quantization tables are too coarse for baseline JPEG")
LJPEG9_JMESSAGE(JTRC_ADOBE,
	 "Adobe APP14 marker: version %d, flags 0x%04x 0x%04x, transform %d")
LJPEG9_JMESSAGE(JTRC_APP0, "Unknown APP0 marker (not JFIF), length %u")
LJPEG9_JMESSAGE(JTRC_APP14, "Unknown APP14 marker (not Adobe), length %u")
LJPEG9_JMESSAGE(JTRC_DAC, "Define Arithmetic Table 0x%02x: 0x%02x")
LJPEG9_JMESSAGE(JTRC_DHT, "Define Huffman Table 0x%02x")
LJPEG9_JMESSAGE(JTRC_DQT, "Define Quantization Table %d  precision %d")
LJPEG9_JMESSAGE(JTRC_DRI, "Define Restart Interval %u")
LJPEG9_JMESSAGE(JTRC_EMS_CLOSE, "Freed EMS handle %u")
LJPEG9_JMESSAGE(JTRC_EMS_OPEN, "Obtained EMS handle %u")
LJPEG9_JMESSAGE(JTRC_EOI, "End Of Image")
LJPEG9_JMESSAGE(JTRC_HUFFBITS, "        %3d %3d %3d %3d %3d %3d %3d %3d")
LJPEG9_JMESSAGE(JTRC_JFIF, "JFIF APP0 marker: version %d.%02d, density %dx%d  %d")
LJPEG9_JMESSAGE(JTRC_JFIF_BADTHUMBNAILSIZE,
	 "Warning: thumbnail image size does not match data length %u")
LJPEG9_JMESSAGE(JTRC_JFIF_EXTENSION,
	 "JFIF extension marker: type 0x%02x, length %u")
LJPEG9_JMESSAGE(JTRC_JFIF_THUMBNAIL, "    with %d x %d thumbnail image")
LJPEG9_JMESSAGE(JTRC_MISC_MARKER, "Miscellaneous marker 0x%02x, length %u")
LJPEG9_JMESSAGE(JTRC_PARMLESS_MARKER, "Unexpected marker 0x%02x")
LJPEG9_JMESSAGE(JTRC_QUANTVALS, "        %4u %4u %4u %4u %4u %4u %4u %4u")
LJPEG9_JMESSAGE(JTRC_QUANT_3_NCOLORS, "Quantizing to %d = %d*%d*%d colors")
LJPEG9_JMESSAGE(JTRC_QUANT_NCOLORS, "Quantizing to %d colors")
LJPEG9_JMESSAGE(JTRC_QUANT_SELECTED, "Selected %d colors for quantization")
LJPEG9_JMESSAGE(JTRC_RECOVERY_ACTION, "At marker 0x%02x, recovery action %d")
LJPEG9_JMESSAGE(JTRC_RST, "RST%d")
LJPEG9_JMESSAGE(JTRC_SMOOTH_NOTIMPL,
	 "Smoothing not supported with nonstandard sampling ratios")
LJPEG9_JMESSAGE(JTRC_SOF, "Start Of Frame 0x%02x: width=%u, height=%u, components=%d")
LJPEG9_JMESSAGE(JTRC_SOF_COMPONENT, "    Component %d: %dhx%dv q=%d")
LJPEG9_JMESSAGE(JTRC_SOI, "Start of Image")
LJPEG9_JMESSAGE(JTRC_SOS, "Start Of Scan: %d components")
LJPEG9_JMESSAGE(JTRC_SOS_COMPONENT, "    Component %d: dc=%d ac=%d")
LJPEG9_JMESSAGE(JTRC_SOS_PARAMS, "  Ss=%d, Se=%d, Ah=%d, Al=%d")
LJPEG9_JMESSAGE(JTRC_TFILE_CLOSE, "Closed temporary file %s")
LJPEG9_JMESSAGE(JTRC_TFILE_OPEN, "Opened temporary file %s")
LJPEG9_JMESSAGE(JTRC_THUMB_JPEG,
	 "JFIF extension marker: JPEG-compressed thumbnail image, length %u")
LJPEG9_JMESSAGE(JTRC_THUMB_PALETTE,
	 "JFIF extension marker: palette thumbnail image, length %u")
LJPEG9_JMESSAGE(JTRC_THUMB_RGB,
	 "JFIF extension marker: RGB thumbnail image, length %u")
LJPEG9_JMESSAGE(JTRC_UNKNOWN_IDS,
	 "Unrecognized component IDs %d %d %d, assuming YCbCr")
LJPEG9_JMESSAGE(JTRC_XMS_CLOSE, "Freed XMS handle %u")
LJPEG9_JMESSAGE(JTRC_XMS_OPEN, "Obtained XMS handle %u")
LJPEG9_JMESSAGE(JWRN_ADOBE_XFORM, "Unknown Adobe color transform code %d")
LJPEG9_JMESSAGE(JWRN_ARITH_BAD_CODE, "Corrupt JPEG data: bad arithmetic code")
LJPEG9_JMESSAGE(JWRN_BOGUS_PROGRESSION,
	 "Inconsistent progression sequence for component %d coefficient %d")
LJPEG9_JMESSAGE(JWRN_EXTRANEOUS_DATA,
	 "Corrupt JPEG data: %u extraneous bytes before marker 0x%02x")
LJPEG9_JMESSAGE(JWRN_HIT_MARKER, "Corrupt JPEG data: premature end of data segment")
LJPEG9_JMESSAGE(JWRN_HUFF_BAD_CODE, "Corrupt JPEG data: bad Huffman code")
LJPEG9_JMESSAGE(JWRN_JFIF_MAJOR, "Warning: unknown JFIF revision number %d.%02d")
LJPEG9_JMESSAGE(JWRN_JPEG_EOF, "Premature end of JPEG file")
LJPEG9_JMESSAGE(JWRN_MUST_RESYNC,
	 "Corrupt JPEG data: found marker 0x%02x instead of RST%d")
LJPEG9_JMESSAGE(JWRN_NOT_SEQUENTIAL, "Invalid SOS parameters for sequential JPEG")
LJPEG9_JMESSAGE(JWRN_TOO_MUCH_DATA, "Application transferred too many scanlines")

#ifdef LJPEG9_JMAKE_ENUM_LIST

  JMSG_LASTMSGCODE
} J_MESSAGE_CODE;

#undef LJPEG9_JMAKE_ENUM_LIST
#endif /* LJPEG9_JMAKE_ENUM_LIST */

/* Zap LJPEG9_JMESSAGE macro so that future re-inclusions do nothing by default */
#undef LJPEG9_JMESSAGE


#ifndef JERROR_H
#define JERROR_H

/* Macros to simplify using the error and trace message stuff */
/* The first parameter is either type of cinfo pointer */

/* Fatal errors (print message and exit) */
#define ERREXIT(cinfo,code)  \
  ((cinfo)->err->msg_code = (code), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXIT1(cinfo,code,p1)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXIT2(cinfo,code,p1,p2)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXIT3(cinfo,code,p1,p2,p3)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (cinfo)->err->msg_parm.i[2] = (p3), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXIT4(cinfo,code,p1,p2,p3,p4)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (cinfo)->err->msg_parm.i[2] = (p3), \
   (cinfo)->err->msg_parm.i[3] = (p4), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXIT6(cinfo,code,p1,p2,p3,p4,p5,p6)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (cinfo)->err->msg_parm.i[2] = (p3), \
   (cinfo)->err->msg_parm.i[3] = (p4), \
   (cinfo)->err->msg_parm.i[4] = (p5), \
   (cinfo)->err->msg_parm.i[5] = (p6), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))
#define ERREXITS(cinfo,code,str)  \
  ((cinfo)->err->msg_code = (code), \
   strncpy((cinfo)->err->msg_parm.s, (str), JMSG_STR_PARM_MAX), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))

#define MAKESTMT(stuff)		do { stuff } while (0)

/* Nonfatal errors (we can keep going, but the data is probably corrupt) */
#define WARNMS(cinfo,code)  \
  ((cinfo)->err->msg_code = (code), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), -1))
#define WARNMS1(cinfo,code,p1)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), -1))
#define WARNMS2(cinfo,code,p1,p2)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), -1))

/* Informational/debugging messages */
#define TRACEMS(cinfo,lvl,code)  \
  ((cinfo)->err->msg_code = (code), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)))
#define TRACEMS1(cinfo,lvl,code,p1)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)))
#define TRACEMS2(cinfo,lvl,code,p1,p2)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (cinfo)->err->msg_parm.i[1] = (p2), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)))
#define TRACEMS3(cinfo,lvl,code,p1,p2,p3)  \
  MAKESTMT(int * _mp = (cinfo)->err->msg_parm.i; \
	   _mp[0] = (p1); _mp[1] = (p2); _mp[2] = (p3); \
	   (cinfo)->err->msg_code = (code); \
	   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)); )
#define TRACEMS4(cinfo,lvl,code,p1,p2,p3,p4)  \
  MAKESTMT(int * _mp = (cinfo)->err->msg_parm.i; \
	   _mp[0] = (p1); _mp[1] = (p2); _mp[2] = (p3); _mp[3] = (p4); \
	   (cinfo)->err->msg_code = (code); \
	   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)); )
#define TRACEMS5(cinfo,lvl,code,p1,p2,p3,p4,p5)  \
  MAKESTMT(int * _mp = (cinfo)->err->msg_parm.i; \
	   _mp[0] = (p1); _mp[1] = (p2); _mp[2] = (p3); _mp[3] = (p4); \
	   _mp[4] = (p5); \
	   (cinfo)->err->msg_code = (code); \
	   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)); )
#define TRACEMS8(cinfo,lvl,code,p1,p2,p3,p4,p5,p6,p7,p8)  \
  MAKESTMT(int * _mp = (cinfo)->err->msg_parm.i; \
	   _mp[0] = (p1); _mp[1] = (p2); _mp[2] = (p3); _mp[3] = (p4); \
	   _mp[4] = (p5); _mp[5] = (p6); _mp[6] = (p7); _mp[7] = (p8); \
	   (cinfo)->err->msg_code = (code); \
	   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)); )
#define TRACEMSS(cinfo,lvl,code,str)  \
  ((cinfo)->err->msg_code = (code), \
   strncpy((cinfo)->err->msg_parm.s, (str), JMSG_STR_PARM_MAX), \
   (*(cinfo)->err->emit_message) ((j_common_ptr) (cinfo), (lvl)))

#endif /* JERROR_H */
