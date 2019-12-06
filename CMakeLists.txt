  
cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0091 NEW) 

project(PacParser)


FILE(GLOB MonkeyBrains_SOURCE_FILES src/spidermonkey/*.c)

FILE(GLOB MonkeyBrains_HEADER_FILES src/spidermonkey/*.h)


add_library(spidermonkey STATIC ${MonkeyBrains_SOURCE_FILES} ${MonkeyBrains_HEADER_FILES})


if (WIN32)
	set_target_properties(spidermonkey PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_definitions (spidermonkey PUBLIC _X86_ _CRT_SECURE_NO_WARNINGS _IEEE_LIBM EXPORT_JS_API WIN32 _WINDOWS XP_WIN)
endif()


FILE(GLOB PacParser_SOURCE_FILES src/pacparser/*.c)
FILE(GLOB PacParser_HEADER_FILES src/pacparser/*.h)

add_library(PacParser STATIC ${PacParser_SOURCE_FILES} ${PacParser_HEADER_FILES})

target_include_directories(PacParser PRIVATE src/spidermonkey/)

target_link_libraries(PacParser
    spidermonkey
)

if (WIN32)
	set_target_properties(PacParser PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()