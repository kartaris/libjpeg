/*
 * jdct.h
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This include file contains common declarations for the forward and
 * inverse DCT modules.  These declarations are private to the DCT managers
 * (jcdctmgr.c, jddctmgr.c) and the individual DCT algorithms.
 * The individual DCT algorithms are kept in separate files to ease 
 * machine-dependent tuning (e.g., assembly coding).
 */


/*
 * A forward DCT routine is given a pointer to an input sample array and
 * a pointer to a work area of type DCTELEM[]; the DCT is to be performed
 * in-place in that buffer.  Type DCTELEM is int for 8-bit samples, INT32
 * for 12-bit samples.  (NOTE: Floating-point DCT implementations use an
 * array of type FAST_FLOAT, instead.)
 * The input data is to be fetched from the sample array starting at a
 * specified column.  (Any row offset needed will be applied to the array
 * pointer before it is passed to the FDCT code.)
 * Note that the number of samples fetched by the FDCT routine is
 * DCT_h_scaled_size * DCT_v_scaled_size.
 * The DCT outputs are returned scaled up by a factor of 8; they therefore
 * have a range of +-8K for 8-bit data, +-128K for 12-bit data.  This
 * convention improves accuracy in integer implementations and saves some
 * work in floating-point ones.
 * Quantization of the output coefficients is done by jcdctmgr.c.
 */

#if BITS_IN_JSAMPLE == 8
typedef int DCTELEM;		/* 16 or 32 bits is fine */
#else
typedef INT32 DCTELEM;		/* must have 32 bits */
#endif

typedef LJPEG9_JMETHOD(void, forward_DCT_method_ptr, (DCTELEM * data,
					       LJPEG9_JSAMPARRAY sample_data,
					       LJPEG9_JDIMENSION start_col));
typedef LJPEG9_JMETHOD(void, float_DCT_method_ptr, (FAST_FLOAT * data,
					     LJPEG9_JSAMPARRAY sample_data,
					     LJPEG9_JDIMENSION start_col));


/*
 * An inverse DCT routine is given a pointer to the input JBLOCK and a pointer
 * to an output sample array.  The routine must dequantize the input data as
 * well as perform the IDCT; for dequantization, it uses the multiplier table
 * pointed to by compptr->dct_table.  The output data is to be placed into the
 * sample array starting at a specified column.  (Any row offset needed will
 * be applied to the array pointer before it is passed to the IDCT code.)
 * Note that the number of samples emitted by the IDCT routine is
 * DCT_h_scaled_size * DCT_v_scaled_size.
 */

/* typedef inverse_DCT_method_ptr is declared in jpegint.h */

/*
 * Each IDCT routine has its own ideas about the best dct_table element type.
 */

typedef MULTIPLIER ISLOW_MULT_TYPE; /* short or int, whichever is faster */
#if BITS_IN_JSAMPLE == 8
typedef MULTIPLIER IFAST_MULT_TYPE; /* 16 bits is OK, use short if faster */
#define IFAST_SCALE_BITS  2	/* fractional bits in scale factors */
#else
typedef INT32 IFAST_MULT_TYPE;	/* need 32 bits for scaled quantizers */
#define IFAST_SCALE_BITS  13	/* fractional bits in scale factors */
#endif
typedef FAST_FLOAT FLOAT_MULT_TYPE; /* preferred floating type */


/*
 * Each IDCT routine is responsible for range-limiting its results and
 * converting them to unsigned form (0..MAXJSAMPLE).  The raw outputs could
 * be quite far out of range if the input data is corrupt, so a bulletproof
 * range-limiting step is required.  We use a mask-and-table-lookup method
 * to do the combined operations quickly.  See the comments with
 * prepare_range_limit_table (in jdmaster.c) for more info.
 */

#define IDCT_range_limit(cinfo)  ((cinfo)->sample_range_limit + CENTERJSAMPLE)

#define RANGE_MASK  (MAXJSAMPLE * 4 + 3) /* 2 bits wider than legal samples */


/* Short forms of external names for systems with brain-damaged linkers. */

