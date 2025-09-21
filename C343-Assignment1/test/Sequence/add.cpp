
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_Add, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        int value = 37;
        //Process
        seq->add(value, 0);
        //Test
        EXPECT_EQ(37, seq->entry(0));
    }

    TEST(Sequence_Add, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        std::string value = "cat";
        std::string value2 = "dog";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        //Test
        EXPECT_EQ("cat", seq->entry(0));
    }

}