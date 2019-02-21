/*
 * jpegint.h
 *
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * Modified 1997-2013 by Guido Vollbeding.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file provides common declarations for the various JPEG modules.
 * These declarations are considered internal to the JPEG library; most
 * applications using the library shouldn't need to include this file.
 */


/* Declarations for both compression & decompression */

typedef enum {			/* Operating modes for buffer controllers */
	JBUF_PASS_THRU,		/* Plain stripwise operation */
	/* Remaining modes require a full-image buffer to have been created */
	JBUF_SAVE_SOURCE,	/* Run source subobject only, save output */
	JBUF_CRANK_DEST,	/* Run dest subobject only, using saved data */
	JBUF_SAVE_AND_PASS	/* Run both subobjects, save output */
} J_BUF_MODE;

/* Values of global_state field (jdapi.c has some dependencies on ordering!) */
#define CSTATE_START	100	/* after create_compress */
#define CSTATE_SCANNING	101	/* start_compress done, write_scanlines OK */
#define CSTATE_RAW_OK	102	/* start_compress done, write_raw_data OK */
#define CSTATE_WRCOEFS	103	/* jpeg_write_coefficients done */
#define DSTATE_START	200	/* after create_decompress */
#define DSTATE_INHEADER	201	/* reading header markers, no SOS yet */
#define DSTATE_READY	202	/* found SOS, ready for start_decompress */
#define DSTATE_PRELOAD	203	/* reading multiscan file in start_decompress*/
#define DSTATE_PRESCAN	204	/* performing dummy pass for 2-pass quant */
#define DSTATE_SCANNING	205	/* start_decompress done, read_scanlines OK */
#define DSTATE_RAW_OK	206	/* start_decompress done, read_raw_data OK */
#define DSTATE_BUFIMAGE	207	/* expecting jpeg_start_output */
#define DSTATE_BUFPOST	208	/* looking for SOS/EOI in jpeg_finish_output */
#define DSTATE_RDCOEFS	209	/* reading file in jpeg_read_coefficients */
#define DSTATE_STOPPING	210	/* looking for EOI in jpeg_finish_decompress */


/* Declarations for compression modules */

/* Master control module */
struct jpeg_comp_master {
  LJPEG9_JMETHOD(void, prepare_for_pass, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, pass_startup, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, finish_pass, (j_compress_ptr cinfo));

  /* State variables made visible to other modules */
  boolean call_pass_startup;	/* True if pass_startup must be called */
  boolean is_last_pass;		/* True during last pass */
};

/* Main buffer control (downsampled-data buffer) */
struct jpeg_c_main_controller {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo, J_BUF_MODE pass_mode));
  LJPEG9_JMETHOD(void, process_data, (j_compress_ptr cinfo,
			       LJPEG9_JSAMPARRAY input_buf, LJPEG9_JDIMENSION *in_row_ctr,
			       LJPEG9_JDIMENSION in_rows_avail));
};

/* Compression preprocessing (downsampling input buffer control) */
struct jpeg_c_prep_controller {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo, J_BUF_MODE pass_mode));
  LJPEG9_JMETHOD(void, pre_process_data, (j_compress_ptr cinfo,
				   LJPEG9_JSAMPARRAY input_buf,
				   LJPEG9_JDIMENSION *in_row_ctr,
				   LJPEG9_JDIMENSION in_rows_avail,
				   JSAMPIMAGE output_buf,
				   LJPEG9_JDIMENSION *out_row_group_ctr,
				   LJPEG9_JDIMENSION out_row_groups_avail));
};

/* Coefficient buffer control */
struct jpeg_c_coef_controller {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo, J_BUF_MODE pass_mode));
  LJPEG9_JMETHOD(boolean, compress_data, (j_compress_ptr cinfo,
				   JSAMPIMAGE input_buf));
};

/* Colorspace conversion */
struct jpeg_color_converter {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, color_convert, (j_compress_ptr cinfo,
				LJPEG9_JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
				LJPEG9_JDIMENSION output_row, int num_rows));
};

/* Downsampling */
struct jpeg_downsampler {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, downsample, (j_compress_ptr cinfo,
			     JSAMPIMAGE input_buf, LJPEG9_JDIMENSION in_row_index,
			     JSAMPIMAGE output_buf,
			     LJPEG9_JDIMENSION out_row_group_index));

  boolean need_context_rows;	/* TRUE if need rows above & below */
};

/* Forward DCT (also controls coefficient quantization) */
typedef LJPEG9_JMETHOD(void, forward_DCT_ptr,
		(j_compress_ptr cinfo, jpeg_component_info * compptr,
		 LJPEG9_JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
		 LJPEG9_JDIMENSION start_row, LJPEG9_JDIMENSION start_col,
		 LJPEG9_JDIMENSION num_blocks));

