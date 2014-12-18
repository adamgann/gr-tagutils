# Copyright 2011,2012 Free Software Foundation, Inc.
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
include(GrMiscUtils)
GR_EXPAND_X_CC_H_IMPL(tagutils tag_at_offset_XX   ss ii ff cc bb)
GR_EXPAND_X_CC_H_IMPL(tagutils tag_to_byte_Xb   s i f c b)

include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND tagutils_sources
    ${generated_sources}
    tag_thresh_switch_impl.cc
    tag_to_byte_c_impl.cc
    tag_to_byte_f_impl.cc
    tag_to_byte_b_impl.cc
    tag_extract_cc_impl.cc
)

add_library(gnuradio-tagutils SHARED ${tagutils_sources})
add_dependencies(gnuradio-tagutils tagutils_generated_includes tagutils_generated_swigs)
target_link_libraries(gnuradio-tagutils ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES})
set_target_properties(gnuradio-tagutils PROPERTIES DEFINE_SYMBOL "gnuradio_tagutils_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-tagutils
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_tagutils_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_tagutils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_tagutils.cc
)

add_executable(test-tagutils ${test_tagutils_sources})

target_link_libraries(
  test-tagutils
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-tagutils
)

GR_ADD_TEST(test_tagutils test-tagutils)
