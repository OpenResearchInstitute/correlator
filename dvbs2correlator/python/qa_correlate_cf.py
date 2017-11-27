#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 Phase 4 Ground.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import dvbs2correlator_swig as dvbs2correlator

class qa_correlate_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	#SOF Correlator Test
	
	#This needs to be a string of data with the SOF in it

	src_data = ()
     
 	#src_data =   (0+0j, 1+0j, 1+0j, 0+0j, 0+0j, 0+0j, 1+0j, 1+0j, 0+0j, 1+0j, 0+0j, 0+0j, 1+0j, 0+0j, 1+0j, 1+0j, 1+0j, 0+0j, 1+0j, 0+0j, 0+0j, 0+0j, 0+0j, 0+0j, 1+0j, 0+0j) 
	#currently this is wrong

	expected_result = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) 
	 # set up fg
	#why doesn't it stop when it runs out of source data?
	src = blocks.vector_source_c(src_data)
	diff = dvbs2correlator.diff_decode_cc()
	corr = dvbs2correlator.correlate_cf()
	dst = blocks.vector_sink_f()
	self.tb.connect(src, diff)
	self.tb.connect(diff, corr)
	self.tb.connect(corr, dst)
        self.tb.run()
        # check data
	result_data = dst.data()
	self.assertFloatTuplesAlmostEqual(expected_result, result_data, 1)

if __name__ == '__main__':
    gr_unittest.run(qa_correlate_cf, "qa_correlate_cf.xml")
