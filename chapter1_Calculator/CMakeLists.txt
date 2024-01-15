cmake_minimum_required(VERSION 3.5)

project(Calculator VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_SOURCES
    main.cpp
	calc.cpp
	calc.h
	divzeroexception.cpp
	divzeroexception.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Calculator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Calculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(Calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# if(WIN32)
#     target_compile_options(Calculator PRIVATE /W4)
# elseif(UNIX)
#     target_compile_options(Calculator PRIVATE -Wall)
# endif()

set_target_properties(Calculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Calculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calculator)
endif()
