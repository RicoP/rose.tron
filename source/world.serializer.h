#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN
//  command:
//    rose.parser -I world.h -O world.serializer.h
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  predef struct Bike
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Bike &lhs, const Bike &rhs);
inline bool operator==(const Bike &lhs, const Bike &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Bike &lhs, const Bike &rhs) { return !equals(lhs, rhs); }
inline void serialize(Bike &o, ISerializer &s);
inline void deserialize(Bike &o, IDeserializer &s);
inline hash_value hash(const Bike &o);

template <>
struct type_id<Bike>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Bike>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct World
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const World &lhs, const World &rhs);
inline bool operator==(const World &lhs, const World &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const World &lhs, const World &rhs) { return !equals(lhs, rhs); }
inline void serialize(World &o, ISerializer &s);
inline void deserialize(World &o, IDeserializer &s);
inline hash_value hash(const World &o);

template <>
struct type_id<World>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<World>();
} //namespace rose



#ifndef IMPL_SERIALIZER_UTIL
#define IMPL_SERIALIZER_UTIL

///////////////////////////////////////////////////////////////////
// internal helper methods
///////////////////////////////////////////////////////////////////

namespace rose {
template<class T>
bool rose_parser_equals(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

template<class T, size_t N>
bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
  for (size_t i = 0; i != N; ++i) {
    if (!rose_parser_equals(lhs, rhs)) return false;
  }
  return true;
}

template<size_t N>
bool rose_parser_equals(const char(&lhs)[N], const char(&rhs)[N]) {
  for (size_t i = 0; i != N; ++i) {
    if (lhs[i] != rhs[i]) return false;
    if (lhs[i] == 0) return true;
  }
  return true;
}

template<class T>
bool rose_parser_equals(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (size_t i = 0; i != lhs.size(); ++i) {
    if (!rose_parser_equals(lhs, rhs)) return false;
  }
  return true;
}

template<class T>
hash_value rose_parser_hash(const T & value) { return hash(value); }

template<class T>
hash_value rose_parser_hash(const std::vector<T>& v) {
  hash_value h = 0;
  for (const auto& o : v) {
    h ^= rose_parser_hash(o);
    h = xor64(h);
  }
  return h;
}

}
#endif
  
///////////////////////////////////////////////////////////////////
//  impl struct Bike
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Bike &lhs, const Bike &rhs) {
  return
    rose::rose_parser_equals(lhs.transform, rhs.transform) &&
    rose::rose_parser_equals(lhs.bike, rhs.bike) &&
    rose::rose_parser_equals(lhs.hero, rhs.hero);
}

inline void rose::serialize(Bike &o, ISerializer &s) {
  if(s.node_begin("Bike", hash("Bike"), &o)) {
    s.key("transform");
    serialize(o.transform, s);
    s.key("bike");
    serialize(o.bike, s);
    s.key("hero");
    serialize(o.hero, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(Bike &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("transform"):
        deserialize(o.transform, s);
        break;
      case rose::hash("bike"):
        deserialize(o.bike, s);
        break;
      case rose::hash("hero"):
        deserialize(o.hero, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const Bike &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.transform);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.bike);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.hero);
  return h;
}

template <>
struct rose::type_id<Bike> {
    inline static rose::hash_value VALUE = 14482573112785096360ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Bike>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Bike"),
    /*           member_hash */ 14482573112785096360ULL,
    /*      memory_footprint */ sizeof(Bike),
    /*      memory_alignment */ 16,
    /*                  name */ "Bike",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Bike(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Bike*>(ptr))->~Bike(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Bike*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Bike*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct World
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const World &lhs, const World &rhs) {
  return
    rose::rose_parser_equals(lhs.bikes, rhs.bikes);
}

inline void rose::serialize(World &o, ISerializer &s) {
  if(s.node_begin("World", hash("World"), &o)) {
    s.key("bikes");
    serialize(o.bikes, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(World &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("bikes"):
        deserialize(o.bikes, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const World &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.bikes);
  return h;
}

template <>
struct rose::type_id<World> {
    inline static rose::hash_value VALUE = 9056699606791894297ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<World>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("World"),
    /*           member_hash */ 9056699606791894297ULL,
    /*      memory_footprint */ sizeof(World),
    /*      memory_alignment */ 16,
    /*                  name */ "World",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) World(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<World*>(ptr))->~World(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<World*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<World*>(ptr)), d); }
  };
  return info;
}

