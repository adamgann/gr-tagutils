/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_TAGUTILS_TAG_TO_BYTE_C_IMPL_H
#define INCLUDED_TAGUTILS_TAG_TO_BYTE_C_IMPL_H

#include <tagutils/tag_to_byte_c.h>

namespace gr {
  namespace tagutils {

    class tag_to_byte_c_impl : public tag_to_byte_c
    {
     private:
		  std::vector<tag_t>::iterator d_tags_itr;
		  pmt::pmt_t d_key;
		  unsigned long d_offset;
      bool d_debug;

     public:
    	tag_to_byte_c_impl(const std::string &tag_key, bool debug);
    	~tag_to_byte_c_impl();

		  void set_tag_key(const std::string &tag_key);
    	void search_for_tag(int nread, int noutput);

    	int work(int noutput_items,
       gr_vector_const_void_star &input_items,
       gr_vector_void_star &output_items);
    };

  } // namespace tagutils
} // namespace gr

#endif /* INCLUDED_TAGUTILS_TAG_TO_BYTE_C_IMPL_H */

