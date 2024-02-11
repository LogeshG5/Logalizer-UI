cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(logalizer-ui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

# hack for buggy CMake's FindwxWidgets script
if (DEFINED ENV_WX_CONFIG)
    set (ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets REQUIRED)

set(SRCS main.cpp
  ui/ui.cpp
  platform/application.cpp
  MainFrameImpl.cpp)

include(${wxWidgets_USE_FILE})

if (APPLE)
    # create bundle on apple compiles
    add_executable(logalizer-ui MACOSX_BUNDLE ${SRCS} )
    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(logalizer-ui PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(logalizer-ui WIN32 ${SRCS})
endif()

target_link_libraries(logalizer-ui PRIVATE ${wxWidgets_LIBRARIES})
target_compile_features(logalizer-ui PRIVATE cxx_std_17)

install(TARGETS logalizer-ui RUNTIME DESTINATION bin )
install(FILES $<TARGET_RUNTIME_DLLS:logalizer-ui> TYPE BIN)
