#This Source Code Form is subject to the terms of the Mozilla Public
#License, v.2.0. If a copy of the MPL was not distributed with this
#file, You can obtain one at http:  // mozilla.org/MPL/2.0/.

add_library(mozillavpn_xpc STATIC)

# include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/shared-sources.cmake)
# target_link_libraries(mozillavpn_xpc PRIVATE shared-sources)

target_link_libraries(mozillavpn_xpc PRIVATE Qt6::Core Qt6::Qml Qt6::Quick)
find_library(FW_FOUNDATION Foundation)
target_link_libraries(mozillavpn_xpc PRIVATE ${FW_FOUNDATION})
target_include_directories(mozillavpn_xpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)

target_sources(mozillavpn_xpc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../leakdetector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../leakdetector.cpp
    xpcbase.h
    xpcservice.h
    xpcservice.cpp
    xpcclient.h
    xpcclient.cpp
)
