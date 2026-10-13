add_executable(ArtNouveauGuestTests
    DomainTests.cpp
    SmokeTests.cpp
)

target_link_libraries(ArtNouveauGuestTests
    PRIVATE
        ArtNouveauGuestCore
        Catch2::Catch2WithMain
)

if(MSVC)
    if(USE_ASAN)
        target_link_options(ArtNouveauGuestTests PRIVATE /fsanitize=address)
    endif()
else()
    set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ArtNouveauGuestTests)
endif()

target_compile_definitions(
    ArtNouveauGuestTests
    PRIVATE
        TEST_DATA_DIR="${CMAKE_BINARY_DIR}/data"
)

include(Catch)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT WIN32)
    detect_libcpp()
    if(HAS_LIBCPP)
        target_compile_options(Catch2 PRIVATE -stdlib=libc++)
        target_link_options(Catch2 PRIVATE -stdlib=libc++)
        target_compile_options(Catch2WithMain PRIVATE -stdlib=libc++)
        target_link_options(Catch2WithMain PRIVATE -stdlib=libc++)
    endif()
endif()

set(catch_discovery_options DISCOVERY_MODE PRE_TEST)
if(WIN32)
    get_filename_component(compiler_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
    list(APPEND catch_discovery_options DL_PATHS "${compiler_bin_dir}")
endif()
catch_discover_tests(ArtNouveauGuestTests ${catch_discovery_options})

add_test(
    NAME golden
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run_golden.sh $<TARGET_FILE:ArtNouveauGuest>
)
set_tests_properties(golden PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
