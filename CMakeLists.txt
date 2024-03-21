cmake_minimum_required(VERSION 3.0)
project(console-runners)

set(CMAKE_C_STANDARD 11)

add_executable(console-runners src/main.c)

if(CMAKE_HOST_SYSTEM MATCHES "Linux")
    target_link_libraries(console-runners m)
endif()

install(TARGETS console-runners
    COMPONENT applications
    DESTINATION "bin"
)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "console-runners")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kingcq")
set(CPACK_PACKAGE_CONTACT "404291187@qq.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "This is a demo package from Kingcq.")
set(CPACK_DEBIAN_PACKAGE_VERSION "1.14.514")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6)")
include(CPack)

