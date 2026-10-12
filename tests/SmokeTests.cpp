#include <catch2/catch_test_macros.hpp>

#include "../headers/Gallery.h"

TEST_CASE("Gallery can be constructed", "[smoke]") {
    Gallery gallery("Test Gallery", "Testing", 2026);

    REQUIRE(gallery.getArtists().empty());
    REQUIRE(gallery.getPaintings().empty());
    REQUIRE(gallery.getGames().empty());
}
