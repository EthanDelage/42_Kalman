add_executable(kalman
        main.cpp
        UdpSocket.cpp
        parser/EventParser.cpp
        parser/MessageParser.cpp
        Application.cpp
        data/print.cpp
        KalmanFilter.cpp
        motion_model.cpp
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
