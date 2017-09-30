#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/abraxas3d/gr-howto/python
export PATH=/home/abraxas3d/gr-howto/build/python:$PATH
export LD_LIBRARY_PATH=/home/abraxas3d/gr-howto/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/abraxas3d/gr-howto/build/swig:$PYTHONPATH
/usr/bin/python2 /home/abraxas3d/gr-howto/python/qa_bpsk90_cf.py 
