#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Thu Dec 18 13:46:28 2014
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import messageutils
import tagutils
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.data_vector = data_vector = [1]*1000
        self.samp_rate = samp_rate = 32000
        self.packet_len_tag = packet_len_tag = "packet_len"
        self.len_data = len_data = len(data_vector)

        ##################################################
        # Blocks
        ##################################################
        self.tagutils_tag_to_byte_xb_0 = tagutils.tag_to_byte_cb("packet_len", False)
        self.messageutils_vector_pdu_xx_0 = messageutils.vector_pdu_source_b(data_vector, 1000, False, True, 0)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc(([-1,1]), 1)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_pdu_to_tagged_stream_1 = blocks.pdu_to_tagged_stream(blocks.byte_t, packet_len_tag)
        self.blocks_file_sink_1 = blocks.file_sink(gr.sizeof_char*1, "/tmp/tag.dat", False)
        self.blocks_file_sink_1.set_unbuffered(True)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, "/tmp/data.dat", False)
        self.blocks_file_sink_0.set_unbuffered(True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_pdu_to_tagged_stream_1, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.tagutils_tag_to_byte_xb_0, 0))
        self.connect((self.tagutils_tag_to_byte_xb_0, 0), (self.blocks_file_sink_1, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.messageutils_vector_pdu_xx_0, "pdus", self.blocks_pdu_to_tagged_stream_1, "pdus")


    def get_data_vector(self):
        return self.data_vector

    def set_data_vector(self, data_vector):
        self.data_vector = data_vector
        self.set_len_data(len(self.data_vector))
        self.messageutils_vector_pdu_xx_0.set_vec(self.data_vector)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_packet_len_tag(self):
        return self.packet_len_tag

    def set_packet_len_tag(self, packet_len_tag):
        self.packet_len_tag = packet_len_tag

    def get_len_data(self):
        return self.len_data

    def set_len_data(self, len_data):
        self.len_data = len_data

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()
