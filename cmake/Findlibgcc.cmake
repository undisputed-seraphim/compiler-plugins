# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.
#[=======================================================================[.rst:
Findlibgcc
-------

Finds the libgcc library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``libgcc::plugin``
  The libgcc plugin library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``libgcc_FOUND``
  True if the system has the libgcc library.
``libgcc_VERSION``
  The version of the libgcc library which was found.

#]=======================================================================]

find_path(libgcc_plugin_INCLUDE_DIR NAMES "gcc.h" PATHS "/usr/${CMAKE_SHARED_LIBRARY_PREFIX}/gcc/${CMAKE_C_LIBRARY_ARCHITECTURE}/${libgcc_FIND_VERSION_MAJOR}/plugin/include")

find_library(libgcc_plugin_LIBRARY NAMES "cc1plugin" PATH_SUFFIXES "gcc/${CMAKE_C_LIBRARY_ARCHITECTURE}/${libgcc_FIND_VERSION_MAJOR}/plugin")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libgcc
    FOUND_VAR libgcc_FOUND
    REQUIRED_VARS libgcc_plugin_LIBRARY libgcc_plugin_INCLUDE_DIR
    VERSION_VAR ${PACKAGE_FIND_VERSION_MAJOR}
)

if (libgcc_FOUND AND NOT libgcc::plugin)
    add_library(libgcc::plugin UNKNOWN IMPORTED)
    set_target_properties(libgcc::plugin PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${libgcc_plugin_INCLUDE_DIR}
        IMPORTED_LOCATION ${libgcc_plugin_LIBRARY}
    )
endif()

mark_as_advanced(libgcc_plugin_INCLUDE_DIR libgcc_plugin_LIBRARY)
