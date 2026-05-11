class_name AutoPlayerSpawnColors
extends Node

## Drop-in/autoload helper that colors player meshes on spawn without touching
## the existing player controller or multiplayer synchronizer scripts.
##
## The color is deterministic from the spawned player's authority/name, so every
## peer computes the same material color for the same player without adding new
## synced properties to the networking code.

@export var player_group_names: Array[StringName] = [&"players", &"Players"]
@export var player_name_tokens: Array[String] = ["PlayerController", "Player", "MrStick", "Mr. Stick"]
@export var ignored_mesh_name_tokens: Array[String] = ["collision", "debug", "camera", "shadow"]
@export var scan_interval_seconds := 0.25
@export var material_parameter_name := &"albedo_color"

var _elapsed := 0.0
var _colored_instance_ids: Dictionary = {}

func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	_scan_for_players()

func _process(delta: float) -> void:
	_elapsed += delta
	if _elapsed < scan_interval_seconds:
		return

	_elapsed = 0.0
	_scan_for_players()

func _scan_for_players() -> void:
	var candidates: Array[Node] = []
	for group_name in player_group_names:
		candidates.append_array(get_tree().get_nodes_in_group(group_name))

	_find_name_candidates(get_tree().root, candidates)
	for candidate in candidates:
		_apply_color_if_needed(candidate)

func _find_name_candidates(node: Node, candidates: Array[Node]) -> void:
	if _looks_like_player(node) and not candidates.has(node):
		candidates.append(node)

	for child in node.get_children():
		_find_name_candidates(child, candidates)

func _looks_like_player(node: Node) -> bool:
	var node_name := String(node.name).to_lower()
	for token in player_name_tokens:
		if node_name.contains(token.to_lower()):
			return true
	return false

func _apply_color_if_needed(player: Node) -> void:
	if not is_instance_valid(player):
		return

	var instance_id := player.get_instance_id()
	if _colored_instance_ids.has(instance_id):
		return

	var spawn_key := _spawn_key_for_player(player)
	var color := PlayerColorPalette.color_for_spawn_key(spawn_key)
	var color_name := PlayerColorPalette.color_name_for_spawn_key(spawn_key)
	var changed_meshes := _apply_color_to_meshes(player, color)
	if changed_meshes > 0:
		player.set_meta(&"spawn_color_name", color_name)
		player.set_meta(&"spawn_color", color)
		_colored_instance_ids[instance_id] = true

func _spawn_key_for_player(player: Node) -> String:
	var authority := 0
	if player.has_method("get_multiplayer_authority"):
		authority = player.get_multiplayer_authority()

	var path_text := String(player.get_path())
	if authority > 0:
		return "%s:%s" % [authority, String(player.name)]
	return path_text

func _apply_color_to_meshes(root: Node, color: Color) -> int:
	var changed := 0
	if root is MeshInstance3D and not _is_ignored_mesh(root):
		_color_mesh_instance(root, color)
		changed += 1

	for child in root.get_children():
		changed += _apply_color_to_meshes(child, color)
	return changed

func _is_ignored_mesh(mesh_instance: MeshInstance3D) -> bool:
	var mesh_name := String(mesh_instance.name).to_lower()
	for token in ignored_mesh_name_tokens:
		if mesh_name.contains(token.to_lower()):
			return true
	return false

func _color_mesh_instance(mesh_instance: MeshInstance3D, color: Color) -> void:
	var surface_count := 1
	if mesh_instance.mesh != null:
		surface_count = max(1, mesh_instance.mesh.get_surface_count())

	for surface_index in surface_count:
		var material := mesh_instance.get_surface_override_material(surface_index)
		if material == null and mesh_instance.mesh != null:
			material = mesh_instance.mesh.surface_get_material(surface_index)
		if material == null:
			material = StandardMaterial3D.new()
		else:
			material = material.duplicate(true)

		if material is StandardMaterial3D:
			material.albedo_color = color
		elif material is ShaderMaterial:
			material.set_shader_parameter(material_parameter_name, color)

		mesh_instance.set_surface_override_material(surface_index, material)
