#ifndef json__marshaling__mapping_hxx_
#define json__marshaling__mapping_hxx_

#include <libjson/variant.hxx>

#include <libjson/marshaling/marshaling-traits.hxx>
#include <libjson/marshaling/traits.hxx>

#include <functional>

namespace json::marshaling {

template< typename T >
class member_mapping {
public:
  template< typename M >
  member_mapping(std::string key, M T::*member)
    : key_{ std::move(key) }, optional_{ is_optional_v< M > }
  {
    getter_ = [member](T const& instance) -> json::variant {
      return marshaling_traits< M >::marshal(instance.*member);
    };

    setter_ = [member](T& instance, json::variant const& value) {
      instance.*member = marshaling_traits< M >::unmarshal(value);
    };
  }

  template< typename U >
  member_mapping(member_mapping< U > const& other)
    : key_{ other.key_ },
      optional_{ other.optional_ },
      getter_{ other.getter_ },
      setter_{ other.setter_ }
  {}

  std::string const&
  key() const
  {
    return key_;
  }

  bool
  optional() const
  {
    return optional_;
  }

  variant
  get(T const& instance) const
  {
    return getter_(instance);
  }

  void
  set(T& instance, variant const& value) const
  {
    setter_(instance, value);
  }

private:
  template< typename U >
  friend class member_mapping;

  std::string key_;
  bool optional_;

  std::function< variant(T const&) > getter_;
  std::function< void(T&, variant const&) > setter_;
};

template< typename T >
class mapping {
public:
  using map_type = std::map< std::string, member_mapping< T > >;
  using const_iterator = typename map_type::const_iterator;

  mapping(std::initializer_list< member_mapping< T > > init)
  {
    for (auto const& j : init)
      mappings_.emplace(j.key(), j);
  }

  template< typename U >
  mapping(mapping< U > inherit,
          std::initializer_list< member_mapping< T > > init)
  {
    for (auto const& j : init)
      mappings_.emplace(j.key(), j);

    for (auto const& j : inherit)
      mappings_.emplace(j);
  }

  const_iterator
  begin() const
  {
    return mappings_.begin();
  }

  const_iterator
  end() const
  {
    return mappings_.end();
  }

private:
  std::map< std::string, member_mapping< T > > mappings_;
};

} // namespace json::marshaling

#endif
