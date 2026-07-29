# ===============================================================================================
# Bar warper project
cmake_minimum_required(VERSION 3.21)

project(bar_nanobind)

include(FeatureSummary)
option(CMAKE_INSTALL_RPATH_USE_LINK_PATH "Add paths to linker search and installed rpath." ON)
add_feature_info(CMAKE_INSTALL_RPATH_USE_LINK_PATH CMAKE_INSTALL_RPATH_USE_LINK_PATH "Add paths to linker search and installed rpath.")

# ===============================================================================================
# nanobind 
find_package(Python COMPONENTS Interpreter Development REQUIRED)
# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)
#list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

# ===============================================================================================
# get target that will be binded
find_package(Bar REQUIRED CONFIG)

if(Bar_FOUND)
   message(STATUS "Found Bar at ${Bar_DIR}")
endif()
if (TARGET BAR)
   get_target_property(barinc BAR INTERFACE_INCLUDE_DIRECTORIES)
   get_target_property(bardef BAR INTERFACE_COMPILE_DEFINITIONS)
endif()

# ===============================================================================================
# Create the binding library nanobind handles its own calls to
# target_link_libraries
nanobind_add_module(
  bar_cpp
  binding/bar.cc
)
target_sources(bar_cpp PRIVATE 
   binding/bar.cc
)
target_link_libraries(bar_cpp PRIVATE BAR)
target_compile_definitions(bar_cpp PRIVATE ${bardef})
target_include_directories(bar_cpp PRIVATE ${barinc})
get_target_property(bardef bar_cpp COMPILE_DEFINITIONS)
message(STATUS "Inherited definition ${bardef}")

# Check for dolfinx python api
execute_process(
   COMMAND ${Python_EXECUTABLE} -c
          "import dolfinx; print(dolfinx.get_include())"
   OUTPUT_VARIABLE SDOLFINX_INCLUDE_DIR
   RESULT_VARIABLE SDOLFINX_COMMAND_RESULT
   ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(NOT SDOLFINX_COMMAND_RESULT)
  message(STATUS "Found dolfinx include directory at ${SDOLFINX_INCLUDE_DIR}")
  target_include_directories(bar_cpp PRIVATE ${SDOLFINX_INCLUDE_DIR})
else()
  message(STATUS "dolfinx not found.")
endif()


install(TARGETS bar_cpp LIBRARY DESTINATION bar)

