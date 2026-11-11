cmake_minimum_required(VERSION 3.16)
project(SCAPMS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Tells VS Code exactly where your Qt installation lives
set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Include implementation files only when they exist; some are added later.
set(SCAPMS_SOURCES main.cpp)
foreach(source ClinicDatabase.cpp PatientRecord.cpp GeneralPatient.cpp EmergencyPatient.cpp FollowUpPatient.cpp controller/SearchEngine.cpp controller/SortEngine.cpp controller/gui/MainWindow.cpp)
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
		list(APPEND SCAPMS_SOURCES "${source}")
	endif()
endforeach()

add_executable(SCAPMS ${SCAPMS_SOURCES})

target_link_libraries(SCAPMS PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)