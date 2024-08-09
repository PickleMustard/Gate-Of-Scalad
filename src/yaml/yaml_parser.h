#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
namespace godot {
class YamlParser : RefCounted {
  GDCLASS(YamlParser, RefCounted);

public:
  YamlParser();
  ~YamlParser();

  void test_yaml();

protected:
  static void _bind_methods();


};

}


#endif
