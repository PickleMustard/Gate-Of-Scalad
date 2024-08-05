#ifndef TILE_H
#define TILE_H

#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/classes/collision_object3d.hpp"
#include "godot_cpp/classes/collision_shape3d.hpp"
#include "godot_cpp/classes/mesh.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/string.hpp"
#include "tile_collision.h"
#include "tile_mesh_generator.h"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class Tile : public Node3D {
	GDCLASS(Tile, Node3D)
private:
	Vector3 m_position;
	int m_tile_row;
	int m_tile_column;
	int m_g_cost;
	int m_h_cost;
	bool m_tile_is_flat_topped;
	float m_tile_outer_size;
	float m_tile_inner_size;
	float m_tile_height;
  String m_tile_type; //Defines the type of the tile walkable, interacable, obstacle, wall
  String m_tile_mesh_name;
  Tile *m_path_parent;
	MeshInstance3D *m_mesh_inst = memnew(MeshInstance3D);
	TileCollision *m_collision_body = memnew(TileCollision);
	CollisionShape3D *m_collision_shape = memnew(CollisionShape3D);
  TileMeshGenerator *m_mesh_generator;
	Ref<Mesh> m_mesh = memnew(Mesh);
	ResourceLoader *m_rl = memnew(ResourceLoader);
	void (*TileSelected)(Tile *);

public:
	static void _bind_methods();
	void _notification(int p_what);

	Tile();
	Tile(Vector3 position, int r, int c, bool flat_topped, float outer_size, float inner_size, float height);
	~Tile();

	Vector2i GetLocation();
	void SetLocation(Vector2i new_location);
	int GetRow();
	void SetRow(int new_row);
	int GetColumn();
  void SetColumn(int new_row);
  bool GetFlatTopped();
  void SetFlatTopped(bool is_flat);
  float GetOuterSize();
  void SetOuterSize(float new_size);
  float GetInnerSize();
  void SetInnerSize(float new_size);
  float GetTileHeight();
  void SetTileHeight(float new_height);
  Vector3 GetTilePosition();
	void SetTilePosition(Vector3 new_pos);
	void SetOwner(Node *owner);
  void SetGCost(int new_g_cost);
  int GetGCost();
  void SetHCost(int new_h_cost);
  int GetHCost();
  int GetFCost();
  String GetTileType();
  Tile *GetParent();
  void SetParent(Tile *parent);


  void NotifyLog();
};

} //namespace godot

#endif
