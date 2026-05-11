class_name PlayerColorPalette
extends RefCounted

## Shared deterministic palette helper for multiplayer player colors.
##
## Keep this list as the single source of truth. Add, remove, or reorder entries
## here to change which colors can be assigned on spawn.
const COLORS: Dictionary = {
	"red": Color(0.95, 0.22, 0.25, 1.0),
	"blue": Color(0.18, 0.45, 1.00, 1.0),
	"green": Color(0.20, 0.85, 0.33, 1.0),
	"yellow": Color(1.00, 0.82, 0.18, 1.0),
	"purple": Color(0.62, 0.28, 1.00, 1.0),
	"orange": Color(1.00, 0.48, 0.18, 1.0),
	"cyan": Color(0.18, 0.90, 0.95, 1.0),
	"pink": Color(1.00, 0.35, 0.72, 1.0),
}

const ORDERED_COLOR_NAMES: Array[String] = [
	"red",
	"blue",
	"green",
	"yellow",
	"purple",
	"orange",
	"cyan",
	"pink",
]

static func color_for_spawn_key(spawn_key: String) -> Color:
	if ORDERED_COLOR_NAMES.is_empty():
		return Color.WHITE

	var color_name := color_name_for_spawn_key(spawn_key)
	return COLORS.get(color_name, Color.WHITE)

static func color_name_for_spawn_key(spawn_key: String) -> String:
	if ORDERED_COLOR_NAMES.is_empty():
		return "white"

	var index := _stable_hash(spawn_key) % ORDERED_COLOR_NAMES.size()
	return ORDERED_COLOR_NAMES[index]

static func _stable_hash(value: String) -> int:
	# FNV-1a style hash. String.hash() is intentionally not used so the same
	# player picks the same palette entry on every machine and Godot version.
	var hash := 2166136261
	for i in value.length():
		hash = hash ^ value.unicode_at(i)
		hash = (hash * 16777619) & 0x7fffffff
	return hash
