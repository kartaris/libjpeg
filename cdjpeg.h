/*
 * cdjpeg.h
 *
 * Copyright (C) 1994-1997, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains common declarations for the sample applications
 * cjpeg and djpeg.  It is NOT used by the core JPEG library.
 */

#define JPEG_CJPEG_DJPEG	/* define proper options in jconfig.h */
#define JPEG_INTERNAL_OPTIONS	/* cjpeg.c,djpeg.c need to see xxx_SUPPORTED */
#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"		/* get library error codes too */
#include "cderror.h"		/* get application-specific error codes */


/*
 * Object interface for cjpeg's source file decoding modules
 */

typedef struct LJPEG9_cjpeg_source_struct * LJPEG9_cjpeg_source_ptr;

struct LJPEG9_cjpeg_source_struct {
  LJPEG9_JMETHOD(void, start_input, (j_compress_ptr cinfo,
			      LJPEG9_cjpeg_source_ptr sinfo));
  LJPEG9_JMETHOD(LJPEG9_JDIMENSION, get_pixel_rows, (j_compress_ptr cinfo,
				       LJPEG9_cjpeg_source_ptr sinfo));
  LJPEG9_JMETHOD(void, finish_input, (j_compress_ptr cinfo,
			       LJPEG9_cjpeg_source_ptr sinfo));

  FILE *input_file;

  LJPEG9_JSAMPARRAY buffer;
  LJPEG9_JDIMENSION buffer_height;
};


/*
 * Object interface for djpeg's output file encoding modules
 */

typedef struct LJPEG9_djpeg_dest_struct * LJPEG9_djpeg_dest_ptr;

struct LJPEG9_djpeg_dest_struct {
  /* start_output is called after jpeg_start_decompress finishes.
   * The color map will be ready at this time, if one is needed.
   */
  LJPEG9_JMETHOD(void, start_output, (LJPEG9_j_decompress_ptr cinfo,
			       LJPEG9_djpeg_dest_ptr dinfo));
  /* Emit the specified number of pixel rows from the buffer. */
  LJPEG9_JMETHOD(void, put_pixel_rows, (LJPEG9_j_decompress_ptr cinfo,
				 LJPEG9_djpeg_dest_ptr dinfo,
				 LJPEG9_JDIMENSION rows_supplied));
  /* Finish up at the end of the image. */
  LJPEG9_JMETHOD(void, finish_output, (LJPEG9_j_decompress_ptr cinfo,
				LJPEG9_djpeg_dest_ptr dinfo));

  /* Target file spec; filled in by djpeg.c after object is created. */
  FILE * output_file;

  /* Output pixel-row buffer.  Created by module init or start_output.
   * Width is cinfo->output_width * cinfo->output_components;
   * height is buffer_height.
   */
  LJPEG9_JSAMPARRAY buffer;
  LJPEG9_JDIMENSION buffer_height;
};


/*
 * cjpeg/djpeg may need to perform extra passes to convert to or from
 * the source/destination file format.  The JPEG library does not know
 * about these passes, but we'd like them to be counted by the progress
 * monitor.  We use an expanded progress monitor object to hold the
 * additional pass count.
 */

struct LJPEG9_cdjpeg_progress_mgr {
  struct jpeg_progress_mgr pub;	/* fields known to JPEG library */
  int completed_extra_passes;	/* extra passes completed */
  int total_extra_passes;	/* total extra */
  /* last printed percentage stored here to avoid multiple printouts */
  int percent_done;
};

typedef struct LJPEG9_cdjpeg_progress_mgr * LJPEG9_cd_progress_ptr;


/* Short forms of external names for systems with brain-damaged linkers. */

#ifdef LJPEG9_NEED_SHORT_EXTERNAL_NAMES
#define LJPEG9_jinit_read_bmp			LJPEG9_jIRdBMP
#define LJPEG9_jinit_write_bmp			LJPEG9_jIWrBMP
#define LJPEG9_jinit_read_gif			LJPEG9_jIRdGIF
#define LJPEG9_jinit_write_gif			LJPEG9_jIWrGIF
#define LJPEG9_jinit_read_ppm			LJPEG9_jIRdPPM
#define LJPEG9_jinit_write_ppm			LJPEG9_jIWrPPM
#define LJPEG9_jinit_read_rle			LJPEG9_jIRdRLE
#define LJPEG9_jinit_write_rle			LJPEG9_jIWrRLE
#define LJPEG9_jinit_read_targa			LJPEG9_jIRdTarga
#define LJPEG9_jinit_write_targa		LJPEG9_jIWrTarga
#define LJPEG9_read_quant_tables		LJPEG9_RdQTables
#define LJPEG9_read_scan_script			LJPEG9_RdScnScript
#define LJPEG9_set_quality_ratings     	LJPEG9_SetQRates
#define LJPEG9_set_quant_slots			LJPEG9_SetQSlots
#define LJPEG9_set_sample_factors		LJPEG9_SetSFacts
#define LJPEG9_read_color_map			LJPEG9_RdCMap
#define LJPEG9_enable_signal_catcher	LJPEG9_EnSigCatcher
#define LJPEG9_start_progress_monitor	LJPEG9_StProgMon
#define LJPEG9_end_progress_monitor		LJPEG9_EnProgMon
#define LJPEG9_read_stdin				LJPEG9_RdStdin
#define LJPEG9_write_stdout				LJPEG9_WrStdout
#endif /* LJPEG9_NEED_SHORT_EXTERNAL_NAMES */

