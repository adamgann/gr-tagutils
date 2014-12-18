/* -*- c++ -*- */

#define TAGUTILS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "tagutils_swig_doc.i"

%{
#include "tagutils/tag_thresh_switch.h"
#include "tagutils/tag_extract_cc.h"

#include "tagutils/tag_at_offset_ss.h"
#include "tagutils/tag_at_offset_ii.h"
#include "tagutils/tag_at_offset_ff.h"
#include "tagutils/tag_at_offset_cc.h"
#include "tagutils/tag_at_offset_bb.h"

#include "tagutils/tag_to_byte_sb.h"
#include "tagutils/tag_to_byte_ib.h"
#include "tagutils/tag_to_byte_fb.h"
#include "tagutils/tag_to_byte_cb.h"
#include "tagutils/tag_to_byte_bb.h"
%}


%include "tagutils/tag_thresh_switch.h"
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_thresh_switch);



%include "tagutils/tag_extract_cc.h"
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_extract_cc);


%include "tagutils/tag_at_offset_ss.h"
%include "tagutils/tag_at_offset_ii.h"
%include "tagutils/tag_at_offset_ff.h"
%include "tagutils/tag_at_offset_cc.h"
%include "tagutils/tag_at_offset_bb.h"

%include "tagutils/tag_to_byte_sb.h"
%include "tagutils/tag_to_byte_ib.h"
%include "tagutils/tag_to_byte_fb.h"
%include "tagutils/tag_to_byte_cb.h"
%include "tagutils/tag_to_byte_bb.h"


GR_SWIG_BLOCK_MAGIC2(tagutils, tag_at_offset_ss);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_at_offset_ii);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_at_offset_ff);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_at_offset_cc);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_at_offset_bb);

GR_SWIG_BLOCK_MAGIC2(tagutils, tag_to_byte_sb);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_to_byte_ib);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_to_byte_fb);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_to_byte_cb);
GR_SWIG_BLOCK_MAGIC2(tagutils, tag_to_byte_bb);


