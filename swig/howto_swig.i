/* -*- c++ -*- */

#define HOWTO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
#include "howto/square_ff.h"
#include "howto/bpsk90_cf.h"
%}


%include "howto/square_ff.h"
GR_SWIG_BLOCK_MAGIC2(howto, square_ff);
%include "howto/bpsk90_cf.h"
GR_SWIG_BLOCK_MAGIC2(howto, bpsk90_cf);
