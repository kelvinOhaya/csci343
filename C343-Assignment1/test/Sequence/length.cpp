
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_Length, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        int value = 37;
        //Process
        seq->add(value, 0);
        //Test
        EXPECT_EQ(1, seq->length());

    }

    TEST(Sequence_Length, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        std::string value = "fish";
        std::string value2 = "sun";
        std::string value3 = "cat";
        std::string value4 = "dog";

        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq->add(value3, 2);
        seq->add(value4, 3);
        //Test
        EXPECT_EQ(4, seq->length());

    }

}