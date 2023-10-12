qt_add_executable(xpc_test_client client.cpp)
qt_add_executable(xpc_test_server server.cpp)

target_link_libraries(xpc_test_client PRIVATE mozillavpn_xpc)
target_link_libraries(xpc_test_server PRIVATE mozillavpn_xpc)
add_custom_target(build_examples)
add_dependencies(build_examples xpc_test_client xpc_test_server)

file(GENERATE
    OUTPUT example.server.plist
    INPUT example.server.plist.in
    TARGET xpc_test_server
)
