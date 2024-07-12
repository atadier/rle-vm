cmake_minimum_required(VERSION 3.20)
project(rle-debug LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    Widgets
)

qt_standard_project_setup()

qt_add_executable(rle-debug main.cpp)

qt_add_resources(rle-debug "qml" FILES
    qml/main.qml
    qml/ProgramViewer.qml
    qml/IntrospectLabels.qml
)

target_sources(rle-debug PRIVATE controller.cpp)

target_link_libraries(rle-debug PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Widgets
    front
    vm
)

install(TARGETS rle-debug RUNTIME DESTINATION bin)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
