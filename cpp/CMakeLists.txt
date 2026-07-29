# ===============================================================================================
# bar project
cmake_minimum_required(VERSION 3.21)
project(Bar VERSION "0.0.1")
# ===============================================================================================
# options
include(FeatureSummary)
option(BUILD_SHARED_LIBS "Build Bar with shared libraries." ON)
add_feature_info(BUILD_SHARED_LIBS BUILD_SHARED_LIBS "Build Bar with shared libraries.")


# ===============================================================================================
# bar requires dolfinx
find_package(DOLFINX REQUIRED CONFIG)

if(DOLFINX_FOUND)
  message(STATUS "Found DOLFINx at ${DOLFINX_DIR}")
endif()


# ===============================================================================================
# dolfinx version add to build process if dolfinx found
if(DOLFINX_FOUND)
   add_library(BAR)
   target_link_libraries(BAR PUBLIC dolfinx)
   target_compile_features(BAR PUBLIC cxx_std_20)
   target_compile_definitions(BAR PUBLIC BAR_VERSION="${Bar_VERSION}")
   set_target_properties(
      BAR
      PROPERTIES VERSION ${Bar_VERSION}
      SOVERSION ${Bar_VERSION_MAJOR}.${Bar_VERSION_MINOR}
   )
   target_sources(
      BAR
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/foo.cc
   )
   set(HEADERS_Bar
      ${CMAKE_CURRENT_SOURCE_DIR}/foo.h
   )
   target_include_directories(
      BAR
      PUBLIC
      $<INSTALL_INTERFACE:include>
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
   )
   install(
      TARGETS BAR
      EXPORT BarTargets
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeExecutables
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
   )
   install(
      FILES ${HEADERS_Bar}
      DESTINATION include/bar
      COMPONENT Development
   )

endif()

# ===============================================================================================
# packaging
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/BarConfigVersion.cmake
  VERSION ${Bar_VERSION}
  COMPATIBILITY ExactVersion
)
configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/BarConfig.cmake.in
   ${CMAKE_BINARY_DIR}/BarConfig.cmake
   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bar
)
# ===============================================================================================
# instalation
install(
  FILES ${CMAKE_BINARY_DIR}/BarConfig.cmake
        ${CMAKE_BINARY_DIR}/BarConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
  COMPONENT Development
)
install(EXPORT BarTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
