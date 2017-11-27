# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND dvbs2correlator_sources
    diff_decode_cc_impl.cc
    correlate_cf_impl.cc
)

set(dvbs2correlator_sources "${dvbs2correlator_sources}" PARENT_SCOPE)
if(NOT dvbs2correlator_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT dvbs2correlator_sources)

add_library(gnuradio-dvbs2correlator SHARED ${dvbs2correlator_sources})
target_link_libraries(gnuradio-dvbs2correlator ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-dvbs2correlator PROPERTIES DEFINE_SYMBOL "gnuradio_dvbs2correlator_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-dvbs2correlator PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-dvbs2correlator RUNTIME_COMPONENT "dvbs2correlator_runtime" DEVEL_COMPONENT "dvbs2correlator_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_dvbs2correlator_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_dvbs2correlator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_dvbs2correlator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_correlate_cf.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_diff_decode_cc.cc
)

add_executable(test-dvbs2correlator ${test_dvbs2correlator_sources})

target_link_libraries(
  test-dvbs2correlator
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-dvbs2correlator
)

GR_ADD_TEST(test_dvbs2correlator test-dvbs2correlator)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

