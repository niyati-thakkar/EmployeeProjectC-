#include "pch.h"
#ifndef _AddressFixture_H_
#define _AddressFixture_H_

#include "Address.h"

class AddressFixture : public ::testing::Test {
protected:
    void SetUp() override {
        address.setEmpId("1000001");
        address.setLocation("1 Main Street");
        address.setCity("Anytown");
        address.setState("CA");
        address.setPincode("123245");
    }

    Address address;
};

#endif
