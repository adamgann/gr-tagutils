/* -*- c++ -*- */
/* 
 * Copyright 2014 Adam Gannon.
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

#ifndef INCLUDED_TAGUTILS_TAG_THRESH_SWITCH_IMPL_H
#define INCLUDED_TAGUTILS_TAG_THRESH_SWITCH_IMPL_H

#include <tagutils/tag_thresh_switch.h>

namespace gr {
  namespace tagutils {

    class tag_thresh_switch_impl : public tag_thresh_switch
    {
     private:
        size_t d_itemsize;
        bool d_debug;      
        pmt::pmt_t d_filter;
        bool d_trigger;
        double d_threshold;
        std::vector<tag_t>::iterator d_tags_itr;
        double d_value;
        value_thresh_comp_type value_thresh_comp;
        bool d_above_if_equal;
        

     public:
        tag_thresh_switch_impl(size_t itemsize, const std::string &key_filter, double threshold, 
                               bool debug, bool above_if_equal);
        ~tag_thresh_switch_impl();

        void set_key_filter(const std::string &key_filter="");
        void set_threshold(double threshold);

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace tagutils
} // namespace gr

#endif /* INCLUDED_TAGUTILS_TAG_THRESH_SWITCH_IMPL_H */

