/* -*- c++ -*- */

#define DVBS2CORRELATOR_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dvbs2correlator_swig_doc.i"

%{
#include "dvbs2correlator/diff_decode_cc.h"
#include "dvbs2correlator/correlate_cf.h"
%}


%include "dvbs2correlator/diff_decode_cc.h"
GR_SWIG_BLOCK_MAGIC2(dvbs2correlator, diff_decode_cc);
%include "dvbs2correlator/correlate_cf.h"
GR_SWIG_BLOCK_MAGIC2(dvbs2correlator, correlate_cf);
