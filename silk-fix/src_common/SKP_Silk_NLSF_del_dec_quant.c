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

#include "SKP_Silk_main.h"

/* Delayed-decision quantizer for NLSF residuals */
SKP_int32 SKP_Silk_NLSF_del_dec_quant(                  /* O    Returns RD value in Q25                     */
    SKP_int8                    indices[],              /* O    Quantization indices [ order ]              */
    const SKP_int16             x_Q10[],                /* I    Input [ order ]                             */
    const SKP_int16             w_Q5[],                 /* I    Weights [ order ]                           */
    const SKP_uint8             pred_coef_Q8[],         /* I    Backward predictor coefs [ order ]          */
    const SKP_int16             ec_ix[],                /* I    Indices to entropy coding tables [ order ]  */
    const SKP_uint8             ec_rates_Q5[],          /* I    Rates []                                    */
    const SKP_int               quant_step_size_Q16,    /* I    Quantization step size                      */
    const SKP_int16             inv_quant_step_size_Q6, /* I    Inverse quantization step size              */
    const SKP_int32             mu_Q20,                 /* I    R/D tradeoff                                */
    const SKP_int16             order                   /* I    Number of input values                      */
)
{
    SKP_int         i, j, nStates, ind_tmp, ind_min_max, ind_max_min, in_Q10, res_Q10;
    SKP_int         pred_Q10, diff_Q10, out0_Q10, out1_Q10, rate0_Q5, rate1_Q5;
    SKP_int32       RD_tmp_Q25, min_Q25, min_max_Q25, max_min_Q25, pred_coef_Q16;
    SKP_int         ind_sort[         NLSF_QUANT_DEL_DEC_STATES ];
    SKP_int8        ind[              NLSF_QUANT_DEL_DEC_STATES ][ MAX_LPC_ORDER ];
    SKP_int16       prev_out_Q10[ 2 * NLSF_QUANT_DEL_DEC_STATES ];
    SKP_int32       RD_Q25[       2 * NLSF_QUANT_DEL_DEC_STATES ];
    SKP_int32       RD_min_Q25[       NLSF_QUANT_DEL_DEC_STATES ];
    SKP_int32       RD_max_Q25[       NLSF_QUANT_DEL_DEC_STATES ];
    const SKP_uint8 *rates_Q5;
    
    SKP_assert( (NLSF_QUANT_DEL_DEC_STATES & (NLSF_QUANT_DEL_DEC_STATES-1)) == 0 );     /* must be power of two */

    nStates = 1;
    RD_Q25[ 0 ] = 0;
    prev_out_Q10[ 0 ] = 0;
    for( i = order - 1; ; i-- ) {
        rates_Q5 = &ec_rates_Q5[ ec_ix[ i ] ];
        pred_coef_Q16 = SKP_LSHIFT( (SKP_int32)pred_coef_Q8[ i ], 8 );
        in_Q10 = x_Q10[ i ];
        for( j = 0; j < nStates; j++ ) {
            pred_Q10 = SKP_SMULWB( pred_coef_Q16, prev_out_Q10[ j ] );
            res_Q10  = SKP_SUB16( in_Q10, pred_Q10 );
            ind_tmp  = SKP_SMULWB( inv_quant_step_size_Q6, res_Q10 );
            ind_tmp  = SKP_LIMIT( ind_tmp, -NLSF_QUANT_MAX_AMPLITUDE_EXT, NLSF_QUANT_MAX_AMPLITUDE_EXT-1 );
            ind[ j ][ i ] = (SKP_int8)ind_tmp;

            /* compute outputs for ind_tmp and ind_tmp + 1 */
            out0_Q10 = SKP_LSHIFT( ind_tmp, 10 );
            out1_Q10 = SKP_ADD16( out0_Q10, 1024 );
            if( ind_tmp > 0 ) {
                out0_Q10 = SKP_SUB16( out0_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
                out1_Q10 = SKP_SUB16( out1_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
            } else if( ind_tmp == 0 ) {
                out1_Q10 = SKP_SUB16( out1_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
            } else if( ind_tmp == -1 ) {
                out0_Q10 = SKP_ADD16( out0_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
            } else {
                out0_Q10 = SKP_ADD16( out0_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
                out1_Q10 = SKP_ADD16( out1_Q10, SKP_FIX_CONST( NLSF_QUANT_LEVEL_ADJ, 10 ) );
            }
            out0_Q10  = SKP_SMULWB( out0_Q10, quant_step_size_Q16 );
            out1_Q10  = SKP_SMULWB( out1_Q10, quant_step_size_Q16 );
            out0_Q10  = SKP_ADD16( out0_Q10, pred_Q10 );
            out1_Q10  = SKP_ADD16( out1_Q10, pred_Q10 );
            prev_out_Q10[ j           ] = out0_Q10;
            prev_out_Q10[ j + nStates ] = out1_Q10;

            /* compute RD for ind_tmp and ind_tmp + 1 */
            if( ind_tmp + 1 >= NLSF_QUANT_MAX_AMPLITUDE ) {
                if( ind_tmp + 1 == NLSF_QUANT_MAX_AMPLITUDE ) {
                    rate0_Q5 = rates_Q5[ ind_tmp + NLSF_QUANT_MAX_AMPLITUDE ];
                    rate1_Q5 = 280;
                } else {
                    rate0_Q5 = SKP_SMLABB( 280 - 43 * NLSF_QUANT_MAX_AMPLITUDE, 43, ind_tmp );
                    rate1_Q5 = SKP_ADD16( rate0_Q5, 43 ); 
                }
            } else if( ind_tmp <= -NLSF_QUANT_MAX_AMPLITUDE ) {
                if( ind_tmp == -NLSF_QUANT_MAX_AMPLITUDE ) {
                    rate0_Q5 = 280;
                    rate1_Q5 = rates_Q5[ ind_tmp + 1 + NLSF_QUANT_MAX_AMPLITUDE ]; 
                } else {
                    rate0_Q5 = SKP_SMLABB( 280 - 43 * NLSF_QUANT_MAX_AMPLITUDE, -43, ind_tmp );
                    rate1_Q5 = SKP_SUB16( rate0_Q5, 43 ); 
                }
            } else {
                rate0_Q5 = rates_Q5[ ind_tmp +     NLSF_QUANT_MAX_AMPLITUDE ];
                rate1_Q5 = rates_Q5[ ind_tmp + 1 + NLSF_QUANT_MAX_AMPLITUDE ];
            }
            RD_tmp_Q25            = RD_Q25[ j ];
            diff_Q10              = SKP_SUB16( in_Q10, out0_Q10 );
            RD_Q25[ j ]           = SKP_SMLABB( SKP_MLA( RD_tmp_Q25, SKP_SMULBB( diff_Q10, diff_Q10 ), w_Q5[ i ] ), mu_Q20, rate0_Q5 );
            diff_Q10              = SKP_SUB16( in_Q10, out1_Q10 );
            RD_Q25[ j + nStates ] = SKP_SMLABB( SKP_MLA( RD_tmp_Q25, SKP_SMULBB( diff_Q10, diff_Q10 ), w_Q5[ i ] ), mu_Q20, rate1_Q5 );
        }

        if( nStates < NLSF_QUANT_DEL_DEC_STATES ) {
            /* double number of states and copy */
            for( j = 0; j < nStates; j++ ) {
                ind[ j + nStates ][ i ] = ind[ j ][ i ] + 1;
            }
            nStates = SKP_LSHIFT( nStates, 1 );
            for( j = nStates; j < NLSF_QUANT_DEL_DEC_STATES; j++ ) {
                ind[ j ][ i ] = ind[ j - nStates ][ i ];
            }
        } else if( i > 0 ) {
            /* sort lower and upper half of RD_Q25, pairwise */
            for( j = 0; j < NLSF_QUANT_DEL_DEC_STATES; j++ ) {
                if( RD_Q25[ j ] > RD_Q25[ j + NLSF_QUANT_DEL_DEC_STATES ] ) {
                    RD_max_Q25[ j ]                         = RD_Q25[ j ];
                    RD_min_Q25[ j ]                         = RD_Q25[ j + NLSF_QUANT_DEL_DEC_STATES ];
                    RD_Q25[ j ]                             = RD_min_Q25[ j ];
                    RD_Q25[ j + NLSF_QUANT_DEL_DEC_STATES ] = RD_max_Q25[ j ];
                    /* swap prev_out values */
                    out0_Q10 = prev_out_Q10[ j ];
                    prev_out_Q10[ j ] = prev_out_Q10[ j + NLSF_QUANT_DEL_DEC_STATES ];
                    prev_out_Q10[ j + NLSF_QUANT_DEL_DEC_STATES ] = out0_Q10;
                    ind_sort[ j ] = j + NLSF_QUANT_DEL_DEC_STATES;
                } else {
                    RD_min_Q25[ j ] = RD_Q25[ j ];
                    RD_max_Q25[ j ] = RD_Q25[ j + NLSF_QUANT_DEL_DEC_STATES ];
                    ind_sort[ j ] = j;
                }
            }
            /* compare the highest RD values of the winning half with the lowest one in the losing half, and copy if necessary */
            /* afterwards ind_sort[] will contain the indices of the NLSF_QUANT_DEL_DEC_STATES winning RD values */
            while( 1 ) {
                min_max_Q25 = SKP_int32_MAX;
                max_min_Q25 = 0;
                ind_min_max = 0;
                ind_max_min = 0;
                for( j = 0; j < NLSF_QUANT_DEL_DEC_STATES; j++ ) {
                    if( min_max_Q25 > RD_max_Q25[ j ] ) {
                        min_max_Q25 = RD_max_Q25[ j ];
                        ind_min_max = j;
                    }
                    if( max_min_Q25 < RD_min_Q25[ j ] ) {
                        max_min_Q25 = RD_min_Q25[ j ];
                        ind_max_min = j;
                    }
                }
                if( min_max_Q25 >= max_min_Q25 ) {
                    break;
                }
                /* copy ind_min_max to ind_max_min */
                ind_sort[     ind_max_min ] = ind_sort[     ind_min_max ] ^ NLSF_QUANT_DEL_DEC_STATES;
                RD_Q25[       ind_max_min ] = RD_Q25[       ind_min_max + NLSF_QUANT_DEL_DEC_STATES ];
                prev_out_Q10[ ind_max_min ] = prev_out_Q10[ ind_min_max + NLSF_QUANT_DEL_DEC_STATES ];
                RD_min_Q25[   ind_max_min ] = 0;
                RD_max_Q25[   ind_min_max ] = SKP_int32_MAX;
                SKP_memcpy( ind[ ind_max_min ], ind[ ind_min_max ], MAX_LPC_ORDER * sizeof( SKP_int8 ) );
            }
            /* increment index if it comes from the upper half */
            for( j = 0; j < NLSF_QUANT_DEL_DEC_STATES; j++ ) {
                ind[ j ][ i ] += SKP_RSHIFT( ind_sort[ j ], NLSF_QUANT_DEL_DEC_STATES_LOG2 );
            }
        } else {  /* i == 0 */
            /* last sample: find winner, copy indices and return RD value */
            ind_tmp = 0;
            min_Q25 = SKP_int32_MAX;
            for( j = 0; j < 2 * NLSF_QUANT_DEL_DEC_STATES; j++ ) {
                if( min_Q25 > RD_Q25[ j ] ) {
                    min_Q25 = RD_Q25[ j ];
                    ind_tmp = j;
                }
            }
            for( j = 0; j < order; j++ ) {
                indices[ j ] = ind[ ind_tmp & ( NLSF_QUANT_DEL_DEC_STATES - 1 ) ][ j ];
                SKP_assert( indices[ j ] >= -NLSF_QUANT_MAX_AMPLITUDE_EXT );
                SKP_assert( indices[ j ] <=  NLSF_QUANT_MAX_AMPLITUDE_EXT );
            }
            indices[ 0 ] += SKP_RSHIFT( ind_tmp, NLSF_QUANT_DEL_DEC_STATES_LOG2 );
            SKP_assert( indices[ 0 ] <= NLSF_QUANT_MAX_AMPLITUDE_EXT );
            SKP_assert( min_Q25 >= 0 );
            return min_Q25;
        }
    }
}
