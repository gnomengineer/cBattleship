cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire OPTIONAL)

project(cBattleship)

set(CMAKE_CXX_FLAGS "-std=c++11 -DBOOST_LOG_DYN_LINK")


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.55.0 REQUIRED COMPONENTS thread system log log_setup signals program_options)
if(Boost_FOUND)
    include_directories(${Boost_system_INCLUDE_DIRS} ${Boost_log_INCLUDE_DIRS} ${Boost_log_setup_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

# protobuf is included as a submodule
set(BUILD_TESTING OFF CACHE BOOL "wheter to build tests for protobuf" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/protobuf/cmake)
set(protobuf_INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/protobuf/src)
include_directories(${protobuf_INCLUDE_DIRECTORY})
link_directories(${protobuf_BINARY_DIR})
# we don't need protobuf lite
set_target_properties(libprotobuf-lite PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

# use pkg-config to find gtk3
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
    link_directories(${GTKMM_LIBRARY_DIRS})
    add_definitions(${GTKMM_CFLAGS_OTHER})
endif(PKG_CONFIG_FOUND)

# add src to include directories so, every module can include headers
# from common
include_directories(${PROJECT_SOURCE_DIR}/src)

# build protobuf C++ classes
set(PROTOBUF_IN_DIR ${PROJECT_SOURCE_DIR}/src/common)
FILE(GLOB_RECURSE PROTO_FILES ${PROTOBUF_IN_DIR}/*.proto)

set(PROTOBUF_OUT_DIR ${PROJECT_BINARY_DIR}/protobuf)
file(MAKE_DIRECTORY ${PROTOBUF_OUT_DIR})
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(FILE_NAME ${PROTO_FILE} NAME_WE)
    list(APPEND PROTO_OUTFILES_CC ${PROTOBUF_OUT_DIR}/${FILE_NAME}.pb.cc)
    list(APPEND PROTO_OUTFILES_H ${PROTOBUF_OUT_DIR}/${FILE_NAME}.pb.h)
endforeach()

add_custom_command(
    OUTPUT ${PROTO_OUTFILES_CC} ${PROTO_OUTFILES_H}
    COMMAND ${protobuf_BINARY_DIR}/protoc -I=${PROTOBUF_IN_DIR} -I=${protobuf_INCLUDE_DIRECTORY} --cpp_out=${PROTOBUF_OUT_DIR} ${PROTO_FILES}
    DEPENDS ${protobuf_BINARY_DIR}/protoc ${PROTO_FILES}
)

include_directories(${PROTOBUF_OUT_DIR})

# common library
set(CBATTLESHIP_COMMON_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/common)
file(GLOB_RECURSE CBATTLESHIP_COMMON_SOURCE_FILES ${CBATTLESHIP_COMMON_SOURCE_PATH}/*.cpp)
add_library(cbattleship-common ${CBATTLESHIP_COMMON_SOURCE_FILES} ${PROTO_OUTFILES_CC})
target_link_libraries(cbattleship-common ${Boost_LIBRARIES} protobuf)
if(COMMAND cotire)
    cotire(cbattleship-common)
endif()

# server
set(CBATTLESHIP_SERVER_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/server)
file(GLOB_RECURSE CBATTLESHIP_SERVER_SOURCE_FILES ${CBATTLESHIP_SERVER_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-server ${CBATTLESHIP_SERVER_SOURCE_FILES})
target_link_libraries(cbattleship-server cbattleship-common ${Boost_LIBRARIES} pthread)
target_include_directories(cbattleship-server PRIVATE ${Boost_thread_INCLUDE_DIRS} ${Boost_program_options_INCLUDE_DIRS})
if(COMMAND cotire)
    cotire(cbattleship-server)
endif()

# client library
set(CBATTLESHIP_CLIENTLIB_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/clientlib)
file(GLOB_RECURSE CBATTLESHIP_CLIENTLIB_SOURCE_FILES ${CBATTLESHIP_CLIENTLIB_SOURCE_PATH}/*.cpp)
add_library(cbattleship-clientlib ${CBATTLESHIP_CLIENTLIB_SOURCE_FILES})
target_link_libraries(cbattleship-clientlib cbattleship-common ${Boost_LIBRARIES})
target_include_directories(cbattleship-clientlib PRIVATE ${Boost_signals_INCLUDE_DIRS})
if(COMMAND cotire)
    cotire(cbattleship-clientlib)
endif()

# curses client
set(CBATTLESHIP_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/client)
file(GLOB_RECURSE CBATTLESHIP_CLIENT_SOURCE_FILES ${CBATTLESHIP_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-curses-client ${CBATTLESHIP_CLIENT_SOURCE_FILES})
target_link_libraries(cbattleship-curses-client cbattleship-clientlib ${Boost_LIBRARIES})
target_include_directories(cbattleship-curses-client PRIVATE ${Boost_signals_INCLUDE_DIRS})
if(COMMAND cotire)
    cotire(cbattleship-curses-client)
endif()

# text client
set(CBATTLESHIP_TEXT_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/text-client)
file(GLOB_RECURSE CBATTLESHIP_TEXT_CLIENT_SOURCE_FILES ${CBATTLESHIP_TEXT_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-text-client ${CBATTLESHIP_TEXT_CLIENT_SOURCE_FILES})
target_link_libraries(cbattleship-text-client cbattleship-clientlib ${Boost_signals_LIBRARIES})
if(COMMAND cotire)
    cotire(cbattleship-text-client)
endif()

# gtk client
if(PKG_CONFIG_FOUND)
    set(CBATTLESHIP_GTK_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/gtk-client)
    set(resource_output ${PROJECT_BINARY_DIR}/gtk-resources.c)
    find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources HINTS ${GLIB3_PREFIX})
    add_custom_command(OUTPUT ${resource_output}
        COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --target=${resource_output} gui.gresource.xml
        DEPENDS ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH}/gui.gresource.xml ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH}/gui-design.glade
        WORKING_DIRECTORY ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH})
    file(GLOB_RECURSE CBATTLESHIP_GTK_CLIENT_SOURCE_FILES ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH}/*.cpp)
    add_executable(cbattleship-gtk-client ${CBATTLESHIP_GTK_CLIENT_SOURCE_FILES} ${resource_output})
    target_link_libraries(cbattleship-gtk-client cbattleship-clientlib ${GTKMM_LIBRARIES})
    target_include_directories(cbattleship-gtk-client PRIVATE ${GTKMM_INCLUDE_DIRS})
    if(COMMAND cotire)
        cotire(cbattleship-gtk-client)
    endif()
endif(PKG_CONFIG_FOUND)

# bot client
set(CBATTLESHIP_BOT_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/bot-client)
file(GLOB_RECURSE CBATTLESHIP_BOT_CLIENT_SOURCE_FILES ${CBATTLESHIP_BOT_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-bot-client ${CBATTLESHIP_BOT_CLIENT_SOURCE_FILES})
target_link_libraries(cbattleship-bot-client cbattleship-clientlib ${Boost_signals_LIBRARIES})
if(COMMAND cotire)
    cotire(cbattleship-bot-client)
endif()


# test cases
set(CBATTLESHIP_TEST_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/test)
file(GLOB_RECURSE CBATTLESHIP_TEST_SOURCE_FILES ${CBATTLESHIP_TEST_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-unit-tests ${CBATTLESHIP_TEST_SOURCE_FILES})
target_link_libraries(cbattleship-unit-tests cbattleship-common cppunit)
if(COMMAND cotire)
    cotire(cbattleship-unit-tests)
endif()

# use ncurses library
set(CURSES_NEED_NCURSES TRUE)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(cbattleship-curses-client pdcurses)
else()
  target_link_libraries(cbattleship-curses-client curses)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(cbattleship-curses-client rt)
  endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()

# automatically run tests after build
enable_testing()
set(BUILD_TESTING ON)
add_test(NAME unit-tests COMMAND ${PROJECT_BINARY_DIR}/cbattleship-unit-tests)
add_test(NAME edge-bot-test COMMAND ${PROJECT_SOURCE_DIR}/scripts/tests/edge-bot-test ${PROJECT_BINARY_DIR})

# compile documentation graphs
find_program(DOT NAMES dot)

if(EXISTS ${DOT})
    file(GLOB_RECURSE DOT_FILES ${PROJECT_SOURCE_DIR}/doc/*.dot)
    foreach(dot_file ${DOT_FILES})
        get_filename_component(dot_file_name ${dot_file} NAME_WE)
        set(dot_file_name "${dot_file_name}.png")
        add_custom_command(OUTPUT ${dot_file_name}
                           COMMAND ${DOT} -Tpng ${dot_file} > ${PROJECT_BINARY_DIR}/${dot_file_name}
                           DEPENDS ${dot_file})
       list(APPEND dot_outfiles ${dot_file_name})
    endforeach()

    add_custom_target(doc ALL
                      DEPENDS ${dot_outfiles})
endif()

# use ccache to speed up compilation (if available)
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)
