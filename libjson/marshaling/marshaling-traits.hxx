#ifndef libjson__marshaling__marshaling_traits_hxx_
#define libjson__marshaling__marshaling_traits_hxx_

#include <libjson/optional.hxx>
#include <libjson/variant.hxx>

#include <chrono>
#include <ctime>
#include <deque>
#include <iomanip>
#include <list>
#include <locale>
#include <map>
#include <string>
#include <vector>

#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>

namespace json::marshaling {

template< typename T >
struct marshaling_traits {
  using model_type = T;

  static variant
  marshal(model_type const& model)
  {
    object obj;

    for (auto const& j : T::json())
      obj.emplace(j.first, j.second.get(model));

    return obj;
  }

  static model_type
  unmarshal(variant const& value)
  {
    if (!value.is_object())
      throw std::runtime_error{
        "cannot unmarshal non-object value"
      }; // TODO change exception type

    auto const& obj = get< object >(value);

    T model;

    for (auto const& j : T::json()) {
      if (obj.count(j.first) != 1) {
        if (!j.second.optional())
          throw std::runtime_error{ "missing field '" + j.first +
                                    "'" }; // TODO change exception type

        continue; // Try next key.
      }

      j.second.set(model, obj.at(j.first));
    }

    return model;
  }
};

template< typename T >
struct marshaling_traits< optional< T > > {
  using model_type = optional< T >;

  static variant
  marshal(optional< T > const& model)
  {
    if (model)
      return marshaling_traits< T >::marshal(*model);

    return {};
  }

  static optional< T >
  unmarshal(variant const& value)
  {
    if (value.is_undefined())
      return {};

    return marshaling_traits< T >::unmarshal(value);
  }
};

template<>
struct marshaling_traits< bool > {
  using model_type = bool;

  static variant
  marshal(bool model)
  {
    return model;
  }

  static bool
  unmarshal(variant const& value)
  {
    if (!value.is_boolean())
      throw std::runtime_error{ "not a boolean" };

    return get< bool >(value);
  }
};

template<>
struct marshaling_traits< short int > {
  using model_type = short int;

  static variant
  marshal(short int model)
  {
    return model;
  }

  static short int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< short int >(value);
  }
};

template<>
struct marshaling_traits< int > {
  using model_type = int;

  static variant
  marshal(int model)
  {
    return model;
  }

  static int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< int >(value);
  }
};

template<>
struct marshaling_traits< long int > {
  using model_type = long int;

  static variant
  marshal(long int model)
  {
    return model;
  }

  static long int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< long int >(value);
  }
};

template<>
struct marshaling_traits< long long int > {
  using model_type = long long int;

  static variant
  marshal(long long int model)
  {
    return model;
  }

  static long long int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< long long int >(value);
  }
};

template<>
struct marshaling_traits< unsigned short int > {
  using model_type = unsigned short int;

  static variant
  marshal(unsigned short int model)
  {
    return model;
  }

  static unsigned short int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< unsigned short int >(value);
  }
};

template<>
struct marshaling_traits< unsigned int > {
  using model_type = unsigned int;

  static variant
  marshal(unsigned int model)
  {
    return model;
  }

  static unsigned int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< unsigned int >(value);
  }
};

template<>
struct marshaling_traits< unsigned long int > {
  using model_type = unsigned long int;

  static variant
  marshal(unsigned long int model)
  {
    return model;
  }

  static unsigned long int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< unsigned long int >(value);
  }
};

// unsigned long long int

template<>
struct marshaling_traits< unsigned long long int > {
  using model_type = unsigned long long int;

  static variant
  marshal(unsigned long long int model)
  {
    return model;
  }

  static unsigned long long int
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< unsigned long long int >(value);
  }
};

template<>
struct marshaling_traits< float > {
  using model_type = float;

  static variant
  marshal(float model)
  {
    return model;
  }

  static float
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< float >(value);
  }
};

template<>
struct marshaling_traits< double > {
  using model_type = double;

  static variant
  marshal(double model)
  {
    return model;
  }

  static double
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< double >(value);
  }
};

template<>
struct marshaling_traits< long double > {
  using model_type = long double;

  static variant
  marshal(long double model)
  {
    return model;
  }

  static long double
  unmarshal(variant const& value)
  {
    if (!value.is_number())
      throw std::runtime_error{ "not a number" };

    return get< long double >(value);
  }
};

template<>
struct marshaling_traits< std::string > {
  using model_type = std::string;

  static variant
  marshal(std::string const& model)
  {
    return model;
  }

  static std::string
  unmarshal(variant const& value)
  {
    if (!value.is_string())
      throw std::runtime_error{ "not a string" };

    return get< std::string >(value);
  }
};

template< typename T >
struct marshaling_traits< std::vector< T > > {
  using model_type = std::vector< T >;

  static variant
  marshal(std::vector< T > const& model)
  {
    array ar;

    for (auto const& j : model)
      ar.emplace_back(marshaling_traits< T >::marshal(j));

    return ar;
  }

  static std::vector< T >
  unmarshal(variant const& value)
  {
    if (!value.is_array())
      throw std::runtime_error{ "not an array" };

    std::vector< T > model;

    for (auto const& j : value.get< json::array >())
      model.emplace_back(marshaling_traits< T >::unmarshal(j));

    return model;
  }
};

template< typename T >
struct marshaling_traits< std::list< T > > {
  using model_type = std::list< T >;

  static variant
  marshal(std::list< T > const& model)
  {
    array ar;

    for (auto const& j : model)
      ar.emplace_back(marshaling_traits< T >::marshal(j));

    return ar;
  }

  static std::list< T >
  unmarshal(variant const& value)
  {
    if (!value.is_array())
      throw std::runtime_error{ "not an array" };

    std::list< T > model;

    for (auto const& j : value.get< json::array >())
      model.emplace_back(marshaling_traits< T >::unmarshal(j));

    return model;
  }
};

template< typename T >
struct marshaling_traits< std::deque< T > > {
  using model_type = std::deque< T >;

  static variant
  marshal(std::deque< T > const& model)
  {
    array ar;

    for (auto const& j : model)
      ar.emplace_back(marshaling_traits< T >::marshal(j));

    return ar;
  }

  static std::deque< T >
  unmarshal(variant const& value)
  {
    if (!value.is_array())
      throw std::runtime_error{ "not an array" };

    std::deque< T > model;

    for (auto const& j : value.get< json::array >())
      model.emplace_back(marshaling_traits< T >::unmarshal(j));

    return model;
  }
};

template<>
struct marshaling_traits< std::chrono::system_clock::time_point > {
  using model_type = std::string;

  static variant
  marshal(std::chrono::system_clock::time_point const& model)
  {
    static constexpr const char time_format[] = "%a, %d %b %Y %H:%M:%S GMT";

    std::time_t now_c = std::chrono::system_clock::to_time_t(model);

    struct std::tm tm_buf;

    std::stringstream str;
    str.imbue(std::locale{});

#ifdef _MSC_VER
    ::gmtime_s(&tm_buf, &now_c); // Stupid Microsoft.
    str << std::put_time(&tm_buf, time_format);
#else
    ::gmtime_s(&now_c, &tm_buf);
    str << std::put_time(&tm_buf, time_format);
#endif

    return str.str();
  }

  static std::chrono::system_clock::time_point
  unmarshal(variant const& value)
  {
    // TODO implement
    throw std::runtime_error{ "not implemented" };
  }
};

} // namespace json::marshaling

#endif
