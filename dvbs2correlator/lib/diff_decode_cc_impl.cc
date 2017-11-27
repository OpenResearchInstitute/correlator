/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "diff_decode_cc_impl.h"

#include <complex.h>

namespace gr {
namespace dvbs2correlator {

    diff_decode_cc::sptr
    diff_decode_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new diff_decode_cc_impl());
    }

    /*
     * The private constructor
     */
    diff_decode_cc_impl::diff_decode_cc_impl()
      : gr::block("diff_decode_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
	set_history(2);
	}

    /*
     * Our virtual destructor.
     */
    diff_decode_cc_impl::~diff_decode_cc_impl()
    {
    }

    void
    diff_decode_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	ninput_items_required[0] = noutput_items+1;
    }

    int
    diff_decode_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
	printf("-=-=-=-=-=-=Differential Decode Work Function.\n");
	
	for(int i = 0; i < noutput_items; i++) {
		gr_complex delayed  = in[i];
		gr_complex current_sample = in[i+1];
		printf("delayed is %f + %fj\n", delayed.real(), delayed.imag());
		printf("current is %f + %fj\n", current_sample.real(), current_sample.imag());
		gr_complex for_printing = conj(current_sample);	
		printf("conjugate is %f + %fj\n", for_printing.real(), for_printing.imag()); 	
		out[i] = delayed * for_printing;	
		//out[i] = delayed * conj(current_sample); 
		printf("output number %d is %f + %fj\n\n", i, out[i].real(), out[i].imag());


	}

	printf("-=-=-=-=-=-=-=Differential Decode Work Function Ends.\n");

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dvbs2correlator */
} /* namespace gr */

