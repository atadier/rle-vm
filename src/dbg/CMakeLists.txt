cmake_minimum_required(VERSION 3.20)
project(rle-debug LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
)

qt_standard_project_setup()

qt_add_executable(rle-debug main.cpp)

qt_add_resources(rle-debug "qml" FILES
  qml/main.qml
)

target_link_libraries(rle-debug PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
)

install(TARGETS rle-debug RUNTIME DESTINATION bin)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
