add_executable(ArtNouveauGuestTests
    DomainTests.cpp
    SmokeTests.cpp
)

target_link_libraries(ArtNouveauGuestTests
    PRIVATE
        ArtNouveauGuestCore
        Catch2::Catch2WithMain
)

target_compile_definitions(
    ArtNouveauGuestTests
    PRIVATE
        TEST_DATA_DIR="${CMAKE_BINARY_DIR}/data"
)

include(Catch)
catch_discover_tests(ArtNouveauGuestTests)

add_test(
    NAME golden
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run_golden.sh $<TARGET_FILE:ArtNouveauGuest>
)
set_tests_properties(golden PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
