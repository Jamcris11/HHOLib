cmake_minimum_required(VERSION 3.17)

project(HHOLib)


add_library(hholib INTERFACE)

target_include_directories(hholib INTERFACE include/)

install(DIRECTORY include/
	DESTINATION /usr/include/libhho)

