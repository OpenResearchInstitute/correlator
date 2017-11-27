/* -*- c++ -*- */
/* 
 * Copyright 2017 Phase 4 Ground.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "correlate_cf_impl.h"

#include <complex.h>
#include <vector>

namespace gr {
  namespace dvbs2correlator {

    correlate_cf::sptr
    correlate_cf::make()
    {
      return gnuradio::get_initial_sptr
        (new correlate_cf_impl());
    }

    /*
     * The private constructor
     */
    correlate_cf_impl::correlate_cf_impl()
      : gr::block("correlate_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
	set_history(1);
	}

    /*
     * Our virtual destructor.
     */
    correlate_cf_impl::~correlate_cf_impl()
    {
    }

    void
    correlate_cf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	ninput_items_required[0] = noutput_items;
    }

    int
    correlate_cf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];

	size_t PLSC_size = 64;
	size_t PLSC_coeff_size = 32;
	size_t SOF_size = 25;

//the SOF from DVB-S2 is 018D2E82 in hex. This is the logical representation. !!!change to differentially encoded symbols.
     
	 // Do <+signal processing+>
	printf("-=-=-=-=-=-=-=-=-=-Correlate Work Function.\n");
	//we use vectors to represent the shift registers and taps. !!!Inits to zero?
	static std::vector<gr_complex> PLSC(PLSC_size); //PLSC Physical Layer Signalling Code	
	static std::vector<gr_complex> SOF(SOF_size);   //SOF Start of Frame fixed code we're searching for
//!!!we're going to need an array of 128 vectors for brute forcing the PLSCODE in the ACM version of the correlator

	for(int i = 0; i < noutput_items; i++) {
		//start at the end of the shift register and make the shifts
		//make a loop that shifts the ones that can be easily represented in a loop
		for(int r = SOF_size-1; r > 0; r--) {
			SOF[r] = SOF[r-1];
			//SOF[24] = SOF[23];
			//SOF[23] = SOF[22];
			//SOF[22] = SOF[21];
			//...
			//SOF[3] = SOF[2];
			//SOF[2] = SOF[1];
			//SOF[1] = SOF[0];
			//printf("SOF[%d] = SOF[%d] = %f %fj\n", r, r-1, SOF[r].real(), SOF[r].imag());	
		}
		SOF[0] = in[i];
		//printf("SOF[%d] = in[%d] = %f %fj\n", 0, i, in[i].real(), in[i].imag());	
		//018D2E82	
		//out[i] = SOF[0].real()*(0-ij)+SOF[1].real()* 
		//printf("out[%d] = %f\n", i, out[i]);
	} //for loop with i
	printf("-=-=-=-=-=-=-=-=-=Correlate Work Function Ends.\n");


      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dvbs2correlator */
} /* namespace gr */