#ifdef LJPEG9_NEED_SHORT_EXTERNAL_NAMES
#define LJPEG9_jpeg_fdct_islow		LJPEG9_jFDislow
#define LJPEG9_jpeg_fdct_ifast		LJPEG9_jFDifast
#define LJPEG9_jpeg_fdct_float		LJPEG9_jFDfloat
#define LJPEG9_jpeg_fdct_7x7		LJPEG9_jFD7x7
#define LJPEG9_jpeg_fdct_6x6		LJPEG9_jFD6x6
#define LJPEG9_jpeg_fdct_5x5		LJPEG9_jFD5x5
#define LJPEG9_jpeg_fdct_4x4		LJPEG9_jFD4x4
#define LJPEG9_jpeg_fdct_3x3		LJPEG9_jFD3x3
#define LJPEG9_jpeg_fdct_2x2		LJPEG9_jFD2x2
#define LJPEG9_jpeg_fdct_1x1		LJPEG9_jFD1x1
#define LJPEG9_jpeg_fdct_9x9		LJPEG9_jFD9x9
#define LJPEG9_jpeg_fdct_10x10		LJPEG9_jFD10x10
#define LJPEG9_jpeg_fdct_11x11		LJPEG9_jFD11x11
#define LJPEG9_jpeg_fdct_12x12		LJPEG9_jFD12x12
#define LJPEG9_jpeg_fdct_13x13		LJPEG9_jFD13x13
#define LJPEG9_jpeg_fdct_14x14		LJPEG9_jFD14x14
#define LJPEG9_jpeg_fdct_15x15		LJPEG9_jFD15x15
#define LJPEG9_jpeg_fdct_16x16		LJPEG9_jFD16x16
#define LJPEG9_jpeg_fdct_16x8		LJPEG9_jFD16x8
#define LJPEG9_jpeg_fdct_14x7		LJPEG9_jFD14x7
#define LJPEG9_jpeg_fdct_12x6		LJPEG9_jFD12x6
#define LJPEG9_jpeg_fdct_10x5		LJPEG9_jFD10x5
#define LJPEG9_jpeg_fdct_8x4		LJPEG9_jFD8x4
#define LJPEG9_jpeg_fdct_6x3		LJPEG9_jFD6x3
#define LJPEG9_jpeg_fdct_4x2		LJPEG9_jFD4x2
#define LJPEG9_jpeg_fdct_2x1		LJPEG9_jFD2x1
#define LJPEG9_jpeg_fdct_8x16		LJPEG9_jFD8x16
#define LJPEG9_jpeg_fdct_7x14		LJPEG9_jFD7x14
#define LJPEG9_jpeg_fdct_6x12		LJPEG9_jFD6x12
#define LJPEG9_jpeg_fdct_5x10		LJPEG9_jFD5x10
#define LJPEG9_jpeg_fdct_4x8		LJPEG9_jFD4x8
#define LJPEG9_jpeg_fdct_3x6		LJPEG9_jFD3x6
#define LJPEG9_jpeg_fdct_2x4		LJPEG9_jFD2x4
#define LJPEG9_jpeg_fdct_1x2		LJPEG9_jFD1x2
#define LJPEG9_jpeg_idct_islow		LJPEG9_jRDislow
#define LJPEG9_jpeg_idct_ifast		LJPEG9_jRDifast
#define LJPEG9_jpeg_idct_float		LJPEG9_jRDfloat
#define LJPEG9_jpeg_idct_7x7		LJPEG9_jRD7x7
#define LJPEG9_jpeg_idct_6x6		LJPEG9_jRD6x6
#define LJPEG9_jpeg_idct_5x5		LJPEG9_jRD5x5
#define LJPEG9_jpeg_idct_4x4		LJPEG9_jRD4x4
#define LJPEG9_jpeg_idct_3x3		LJPEG9_jRD3x3
#define LJPEG9_jpeg_idct_2x2		LJPEG9_jRD2x2
#define LJPEG9_jpeg_idct_1x1		LJPEG9_jRD1x1
#define LJPEG9_jpeg_idct_9x9		LJPEG9_jRD9x9
#define LJPEG9_jpeg_idct_10x10		LJPEG9_jRD10x10
#define LJPEG9_jpeg_idct_11x11		LJPEG9_jRD11x11
#define LJPEG9_jpeg_idct_12x12		LJPEG9_jRD12x12
#define LJPEG9_jpeg_idct_13x13		LJPEG9_jRD13x13
#define LJPEG9_jpeg_idct_14x14		LJPEG9_jRD14x14
#define LJPEG9_jpeg_idct_15x15		LJPEG9_jRD15x15
#define LJPEG9_jpeg_idct_16x16		LJPEG9_jRD16x16
#define LJPEG9_jpeg_idct_16x8		LJPEG9_jRD16x8
#define LJPEG9_jpeg_idct_14x7		LJPEG9_jRD14x7
#define LJPEG9_jpeg_idct_12x6		LJPEG9_jRD12x6
#define LJPEG9_jpeg_idct_10x5		LJPEG9_jRD10x5
#define LJPEG9_jpeg_idct_8x4		LJPEG9_jRD8x4
#define LJPEG9_jpeg_idct_6x3		LJPEG9_jRD6x3
#define LJPEG9_jpeg_idct_4x2		LJPEG9_jRD4x2
#define LJPEG9_jpeg_idct_2x1		LJPEG9_jRD2x1
#define LJPEG9_jpeg_idct_8x16		LJPEG9_jRD8x16
#define LJPEG9_jpeg_idct_7x14		LJPEG9_jRD7x14
#define LJPEG9_jpeg_idct_6x12		LJPEG9_jRD6x12
#define LJPEG9_jpeg_idct_5x10		LJPEG9_jRD5x10
#define LJPEG9_jpeg_idct_4x8		LJPEG9_jRD4x8
#define LJPEG9_jpeg_idct_3x6		LJPEG9_jRD3x8
#define LJPEG9_jpeg_idct_2x4		LJPEG9_jRD2x4
#define LJPEG9_jpeg_idct_1x2		LJPEG9_jRD1x2
#endif /* LJPEG9_NEED_SHORT_EXTERNAL_NAMES */

