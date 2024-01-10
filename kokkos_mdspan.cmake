include(FetchContent)

FetchContent_Declare(KokkosMdspan
    GIT_REPOSITORY https://github.com/kokkos/mdspan.git
    GIT_TAG mdspan-0.6.0
)
FetchContent_MakeAvailable(KokkosMdspan)

message(STATUS "Kokkos MDSPAN: ${kokkosmdspan_SOURCE_DIR}")

include_directories(${kokkosmdspan_SOURCE_DIR}/include)