struct jpeg_forward_dct {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo));
  /* It is useful to allow each component to have a separate FDCT method. */
  forward_DCT_ptr forward_DCT[MAX_COMPONENTS];
};

/* Entropy encoding */
struct jpeg_entropy_encoder {
  LJPEG9_JMETHOD(void, start_pass, (j_compress_ptr cinfo, boolean gather_statistics));
  LJPEG9_JMETHOD(boolean, encode_mcu, (j_compress_ptr cinfo, JBLOCKROW *MCU_data));
  LJPEG9_JMETHOD(void, finish_pass, (j_compress_ptr cinfo));
};

/* Marker writing */
struct jpeg_marker_writer {
  LJPEG9_JMETHOD(void, write_file_header, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, write_frame_header, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, write_scan_header, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, write_file_trailer, (j_compress_ptr cinfo));
  LJPEG9_JMETHOD(void, write_tables_only, (j_compress_ptr cinfo));
  /* These routines are exported to allow insertion of extra markers */
  /* Probably only COM and APPn markers should be written this way */
  LJPEG9_JMETHOD(void, write_marker_header, (j_compress_ptr cinfo, int marker,
				      unsigned int datalen));
  LJPEG9_JMETHOD(void, write_marker_byte, (j_compress_ptr cinfo, int val));
};


/* Declarations for decompression modules */

/* Master control module */
struct jpeg_decomp_master {
  LJPEG9_JMETHOD(void, prepare_for_output_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, finish_output_pass, (LJPEG9_j_decompress_ptr cinfo));

  /* State variables made visible to other modules */
  boolean is_dummy_pass;	/* True during 1st pass for 2-pass quant */
};

/* Input control module */
struct jpeg_input_controller {
  LJPEG9_JMETHOD(int, consume_input, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, reset_input_controller, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, start_input_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, finish_input_pass, (LJPEG9_j_decompress_ptr cinfo));

  /* State variables made visible to other modules */
  boolean has_multiple_scans;	/* True if file has multiple scans */
  boolean eoi_reached;		/* True when EOI has been consumed */
};

/* Main buffer control (downsampled-data buffer) */
struct jpeg_d_main_controller {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo, J_BUF_MODE pass_mode));
  LJPEG9_JMETHOD(void, process_data, (LJPEG9_j_decompress_ptr cinfo,
			       LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION *out_row_ctr,
			       LJPEG9_JDIMENSION out_rows_avail));
};

/* Coefficient buffer control */
struct jpeg_d_coef_controller {
  LJPEG9_JMETHOD(void, start_input_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(int, consume_data, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, start_output_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(int, decompress_data, (LJPEG9_j_decompress_ptr cinfo,
				 JSAMPIMAGE output_buf));
  /* Pointer to array of coefficient virtual arrays, or NULL if none */
  jvirt_barray_ptr *coef_arrays;
};

/* Decompression postprocessing (color quantization buffer control) */
struct jpeg_d_post_controller {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo, J_BUF_MODE pass_mode));
  LJPEG9_JMETHOD(void, post_process_data, (LJPEG9_j_decompress_ptr cinfo,
				    JSAMPIMAGE input_buf,
				    LJPEG9_JDIMENSION *in_row_group_ctr,
				    LJPEG9_JDIMENSION in_row_groups_avail,
				    LJPEG9_JSAMPARRAY output_buf,
				    LJPEG9_JDIMENSION *out_row_ctr,
				    LJPEG9_JDIMENSION out_rows_avail));
};

/* Marker reading & parsing */
struct jpeg_marker_reader {
  LJPEG9_JMETHOD(void, reset_marker_reader, (LJPEG9_j_decompress_ptr cinfo));
  /* Read markers until SOS or EOI.
   * Returns same codes as are defined for jpeg_consume_input:
   * JPEG_SUSPENDED, JPEG_REACHED_SOS, or JPEG_REACHED_EOI.
   */
  LJPEG9_JMETHOD(int, read_markers, (LJPEG9_j_decompress_ptr cinfo));
  /* Read a restart marker --- exported for use by entropy decoder only */
  jpeg_marker_parser_method read_restart_marker;

  /* State of marker reader --- nominally internal, but applications
   * supplying COM or APPn handlers might like to know the state.
   */
  boolean saw_SOI;		/* found SOI? */
  boolean saw_SOF;		/* found SOF? */
  int next_restart_num;		/* next restart number expected (0-7) */
  unsigned int discarded_bytes;	/* # of bytes skipped looking for a marker */
};

/* Entropy decoding */
struct jpeg_entropy_decoder {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(boolean, decode_mcu, (LJPEG9_j_decompress_ptr cinfo, JBLOCKROW *MCU_data));
  LJPEG9_JMETHOD(void, finish_pass, (LJPEG9_j_decompress_ptr cinfo));
};

