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

/**********************************************/
/* This file has been automatically generated */
/*                                            */
/* ROM usage:  0.16 + 1.43 kB                 */
/**********************************************/

#include "SKP_Silk_structs.h"
#include "SKP_Silk_tables.h"
#include "SKP_Silk_tables_NLSF_CB.h"

const SKP_uint8 SKP_Silk_NLSF_MSVQ_CB0_10_CDF[ NLSF_MSVQ_CB0_10_VECTORS ] =
{
          246,
          237,
          230,
          223,
          216,
          210,
          204,
          198,
          192,
          186,
          180,
          175,
          169,
          164,
          158,
          153,
          147,
          142,
          137,
          132,
          127,
          123,
          118,
          113,
          109,
          105,
          101,
           97,
           93,
           89,
           85,
           81,
           78,
           74,
           71,
           67,
           64,
           60,
           57,
           54,
           50,
           47,
           44,
           41,
           38,
           35,
           32,
           29,
           27,
           24,
           21,
           19,
           16,
           14,
           12,
           10,
            8,
            6,
            5,
            4,
            3,
            2,
            1,
            0,
          234,
          216,
          198,
          180,
          162,
          145,
          128,
          111,
           95,
           79,
           64,
           50,
           37,
           23,
           10,
            0,
          221,
          188,
          154,
          123,
           91,
           59,
           28,
            0,
          220,
          185,
          151,
          118,
           85,
           51,
           26,
            0,
          220,
          185,
          150,
          116,
           86,
           55,
           26,
            0,
          220,
          185,
          152,
          118,
           88,
           57,
           28,
            0,
          236,
          217,
          199,
          181,
          164,
          146,
          130,
          113,
           97,
           81,
           66,
           51,
           37,
           23,
           11,
            0
};

