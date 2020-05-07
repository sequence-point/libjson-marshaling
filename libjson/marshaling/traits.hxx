#ifndef libjson__marshaling__traits_hxx_
#define libjson__marshaling__traits_hxx_

#include <libjson/optional.hxx>

#include <type_traits>

namespace json::marshaling {

template< typename >
struct is_optional : std::false_type {
};

template< typename T >
struct is_optional< optional< T > > : std::true_type {
};

template< typename T >
constexpr bool is_optional_v = is_optional< T >::value;

} // namespace json::marshaling

#endif
