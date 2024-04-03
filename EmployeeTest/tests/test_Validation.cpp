#include "pch.h"
#include "gtest/gtest.h"
#include "Validation.h" 

TEST(ValidationTest, ValidateID_Empty) {
    EXPECT_FALSE(Validation::validateID(""));
}

TEST(ValidationTest, ValidateID_LessThan7) {
    EXPECT_FALSE(Validation::validateID("123456"));
}

TEST(ValidationTest, ValidateID_MoreThan7) {
    EXPECT_FALSE(Validation::validateID("12345678"));
}

TEST(ValidationTest, ValidateID_Valid) {
    EXPECT_TRUE(Validation::validateID("1234567"));
}

TEST(ValidationTest, ValidateString_Empty) {
    EXPECT_FALSE(Validation::validateString(""));
}

TEST(ValidationTest, ValidateString_SpecialChars) {
    EXPECT_FALSE(Validation::validateString("!@#$%^&*"));
}

TEST(ValidationTest, ValidateString_NumbersOnly) {
    EXPECT_FALSE(Validation::validateString("12345"));
}

TEST(ValidationTest, ValidateString_Valid) {
    EXPECT_TRUE(Validation::validateString("Hello World"));
    EXPECT_TRUE(Validation::validateString("This is a valid string"));
    EXPECT_TRUE(Validation::validateString("OneWord"));
}

TEST(ValidationTest, ValidateString_LongString) {
    std::string longString(51, 'a');
    EXPECT_FALSE(Validation::validateString(longString));
}

TEST(ValidationTest, ValidatePincode_Empty) {
    EXPECT_FALSE(Validation::validatePincode(""));
}

TEST(ValidationTest, ValidatePincode_LessThan6) {
    EXPECT_FALSE(Validation::validatePincode("12345"));
}

TEST(ValidationTest, ValidatePincode_MoreThan6) {
    EXPECT_FALSE(Validation::validatePincode("1234567"));
}

TEST(ValidationTest, ValidatePincode_Valid) {
    EXPECT_TRUE(Validation::validatePincode("123456"));
}