/* Inverse DCT (also performs dequantization) */
typedef LJPEG9_JMETHOD(void, inverse_DCT_method_ptr,
		(LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
		 JCOEFPTR coef_block,
		 LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));

struct jpeg_inverse_dct {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo));
  /* It is useful to allow each component to have a separate IDCT method. */
  inverse_DCT_method_ptr inverse_DCT[MAX_COMPONENTS];
};

/* Upsampling (note that upsampler must also call color converter) */
struct jpeg_upsampler {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, upsample, (LJPEG9_j_decompress_ptr cinfo,
			   JSAMPIMAGE input_buf,
			   LJPEG9_JDIMENSION *in_row_group_ctr,
			   LJPEG9_JDIMENSION in_row_groups_avail,
			   LJPEG9_JSAMPARRAY output_buf,
			   LJPEG9_JDIMENSION *out_row_ctr,
			   LJPEG9_JDIMENSION out_rows_avail));

  boolean need_context_rows;	/* TRUE if need rows above & below */
};

/* Colorspace conversion */
struct jpeg_color_deconverter {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, color_convert, (LJPEG9_j_decompress_ptr cinfo,
				JSAMPIMAGE input_buf, LJPEG9_JDIMENSION input_row,
				LJPEG9_JSAMPARRAY output_buf, int num_rows));
};

/* Color quantization or color precision reduction */
struct jpeg_color_quantizer {
  LJPEG9_JMETHOD(void, start_pass, (LJPEG9_j_decompress_ptr cinfo, boolean is_pre_scan));
  LJPEG9_JMETHOD(void, color_quantize, (LJPEG9_j_decompress_ptr cinfo,
				 LJPEG9_JSAMPARRAY input_buf, LJPEG9_JSAMPARRAY output_buf,
				 int num_rows));
  LJPEG9_JMETHOD(void, finish_pass, (LJPEG9_j_decompress_ptr cinfo));
  LJPEG9_JMETHOD(void, new_color_map, (LJPEG9_j_decompress_ptr cinfo));
};


/* Miscellaneous useful macros */

#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))


/* We assume that right shift corresponds to signed division by 2 with
 * rounding towards minus infinity.  This is correct for typical "arithmetic
 * shift" instructions that shift in copies of the sign bit.  But some
 * C compilers implement >> with an unsigned shift.  For these machines you
 * must define RIGHT_SHIFT_IS_UNSIGNED.
 * RIGHT_SHIFT provides a proper signed right shift of an INT32 quantity.
 * It is only applied with constant shift counts.  SHIFT_TEMPS must be
 * included in the variables of any routine using RIGHT_SHIFT.
 */

#ifdef RIGHT_SHIFT_IS_UNSIGNED
#define SHIFT_TEMPS	INT32 shift_temp;
#define RIGHT_SHIFT(x,shft)  \
	((shift_temp = (x)) < 0 ? \
	 (shift_temp >> (shft)) | ((~((INT32) 0)) << (32-(shft))) : \
	 (shift_temp >> (shft)))
#else
#define SHIFT_TEMPS
#define RIGHT_SHIFT(x,shft)	((x) >> (shft))
#endif


/* Short forms of external names for systems with brain-damaged linkers. */

#ifdef LJPEG9_NEED_SHORT_EXTERNAL_NAMES
#define jinit_compress_master	jICompress
#define jinit_c_master_control	jICMaster
#define jinit_c_main_controller	jICMainC
#define jinit_c_prep_controller	jICPrepC
#define jinit_c_coef_controller	jICCoefC
#define jinit_color_converter	jICColor
#define jinit_downsampler	jIDownsampler
#define jinit_forward_dct	jIFDCT
#define jinit_huff_encoder	jIHEncoder
#define jinit_arith_encoder	jIAEncoder
#define jinit_marker_writer	jIMWriter
#define jinit_master_decompress	jIDMaster
#define jinit_d_main_controller	jIDMainC
#define jinit_d_coef_controller	jIDCoefC
#define jinit_d_post_controller	jIDPostC
#define jinit_input_controller	jIInCtlr
#define jinit_marker_reader	jIMReader
#define jinit_huff_decoder	jIHDecoder
#define jinit_arith_decoder	jIADecoder
#define jinit_inverse_dct	jIIDCT
#define jinit_upsampler		jIUpsampler
#define jinit_color_deconverter	jIDColor
#define jinit_1pass_quantizer	jI1Quant
#define jinit_2pass_quantizer	jI2Quant
#define jinit_merged_upsampler	jIMUpsampler
#define jinit_memory_mgr	jIMemMgr
#define jdiv_round_up		jDivRound
#define jround_up		jRound
#define jzero_far		jZeroFar
#define jcopy_sample_rows	jCopySamples
#define jcopy_block_row		jCopyBlocks
#define jpeg_zigzag_order	jZIGTable
#define jpeg_natural_order	jZAGTable
#define jpeg_natural_order7	jZAG7Table
#define jpeg_natural_order6	jZAG6Table
#define jpeg_natural_order5	jZAG5Table
#define jpeg_natural_order4	jZAG4Table
#define jpeg_natural_order3	jZAG3Table
#define jpeg_natural_order2	jZAG2Table
#define jpeg_aritab		jAriTab
#endif /* LJPEG9_NEED_SHORT_EXTERNAL_NAMES */


