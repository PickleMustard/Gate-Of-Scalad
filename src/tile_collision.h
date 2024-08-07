#ifndef TILE_COLLISION_H
#define TILE_COLLISION_H

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/collision_object3d.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/static_body3d.hpp"
#include "godot_cpp/variant/vector3.hpp"
namespace godot {

class TileCollision : public StaticBody3D {
	GDCLASS(TileCollision, StaticBody3D);

public:
	static void _bind_methods();
	TileCollision();
	~TileCollision();
	void NotifyLog();
	void _input_event(Camera3D *camera, const Ref<InputEvent> &event, const Vector3 &position, const Vector3 &normal, int32_t shape_idx) override;
};
} //namespace godot

#endif
