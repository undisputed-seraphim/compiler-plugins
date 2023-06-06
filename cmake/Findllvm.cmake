# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.
#[=======================================================================[.rst:
Findclang
-------

Finds the clang library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``clang::plugin``
  The clang plugin library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``clang_FOUND``
  True if the system has the clang library.
``clang_VERSION``
  The version of the clang library which was found.

#]=======================================================================]
find_path(_llvm_INCLUDE_DIR
    NAMES "clang/Basic/LLVM.h"
    PATHS "/usr/lib/llvm-${llvm_FIND_VERSION_MAJOR}/include"
)

find_library(_llvm_LIBRARY
    NAMES "clang-${llvm_FIND_VERSION_MAJOR}"
    PATH_SUFFIXES "llvm-${llvm_FIND_VERSION_MAJOR}/lib"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(llvm
    FOUND_VAR llvm_FOUND
    REQUIRED_VARS _llvm_LIBRARY _llvm_INCLUDE_DIR
    VERSION_VAR ${PACKAGE_FIND_VERSION_MAJOR}
)

if (NOT llvm_FOUND)
  message(WARNING "llvm ${llvm_FIND_VERSION} not found.")
  return()
endif()

if (NOT llvm::llvm)
  add_library(llvm::llvm SHARED IMPORTED)
  set_target_properties(llvm::llvm PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${_llvm_INCLUDE_DIR}
      IMPORTED_LOCATION ${_llvm_LIBRARY}
  )

  find_library(clangBasic_LIBRARY NAMES "clangBasic" PATH_SUFFIXES "llvm-${llvm_FIND_VERSION_MAJOR}/lib")
  add_library(clang::Basic STATIC IMPORTED)
  set_target_properties(clang::Basic PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${_llvm_INCLUDE_DIR}
      IMPORTED_LOCATION ${clangBasic_LIBRARY}
      INTERFACE_LINK_LIBRARIES llvm::llvm
  )

  find_library(clangAST_LIBRARY NAMES "clangAST" PATH_SUFFIXES "llvm-${llvm_FIND_VERSION_MAJOR}/lib")
  add_library(clang::AST STATIC IMPORTED)
  set_target_properties(clang::AST PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${_llvm_INCLUDE_DIR}
      IMPORTED_LOCATION ${clangAST_LIBRARY}
      INTERFACE_LINK_LIBRARIES clang::Basic
  )

  find_library(clangTooling_LIBRARY NAMES "clangTooling" PATH_SUFFIXES "llvm-${llvm_FIND_VERSION_MAJOR}/lib")
  add_library(clang::Tooling STATIC IMPORTED)
  set_target_properties(clang::Tooling PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${_llvm_INCLUDE_DIR}
      IMPORTED_LOCATION ${clangTooling_LIBRARY}
      INTERFACE_LINK_LIBRARIES clang::AST
  )
endif()

mark_as_advanced(_llvm_INCLUDE_DIR _llvm_plugin_LIBRARY)
