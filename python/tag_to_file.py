#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr
from gnuradio import blocks

import tagutils

class tag_to_file(gr.hier_block2):
    """
    docstring for block tag_to_file
    """
    def __init__(self,data_size,tag_key,file_name):
        gr.hier_block2.__init__(self,
            "tag_to_file",
            gr.io_signature(1,1, data_size),  # Input signature
            gr.io_signature(0,0,0)) # Output signature

        # Setup File Sink  
        self.file_sink = blocks.file_sink(gr.sizeof_char,file_name,False)
        self.file_sink.set_unbuffered(True)
        open_return = self.file_sink.open(file_name)

        # Make correct version of tag to byte
        if (data_size == gr.sizeof_gr_complex):
          self.tag_to_byte = tagutils.tag_to_byte_cb(tag_key,False)
        elif (data_size == gr.sizeof_float):
          self.tag_to_byte = tagutils.tag_to_byte_fb(tag_key,False)
        elif (data_size == gr.sizeof_char):
          self.tag_to_byte = tagutils.tag_to_byte_bb(tag_key,False)
        elif (data_size == gr.sizeof_int):
          self.tag_to_byte = tagutils.tag_to_byte_ib(tag_key,False)
        elif (data_size == gr.sizeof_short):
          self.tag_to_byte = tagutils.tag_to_byte_sb(tag_key,False)
        else:
          print "Invalid Data Type. I don't know how you got here, honestly."


        # Define blocks and connect them
        self.connect(self,self.tag_to_byte)
        self.connect(self.tag_to_byte,self.file_sink)


