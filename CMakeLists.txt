cmake_minimum_required(VERSION 2.8.11)

project(font-tester)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Use .ui file
qt5_wrap_ui(UIS_HDRS src/mainwindow.ui)

# Tell CMake to create the executable
add_executable(font-tester src/mainwindow.cpp src/main.cpp ${UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(font-tester Qt5::Widgets)

install(TARGETS font-tester DESTINATION bin)
install(FILES font-tester.desktop DESTINATION share/applications)
