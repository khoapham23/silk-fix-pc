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

//#define SKP_enc_map(a)                ((a) > 0 ? 1 : 0)
//#define SKP_dec_map(a)                ((a) > 0 ? 1 : -1)
/* shifting avoids if-statement */
#define SKP_enc_map(a)                  ( SKP_RSHIFT( (a), 15 ) + 1 )
#define SKP_dec_map(a)                  ( SKP_LSHIFT( (a),  1 ) - 1 )

/* Encodes signs of excitation */
void SKP_Silk_encode_signs(
    ec_enc                      *psRangeEnc,                        /* I/O  Compressor data structure                   */
    const SKP_int8              pulses[],                           /* I    pulse signal                                */
    SKP_int                     length,                             /* I    length of input                             */
    const SKP_int               signalType,                         /* I    Signal type                                 */
    const SKP_int               quantOffsetType,                    /* I    Quantization offset type                    */
    const SKP_int               sum_pulses[ MAX_NB_SHELL_BLOCKS ]   /* I    Sum of absolute pulses per block            */
)
{
    SKP_int         i, j, p;
    SKP_uint8       icdf[ 2 ];
    const SKP_int8  *q_ptr;
    const SKP_uint8 *icdf_ptr;

    icdf[ 1 ] = 0;
    q_ptr = pulses;
    i = SKP_SMULBB( 6, SKP_ADD_LSHIFT( quantOffsetType, signalType, 1 ) );
    icdf_ptr = &SKP_Silk_sign_iCDF[ i ];
    length = SKP_RSHIFT( length + SHELL_CODEC_FRAME_LENGTH/2, LOG2_SHELL_CODEC_FRAME_LENGTH );
    for( i = 0; i < length; i++ ) {
        p = sum_pulses[ i ];
        if( p > 0 ) {
            icdf[ 0 ] = icdf_ptr[ SKP_min( p - 1, 5 ) ];
            for( j = 0; j < SHELL_CODEC_FRAME_LENGTH; j++ ) {
                if( q_ptr[ j ] != 0 ) {
                    ec_enc_icdf( psRangeEnc, SKP_enc_map( q_ptr[ j ]), icdf, 8 );
                }
            }
        }
        q_ptr += SHELL_CODEC_FRAME_LENGTH;
    }
}

/* Decodes signs of excitation */
void SKP_Silk_decode_signs(
    ec_dec                      *psRangeDec,                        /* I/O  Compressor data structure                   */
    SKP_int                     pulses[],                           /* I/O  pulse signal                                */
    SKP_int                     length,                             /* I    length of input                             */
    const SKP_int               signalType,                         /* I    Signal type                                 */
    const SKP_int               quantOffsetType,                    /* I    Quantization offset type                    */
    const SKP_int               sum_pulses[ MAX_NB_SHELL_BLOCKS ]   /* I    Sum of absolute pulses per block            */
)
{
    SKP_int         i, j, p;
    SKP_uint8       icdf[ 2 ];
    SKP_int         *q_ptr;
    const SKP_uint8 *icdf_ptr;

    icdf[ 1 ] = 0;
    q_ptr = pulses;
    i = SKP_SMULBB( 6, SKP_ADD_LSHIFT( quantOffsetType, signalType, 1 ) );
    icdf_ptr = &SKP_Silk_sign_iCDF[ i ];
    length = SKP_RSHIFT( length + SHELL_CODEC_FRAME_LENGTH/2, LOG2_SHELL_CODEC_FRAME_LENGTH );
    for( i = 0; i < length; i++ ) {
        p = sum_pulses[ i ];
        if( p > 0 ) {
            icdf[ 0 ] = icdf_ptr[ SKP_min( p - 1, 5 ) ];
            for( j = 0; j < SHELL_CODEC_FRAME_LENGTH; j++ ) {
                if( q_ptr[ j ] > 0 ) {
                    /* attach sign */
#if 0
                    /* conditional implementation */
                    if( ec_dec_icdf( psRangeDec, icdf, 8 ) == 0 ) {
                        q_ptr[ j ] = -q_ptr[ j ];
                    }
#else
                    /* implementation with shift, subtraction, multiplication */
                    q_ptr[ j ] *= SKP_dec_map( ec_dec_icdf( psRangeDec, icdf, 8 ) );
#endif
                }
            }
        }
        q_ptr += SHELL_CODEC_FRAME_LENGTH;
    }
}
