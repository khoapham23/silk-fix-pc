/***********************************************************************
Copyright (c) 2006-2011, Skype Limited. All rights reserved. 
Redistribution and use in source and binary forms, with or without 
modification, (subject to the limitations in the disclaimer below) 
are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright 
notice, this list of conditions and the following disclaimer in the 
documentation and/or other materials provided with the distribution.
- Neither the name of Skype Limited, nor the names of specific 
contributors, may be used to endorse or promote products derived from 
this software without specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED 
BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************/

#ifndef SKP_SILK_TABLES_H
#define SKP_SILK_TABLES_H

#include "SKP_Silk_define.h"
#include "SKP_Silk_structs.h"

#define PITCH_EST_MAX_LAG_MS                18          /* 18 ms -> 56 Hz */
#define PITCH_EST_MIN_LAG_MS                2           /* 2 ms -> 500 Hz */

#ifdef __cplusplus
extern "C"
{
#endif

/* entropy coding tables */
extern const SKP_uint8  SKP_Silk_gain_iCDF[ 3 ][ N_LEVELS_QGAIN / 8 ];                               /* 24 */
extern const SKP_uint8  SKP_Silk_delta_gain_iCDF[ MAX_DELTA_GAIN_QUANT - MIN_DELTA_GAIN_QUANT + 1 ]; /* 41 */

extern const SKP_uint8  SKP_Silk_pitch_lag_iCDF[ 2 * ( PITCH_EST_MAX_LAG_MS - PITCH_EST_MIN_LAG_MS ) ];  /* 32 */
extern const SKP_uint8  SKP_Silk_pitch_delta_iCDF[21];                                              /*  21 */
extern const SKP_uint8  SKP_Silk_pitch_contour_iCDF[34];                                            /*  34 */
extern const SKP_uint8  SKP_Silk_pitch_contour_NB_iCDF[ 11 ];                                       /*  11 */
extern const SKP_uint8 SKP_Silk_pitch_contour_10_ms_iCDF[12];                                       /*  12 */
extern const SKP_uint8 SKP_Silk_pitch_contour_10_ms_NB_iCDF[3];                                     /*   3 */

extern const SKP_uint8  SKP_Silk_pulses_per_block_iCDF[ N_RATE_LEVELS ][ MAX_PULSES + 2 ];          /* 180 */
extern const SKP_uint8  SKP_Silk_pulses_per_block_BITS_Q5[ N_RATE_LEVELS - 1 ][ MAX_PULSES + 2 ];   /* 162 */

extern const SKP_uint8  SKP_Silk_rate_levels_iCDF[ 2 ][ N_RATE_LEVELS - 1 ];                        /*  18 */
extern const SKP_uint8  SKP_Silk_rate_levels_BITS_Q5[ 2 ][ N_RATE_LEVELS - 1 ];                     /*  18 */

extern const SKP_uint8  SKP_Silk_max_pulses_table[ 4 ];                                             /*   4 */

extern const SKP_uint8  SKP_Silk_shell_code_table0[  44 ];                                          /*  44 */
extern const SKP_uint8  SKP_Silk_shell_code_table1[  65 ];                                          /*  65 */
extern const SKP_uint8  SKP_Silk_shell_code_table2[  90 ];                                          /*  90 */
extern const SKP_uint8  SKP_Silk_shell_code_table3[ 152 ];                                          /* 152 */
extern const SKP_uint8  SKP_Silk_shell_code_table_offsets[ MAX_PULSES + 1 ];                        /*  17 */

extern const SKP_uint8  SKP_Silk_lsb_iCDF[ 2 ];                                                     /*   2 */

extern const SKP_uint8  SKP_Silk_sign_iCDF[ 36 ];                                                   /*  36 */

extern const SKP_uint8  SKP_Silk_uniform2_iCDF[   2 ];                                              /*   2 */
extern const SKP_uint8  SKP_Silk_uniform4_iCDF[   4 ];                                              /*   4 */
extern const SKP_uint8  SKP_Silk_uniform6_iCDF[   6 ];                                              /*   6 */
extern const SKP_uint8  SKP_Silk_uniform8_iCDF[   8 ];                                              /*   8 */

extern const SKP_uint8 SKP_Silk_NLSF_EXT_iCDF[ 7 ];                                                 /*   7 */

extern const SKP_uint8  SKP_Silk_LTP_per_index_iCDF[ 3 ];                                           /*   3 */
extern const SKP_uint8  * const SKP_Silk_LTP_gain_iCDF_ptrs[ NB_LTP_CBKS ];                         /*   3 */
extern const SKP_uint8  * const SKP_Silk_LTP_gain_BITS_Q5_ptrs[ NB_LTP_CBKS ];                      /*   3 */
extern const SKP_int16  SKP_Silk_LTP_gain_middle_avg_RD_Q14;
extern const SKP_int8   * const SKP_Silk_LTP_vq_ptrs_Q7[ NB_LTP_CBKS ];                             /* 168 */
extern const SKP_int8   SKP_Silk_LTP_vq_sizes[ NB_LTP_CBKS ];                                       /*   3 */

extern const SKP_uint8  SKP_Silk_LTPscale_iCDF[ 3 ];                                                /*   4 */
extern const SKP_int16  SKP_Silk_LTPScales_table_Q14[ 3 ];

extern const SKP_uint8 SKP_Silk_type_offset_VAD_iCDF[4];                                            /*   4 */
extern const SKP_uint8 SKP_Silk_type_offset_no_VAD_iCDF[2];                                         /*   2 */

extern const SKP_uint8 * const SKP_Silk_LBRR_flags_iCDF_ptr[2];                                     /*  10 */

extern const SKP_uint8  SKP_Silk_NLSF_interpolation_factor_iCDF[ 5 ];                               /*   5 */

extern const SKP_Silk_NLSF_CB_struct SKP_Silk_NLSF_CB_WB;
extern const SKP_Silk_NLSF_CB_struct SKP_Silk_NLSF_CB_NB_MB;

/* Piece-wise linear mapping from bitrate in kbps to coding quality in dB SNR */
extern const SKP_int32  TargetRate_table_NB[  TARGET_RATE_TAB_SZ ];
extern const SKP_int32  TargetRate_table_MB[  TARGET_RATE_TAB_SZ ];
extern const SKP_int32  TargetRate_table_WB[  TARGET_RATE_TAB_SZ ];
extern const SKP_int16  SNR_table_Q1[         TARGET_RATE_TAB_SZ ];

/* Decoder high-pass filter coefficients */
extern const SKP_int32  SKP_Silk_Dec_A_HP_16[ DEC_HP_ORDER ];                                       /*   2 */
extern const SKP_int32  SKP_Silk_Dec_B_HP_16[ DEC_HP_ORDER + 1 ];                                   /*   3 */
extern const SKP_int32  SKP_Silk_Dec_A_HP_12[ DEC_HP_ORDER ];                                       /*   2 */
extern const SKP_int32  SKP_Silk_Dec_B_HP_12[ DEC_HP_ORDER + 1 ];                                   /*   3 */
extern const SKP_int32  SKP_Silk_Dec_A_HP_8[ DEC_HP_ORDER ];                                        /*   2 */
extern const SKP_int32  SKP_Silk_Dec_B_HP_8[ DEC_HP_ORDER + 1 ];                                    /*   3 */

/* Quantization offsets */
extern const SKP_int16  SKP_Silk_Quantization_Offsets_Q10[ 2 ][ 2 ];

#if SWITCH_TRANSITION_FILTERING
/* Interpolation points for filter coefficients used in the bandwidth transition smoother */
extern const SKP_int32 SKP_Silk_Transition_LP_B_Q28[ TRANSITION_INT_NUM ][ TRANSITION_NB ];
extern const SKP_int32 SKP_Silk_Transition_LP_A_Q28[ TRANSITION_INT_NUM ][ TRANSITION_NA ];
#endif

#ifdef __cplusplus
}
#endif

#endif
