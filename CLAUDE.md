# Project notes (read this first)

A Nuzlocke-style hack built on **pokeemerald-expansion**. The player is trapped in the Mauville **Game Corner**
and must beat 8 bosses (then the Elite Four) to escape. Everything happens through slot machines.
The repo lives in WSL Ubuntu at `~/decomps/pokeemerald-expansion`.

## How to build / work
- Build (from Windows): `wsl -d Ubuntu -- bash -lc 'cd ~/decomps/pokeemerald-expansion && make -j$(nproc)'` -> `pokeemerald.gba`.
- There is no `python3` in Git Bash, but there is one **inside WSL**. Run scripts through `wsl -d Ubuntu -- bash -lc '...'`.
- **Close Porymap while building.** It once overwrote `src/data/heal_locations.json` with an empty file (0 bytes) and broke the build.
  Fix was `git checkout -- src/data/heal_locations.json`.
- When writing `.string` text from a script, `\n` gets turned into a real newline by the shell layers. Write text with the Edit tool
  (or a script file) and check that each `.string "..."` line ends with `\n"` on the same line.
- Editing files over the `\\wsl.localhost\...` path sometimes fails once with `EPERM`; just retry the edit.
- `data/maps/RouteOne/scripts.pory` mirrors `scripts.inc` (raw assembly). Keep both in sync when editing Route One.
- Nothing here has been play-tested by Claude (no emulator). The user tests in mGBA and reports back.

## The hub (Mauville Game Corner) - `data/maps/MauvilleCity_GameCorner/`
- 16 slot machines, stage `n` = 1..8: encounter slot at x=2+(n-1)/4, y=6+(n-1)%4 (left, orange), boss slot at x+5 (right, black).
- Encounter room `n` needs badge n-1 and can only be entered **once** (`FLAG_ENCOUNTER_n_USED`, unused flags 0x020-0x027).
  Boss room `n` needs badge n-1 and closes once badge n is earned. All slot scripts are at the end of `scripts.inc`.
- Black boss machines: palette `data/tilesets/secondary/mauville_game_corner/palettes/10.pal`, metatiles 0x260-0x267.
- Intro on first arrival from the truck: silent map, kidnapping dialogue (`VAR_GAME_CORNER_INTRO` = alias of `VAR_LOOP_STAGE`,
  music suppressed in `GetLocationMusic` in `src/overworld.c`). The old top-left trash can was removed; the starter trash can is at (21,4).
- Nurse (`Nursegame`): first talk explains the rules (`FLAG_NURSE_INTRO_DONE` = 0x028); skipped once `FLAG_BADGE01_GET` is set.
- A **test PC** is at (1,2) (bg event `EventScript_PC`). Delete it when done testing.

## Maps
- `RouteOne`..`RouteEight`: encounter rooms (same layout, small pond at x=8-11, y=4-7, return NPC at (18,7)).
  Entering shows the catch-limit message (`Route_EventScript_EncounterIntro`, VAR_TEMP_0) and gives Poke Balls = the route's limit.
  Route One also has the Fisherman (7,6) who gives the Super Rod.
- `BossOne`..`BossEight`: arenas with the leader NPC. Defeating one sets the badge, announces the new level cap, warps back to the hub.
- `GameOverRoom`: dark room (8x8 pyramid floor, flash-level darkness) with Scott behind the player. See "Whiteout".

## Bosses - `src/data/trainers.party`
Roxanne `TRAINER_ROXANNE_1` (Lv16), Brawly `_BRAWLY_1` (26), Wattson `_WATTSON_1` (33), Flannery `_FLANNERY_1` (39), Norman `_NORMAN_1` (44),
Winona `_WINONA_1` (53), Wallace `TRAINER_WALLACE` (56), Wally `TRAINER_WALLY_VR_5` (62, **placeholder team**).
Teams come from the user's Showdown exports. AI: `Smart Trainer / Prediction / Try To 2HKO / HP Aware / Powerful Status`,
each has a mugshot color. EVs are 0 and IVs 31 except Manectric (Speed 30 = Hidden Power Ice) and Farigiraf/Slaking (0 Speed).
Enemies can **never Terastallize** (`ShouldTrainerBattlerUseGimmick` in `src/battle_gimmick.c`).

