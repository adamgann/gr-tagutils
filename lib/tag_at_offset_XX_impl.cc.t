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
#include <@NAME_IMPL@.h>

namespace gr {
  namespace tagutils {

    @NAME@::sptr
    @NAME@::make(const std::string &tag_key, const std::vector<unsigned int> &tag_offset, unsigned int tag_value, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new @NAME_IMPL@(tag_key, tag_offset, tag_value, debug));
    }


    @NAME_IMPL@::@NAME_IMPL@(const std::string &tag_key, const std::vector<unsigned int> &tag_offset, 
                                                    unsigned int tag_value, bool debug)
      : gr::sync_block("@NAME@",
              gr::io_signature::make(1,1, sizeof(@I_TYPE@)),
              gr::io_signature::make(1,1, sizeof(@O_TYPE@))),
              d_offset(tag_offset), d_val(tag_value), d_debug(debug), d_index(0)
    {
      
      set_key(tag_key);
      d_offset_size = d_offset.size();
      
      if (d_debug) std::cout<<"Offset Size is "<<d_offset_size<<std::endl;

    }


    @NAME_IMPL@::~@NAME_IMPL@()
    {
    }

    void
    @NAME_IMPL@::set_key(const std::string &tag_key)
    {
      if(tag_key == "")
        d_key = pmt::PMT_NIL;
      else
        d_key = pmt::intern(tag_key);
    }
    
    void
    @NAME_IMPL@::check_and_place_tag(unsigned int nwritten, unsigned int noutput)
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
    @NAME_IMPL@::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        @I_TYPE@ *in = (@I_TYPE@ *) input_items[0];
        @O_TYPE@ *out = (@O_TYPE@ *) output_items[0];

       
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

        memcpy(out,in,noutput_items*sizeof(@I_TYPE@));

        return noutput_items;
        
    }

  } /* namespace tagutils */
} /* namespace gr */

