#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I world.h -O world.serializer.h
///////////////////////////////////////////////////////////////////

struct                Bike;
namespace rose {
  namespace ecs {
    void        serialize(Bike &o, ISerializer &s);
    void      deserialize(Bike &o, IDeserializer &s);
  }
  hash_value         hash(const Bike &o);
  template<>
  struct type_id<Bike> {
    inline static hash_value VALUE = 4055817582476387677ULL;
  };
  void construct_defaults(      Bike &o); // implement me
}
bool operator==(const Bike &lhs, const Bike &rhs);
bool operator!=(const Bike &lhs, const Bike &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Bike>();
}

struct                World;
namespace rose {
  namespace ecs {
    void        serialize(World &o, ISerializer &s);
    void      deserialize(World &o, IDeserializer &s);
  }
  hash_value         hash(const World &o);
  template<>
  struct type_id<World> {
    inline static hash_value VALUE = 11909758945263842450ULL;
  };
  void construct_defaults(      World &o); // implement me
}
bool operator==(const World &lhs, const World &rhs);
bool operator!=(const World &lhs, const World &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<World>();
}

#ifdef IMPL_SERIALIZER

    #ifndef IMPL_SERIALIZER_UTIL
    #define IMPL_SERIALIZER_UTIL
    #include <cstring>

    namespace {
    //internal helper methods
    template<class T>
    bool rose_parser_equals(const T& lhs, const T& rhs) {
      return lhs == rhs;
    }

    template<class T, size_t N>
    bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
      for (size_t i = 0; i != N; ++i) {
        if (lhs[i] != rhs[i]) return false;
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
        if (lhs[i] != rhs[i]) return false;
      }
      return true;
    }

    template<class TL, class TR>
    void assign(TL& lhs, TR&& rhs) {
      lhs = rhs;
    }

    template<class T>
    void construct_default(std::vector<T> & v) {
      c.clear();
    }
    }
    #endif
  
///////////////////////////////////////////////////////////////////
//  struct Bike
///////////////////////////////////////////////////////////////////
bool operator==(const Bike &lhs, const Bike &rhs) {
  return
    rose_parser_equals(lhs.transform, rhs.transform) &&
    rose_parser_equals(lhs.bike, rhs.bike) &&
    rose_parser_equals(lhs.hero, rhs.hero);
}

bool operator!=(const Bike &lhs, const Bike &rhs) {
  return !(lhs == rhs);
}

void rose::ecs::serialize(Bike &o, ISerializer &s) {
  if(s.node_begin("Bike", rose::hash("Bike"), &o)) {
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

void rose::ecs::deserialize(Bike &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

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

rose::hash_value rose::hash(const Bike &o) {
  rose::hash_value h = rose::hash(o.transform);
  h = rose::xor64(h);
  h ^= rose::hash(o.bike);
  h = rose::xor64(h);
  h ^= rose::hash(o.hero);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Bike>() {
    static rose::reflection::TypeInfo info = {
      /*             unique_id */ rose::hash("Bike"),
      /*           member_hash */ 4055817582476387677ULL,
      /*      memory_footprint */ sizeof(Bike),
      /*      memory_alignment */ 16,
      /*                  name */ "Bike",
      /*  fp_default_construct */ +[](void * ptr) { new (ptr) Bike(); },
      /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Bike*>(ptr))->~Bike(); },
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<Bike*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<Bike*>(ptr)), d); }
    };
    return info;
  }
}

///////////////////////////////////////////////////////////////////
//  struct World
///////////////////////////////////////////////////////////////////
bool operator==(const World &lhs, const World &rhs) {
  return
    rose_parser_equals(lhs.bikes, rhs.bikes);
}

bool operator!=(const World &lhs, const World &rhs) {
  return !(lhs == rhs);
}

void rose::ecs::serialize(World &o, ISerializer &s) {
  if(s.node_begin("World", rose::hash("World"), &o)) {
    s.key("bikes");
    serialize(o.bikes, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(World &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("bikes"):
        deserialize(o.bikes, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const World &o) {
  rose::hash_value h = rose::hash(o.bikes);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<World>() {
    static rose::reflection::TypeInfo info = {
      /*             unique_id */ rose::hash("World"),
      /*           member_hash */ 11909758945263842450ULL,
      /*      memory_footprint */ sizeof(World),
      /*      memory_alignment */ 16,
      /*                  name */ "World",
      /*  fp_default_construct */ +[](void * ptr) { new (ptr) World(); },
      /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<World*>(ptr))->~World(); },
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<World*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<World*>(ptr)), d); }
    };
    return info;
  }
}


#endif