/* Extern declarations for the forward and inverse DCT routines. */

LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_islow
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_ifast
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_float
    LJPEG9_JPP((FAST_FLOAT * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_7x7
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_6x6
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_5x5
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_4x4
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_3x3
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_2x2
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_1x1
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_9x9
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_10x10
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_11x11
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_12x12
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_13x13
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_14x14
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_15x15
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_16x16
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_16x8
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_14x7
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_12x6
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_10x5
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_8x4
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_6x3
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_4x2
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_2x1
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_8x16
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_7x14
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_6x12
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_5x10
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_4x8
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_3x6
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_2x4
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_fdct_1x2
    LJPEG9_JPP((DCTELEM * data, LJPEG9_JSAMPARRAY sample_data, LJPEG9_JDIMENSION start_col));

LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_islow
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_ifast
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_float
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_7x7
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_6x6
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_5x5
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_4x4
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_3x3
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_2x2
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_1x1
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_9x9
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_10x10
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_11x11
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_12x12
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_13x13
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_14x14
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_15x15
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_16x16
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_16x8
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_14x7
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_12x6
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_10x5
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_8x4
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_6x3
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_4x2
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_2x1
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_8x16
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_7x14
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_6x12
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_5x10
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_4x8
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_3x6
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_2x4
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));
LJPEG9_EXTERN(void) LJPEG9_jpeg_idct_1x2
    LJPEG9_JPP((LJPEG9_j_decompress_ptr cinfo, jpeg_component_info * compptr,
	 JCOEFPTR coef_block, LJPEG9_JSAMPARRAY output_buf, LJPEG9_JDIMENSION output_col));


/*
 * Macros for handling fixed-point arithmetic; these are used by many
 * but not all of the DCT/IDCT modules.
 *
 * All values are expected to be of type INT32.
 * Fractional constants are scaled left by CONST_BITS bits.
 * CONST_BITS is defined within each module using these macros,
 * and may differ from one module to the next.
 */

#define ONE	((INT32) 1)
#define CONST_SCALE (ONE << CONST_BITS)

/* Convert a positive real constant to an integer scaled by CONST_SCALE.
 * Caution: some C compilers fail to reduce "FIX(constant)" at compile time,
 * thus causing a lot of useless floating-point operations at run time.
 */

#define FIX(x)	((INT32) ((x) * CONST_SCALE + 0.5))

/* Descale and correctly round an INT32 value that's scaled by N bits.
 * We assume RIGHT_SHIFT rounds towards minus infinity, so adding
 * the fudge factor is correct for either sign of X.
 */

#define DESCALE(x,n)  RIGHT_SHIFT((x) + (ONE << ((n)-1)), n)

/* Multiply an INT32 variable by an INT32 constant to yield an INT32 result.
 * This macro is used only when the two inputs will actually be no more than
 * 16 bits wide, so that a 16x16->32 bit multiply can be used instead of a
 * full 32x32 multiply.  This provides a useful speedup on many machines.
 * Unfortunately there is no way to specify a 16x16->32 multiply portably
 * in C, but some C compilers will do the right thing if you provide the
 * correct combination of casts.
 */

#ifdef SHORTxSHORT_32		/* may work if 'int' is 32 bits */
#define MULTIPLY16C16(var,const)  (((INT16) (var)) * ((INT16) (const)))
#endif
#ifdef SHORTxLCONST_32		/* known to work with Microsoft C 6.0 */
#define MULTIPLY16C16(var,const)  (((INT16) (var)) * ((INT32) (const)))
#endif

#ifndef MULTIPLY16C16		/* default definition */
#define MULTIPLY16C16(var,const)  ((var) * (const))
#endif

/* Same except both inputs are variables. */

#ifdef SHORTxSHORT_32		/* may work if 'int' is 32 bits */
#define MULTIPLY16V16(var1,var2)  (((INT16) (var1)) * ((INT16) (var2)))
#endif

#ifndef MULTIPLY16V16		/* default definition */
#define MULTIPLY16V16(var1,var2)  ((var1) * (var2))
#endif
