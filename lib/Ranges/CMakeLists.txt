add_library(RangesLib STATIC Ranges.cpp Ranges.hpp)

target_include_directories(RangesLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
