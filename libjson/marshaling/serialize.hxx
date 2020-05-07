#ifndef libjson__marshaling__serialize_hxx_
#define libjson__marshaling__serialize_hxx_

#include <libjson/marshaling/marshaling.hxx>

#include <libjson/read.hxx>
#include <libjson/write.hxx>

#include <istream>

namespace json::marshaling {

template< typename T >
void
serialize(std::ostream& o, T const& model)
{
  write(o, marshal(model));
}

template< typename T >
void
serialize(std::ostream&& o, T const& model)
{
  serialize(o, model);
}

template< typename T >
std::string
serialize(T const& model)
{
  std::ostringstream str;
  serialize(str, model);
  return str.str();
}

template< typename T >
T
deserialize(std::istream& i)
{
  return unmarshal< T >(read(i));
}

template< typename T >
T
deserialize(std::istream&& i)
{
  return deserialize< T >(i);
}

template< typename T >
T
deserialize(std::string const& str)
{
  return deserialize< T >(
    std::istringstream{ str, std::ios::in | std::ios::binary });
}

} // namespace json::marshaling

#endif
