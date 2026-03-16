find_path(OPENAUTO_INCLUDE_DIR
    f1x/openauto/Common/Log.hpp
    PATHS /usr/local /usr
    PATH_SUFFIXES include
)

find_library(OPENAUTO_LIB_DIR
    NAMES openauto
    PATHS /usr/local /usr
    PATH_SUFFIXES lib
)

if (OPENAUTO_INCLUDE_DIR AND OPENAUTO_LIB_DIR)
    set(OPENAUTO_FOUND TRUE)
endif()
  
if (OPENAUTO_FOUND)
    if (NOT openauto_FIND_QUIETLY)
        message(STATUS "Found openauto:")
        message(STATUS " - Includes: ${OPENAUTO_INCLUDE_DIR}")
        message(STATUS " - Libraries: ${OPENAUTO_LIB_DIR}")
    endif()
    add_library(openauto INTERFACE)
    target_include_directories(openauto INTERFACE ${OPENAUTO_INCLUDE_DIR}) 
    target_link_libraries(openauto INTERFACE ${OPENAUTO_LIB_DIR})
else()
    if (openauto_FIND_REQUIRED)
               message(FATAL_ERROR "Could not find openauto")
    endif()
endif()

mark_as_advanced(OPENAUTO_INCLUDE_DIRS OPENAUTO_LIBRARIES)