/* Module selection routines for I/O modules. */

LJPEG9_EXTERN(LJPEG9_cjpeg_source_ptr) LJPEG9_jinit_read_bmp JPP((j_compress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_djpeg_dest_ptr) LJPEG9_jinit_write_bmp JPP((LJPEG9_j_decompress_ptr cinfo,
					    boolean is_os2));
LJPEG9_EXTERN(LJPEG9_cjpeg_source_ptr) LJPEG9_jinit_read_gif JPP((j_compress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_djpeg_dest_ptr) LJPEG9_jinit_write_gif JPP((LJPEG9_j_decompress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_cjpeg_source_ptr) LJPEG9_jinit_read_ppm JPP((j_compress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_djpeg_dest_ptr) LJPEG9_jinit_write_ppm JPP((LJPEG9_j_decompress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_cjpeg_source_ptr) LJPEG9_jinit_read_rle JPP((j_compress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_djpeg_dest_ptr) LJPEG9_jinit_write_rle JPP((LJPEG9_j_decompress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_cjpeg_source_ptr) LJPEG9_jinit_read_targa JPP((j_compress_ptr cinfo));
LJPEG9_EXTERN(LJPEG9_djpeg_dest_ptr) LJPEG9_jinit_write_targa JPP((LJPEG9_j_decompress_ptr cinfo));

/* cjpeg support routines (in rdswitch.c) */

LJPEG9_EXTERN(boolean) LJPEG9_read_quant_tables JPP((j_compress_ptr cinfo, char * filename,
				       boolean force_baseline));
LJPEG9_EXTERN(boolean) LJPEG9_read_scan_script JPP((j_compress_ptr cinfo, char * filename));
LJPEG9_EXTERN(boolean) LJPEG9_set_quality_ratings JPP((j_compress_ptr cinfo, char *arg,
					 boolean force_baseline));
LJPEG9_EXTERN(boolean) LJPEG9_set_quant_slots JPP((j_compress_ptr cinfo, char *arg));
LJPEG9_EXTERN(boolean) LJPEG9_set_sample_factors JPP((j_compress_ptr cinfo, char *arg));

/* djpeg support routines (in rdcolmap.c) */

LJPEG9_EXTERN(void) LJPEG9_read_color_map JPP((LJPEG9_j_decompress_ptr cinfo, FILE * infile));

/* common support routines (in cdjpeg.c) */

LJPEG9_EXTERN(void) LJPEG9_enable_signal_catcher JPP((LJPEG9_j_common_ptr cinfo));
LJPEG9_EXTERN(void) LJPEG9_start_progress_monitor JPP((LJPEG9_j_common_ptr cinfo,
					 LJPEG9_cd_progress_ptr progress));
LJPEG9_EXTERN(void) LJPEG9_end_progress_monitor JPP((LJPEG9_j_common_ptr cinfo));
LJPEG9_EXTERN(boolean) LJPEG9_keymatch JPP((char * arg, const char * keyword, int minchars));
LJPEG9_EXTERN(FILE *) LJPEG9_read_stdin JPP((void));
LJPEG9_EXTERN(FILE *) LJPEG9_write_stdout JPP((void));

/* miscellaneous useful macros */

#ifdef DONT_USE_B_MODE		/* define mode parameters for fopen() */
#define READ_BINARY	"r"
#define WRITE_BINARY	"w"
#else
#ifdef VMS			/* VMS is very nonstandard */
#define READ_BINARY	"rb", "ctx=stm"
#define WRITE_BINARY	"wb", "ctx=stm"
#else				/* standard ANSI-compliant case */
#define READ_BINARY	"rb"
#define WRITE_BINARY	"wb"
#endif
#endif

#ifndef LJPEG9_EXIT_FAILURE		/* define exit() codes if not provided */
#define LJPEG9_EXIT_FAILURE  1
#endif
#ifndef EXIT_SUCCESS
#ifdef VMS
#define EXIT_SUCCESS  1		/* VMS is very nonstandard */
#else
#define EXIT_SUCCESS  0
#endif
#endif
#ifndef EXIT_WARNING
#ifdef VMS
#define EXIT_WARNING  1		/* VMS is very nonstandard */
#else
#define EXIT_WARNING  2
#endif
#endif
