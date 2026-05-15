#pragma once

#include <Arduino.h>

struct Spool {

    int id = 0;

    String slot;

    bool isActive = false;

    bool isEmpty = false;

    int weight = 0;

    String material;

    String vendor;

    String brand;

    String color;
};