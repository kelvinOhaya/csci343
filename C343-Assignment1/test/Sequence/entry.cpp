
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_Entry, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        //Test
        EXPECT_EQ(std::nullopt,seq->entry(0));
    }


    TEST(Sequence_Entry, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        //Test
        EXPECT_EQ(std::nullopt,seq->entry(0));
    }

}