add_executable(kalman
        main.cpp
        UdpSocket.cpp
        parser/EventParser.cpp
        parser/MessageParser.cpp
)

include(FetchContent)

FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG 5.0.0
)

FetchContent_MakeAvailable(eigen)

target_link_libraries(kalman
        PRIVATE
        common_compile_flags
        Eigen3::Eigen
)
