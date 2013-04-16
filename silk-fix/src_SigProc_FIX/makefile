# our first makefile - version 3
#-------------------------------

CC=gcc
INCLUDE= -I. -I../interface/ -I../src_FIX/ -I../src_SigProc_FIX/ -I../src_common/    -I../../celt/libcelt/
CFLAGS = -std=c99 -c -g -Wall -pg
CONFIG = -DFIXED_POINT
LIBS=-lm

OBJECTS =    SKP_Silk_A2NLSF.o \
	 SKP_Silk_ana_filt_bank_1.o \
	 SKP_Silk_apply_sine_window.o \
	 SKP_Silk_array_maxabs.o \
	 SKP_Silk_autocorr.o \
	 SKP_Silk_biquad_alt.o \
	 SKP_Silk_burg_modified.o \
	 SKP_Silk_bwexpander_32.o \
	 SKP_Silk_bwexpander.o \
	 SKP_Silk_debug.o \
	 SKP_Silk_decode_pitch.o \
	 SKP_Silk_inner_prod_aligned.o \
	 SKP_Silk_k2a.o \
	 SKP_Silk_k2a_Q16.o \
	 SKP_Silk_lin2log.o \
	 SKP_Silk_log2lin.o \
	 SKP_Silk_LPC_analysis_filter.o \
	 SKP_Silk_LPC_inv_pred_gain.o \
	 SKP_Silk_LPC_stabilize.o \
	 SKP_Silk_LPC_synthesis_filter.o \
	 SKP_Silk_LPC_synthesis_order16.o \
	 SKP_Silk_LSF_cos_table.o \
	 SKP_Silk_NLSF2A.o \
	 SKP_Silk_NLSF_stabilize.o \
	 SKP_Silk_NLSF_VQ_weights_laroia.o \
	 SKP_Silk_pitch_analysis_core.o \
	 SKP_Silk_pitch_est_tables.o \
	 SKP_Silk_resampler.o \
	 SKP_Silk_resampler_down2_3.o \
	 SKP_Silk_resampler_down2.o \
	 SKP_Silk_resampler_down3.o \
	 SKP_Silk_resampler_private_AR2.o \
	 SKP_Silk_resampler_private_ARMA4.o \
	 SKP_Silk_resampler_private_copy.o \
	 SKP_Silk_resampler_private_down4.o \
	 SKP_Silk_resampler_private_down_FIR.o \
	 SKP_Silk_resampler_private_IIR_FIR.o \
	 SKP_Silk_resampler_private_up2_HQ.o \
	 SKP_Silk_resampler_private_up4.o \
	 SKP_Silk_resampler_rom.o \
	 SKP_Silk_resampler_up2.o \
	 SKP_Silk_scale_copy_vector16.o \
	 SKP_Silk_scale_vector.o \
	 SKP_Silk_schur64.o \
	 SKP_Silk_schur.o \
	 SKP_Silk_sigm_Q15.o \
	 SKP_Silk_sort.o \
	 SKP_Silk_sum_sqr_shift.o \
	
all:$(OBJECTS)
	mv $(OBJECTS) ../source
%.o: %.c 
	$(CC) $(CFLAGS) $(CONFIG)  $(INCLUDE) $(LIBS)  $< -o  $@ 

clean:
	rm *.o 
