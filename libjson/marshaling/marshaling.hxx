#ifndef libjson__marshaling__marshaling_hxx_
#define libjson__marshaling__marshaling_hxx_

#include <libjson/variant.hxx>

#include <libjson/marshaling/marshaling-traits.hxx>

namespace json::marshaling {

template< typename T >
variant
marshal(T const& model)
{
  return marshaling_traits< T >::marshal(model);
}

template< typename T >
T
unmarshal(variant const& value)
{
  return marshaling_traits< T >::unmarshal(value);
}

} // namespace json::marshaling

#endif
