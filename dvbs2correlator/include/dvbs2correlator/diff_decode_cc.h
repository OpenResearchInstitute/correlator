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


#ifndef INCLUDED_DVBS2CORRELATOR_DIFF_DECODE_CC_H
#define INCLUDED_DVBS2CORRELATOR_DIFF_DECODE_CC_H

#include <dvbs2correlator/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dvbs2correlator {

    /*!
     * \brief <+description of block+>
     * \ingroup dvbs2correlator
     *
     */
    class DVBS2CORRELATOR_API diff_decode_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<diff_decode_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dvbs2correlator::diff_decode_cc.
       *
       * To avoid accidental use of raw pointers, dvbs2correlator::diff_decode_cc's
       * constructor is in a private implementation
       * class. dvbs2correlator::diff_decode_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace dvbs2correlator
} // namespace gr

#endif /* INCLUDED_DVBS2CORRELATOR_DIFF_DECODE_CC_H */

