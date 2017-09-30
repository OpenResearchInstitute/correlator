#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/abraxas3d/gr-howto/lib
export PATH=/home/abraxas3d/gr-howto/build/lib:$PATH
export LD_LIBRARY_PATH=/home/abraxas3d/gr-howto/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-howto 
