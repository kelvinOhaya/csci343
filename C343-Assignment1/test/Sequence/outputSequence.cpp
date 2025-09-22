
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_OutputSequence, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        int value = 37;
        int value2 = 7;
        int value3 = 3;
        int value4 = 10;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq->add(value3, 2);
        seq->add(value4, 3);
        //Test
        EXPECT_EQ("37, 7, 3, 10", seq->outputSequence());
    }

    TEST(Sequence_OutputSequence, Test1_String) {
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
        EXPECT_EQ("fish, sun, cat, dog", seq->outputSequence());
    }

    TEST(Sequence_Operator, Boolean_Case) {
        auto seq = std::make_unique<Sequence<bool>>();
        bool value = false;
        bool value2 = true;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        //Test
        EXPECT_EQ("0, 1", seq->outputSequence());
    }

}