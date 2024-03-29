cmake_minimum_required(VERSION 2.6)
set(PROJECT_NAME Test)

set(LOG_LEVEL 0xf CACHE STRING INTERNAL)

option(OUTPUT_EXECUTABLE "Output executable(YES) ? or API Lib(NO)" YES)
option(OUTPUT_TESTPROJECT "Output test project(YES) ? or (NO)" NO)

project(${PROJECT_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../Targets)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../Targets)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../Targets)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../Targets)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
else()
    set(CMAKE_C_FLAGS "-m32")
    set(CMAKE_CXX_FLAGS "-m32")
endif()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DCMODEL_CODE)

if((LOG_LEVEL LESS 0x10) AND (LOG_LEVEL GREATER -1))
    message("LOG_LEVEL=${LOG_LEVEL}")
    add_definitions(-DLOG_LEVEL=${LOG_LEVEL})
else()
    message("LOG_LEVEL error, use default value 0xf")
    add_definitions(-DLOG_LEVEL=0xf)
endif()

if(OUTPUT_TESTPROJECT)
    add_definitions(-DGTEST)
endif()

if(OUTPUT_EXECUTABLE)
    add_definitions(-DCMODEL_DLL_OPTION=0)
else()
    add_definitions(-DCMODEL_DLL_OPTION=1)
endif()

# set(PROJECT_MODULES src)

include_directories(HlsLib/include/ac_types)
file(GLOB_RECURSE CURRENT_HEADERS HlsLib/include/ac_types/*.h)

source_group("Include" FILES ${CURRENT_HEADERS})

aux_source_directory(Main DIR_MAIN_SRCS)

# foreach(FOLDER IN LISTS PROJECT_MODULES)
#     add_subdirectory(${FOLDER})
# endforeach(FOLDER IN LISTS PROJECT_MODULES)

if(OUTPUT_TESTPROJECT)
    add_subdirectory(UnitTest)
endif()

if(OUTPUT_EXECUTABLE)
    add_executable(${PROJECT_NAME} ${DIR_MAIN_SRCS} ${CURRENT_HEADERS})

    if(MSVC)
        target_link_libraries(${PROJECT_NAME} ${PROJECT_MODULES} -lpthread)
    else()
        target_link_libraries(${PROJECT_NAME} -Wl, --start-group ${PROJECT_MODULES} -Wl, --end-group)
    endif()
else()
endif()