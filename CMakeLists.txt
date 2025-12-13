cmake_minimum_required(VERSION 3.30)
project(lvgl_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_LOGGING_TO_CONSOLE 1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(PROJECT_SOURCES
        src/main.cpp
        src/Global.h
        src/MainWindow.cpp
        src/MainWindow.h
        src/Viewer.h
        src/Viewer.cpp
        src/scenes/Scene.h
        src/scenes/Scene.cpp
        src/LvglInputState.h
        src/LvglInputState.cpp
        src/LvglAgent.h
        src/LvglAgent.cpp
        src/LvglItem.h
        src/LvglItem.cpp
        src/lvgl_ui/LvglDemo1.cpp
        src/lvgl_ui/LvglDemo1.h
)

set(TS_FILES
        i18n/lvgl_qt_en_US.ts
        i18n/lvgl_qt_zh_CN.ts
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # for only Qt6
    qt_add_executable(lvgl_qt
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(lvgl_qt SHARED
                ${PROJECT_SOURCES}
        )
    else ()
        # for Qt5
        add_executable(lvgl_qt
                ${PROJECT_SOURCES}
        )
    endif ()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/rc/app_icon.rc")
    list(APPEND PROJECT_SOURCES "${APP_ICON_RESOURCE_WINDOWS}")
endif ()

if (APPLE)
    set(APP_ICON_RESOURCE_MACOSX "${CMAKE_CURRENT_SOURCE_DIR}/rc/logo.icns")
    add_custom_command(TARGET lvgl_qt POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${APP_ICON_RESOURCE_MACOSX}"
            "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources/icon.icns"
    )
endif ()

set(QM_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/i18n)
file(MAKE_DIRECTORY ${QM_OUTPUT_DIR})

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

add_custom_command(
        OUTPUT ${QM_OUTPUT_DIR}/lvgl_qt_en_US.qm ${QM_OUTPUT_DIR}/lvgl_qt_zh_CN.qm
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/lvgl_qt_en_US.qm ${QM_OUTPUT_DIR}/lvgl_qt_en_US.qm
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/lvgl_qt_zh_CN.qm ${QM_OUTPUT_DIR}/lvgl_qt_zh_CN.qm
        DEPENDS ${QM_FILES}
)

add_custom_target(translations ALL
        DEPENDS
        ${QM_OUTPUT_DIR}/lvgl_qt_en_US.qm
        ${QM_OUTPUT_DIR}/lvgl_qt_zh_CN.qm
)

# Link Qt Widgets
target_link_libraries(lvgl_qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Ensure LVGL headers are available
# The repository has headers under `${CMAKE_SOURCE_DIR}/include`. Add them for compilation.
target_include_directories(lvgl_qt PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link to LVGL import library and ensure DLL is available at runtime on Windows
if (WIN32)
    # Explicitly link the MinGW import library if present
    # This avoids name resolution issues and works regardless of generator
    set(LVGL_DLL "${CMAKE_SOURCE_DIR}/lib/liblvgl.dll")
    set(LVGL_IMP_LIB "${CMAKE_SOURCE_DIR}/lib/liblvgl.dll.a")
    if (EXISTS "${LVGL_IMP_LIB}")
        target_link_libraries(lvgl_qt PRIVATE "${LVGL_IMP_LIB}")
    else ()
        # Fallback: try linking by name if only -llvgl is available
        target_link_directories(lvgl_qt PRIVATE "${CMAKE_SOURCE_DIR}/lib")
        target_link_libraries(lvgl_qt PRIVATE lvgl)
    endif ()
    # Copy the DLL next to the built executable so it loads at runtime
    add_custom_command(TARGET lvgl_qt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${LVGL_DLL}" "$<TARGET_FILE_DIR:lvgl_qt>/liblvgl.dll"
    )
endif ()

target_compile_definitions(lvgl_qt PRIVATE QT_USE_QSTRINGBUILDER)

set_target_properties(lvgl_qt PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER zmexing.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        $<$<CONFIG:Release>:WIN32_EXECUTABLE TRUE>
)

install(TARGETS lvgl_qt
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lvgl_qt)
endif ()