## Rules implemented
- **Level caps** (`src/caps.c`, `include/config/caps.h`): cap = top level of the next boss by badge: 16, 26, 33, 39, 44, 53, 56, 62; none after badge 8.
  Hard EXP cap and Rare Candy cap are on. Bosses announce the new cap.
- **Perma-death**: a fainted Pokemon gets the `isDead` bit (`include/pokemon.h`, `MON_DATA_IS_DEAD`, set in `SetMonData(MON_DATA_HP)` in `src/pokemon.c`).
  Dead Pokemon can't be healed/revived (nurse, items, PC heal).
- **Graveyard**: dead party Pokemon move to the last PC box (`GRAVEYARD_BOX`, named GRAVES) after every non-whiteout battle and when healing
  (`SendDeadMonsToGraveyard` in `src/pokemon_storage_system.c`, called from `DowngradeBadPoison` in `src/battle_setup.c` and `HealPlayerParty`).
  The box is locked in the PC (view/summary only). A message is shown (`HasGraveyardMessagePending` hook in `src/field_control_avatar.c`).
- **Encounter clause** (`src/wild_encounter.c`): per-route catch window shared by land, water and fishing. Limit per route is in the
  `sRouteEncounterLimits` table (currently 5 everywhere); counters live in SaveBlock3 (`routeEncounters`).
  **Dupes clause**: a species whose evolution family is already caught can't be caught and doesn't use up an encounter (`IsSpeciesFamilyCaught` in `src/pokemon.c`).
  Blocked balls show a message from `src/item_use.c`. Scripted/static encounters ignore the window.
- **All balls are guaranteed catches** (`B_ALL_BALLS_GUARANTEED_CATCH` in `include/config/battle.h`).
- **Fishing** (`src/fishing.c`): always bites, no timing. Fishing tables have 11 slots (Super Rod = slots 5-10, 6 slots).
  Tables for Routes 2-8 are placeholders (water Pokemon, same levels as the land tables).
- **Level to Cap**: party menu entry after ITEM (`CursorCb_LevelToCap` in `src/party_menu.c`) and a PC version (`Task_LevelToCap` in
  `src/pokemon_storage_system.c`). Shared helpers in `src/pokemon.c` (`GetLevelToCapTarget`, `SetMonLevelViaExp`). Evolution scene is instant (`src/evolution_scene.c`).
- **Whiteout = game over**: `CB2_WhiteOut` (`src/overworld.c`) warps to `GameOverRoom`, the player spawns facing up
  (`GetAdjustedInitialDirection`), Scott says "Hmph... I'm disappointed...", then `DoSoftReset`. The save is not erased.
- **Starter**: trash can uses `special ChooseStarterNoBattle` (original bag screen, no battle). Treecko / Charmander / Totodile, plus the
  Mega Stone of the final evolution (Sceptilite / Charizardite X / Feraligite). Mega Ring, National Dex given at new game (`src/new_game.c`).
- Other settings already on: instant text, no bag in battle, shiny odds 1/512, no EV gain, `B_SHOW_TYPES` always, effectiveness always,
  low-HP beep 3 times, Pokedex button removed from the start menu.

## Graphics
- Player sprites (Brendan/May) were recolored (soft off-white hat, graphite clothes, deep red accents) by editing palettes only
  (object event, trainer front/back, decoration, intro, credits, region-map icon). Originals are in git.

## Open decisions / todo
- Catch window vs. ball supply: currently both = 5 per route, so saving a ball has no effect. Proposal was window 8 / balls 5 (awaiting the user's numbers).
- Real encounter tables (12 land + 6 Super Rod per route, themed). Wally's real team. Norman "rock type cap 16" note is unclear.
- Autoheal, random items after battles, free Ability Capsule / mints / patches, Paradox Pokemon before the finale, Tate & Liza Trick Room.
- Whiteout: optionally erase the save for true permadeath (destructive, needs the user's yes).
- Vanilla maps still have 10 fishing slots (harmless: they are not reachable in this hack).
