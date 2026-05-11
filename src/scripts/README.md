# Drop-in Godot helpers

These scripts are intentionally isolated from the existing player controller,
multiplayer spawner/synchronizer, and terrain scripts.

Recommended setup in Godot:

1. Use this `src/scripts/` folder inside the Godot project.
2. Add `src/scripts/auto_player_spawn_colors.gd` as an Autoload singleton.
3. Add `src/scripts/terrain_seed_autoconfig.gd` as an Autoload singleton.
4. Edit only `src/scripts/player_color_palette.gd` when you want to change the list
   of possible player colors.

`AutoPlayerSpawnColors` scans spawned player nodes and assigns a palette color
that is deterministic from the player's authority/name. Because every peer can
calculate the same key, both players see the same color without changing the
existing networking code.

`TerrainSeedAutoconfig` picks a random terrain seed on the host/server, applies
it to common terrain seed/noise properties, asks terrain scripts to regenerate,
and moves spawned players upward with a physics raycast if the new surface is
above their current spawn height.
