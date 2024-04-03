#include "pch.h"
#include "AddressFixture.h"

TEST_F(AddressFixture, GetIDTest) {
    EXPECT_TRUE(address.setid("6000015"));
    EXPECT_EQ(address.getid(), "6000015");
}

TEST_F(AddressFixture, GetLocationTest) {
    EXPECT_EQ(address.getLocation(), "1 Main Street");
}

TEST_F(AddressFixture, GetCityTest) {
    EXPECT_EQ(address.getCity(), "Anytown");
}

TEST_F(AddressFixture, GetStateTest) {
    EXPECT_EQ(address.getState(), "CA");
}

TEST_F(AddressFixture, GetPincodeTest) {
    EXPECT_EQ(address.getPincode(), "123245");
}

TEST_F(AddressFixture, GetEmpIdTest) {
    EXPECT_EQ(address.getEmpId(), "1000001");
}

TEST_F(AddressFixture, SetIDValidTest) {
    EXPECT_TRUE(address.setid("6000001"));
    EXPECT_EQ(address.getid(), "6000001");
}

TEST_F(AddressFixture, SetIDInvalidTest) {
    EXPECT_FALSE(address.setid("invalid_id"));
}

TEST_F(AddressFixture, SetLocationValidTest) {
    EXPECT_TRUE(address.setLocation("100 Mill Road"));
    EXPECT_EQ(address.getLocation(), "100 Mill Road");
}

TEST_F(AddressFixture, SetLocationInvalidTest) {
    EXPECT_FALSE(address.setLocation(""));
}

TEST_F(AddressFixture, SetCityValidTest) {
    EXPECT_TRUE(address.setCity("Metropolis"));
    EXPECT_EQ(address.getCity(), "Metropolis");
}

TEST_F(AddressFixture, SetCityInvalidTest) {
    EXPECT_FALSE(address.setCity(""));
}

TEST_F(AddressFixture, SetStateValidTest) {
    EXPECT_TRUE(address.setState("NY"));
    EXPECT_EQ(address.getState(), "NY");
}

TEST_F(AddressFixture, SetStateInvalidTest) {
    EXPECT_FALSE(address.setState(""));
}

TEST_F(AddressFixture, SetPincodeValidTest) {
    EXPECT_TRUE(address.setPincode("987765"));
    EXPECT_EQ(address.getPincode(), "987765");
}

TEST_F(AddressFixture, SetPincodeInvalidTest) {
    EXPECT_FALSE(address.setPincode("invalid_pincode"));
    EXPECT_FALSE(address.setPincode("1234352456"));
}

TEST_F(AddressFixture, SetEmpIdValidTest) {
    EXPECT_TRUE(address.setEmpId("1000002"));
    EXPECT_EQ(address.getEmpId(), "1000002");
}

TEST_F(AddressFixture, SetEmpIdInvalidTest) {
    EXPECT_FALSE(address.setEmpId("invalid_id"));
}
