#include <libunittest/unittest.hxx>

#include <libjson/optional.hxx>

#include <libjson/marshaling/marshaling-traits.hxx>

#include <cstdint>
#include <deque>
#include <list>
#include <string>
#include <vector>

DEFINE_TEST("optional<int>{}")
{
  using traits_type =
    json::marshaling::marshaling_traits< json::optional< int > >;

  std::optional< int > model;

  auto j = traits_type::marshal(model);

  TEST_TRUE(j.is_undefined());
}

DEFINE_TEST("optional<int>{0}")
{
  using traits_type =
    json::marshaling::marshaling_traits< json::optional< int > >;

  std::optional< int > model{ 0 };

  auto j = traits_type::marshal(model);

  TEST_FALSE(j.is_undefined());
  TEST_TRUE(j.is_number());
}

DEFINE_TEST("string")
{
  using traits_type = json::marshaling::marshaling_traits< std::string >;

  std::string model{ "hello, world" };

  auto j = traits_type::marshal(model);

  TEST_TRUE(j.is_string());
  TEST_EQUAL(json::get< std::string >(j), "hello, world");
}

DEFINE_TEST("vector<int>{}")
{
  using traits_type = json::marshaling::marshaling_traits< std::vector< int > >;

  std::vector< int > model1;

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}

DEFINE_TEST("vector<int>{...}")
{
  using traits_type = json::marshaling::marshaling_traits< std::vector< int > >;

  std::vector< int > model1{ 1, 2, 3, 4 };

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}

DEFINE_TEST("list<int>{}")
{
  using traits_type = json::marshaling::marshaling_traits< std::list< int > >;

  std::list< int > model1;

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}

DEFINE_TEST("list<int>{...}")
{
  using traits_type = json::marshaling::marshaling_traits< std::list< int > >;

  std::list< int > model1{ 1, 2, 3, 4 };

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}

DEFINE_TEST("deque<int>{}")
{
  using traits_type = json::marshaling::marshaling_traits< std::deque< int > >;

  std::deque< int > model1;

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}

DEFINE_TEST("deque<int>{...}")
{
  using traits_type = json::marshaling::marshaling_traits< std::deque< int > >;

  std::deque< int > model1{ 1, 2, 3, 4 };

  auto j = traits_type::marshal(model1);

  TEST_TRUE(j.is_array());

  auto model2 = traits_type::unmarshal(j);

  TEST_EQUAL(model1, model2);
}