const SKP_uint8 * const SKP_Silk_NLSF_MSVQ_CB0_10_CDF_start_ptr[ NLSF_MSVQ_CB0_10_STAGES ] =
{
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[   0 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[  64 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[  80 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[  88 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[  96 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[ 104 ],
     &SKP_Silk_NLSF_MSVQ_CB0_10_CDF[ 112 ]
};

const SKP_uint8 SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[ NLSF_MSVQ_CB0_10_VECTORS ] =
{
               74,               79,
               83,               83,
               84,               85,
               85,               87,
               87,               87,
               88,               88,
               89,               89,
               89,               89,
               89,               89,
               91,               91,
               92,               92,
               92,               94,
               94,               94,
               95,               96,
               96,               97,
               97,               98,
               98,               99,
               99,              100,
              100,              100,
              100,              100,
              101,              101,
              102,              102,
              102,              103,
              103,              105,
              105,              105,
              106,              106,
              108,              108,
              109,              111,
              111,              121,
              124,              128,
              128,              128,
              128,              128,
               57,               61,
               61,               61,
               61,               63,
               63,               63,
               64,               64,
               65,               67,
               68,               68,
               69,               74,
               46,               47,
               47,               48,
               48,               48,
               49,               51,
               45,               46,
               47,               47,
               47,               47,
               53,               53,
               45,               46,
               46,               47,
               49,               49,
               50,               53,
               45,               46,
               47,               47,
               49,               49,
               50,               51,
               59,               60,
               61,               61,
               62,               62,
               63,               63,
               64,               64,
               65,               65,
               67,               67,
               71,               72
};

const SKP_int SKP_Silk_NLSF_MSVQ_CB0_10_ndelta_min_Q15[ 10 + 1 ] =
{
              550,
                3,
               22,
               18,
                3,
                3,
              181,
              162,
              310,
              172,
              982
};

const SKP_int8 SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 * NLSF_MSVQ_CB0_10_VECTORS ] =
{
             -107,              -97,
              -74,              -56,
              -37,               -8,
               20,               48,
               75,              100,
             -109,              -91,
              -71,              -48,
              -20,               -1,
               23,               47,
               77,              100,
             -100,              -93,
              -78,              -50,
               -5,                8,
               28,               53,
               72,               93,
             -105,              -97,
              -82,              -49,
              -16,               -5,
               33,               52,
               72,              100,
              -98,              -92,
              -75,              -39,
              -10,                1,
               24,               41,
               62,              103,
              -99,              -92,
              -74,              -44,
              -30,              -16,
               33,               51,
               69,              105,
             -105,              -98,
              -82,              -51,
                5,               19,
               35,               54,
               73,              102,
             -110,             -101,
              -85,              -61,
              -40,              -24,
               12,               45,
               67,               97,
             -104,              -95,
              -81,              -61,
              -22,               -8,
               14,               50,
               68,               88,
              -96,              -90,
              -74,              -44,
              -30,              -16,
               20,               34,
               74,               90,
              -89,              -83,
              -64,              -27,
              -11,                0,
               36,               54,
               74,              103,
             -102,              -96,
              -71,              -28,
              -16,                1,
               21,               40,
               71,               86,
             -102,              -96,
              -80,              -32,
              -19,               -4,
               31,               45,
               88,              103,
              -90,              -83,
              -66,              -51,
              -40,              -20,
               43,               62,
               81,              105,
             -115,             -108,
              -79,              -49,
              -21,                0,
               26,               54,
               78,              100,
             -105,              -93,
              -78,              -59,
              -28,              -14,
               11,               32,
               57,               96,
             -101,              -96,
              -68,              -17,
               -5,                9,
               30,               46,
               87,              103,
             -109,             -101,
              -87,              -59,
              -10,                5,
               23,               41,
               63,              100,
              -86,              -78,
              -63,              -45,
              -28,              -15,
               26,               43,
               63,              102,
             -106,              -98,
              -83,              -41,
              -21,               -7,
               13,               30,
               80,               96,
              -94,              -88,
              -67,              -30,
                7,               18,
               37,               55,
               73,              102,
              -96,              -90,
              -73,              -61,
              -51,              -15,
               30,               44,
               83,               99,
             -112,             -105,
              -84,              -61,
              -35,               -3,
               21,               39,
               61,               92,
             -105,              -98,
              -80,              -49,
              -38,               -2,
               17,               38,
               79,               94,
              -86,              -78,
              -66,              -48,
              -12,                1,
               25,               51,
               71,               94,
             -108,             -102,
              -83,              -30,
                0,               10,
               35,               51,
               82,              100,
             -107,              -99,
              -84,              -70,
              -58,              -14,
               17,               40,
               75,               97,
              -94,              -88,
              -62,              -32,
              -20,               -6,
               10,               28,
               86,              105,
              -97,              -91,
              -72,              -62,
              -50,                1,
               18,               43,
               68,               84,
             -103,              -98,
              -72,              -32,
               17,               31,
               47,               66,
               83,              105,
              -99,              -90,
              -76,              -61,
              -49,              -33,
               21,               40,
               63,              100,
              -86,              -80,
              -60,              -43,
              -32,              -13,
               26,               39,
               84,              104,
             -102,              -96,
              -61,              -33,
              -23,               13,
               31,               54,
               85,              100,
             -110,             -100,
              -87,              -52,
              -35,              -20,
               28,               41,
               83,              102,
              -91,              -84,
              -58,              -45,
              -36,               -2,
               22,               42,
               72,               85,
             -105,              -96,
              -66,              -47,
              -24,               11,
               31,               45,
               63,               91,
              -93,              -87,
              -70,              -45,
              -31,              -18,
               -2,               14,
               69,              105,
              -98,              -93,
              -61,              -48,
              -35,              -19,
               -6,               44,
               69,               85,
             -101,              -94,
              -77,              -56,
              -43,              -24,
               -7,               18,
               73,               92,
             -102,              -95,
              -77,              -48,
              -34,              -15,
                5,               30,
               55,               79,
             -100,              -95,
              -50,              -32,
              -22,               -5,
               10,               52,
               77,               91,
             -114,             -109,
              -94,              -71,
              -27,               -5,
               21,               47,
               74,              100,
              -95,              -80,
              -65,              -46,
              -27,              -15,
               16,               61,
               79,               98,
             -105,             -100,
              -62,               -7,
                7,               20,
               44,               61,
               87,              102,
             -101,              -95,
              -81,              -66,
              -57,              -26,
               40,               57,
               83,              104,
              -97,              -92,
              -66,              -53,
              -43,               11,
               32,               49,
               89,              102,
              -99,              -91,
              -75,              -57,
              -45,              -29,
               19,               64,
               83,              101,
              -91,              -85,
              -66,              -55,
              -44,               -9,
               11,               27,
               83,               99,
             -107,              -99,
              -83,              -59,
               -9,               29,
               43,               61,
               81,               99,
             -101,              -96,
              -77,              -68,
              -53,               17,
               35,               53,
               80,               94,
              -99,              -93,
              -65,              -50,
              -37,              -20,
               -7,               51,
               85,              101,
              -97,              -91,
              -72,              -64,
              -49,                2,
               49,               65,
               89,              105,
             -107,              -95,
              -63,              -41,
              -14,               17,
               43,               66,
               89,              106,
              -84,              -76,
              -44,              -28,
              -15,                5,
               25,               44,
               78,               95,
             -102,              -97,
              -42,              -17,
               -7,               13,
               29,               55,
               82,               98,
              -99,              -94,
              -81,              -71,
              -21,                9,
               28,               53,
               76,               95,
              -86,              -79,
              -62,              -53,
              -34,               15,
               37,               54,
               83,               97,
              -76,              -73,
              -57,              -33,
              -26,              -14,
               37,               56,
               76,              103,
              -85,              -71,
              -35,              -10,
                4,               21,
               40,               59,
               84,              100,
              -79,              -77,
              -71,              -63,
              -27,              -18,
               25,               52,
               77,              103,
              -81,              -60,
              -50,              -47,
              -42,                3,
               24,               54,
               80,              104,
              -97,              -79,
              -23,              -16,
              -12,               -9,
                6,               55,
               78,              102,
              -76,              -74,
              -66,              -49,
              -47,              -38,
               14,               47,
               75,              101,
              -93,              -63,
              -44,              -37,
              -30,              -23,
               28,               52,
               77,              102,
                5,                4,
                6,                5,
                5,                8,
                4,                4,
                0,               -2,
                0,               -1,
               -3,               -3,
               -5,               -6,
              -12,                4,
               -1,               -3,
                2,                1,
                2,                0,
                1,               -1,
               -1,               -7,
              -12,                6,
               -2,               -3,
               -8,                8,
                6,                5,
                1,                2,
                0,               -1,
               -1,               -1,
                1,                1,
                1,                0,
               -3,               -5,
               -9,              -13,
                0,                0,
               -2,               -3,
               -6,              -10,
                3,               -3,
               -3,               -5,
               -2,               -3,
               -4,               -7,
               -8,               10,
                4,                2,
                1,               -2,
               -5,               -6,
               -9,               -3,
                0,               -3,
                2,               -2,
                2,                3,
                0,               -1,
                2,               -1,
               -2,               -3,
               -8,              -14,
                4,                2,
                2,                1,
                2,                2,
               -1,               -4,
               12,                6,
                4,                5,
                2,                1,
                2,                4,
                3,                3,
                1,               -5,
               10,                7,
                8,                8,
                4,               -1,
               -1,               -4,
               -6,                2,
                0,               -1,
                1,                0,
               -4,              -12,
                5,                3,
                3,                3,
                2,                2,
                1,                0,
                2,               -1,
                1,                0,
               -3,               15,
                7,                4,
               -5,               -6,
                9,                5,
                2,                3,
                4,                0,
               -1,                3,
               -8,                7,
                3,                2,
                0,               -2,
                0,                0,
               -2,                0,
               -2,               -2,
               -3,               -4,
               -3,               -3,
               -3,                0,
               -5,                4,
                3,                3,
                2,               -2,
               -2,                0,
               -1,               -2,
               -4,               -8,
                2,                2,
                0,                0,
                7,                4,
                2,                1,
                0,                3,
                2,                2,
                1,                1,
               -2,               -6,
                3,                0,
               -1,                4,
               -4,               -4,
               -5,                1,
                1,                3,
                5,                4,
                1,               -1,
               -1,               -1,
                7,                5,
                3,                0,
               -2,                5,
                1,               -2,
               -2,               -2,
               -3,                2,
                2,               -1,
               -4,               -7,
                3,               -2,
                1,                1,
                2,               -3,
               -7,                3,
                1,               -1,
                7,                2,
               -1,               -1,
               -3,                3,
                0,               -1,
               -2,                0,
               -6,                0,
                0,                0,
               -2,                3,
                0,                2,
                3,                1,
                4,                5,
                1,                1,
               -3,               -3,
               -4,               -3,
               -2,               -2,
                2,                0,
                1,                1,
                0,                0,
               -1,               -2,
                5,                5,
                0,               -3,
               -1,               -1,
               -1,               -5,
                5,                4,
                1,                0,
               -1,               -2,
                3,                2,
                3,                4,
                1,                1,
               -1,               -3,
                0,               -1,
               -3,               -4,
                4,                1,
               -2,                0,
                0,               -2,
                2,                0,
                0,                4,
                4,               -3,
                0,               -1,
               -4,                2,
                0,                1,
               -1,               -1,
                0,               -1,
               -3,                4,
                1,               -2,
               -2,               -1,
                1,                1,
                0,                0,
                1,               -1,
               -4,               -3,
                0,                2,
               -1,               -1,
                0,                3,
                4,                0,
                2,                0,
               -3,                1,
               -1,               -1,
               -3,                2,
               -1,                2,
               -3,                3,
                2,                0,
                1,                0,
                4,                0,
               -1,                0,
                2,                2,
                1,                3,
                0,                0,
                2,                1,
                1,               -1,
                0,               -2,
                1,               -5,
               -2,               -1,
               -2,               -2,
                0,               -4,
                1,                0,
                2,                1,
                3,                4,
                0,               -3,
                1,               -1,
                1,                1,
                0,               -1,
               -4,                2,
               -1,                0,
               -1,               -1,
                0,                0,
                0,                0,
                0,               -1,
                2,                0,
               -2,               -3,
               -2,                0,
               -2,               -1,
                2,                0,
               -2,                1,
                0,                0,
                1,                0,
                0,               -3,
                1,                0,
                0,               -1,
                0,               -1,
                1,               -3,
                0,                3,
                0,               -2,
               -1,               -3,
                0,                1,
                0,                2,
                0,                0,
                2,                2,
                1,                1,
                0,                3,
                1,                1,
                0,                1,
               -1,               -2,
                2,                2,
                1,                2,
                0,               -1,
                0,                0,
                1,                0,
                0,                0,
                2,               -1,
               -2,                1,
                3,                0,
                1,                0,
               -1,                0,
                0,                0,
               -1,                4,
               -1,                1,
               -1,                0,
                0,               -1,
                0,                1,
                4,                0,
               -2,                0,
                0,               -1,
               -3,               -1,
                0,                0,
                0,               -2,
                1,                1,
               -1,                2,
                0,                0,
                0,                1,
                1,                0,
                4,                0,
                1,                0,
                1,               -1,
                0,                2,
               -3,                0,
                1,               -1,
                0,                2,
               -1,                3,
                1,                0,
               -1,               -1,
               -1,                0,
                0,                1,
                0,                0,
               -4,               -1,
                0,                1,
                1,                0,
               -1,                2,
               -1,               -1,
                2,                1,
               -1,                0,
               -1,               -1,
               -2,               -2,
                1,               -1,
                0,                0,
               -1,                1,
                0,                2,
                2,               -1,
                1,                1,
               -1,                1,
                0,               -1,
               -3,                0,
                0,                1,
                3,               -2,
                0,                0,
                0,               -1,
               -1,               -1,
               -1,               -2,
               -1,                1,
                1,               -1,
               -1,                0,
               -1,               -2,
                0,                1,
                1,                1,
                1,               -3,
                1,                1,
                0,                0,
                0,               -1,
                0,                2,
               -2,                0,
                1,                0,
                1,                0,
                2,                1,
               -1,               -1,
                0,               -1,
                1,                0,
                2,                0,
                0,               -2,
                1,               -1,
                1,               -1,
                1,                0,
                2,                0
};

const SKP_Silk_NLSF_CBS SKP_Silk_NLSF_CB0_10_Stage_info[ NLSF_MSVQ_CB0_10_STAGES ] =
{
        {  64, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 *   0 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[   0 ] },
        {  16, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 *  64 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[  64 ] },
        {   8, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 *  80 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[  80 ] },
        {   8, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 *  88 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[  88 ] },
        {   8, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 *  96 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[  96 ] },
        {   8, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 * 104 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[ 104 ] },
        {  16, &SKP_Silk_NLSF_MSVQ_CB0_10_Q8[ 10 * 112 ], &SKP_Silk_NLSF_MSVQ_CB0_10_rates_Q4[ 112 ] }
};

const SKP_Silk_NLSF_CB_struct SKP_Silk_NLSF_CB0_10 =
{
        NLSF_MSVQ_CB0_10_STAGES,
        SKP_Silk_NLSF_CB0_10_Stage_info,
        SKP_Silk_NLSF_MSVQ_CB0_10_ndelta_min_Q15,
        SKP_Silk_NLSF_MSVQ_CB0_10_CDF_start_ptr
};

