#include "register_types.h"
#include "godot_cpp/classes/engine.hpp"
#include "level_generator.h"
#include "seeded_random_access.h"
#include "tile_collision.h"
#include "tile_notifier.h"
#include "tilegrid.h"
#include "level.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	//ClassDB::register_class<GDExample>();
  //Tile Objects
  ClassDB::register_class<TileCollision>();
	ClassDB::register_class<TileGrid>();
	ClassDB::register_class<Tile>();

  //Level Objects
	ClassDB::register_class<LevelGenerator>();
  ClassDB::register_class<Level>();

  //Singletons
  ClassDB::register_class<SeededRandomAccess>();
  ClassDB::register_class<TileNotifier>();

  //Register Singletons
	SeededRandomAccess *SRA = memnew(SeededRandomAccess);
	Engine::get_singleton()->register_singleton("GlobalSeededRandom", SRA);

  TileNotifier *Notifier = memnew(TileNotifier);
  Engine::get_singleton()->register_singleton("GlobalTileNotifier", Notifier);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_gdextension_types);
	init_obj.register_terminator(uninitialize_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
