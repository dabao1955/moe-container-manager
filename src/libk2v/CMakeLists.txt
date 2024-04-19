cmake_minimum_required(VERSION 3.10)
project(libk2v)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER "clang")
add_compile_options("-D_FORTIFY_SOURCE=3")
add_compile_options("-Wno-unused-result")
add_compile_options("-O2")
add_compile_options("-std=gnu99")
add_compile_options("-Wno-gnu-zero-variadic-macro-arguments")

include_directories(${CMAKE_SOURCE_DIR}/src/include)

set(K2V_SRC ${CMAKE_SOURCE_DIR}/src/k2v.c)
set(K2SH_SRC ${CMAKE_SOURCE_DIR}/src/k2sh.c)

add_library(k2v_shared SHARED ${K2V_SRC})
set_target_properties(k2v_shared PROPERTIES LINK_FLAGS "-z noexecstack -z now")
set_target_properties(k2v_shared PROPERTIES OUTPUT_NAME "k2v")

add_library(k2v_static STATIC ${K2V_SRC})
set_target_properties(k2v_static PROPERTIES LINK_FLAGS "-z noexecstack -z now -static")
set_target_properties(k2v_static PROPERTIES OUTPUT_NAME "k2v")

add_executable(k2sh ${K2SH_SRC})
set_target_properties(k2sh PROPERTIES LINK_FLAGS "-Wl,--gc-sections -z noexecstack -z now -static")
target_link_libraries(k2sh k2v_static)

add_custom_command(
    TARGET k2sh
    POST_BUILD
    COMMAND strip k2sh
    VERBATIM
    )

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

enable_testing()
add_test(
  NAME k2v_test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND perl test/test.pl
)

install (TARGETS k2sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out)
install (TARGETS k2v_shared DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/lib/moe-container-manager)
install (TARGETS k2v_static DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/lib/moe-container-manager)
