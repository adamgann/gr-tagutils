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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "tag_thresh_switch_impl.h"

namespace gr {
  namespace tagutils {

    tag_thresh_switch::sptr
    tag_thresh_switch::make(size_t itemsize, const std::string &key_filter, 
                            double threshold, bool debug, bool above_if_equal)
    {
      return gnuradio::get_initial_sptr
        (new tag_thresh_switch_impl(itemsize, key_filter, threshold, debug, above_if_equal));
    }


    tag_thresh_switch_impl::tag_thresh_switch_impl(size_t itemsize, const std::string &key_filter, 
                                                    double threshold, bool debug, bool above_if_equal)
      : gr::sync_block("tag_thresh_switch",
              gr::io_signature::make(1, 1, itemsize),
              gr::io_signature::make2(2, 2, itemsize, itemsize)),
        d_itemsize(itemsize), d_debug(debug),d_above_if_equal(above_if_equal)
    {
        set_key_filter(key_filter);
        set_threshold(threshold);          
    }


    tag_thresh_switch_impl::~tag_thresh_switch_impl()
    {
    }

    void
    tag_thresh_switch_impl::set_key_filter(const std::string &key_filter)
    {
      if(key_filter == "")
        d_filter = pmt::PMT_NIL;
      else
        d_filter = pmt::intern(key_filter);
    }

    void
    tag_thresh_switch_impl::set_threshold(double threshold)
    {
       d_threshold = threshold;
    }


    int
    tag_thresh_switch_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *signal = (const char *) input_items[0];
        char *out_above = (char *) output_items[0];
        char *out_below = (char *) output_items[1];
        const unsigned int nread = nitems_read(0);
        std::vector<tag_t> t;

        /* Get the requested stream tag and its value */
        get_tags_in_range(t, 0, nread, nread + noutput_items,d_filter);
        for(d_tags_itr = t.begin(); d_tags_itr != t.end(); d_tags_itr++)
        {
            d_value = pmt::to_double(d_tags_itr->value);           
           
            if (d_value > d_threshold)
            {
                d_trigger = true;
                value_thresh_comp = ABOVE;  
            }
            else if (d_value < d_threshold)                         
            {
                d_trigger = false;
                value_thresh_comp = BELOW;
            }
            else                                                //Won't happen for floats, but covering all bases here.
            {
                value_thresh_comp = EQUAL;
            }
        }


        /* Output at either above or below depending on value and threshold */
        if (value_thresh_comp == ABOVE)
        {
            memcpy(out_above,signal,noutput_items*d_itemsize);
            memset(out_below, 0.0, noutput_items * output_signature()->sizeof_stream_item(0)); 
        }
        else if (value_thresh_comp == BELOW)
        {
            memcpy(out_below,signal,noutput_items*d_itemsize);
            memset(out_above, 0.0, noutput_items * output_signature()->sizeof_stream_item(0));     
        }
        else
        {
            if (d_above_if_equal)
            {
                memcpy(out_above,signal,noutput_items*d_itemsize);
                memset(out_below, 0.0, noutput_items * output_signature()->sizeof_stream_item(0)); 
            }
            else
            {
                memcpy(out_below,signal,noutput_items*d_itemsize);
                memset(out_above, 0.0, noutput_items * output_signature()->sizeof_stream_item(0)); 
            }

        }
        
        

        if (d_debug) 
        {
            std::cout<<"Key: " << d_filter<< 
            std::setw(10)<<"\tValue: " << d_value <<
            std::setw(10)<<"\tThreshold " << d_threshold << 
            std::setw(10)<<"\tTrigger: "<< ((value_thresh_comp == ABOVE) ? ("ABOVE") : ("BELOW")) << std::endl;
        } //if debug


        return noutput_items;
    }

  } /* namespace tagutils */
} /* namespace gr */

