#include <libunittest/unittest.hxx>

#include <libjson/marshaling/mapping.hxx>
#include <libjson/marshaling/serialize.hxx>

struct name {
  std::string first;
  std::string last;

  inline static json::marshaling::mapping< name > const json{
    { "first", &name::first },
    { "last", &name::last }
  };
};

struct person {
  name name;
  int age;

  inline static json::marshaling::mapping< person > const json{
    { "name", &person::name },
    { "age", &person::age }
  };
};

DEFINE_TEST("round trip")
{
  using namespace json::marshaling;

  person p1{ { "Jane", "Doe" }, 37 };

  auto p2 = deserialize< person >(serialize(p1));

  TEST_EQUAL(p1.name.first, p2.name.first);
  TEST_EQUAL(p1.name.last, p2.name.last);
  TEST_EQUAL(p1.age, p2.age);
}
