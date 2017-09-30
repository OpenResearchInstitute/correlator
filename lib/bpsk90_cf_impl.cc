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
#include "bpsk90_cf_impl.h"
#include <stdio.h>
#include <cmath>
namespace gr {
  namespace howto {

    bpsk90_cf::sptr
    bpsk90_cf::make()
    {
      return gnuradio::get_initial_sptr
        (new bpsk90_cf_impl());
    }

    /*
     * The private constructor
     */
    bpsk90_cf_impl::bpsk90_cf_impl()
      : gr::block("bpsk90_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
	set_history(2);
	//If you choose a larger value, N, this means your output
	//item is calculated from the current input item and from
	//the N-1 previous input items.
    	//Paul thinks this is badly worded.
    }

    /*
     * Our virtual destructor.
     */
    bpsk90_cf_impl::~bpsk90_cf_impl()
    {
    }

    void
    bpsk90_cf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items+1; 
	//depends on whether we have to take history into account
	//or it's automagical. 
    }

    int
    bpsk90_cf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];

	float mega[] = {0.0, 1.0, -1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, -1.0, 0.0, -1.0, 1.0, 0.0};
	printf("We are starting work\n");
	for(int i = 0; i < noutput_items; i++) {
		//input 0 and 1 and output at 0
		gr_complex previous_input = in[i];
		gr_complex current_input = in[i+1];
		//Identify the quadrant transition between
		//previous_input and current_input.

	int tesla = (!!std::signbit(previous_input.real()))*8 + (!!std::signbit(previous_input.imag()))*4 + (!!std::signbit(current_input.real()))*2 + (!!std::signbit(current_input.imag()));
	
	out[i] = mega[tesla];	

	printf("i = %d prev = %f %fi curr = %f %fi TESLA! %d Power! %f\n",i, previous_input.real(), previous_input.imag(), current_input.real(), current_input.imag(), tesla, mega[tesla]);











/*
		bool up = false;
		bool dn = false;
		bool rt = false;
		bool lt = false;
		bool cw = false;
		bool ccw = false;
	
		if((previous_input.imag() < 0) && (current_input.imag() > 0)){
			up = true;
			}
		if((previous_input.imag() > 0) && (current_input.imag() < 0)){
			dn = true;
			}
		if((previous_input.real() < 0) && (current_input.real() > 0)){
			rt = true;
			}
		if((previous_input.real() > 0) && (current_input.real() < 0)){
			lt = true;
			}	
		if(up && rt){
			cw = true;
			}
		if(dn && lt){
			cw = true;
			}
		if(up && lt){
			ccw = true;
			}
		if(dn && rt){
			ccw = true;
			}		
		//1 if cw, -1 if ccw, 0 if neither
		if(cw){
			out[i-1] = 1.0;
			}
		else if(ccw){
			out[i-1] = -1.0;
			}
		else{
			out[i-1] = 0.0;
			}
	
	printf("prev = %f %fi curr = %f %fi up = %d dn = %d lt = %d rt = %d cw = %d ccw = %d out[%d] = %f\n", previous_input.real(), previous_input.imag(), current_input.real(), current_input.imag(), up, dn, lt, rt, cw, ccw, i-1, out[i-1]);
*/
	}
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace howto */
} /* namespace gr */

