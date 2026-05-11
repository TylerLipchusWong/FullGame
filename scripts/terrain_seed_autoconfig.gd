class_name TerrainSeedAutoconfig
extends Node

## Drop-in/autoload terrain helper.
##
## It randomizes FastNoiseLite-style seeds on the multiplayer authority, shares
## that seed with peers from this isolated helper, then asks common terrain
## scripts to regenerate. It also nudges players above the generated surface so
## they do not spawn inside terrain when the new seed changes the height at 0,0.

@export var terrain_group_names: Array[StringName] = [&"terrain", &"Terrain"]
@export var terrain_name_tokens: Array[String] = ["Terrain", "WorldTerrain"]
@export var seed_property_names: Array[StringName] = [&"seed", &"terrain_seed", &"world_seed"]
@export var noise_property_names: Array[StringName] = [&"noise", &"terrain_noise", &"height_noise"]
@export var regenerate_method_names: Array[StringName] = [&"regenerate", &"generate", &"generate_terrain", &"build", &"rebuild"]
@export var player_container_path: NodePath = ^"/root/World/Players"
@export var spawn_clearance := 3.0
@export var spawn_probe_height := 500.0
@export var spawn_probe_depth := 1000.0
@export var post_generation_spawn_fix_delay := 0.25

var _seed := 0
var _seed_applied := false
var _last_had_multiplayer_peer := false

func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	_last_had_multiplayer_peer = multiplayer.has_multiplayer_peer()
	if _last_had_multiplayer_peer and not multiplayer.is_server():
		_request_seed.rpc_id(1)
	else:
		_apply_seed(_create_random_seed())

func _process(_delta: float) -> void:
	var has_peer := multiplayer.has_multiplayer_peer()
	if has_peer == _last_had_multiplayer_peer:
		return

	_last_had_multiplayer_peer = has_peer
	if not has_peer:
		return
	if multiplayer.is_server():
		_receive_seed.rpc(_seed)
	else:
		_request_seed.rpc_id(1)

@rpc("any_peer", "call_remote", "reliable")
func _request_seed() -> void:
	if not multiplayer.is_server():
		return
	if _seed == 0:
		_apply_seed(_create_random_seed())
	_receive_seed.rpc_id(multiplayer.get_remote_sender_id(), _seed)

@rpc("authority", "call_remote", "reliable")
func _receive_seed(seed: int) -> void:
	_apply_seed(seed)

func _create_random_seed() -> int:
	var rng := RandomNumberGenerator.new()
	rng.randomize()
	return rng.randi_range(1, 2147483647)

func _apply_seed(seed: int) -> void:
	_seed = seed
	_seed_applied = true
	for terrain in _find_terrain_nodes():
		_apply_seed_to_terrain(terrain, seed)
		_call_regenerate(terrain)

	if multiplayer.has_multiplayer_peer() and multiplayer.is_server():
		_receive_seed.rpc(seed)

	await get_tree().create_timer(post_generation_spawn_fix_delay).timeout
	_place_players_above_surface()

func _find_terrain_nodes() -> Array[Node]:
	var terrains: Array[Node] = []
	for group_name in terrain_group_names:
		terrains.append_array(get_tree().get_nodes_in_group(group_name))
	_find_terrain_name_candidates(get_tree().root, terrains)
	return terrains

func _find_terrain_name_candidates(node: Node, terrains: Array[Node]) -> void:
	var node_name := String(node.name).to_lower()
	for token in terrain_name_tokens:
		if node_name.contains(token.to_lower()) and not terrains.has(node):
			terrains.append(node)
			break

	for child in node.get_children():
		_find_terrain_name_candidates(child, terrains)

func _apply_seed_to_terrain(terrain: Node, seed: int) -> void:
	for property_name in seed_property_names:
		if _has_property(terrain, property_name):
			terrain.set(property_name, seed)

	for noise_property_name in noise_property_names:
		if not _has_property(terrain, noise_property_name):
			continue
		var noise_resource = terrain.get(noise_property_name)
		if noise_resource != null and _has_property(noise_resource, &"seed"):
			noise_resource.set(&"seed", seed)

func _call_regenerate(terrain: Node) -> void:
	for method_name in regenerate_method_names:
		if terrain.has_method(method_name):
			terrain.call(method_name)
			return

func _place_players_above_surface() -> void:
	var container := get_node_or_null(player_container_path)
	if container == null:
		return
	for player in container.get_children():
		if player is Node3D:
			_place_player_above_surface(player)

func _place_player_above_surface(player: Node3D) -> void:
	var world := player.get_world_3d()
	if world == null:
		return

	var origin := player.global_position + Vector3.UP * spawn_probe_height
	var target := player.global_position - Vector3.UP * spawn_probe_depth
	var query := PhysicsRayQueryParameters3D.create(origin, target)
	query.collide_with_areas = false
	query.collide_with_bodies = true
	var hit := world.direct_space_state.intersect_ray(query)
	if hit.has("position"):
		var hit_position: Vector3 = hit["position"]
		if player.global_position.y < hit_position.y + spawn_clearance:
			player.global_position.y = hit_position.y + spawn_clearance

func _has_property(object: Object, property_name: StringName) -> bool:
	for property in object.get_property_list():
		if property.get("name") == String(property_name):
			return true
	return false
