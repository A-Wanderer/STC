CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(STC)
PROJECT(DATA)
PROJECT(CLI)
PROJECT(SER)
include_directories (./)


ADD_EXECUTABLE(STC test_modu.cpp stc/stc_control.cpp stc/psk_mod.cpp stc/matrix_control.cpp)
ADD_EXECUTABLE(DATA test_data.cpp)
ADD_EXECUTABLE(CLI client.cpp web/web_client.cpp stc/stc_control.cpp stc/psk_mod.cpp stc/matrix_control.cpp)
ADD_EXECUTABLE(SER server.cpp epoll/epoller.cpp web/web_server.cpp stc/stc_control.cpp stc/psk_mod.cpp stc/matrix_control.cpp)

target_link_libraries(SER -lpthread)

