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


/*****************************/
/* Silk encoder test program */
/*****************************/

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE    1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "SKP_Silk_SDK_API.h"
#include "../src_SigProc_FIX/SKP_Silk_SigProc_FIX.h"

/* Define codec specific settings */
#define MAX_BYTES_PER_FRAME     250 // Equals peak bitrate of 100 kbps 
#define MAX_INPUT_FRAMES        5
#define MAX_LBRR_DELAY          2
#define MAX_FRAME_LENGTH        320
#define MAX_FRAME_LENGTH_MS     20
#define MAX_API_FS_KHZ          48


static void print_usage( char* argv[] ) {
    printf( "\nusage: %s in.pcm out.bit [settings]\n", argv[ 0 ] );
    printf( "\nin.pcm               : Speech input to encoder" );
    printf( "\nout.bit              : Bitstream output from encoder" );
    printf( "\n   settings:" );
    printf( "\n-Fs <Hz>         : API sampling rate in Hz, default: 48000" );
    printf( "\n-Fs_maxInternal <Hz> : Maximum internal sampling rate in Hz, default: 16000" ); 
    printf( "\n-plength <ms>   : Packet interval in ms, default: 20" );
    printf( "\n-rate <bps>          : Target bitrate; default: 64000" );
    printf( "\n-complexity <comp>   : Set complexity, 0: low, 1: medium, 2: high; default: 2" );
    printf( "\n-quiet               : Print only some basic values" );
    printf( "\n");
}

