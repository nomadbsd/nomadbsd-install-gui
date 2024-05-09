cmake_minimum_required(VERSION 3.16)
project(
  nomadbsd-install-gui
  HOMEPAGE_URL https://github.com/nomadbsd/nomadbsd-install-gui
  LANGUAGES CXX)
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROGRAM ${CMAKE_PROJECT_NAME})
set(BACKEND "nomadbsd-install")

set(BACKEND_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/libexec)
set(PATH_BACKEND ${BACKEND_INSTALL_DIR}/${BACKEND})
set(PATH_SLIM_THEME_DIR "/usr/local/share/slim/themes")
set(PATH_SDDM_THEME_DIR "/usr/local/share/sddm/themes")

set(SOURCE_FILES src/backend.h src/main.cpp src/wizard.cpp src/wizard.h
                 lib/qt-helper/qt-helper.cpp)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
qt_standard_project_setup()

set(TS_FILES
    locale/${PROGRAM}_cs.ts locale/${PROGRAM}_de.ts locale/${PROGRAM}_fr.ts
    locale/${PROGRAM}_id.ts locale/${PROGRAM}_ru.ts)

add_executable(nomadbsd-install-gui ${SOURCE_FILES})

qt_add_translations(nomadbsd-install-gui TS_FILES ${TS_FILES})

target_include_directories(
  nomadbsd-install-gui
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
         "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
if(MAC)
  set(EFI_PART_SIZE "200M")
else()
  set(EFI_PART_SIZE "40M")
endif()

configure_file(defs.h.in defs.h @ONLY)
configure_file(nomadbsd-install.in nomadbsd-install @ONLY)

set(LIBS Qt6::Widgets)
target_link_libraries(nomadbsd-install-gui PRIVATE ${LIBS})

install(TARGETS nomadbsd-install-gui DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${BACKEND} DESTINATION libexec)
install(FILES "${CMAKE_PROJECT_NAME}.desktop" DESTINATION share/applications)
