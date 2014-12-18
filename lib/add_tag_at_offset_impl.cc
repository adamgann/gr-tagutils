/* -*- c++ -*- */
/* 
 * Copyright 2014 Adam Gannon
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
#include "add_tag_at_offset_impl.h"

namespace gr {
  namespace tagutils {

    add_tag_at_offset::sptr
    add_tag_at_offset::make(const std::string &tag_key, const std::vector<unsigned int> &tag_offset, unsigned int tag_value, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new add_tag_at_offset_impl(tag_key, tag_offset, tag_value, debug));
    }


    add_tag_at_offset_impl::add_tag_at_offset_impl(const std::string &tag_key, const std::vector<unsigned int> &tag_offset, 
                                                    unsigned int tag_value, bool debug)
      : gr::sync_block("add_tag_at_offset",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(gr_complex))),
              d_offset(tag_offset), d_val(tag_value), d_debug(debug), d_index(0)
    {
      
      set_key(tag_key);
      d_offset_size = d_offset.size();
      
      if (d_debug) std::cout<<"Offset Size is "<<d_offset_size<<std::endl;

    }


    add_tag_at_offset_impl::~add_tag_at_offset_impl()
    {
    }

    void
    add_tag_at_offset_impl::set_key(const std::string &tag_key)
    {
      if(tag_key == "")
        d_key = pmt::PMT_NIL;
      else
        d_key = pmt::intern(tag_key);
    }
    
    void
    add_tag_at_offset_impl::check_and_place_tag(unsigned int nwritten, unsigned int noutput)
    {
      while(d_index<d_offset_size)
      {
        
        if ((d_offset[d_index] > nwritten) && (d_offset[d_index] < (nwritten+noutput)))
        {         
          if (d_debug) std::cout<<"Added tag at offset: "<<d_offset[d_index]<<std::endl;
          
          add_item_tag(0, d_offset[d_index], d_key, pmt::from_long(d_val),pmt::string_to_symbol(name()));
          d_index++;
        }
        else
        {
          return;
        }
        
      }//while
      
    }



    int
    add_tag_at_offset_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

       
        unsigned int nwritten = nitems_written(0);
        
        check_and_place_tag(nwritten,noutput_items);
        
        /*
        if ((d_offset[d_index] > nwritten) && (d_offset[d_index] < (nwritten+noutput_items)))
        {

          if (d_debug)
          {
            std::cout<<"Adding tag at: "<<d_offset[d_index]<<std::endl;
          }  
          
          add_item_tag(0, d_offset[d_index], d_key, pmt::from_long(d_val),pmt::string_to_symbol(name()));

        }  
        */     

        memcpy(out,in,noutput_items*sizeof(gr_complex));

        return noutput_items;
        
    }

  } /* namespace tagutils */
} /* namespace gr */

