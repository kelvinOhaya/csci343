
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_Remove, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        int value = 37;
        int value2 = 45;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq->remove(value, 0);
        //Test
        EXPECT_EQ(45, seq->entry(0));
    }

    TEST(Sequence_Remove, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        std::string value = "cat";
        std::string value2 = "dog";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq->remove(value, 0);
        //Test
        EXPECT_EQ("dog", seq->entry(0));
    }

}