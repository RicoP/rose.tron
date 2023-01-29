#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <rose/hash.h>
#include <rose/raylibutils/raylibutils.h>
#include <rose/raylibutils/types.h>
#include <rose/raylibutils/types.serializer.h>

struct Bike {
  Matrix transform;
  RaylibAssetModel bike = "bike.glb";
  bool hero = false;

  int foo() { return 0; }

  Bike() {
    transform = MatrixIdentity();
  }
};

inline int bar() { return 0; }


struct World {
  Bike bikes[4];
};