int main( int argc, char* argv[] )
{
	unsigned long int temp=0;
	clock_t start_cycles,stop_cycles;
    double    filetime;
    size_t    counter;
    SKP_int32  args, totPackets, ret, nBytes;
    double    sumBytes,avg_rate;
    SKP_int16 in[ MAX_FRAME_LENGTH_MS * MAX_API_FS_KHZ * MAX_INPUT_FRAMES ];
    char      speechInFileName[ 150 ], bitOutFileName[ 150 ];
    FILE      *bitOutFile, *speechInFile;
    SKP_int32 encSizeBytes;
    void      *psEnc;

    SKP_uint8      range_buf[ MAX_BYTES_PER_FRAME * MAX_INPUT_FRAMES ];
    ec_enc         range_enc_celt_state;

    /* default settings */
    SKP_int32 API_fs_Hz = 48000;
    SKP_int32 max_internal_fs_Hz = 16000;
    SKP_int32 min_internal_fs_Hz = 8000;
    SKP_int32 targetRate_bps = 64000;
    SKP_int32 packetSize_ms = 20;
    SKP_int32 frameSizeReadFromFile_ms = 10;
    SKP_int32 complexity_mode = 2, smplsSinceLastPacket;
    SKP_int32 quiet = 0;
    SKP_SILK_SDK_EncControlStruct encControl; // Struct for input to encoder

        
    if( argc < 3 ) {
        print_usage( argv );
        exit( 0 );
    } 
    
    /* get arguments */
    args = 1;
    strcpy( speechInFileName, argv[ args ] );
    args++;
    strcpy( bitOutFileName,   argv[ args ] );
    args++;
    while( args < argc ) {
        if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-Fs" ) == 0 ) {
            sscanf( argv[ args + 1 ], "%d", &API_fs_Hz );
            args += 2;
        } else if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-Fs_maxInternal" ) == 0 ) {
            sscanf( argv[ args + 1 ], "%d", &max_internal_fs_Hz );
            args += 2;
        } else if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-plength" ) == 0 ) {
            sscanf( argv[ args + 1 ], "%d", &packetSize_ms );
            args += 2;
        } else if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-rate" ) == 0 ) {
            sscanf( argv[ args + 1 ], "%d", &targetRate_bps );
            args += 2;
        } else if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-complexity" ) == 0 ) {
            sscanf( argv[ args + 1 ], "%d", &complexity_mode );
            args += 2;
        }else if( SKP_STR_CASEINSENSITIVE_COMPARE( argv[ args ], "-quiet" ) == 0 ) {
            quiet = 1;
            args++;
        } else {
            printf( "Error: unrecognized setting: %s\n\n", argv[ args ] );
            print_usage( argv );
            exit( 0 );
        }
    }

    /* If no max internal set set to API fs */
    if( max_internal_fs_Hz == 0 ) {
        max_internal_fs_Hz = API_fs_Hz;
    }

    /* Print options */
    if( !quiet ) {
        printf("******************* Compiled for %d bit cpu ********* \n", (int)sizeof(void*) * 8 );
        printf( "Input:                          %s\n",     speechInFileName );
        printf( "Output:                         %s\n",     bitOutFileName );
        printf( "API sampling rate:              %d Hz\n",  API_fs_Hz );
        printf( "Maximum internal sampling rate: %d Hz\n",  max_internal_fs_Hz );
        printf( "Packet interval:                %d ms\n",  packetSize_ms );
        printf( "Complexity:                     %d\n",     complexity_mode );
        printf( "Target bitrate:                 %d bps\n", targetRate_bps );
    }

    /* Open files */
    speechInFile = fopen( speechInFileName, "rb" );
    if( speechInFile == NULL ) {
        printf( "Error: could not open input file %s\n", speechInFileName );
        exit( 0 );
    }
    bitOutFile = fopen( bitOutFileName, "wb" );
    if( bitOutFile == NULL ) {
        printf( "Error: could not open output file %s\n", bitOutFileName );
        exit( 0 );
    }

    /* Create Encoder */
    ret = SKP_Silk_SDK_Get_Encoder_Size( &encSizeBytes );
    if( ret ) {
        printf( "\nSKP_Silk_create_encoder returned %d", ret );
    }

    psEnc = malloc( encSizeBytes );

    /* Reset Encoder */
    ret = SKP_Silk_SDK_InitEncoder( psEnc, &encControl );
    if( ret ) {
        printf( "\nSKP_Silk_reset_encoder returned %d", ret );
    }
    
    /* Set Encoder parameters */
    encControl.API_sampleRate        = API_fs_Hz;
    encControl.maxInternalSampleRate = max_internal_fs_Hz;
    encControl.minInternalSampleRate = min_internal_fs_Hz;
    encControl.payloadSize_ms        = packetSize_ms;
    encControl.complexity            = complexity_mode;
    encControl.bitRate               = ( targetRate_bps > 0 ? targetRate_bps : 0 );

    if( API_fs_Hz > MAX_API_FS_KHZ * 1000 || API_fs_Hz < 0 ) {
        printf( "\nError: API sampling rate = %d out of range, valid range 8000 - 48000 \n \n", API_fs_Hz );
        exit( 0 );
    }
     /*Reset init */
    totPackets           = 0;
 //   totActPackets        = 0;
    smplsSinceLastPacket = 0;
    sumBytes             = 0.0;
   // sumActBytes          = 0.0;
    
    while( 1 ) {
        if( smplsSinceLastPacket == 0 ) {
            /* Init range coder */
            ec_enc_init( &range_enc_celt_state, range_buf, MAX_BYTES_PER_FRAME * MAX_INPUT_FRAMES );
        }

        /* Read input from file */
        counter = fread( in, sizeof( SKP_int16 ), ( frameSizeReadFromFile_ms * API_fs_Hz ) / 1000, speechInFile );
        /*check end of input file*/
        if( (SKP_int)counter < ( ( frameSizeReadFromFile_ms * API_fs_Hz ) / 1000 ) ) {
            break;
        }

        /* max payload size */
        nBytes = MAX_BYTES_PER_FRAME * MAX_INPUT_FRAMES;

        /////////////* Silk Encoder */////////////////////
        start_cycles = clock();
        ret = SKP_Silk_SDK_Encode( psEnc, &encControl, in, (SKP_int16)counter, &range_enc_celt_state, &nBytes, 0 );
        stop_cycles = clock();
        temp = temp + (stop_cycles - start_cycles);
        if( ret ) {
            printf( "\nSKP_Silk_Encode returned %d", ret );
            break;
        }
        //////////////////////////////////////////////////


        /* Get packet size */
        packetSize_ms = encControl.payloadSize_ms;

        smplsSinceLastPacket += ( SKP_int )counter;
        
        if( ( ( 1000 * smplsSinceLastPacket ) / API_fs_Hz ) == packetSize_ms ) {
            
            /* Finish up the range coder */
            ec_enc_done( &range_enc_celt_state );
            
            /* Sends a dummy zero size packet in case of DTX period  */
            /* to make it work with the decoder test program.        */
            /* In practice should be handled by RTP sequence numbers */
            totPackets++;
            sumBytes += nBytes;

            /* Write payload size */

            fwrite( &nBytes, sizeof( SKP_int32 ), 1, bitOutFile );


            /* Write payload */
            fwrite( range_buf, sizeof( SKP_uint8 ), nBytes, bitOutFile );
        

            smplsSinceLastPacket = 0;
        }
    }

    /* Write dummy because it can not end with 0 bytes */
    nBytes = -1;

    /* Write payload size */
    fwrite( &nBytes, sizeof( SKP_int32 ), 1, bitOutFile );

    /* Free Encoder */
    free( psEnc );

    fclose( speechInFile );
    fclose( bitOutFile   );

    filetime  = totPackets * 1e-3 * packetSize_ms;
    avg_rate  = 8.0 / packetSize_ms * sumBytes       / totPackets;
  //  act_rate  = 8.0 / packetSize_ms * sumActBytes    / totActPackets;
    if( !quiet ) {
    	printf( "Took %ld cycles to decode...\n", temp);
        printf( "\nFile length:                 %.3f s\n", filetime );
        printf( "\nAverage bitrate:             %.3f kbps\n", avg_rate  );
        printf( "\rPackets encoded:              %d\n", totPackets );
      //  printf( "\nActive bitrate:              %.3f kbps", act_rate  );

        printf( "\n\n" );
    }

    return 0;
}