/* On normal machines we can apply MEMCOPY() and MEMZERO() to sample arrays
 * and coefficient-block arrays.  This won't work on 80x86 because the arrays
 * are FAR and we're assuming a small-pointer memory model.  However, some
 * DOS compilers provide far-pointer versions of memcpy() and memset() even
 * in the small-model libraries.  These will be used if USE_FMEM is defined.
 * Otherwise, the routines in jutils.c do it the hard way.
 */

#ifndef NEED_FAR_POINTERS	/* normal case, same as regular macro */
#define FMEMZERO(target,size)	MEMZERO(target,size)
#else				/* 80x86 case */
#ifdef USE_FMEM
#define FMEMZERO(target,size)	_fmemset((void FAR *)(target), 0, (size_t)(size))
#else
EXTERN(void) jzero_far JPP((void FAR * target, size_t bytestozero));
#define FMEMZERO(target,size)	jzero_far(target, size)
#endif
#endif


/* Compression module initialization routines */
EXTERN(void) jinit_compress_master JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_c_master_control JPP((j_compress_ptr cinfo,
					 boolean transcode_only));
EXTERN(void) jinit_c_main_controller JPP((j_compress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_c_prep_controller JPP((j_compress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_c_coef_controller JPP((j_compress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_color_converter JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_downsampler JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_forward_dct JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_huff_encoder JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_arith_encoder JPP((j_compress_ptr cinfo));
EXTERN(void) jinit_marker_writer JPP((j_compress_ptr cinfo));
/* Decompression module initialization routines */
EXTERN(void) jinit_master_decompress JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_d_main_controller JPP((LJPEG9_j_decompress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_d_coef_controller JPP((LJPEG9_j_decompress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_d_post_controller JPP((LJPEG9_j_decompress_ptr cinfo,
					  boolean need_full_buffer));
EXTERN(void) jinit_input_controller JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_marker_reader JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_huff_decoder JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_arith_decoder JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_inverse_dct JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_upsampler JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_color_deconverter JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_1pass_quantizer JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_2pass_quantizer JPP((LJPEG9_j_decompress_ptr cinfo));
EXTERN(void) jinit_merged_upsampler JPP((LJPEG9_j_decompress_ptr cinfo));
/* Memory manager initialization */
EXTERN(void) jinit_memory_mgr JPP((j_common_ptr cinfo));

/* Utility routines in jutils.c */
EXTERN(long) jdiv_round_up JPP((long a, long b));
EXTERN(long) jround_up JPP((long a, long b));
EXTERN(void) jcopy_sample_rows JPP((LJPEG9_JSAMPARRAY input_array, int source_row,
				    LJPEG9_JSAMPARRAY output_array, int dest_row,
				    int num_rows, LJPEG9_JDIMENSION num_cols));
EXTERN(void) jcopy_block_row JPP((JBLOCKROW input_row, JBLOCKROW output_row,
				  LJPEG9_JDIMENSION num_blocks));
/* Constant tables in jutils.c */
#if 0				/* This table is not actually needed in v6a */
extern const int jpeg_zigzag_order[]; /* natural coef order to zigzag order */
#endif
extern const int jpeg_natural_order[]; /* zigzag coef order to natural order */
extern const int jpeg_natural_order7[]; /* zz to natural order for 7x7 block */
extern const int jpeg_natural_order6[]; /* zz to natural order for 6x6 block */
extern const int jpeg_natural_order5[]; /* zz to natural order for 5x5 block */
extern const int jpeg_natural_order4[]; /* zz to natural order for 4x4 block */
extern const int jpeg_natural_order3[]; /* zz to natural order for 3x3 block */
extern const int jpeg_natural_order2[]; /* zz to natural order for 2x2 block */

/* Arithmetic coding probability estimation tables in jaricom.c */
extern const INT32 jpeg_aritab[];

/* Suppress undefined-structure complaints if necessary. */

#ifdef INCOMPLETE_TYPES_BROKEN
#ifndef AM_MEMORY_MANAGER	/* only jmemmgr.c defines these */
struct jvirt_sarray_control { long dummy; };
struct jvirt_barray_control { long dummy; };
#endif
#endif /* INCOMPLETE_TYPES_BROKEN */
