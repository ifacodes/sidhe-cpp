/* Thanks to val / einpoklum: https://stackoverflow.com/a/58331141/14658973 */

#include <string_view>

template <typename T>
constexpr std::string_view type_name();

template <>
constexpr std::string_view type_name<void>() {
  return "void";
}

namespace typeprobe {

using type_name_probe = void;

template <typename T>
constexpr std::string_view wrapped_type_name() {
#ifdef __clang__
  return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
  return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
  return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
}

constexpr size_t wrapped_type_name_prefix_length() {
  return wrapped_type_name<type_name_probe>().find(
      type_name<type_name_probe>());
}

constexpr size_t wrapped_type_name_suffix_length() {
  return wrapped_type_name<type_name_probe>().length() -
         wrapped_type_name_prefix_length() -
         type_name<type_name_probe>().length();
}

}  // namespace typeprobe

template <typename T>
constexpr std::string_view type_name() {
  constexpr auto wrapped_name = typeprobe::wrapped_type_name<T>();
  constexpr auto prefix_length = typeprobe::wrapped_type_name_prefix_length();
  constexpr auto suffix_length = typeprobe::wrapped_type_name_suffix_length();
  constexpr auto type_name_length =
      wrapped_name.length() - prefix_length - suffix_length;
  return wrapped_name.substr(prefix_length, type_name_length);
}