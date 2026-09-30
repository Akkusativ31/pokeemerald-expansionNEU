# Project notes (read this first)

**Maintenance rule (for Claude):** after every finished feature, fix or design change in this project, update this file yourself
(rules, file locations, flags, open decisions) without being asked. Keep it short and accurate; remove things that are done or wrong.
**Every idea or plan the user writes goes into the todo section below**, even if it's only a "maybe". Claude's own suggestions only go in
once the user picks them.

A Nuzlocke-style hack built on **pokeemerald-expansion**. The player is trapped in the Mauville **Game Corner**
and must beat 8 bosses to escape (a final boss, likely Scott, is being discussed; no Elite Four). Everything happens through slot machines.
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
- Naming: encounter slots use "Spin" wording ("Spin slot N? You can only spin it once!"). The word for the 8 fights is still undecided
  ("boss"/"stage" still in text; "wager"/"gamble" are reserved for a later trading mechanic).
- Intro on first arrival from the truck: silent map, kidnapping dialogue (`VAR_GAME_CORNER_INTRO` = alias of `VAR_LOOP_STAGE`,
  music suppressed in `GetLocationMusic` in `src/overworld.c`). The old top-left trash can was removed; the starter trash can is at (21,4).
- Nurse (`Nursegame`): first talk explains the rules (`FLAG_NURSE_INTRO_DONE` = 0x028); skipped once `FLAG_BADGE01_GET` is set.
- A **test PC** is at (1,2) (bg event `EventScript_PC`). Delete it when done testing.

## Maps
- `RouteOne`..`RouteEight`: encounter rooms (same layout, small pond at x=8-11, y=4-7, return NPC at (18,7)).
  Entering shows the catch-limit message (`Route_EventScript_EncounterIntro`, VAR_TEMP_0) and gives Poke Balls = the route's limit.
  The Super Rod is given on a new game (`src/new_game.c`); the Route One fisherman was removed.
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
- Held items of Pokemon sent to the graveyard go back to the bag (already built into `SendDeadMonsToGraveyard`).
  Consumed non-berry held items (Focus Sash, White Herb, gems...) are restored after battle: `B_RESTORE_HELD_BATTLE_ITEMS` = GEN_LATEST (Gen 9).
- **All balls are guaranteed catches** (`B_ALL_BALLS_GUARANTEED_CATCH` in `include/config/battle.h`).
- **Fishing** (`src/fishing.c`): always bites, no timing. Fishing tables have 11 slots (Super Rod = slots 5-10, 6 slots).
  All route tables are still placeholders (test species, scaled levels). The user designs the real tables.
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
- Catch window vs. ball supply: **decided budget is 4 balls on route 1 and 3 balls on routes 2-8 (25 catches) + 8 gift boxes = 33**
  (see the black machines below; fallback 4 balls per route = 40). Currently the game gives window = 5 encounters and 5 balls, so saving a
  ball has no effect. The user wants **skipping a Pokemon to let you catch a better one on a later route**. Plan: window bigger than the
  ball supply (e.g. 6-8 encounters per route); leftover balls already stay in the bag, so a saved ball can be used on a later route.
  Balls cap the total, the window still stops rerolling. Not implemented yet: only needs the numbers in `sRouteEncounterLimits` (window) and the ball amount (currently = window,
  `GiveRouteEncounterBalls`) separated.
- Real encounter tables for all routes (12 land + 6 Super Rod per route). The user wants to design these. Wally's real team.
  User's note: a route themed around the next boss's weakness (e.g. Water before the Rock boss) is too easy / weak design.
  References the user looked at: Renegade Platinum wiki (fredericdlugi.github.io/platinum-renegade-wiki/wild_pokemon/...) and the
  Run & Bun Google Drive (its "Pokémon Locations" sheet, plus "Trainer Battles" and "AI Document for RnB").
  Run & Bun design philosophy (Claude's analysis, reference only; the user takes the philosophy, not their tools):
  loose type theme per route (~10 land species), several themes before each gym with traps and answers mixed (Fire route and Grass
  route before the Rock gym); rare 4%/1% slots stay on theme or hold one standout; pseudo-legendaries and other starters only as
  rare lotteries from mid-game; fishing/surf is a second pool with a different theme; a few fixed gifts/statics beside the luck.
- **Final boss: Scott** (the figure from the game over room), instead of an Elite Four. All Elite Four mentions were removed from the
  hack's text. Open: final level cap (after 62, e.g. 65-70), Scott's team (placeholder until the user sends one), win = credits or
  an ending message, and a front sprite (Emerald has no Scott battle picture: stand-in, custom sprite later, or a dark silhouette recolor).
- Naming of the 8 fights still open (the user rejected "test", Payout/Payline; "Spin" is used for the encounter slots;
  mahjong/casino ideas were discussed but not chosen).
- Random items after battles, free Ability Capsule / patches (no free mints), grey out the bag in battle.
- **Unique battle-start text for each leader**, matching their personality/team (currently all use the same template intro).
- **Shorter nurse tutorial**: cut the text down and let the player learn the rules more naturally (e.g. messages at the moment a rule
  applies, like the route-entry and dupes messages already do).
- **Better, easier-to-see PC** in the Game Corner (the test PC is invisible; it acts through an arcade machine at (1,2)).
- **Coin economy (user leaning yes, needs a lot of testing):** reuse the Game Corner's coin system.
  - Give the **Coin Case** instantly on a new game.
  - Coins as rewards (e.g. per fight; this could replace "random items after battles").
  - The Game Corner has **2 free NPC spots**: one shop NPC for **battle items**, one for **Mega Stones**, so neither list is long to scroll.
  - **Mints from a machine**, paid with coins.
  - **Buy Pokemon with coins, role-played as "buy free spins" / "feature buy"** (slot-machine bonus buy): coins buy extra spins,
    i.e. extra encounters/catches. Open: what exactly is bought (an extra encounter on a route, an extra ball, or a random Pokemon
    from a pool), price, and a limit (e.g. per badge) so it doesn't break the ~40-catch budget. Dupes clause should still apply.
    Reference: Run & Bun's Game Corner has a similar system: each badge unlocks a new reward set, and the Pokemon you get is random
    among the options (Knuckle: Smoochum/Elekid/Magby; Stone: Tauros/Miltank; Dynamo: Throh/Sawk; Balance: Pinsir/Heracross;
    Heat: Larvitar/Beldum; Feather: Dratini/Bagon/Deino; Mind: Gible/Goomy/Jangmo-o/Dreepy; Rain: Mew/Celebi/Jirachi/Victini).
  - **Kubfu / Urshifu** (user's idea, maybe): Run & Bun gives a gift Kubfu in Mossdeep City (late, ~7th gym area). Mossdeep also has
    wild encounters, so under normal Nuzlocke rules the gift costs that area's encounter: offered for sure, but not a free extra. In expansion Kubfu evolves with the items
    Scroll of Darkness (Single Strike) / Scroll of Waters (Rapid Strike) via EVO_ITEM, so a gift Kubfu plus the player's choice of scroll
    (later, e.g. from the prize counter) would be a meaningful choice. Where it's given is open (black machine gift, prize, etc.).
  - No free mints (decided). Amounts and prices to be decided when testing.
- Remove the test PC in the Game Corner before release.
- **Planned layout of the Game Corner (not built yet, do not implement until asked; the user can't test right now):**
  - **Left roulette table** (x=14-15, y=6-8, `Roulette_EventScript_Table1`): the fights. It offers the next fight in order
    ("Take a seat? Your opponent: ROXANNE"), warping to BossN. Arenas, badges and level cap messages stay the same.
  - **Right roulette table** (x=18-19, y=6-8, `Roulette_EventScript_Table2`): the **gamble mechanic**. Once per badge, the player can
    gamble away one bad encounter (a single caught Pokemon). Open: what the player gets back (a random new Pokemon? from which pool/level?),
    whether the use carries over if skipped, and whether dead/graveyard Pokemon are allowed.
    This table needs a **recolor** so it stands out (like the black slot machines got).
  - **The 8 black slot machines** (x=7-8, y=6-9), **current direction (user): random gift boxes**, one per stage: each gives one Pokemon
    at random from a small pool (several possible results, like Renegade's random gifts / Run & Bun's per-badge Game Corner rewards),
    so the player has to adapt. This gives a second pool/theme per stage without a second route. Gifts count toward the stage budget.
    **Decided budget (user agreed): stage 1 = 4 balls + 1 gift box, stages 2-8 = 3 balls + 1 gift box each: 25 catches + 8 gifts = 33,
    plus the starter.** Fallback if testing shows it's too tight: 4 balls per stage (40 total). Encounter window per route stays larger
    than the balls so skipping is a real choice. Still open: pools per stage (niche early, stronger mid/late) and rerolling if the result's
    family is already caught (dupes clause).
    Earlier ideas for them:
    **special static / gift encounters**, not fights (one per badge, presumably).
    User's ideas: machine 1 = a guaranteed **Eevee**; later machines give **Paradox Pokemon**, but from a curated pool,
    since some Paradox Pokemon are weak (note: Sandy Shocks and Iron Treads are already on boss teams). Details open.
    **Alternative (user's idea, open):** use the black machines as a **second encounter route per stage** (16 routes, two themes per stage,
    closer to Run & Bun's several met locations before each gym). Then the gifts (Eevee, curated Paradox) need another home
    (e.g. from the nurse after each badge). Balls/windows would need rebalancing to stay near 40 catches (e.g. window 4 + 3 balls per route).
    User's current leaning: **split the 5 catches per stage across the two slots** (normal + black). Proposal: 5 balls per stage shared by
    both rooms, window 4 encounters per room (8 draws per stage), leftover balls carry over, total stays 40 (Run & Bun gives more, but has
    many more fights; the user doesn't want that difficulty or too many options). Open: give all 5 balls on entering the stage's first room
    (Claude's suggestion) or a fixed 3 + 2 split.
    Comparison (Claude's count of Renegade Platinum met locations; floors/sections merged; starter = the Route 201 slot; gifts count when
    their location is new: Sandgem extra starter, Jubilife egg/Kanto starter, Oreburgh Hoenn starter, Floaroma Johto starter, Eterna
    Galactic Building Porygon; Beldum removed; rod from the start; dupes clause makes ~1-3 tiny water tables dead by gym 4):
    ~13 before gym 1, ~24 before gym 2, ~27 before gym 3, ~31-34 before Maylene (gym 4), ~58 before the Elite Four, ~69 with post-game. This hack: 5/stage = 20 by
    stage 4, 40 total (+ starter + gifts), but every catch is guaranteed and chosen from a window, so fewer "trash" catches.
  - **"Enter the slot" transition: BUILT, not yet tested by the user.** `DoSlotGlitchEffect` at the end of `src/field_specials.c`
    (special + `waitstate`): the screen **pixelates** (GBA hardware mosaic on all 4 BGs and all sprites, growing to 16px over
    `PIXEL_FRAMES` = 36 frames) with PC-on / Thunder Wave / warp-out sounds, then fades to black and turns mosaic off behind the black
    screen. Called in all 8 encounter slot scripts right before `warpsilent`. (The first version was a color-flicker glitch; the user
    preferred pixelation "like getting transported into the screen".) **Arrival does the reverse**: the effect sets a pending flag,
    and `FieldCB_DefaultWarpExit` (`src/field_screen_effect.c`) calls `TryStartSlotArrivalEffect`, which starts the new map fully
    pixelated and sharpens it over the same 36 frames while it fades in (warp-in sound). Only the map layers BG1-3 and sprites are
    pixelated; BG0 (text windows) stays sharp.
  - **Route exit = Deoxys triangle: BUILT, not yet tested by the user.** In all 8 routes the exit object at (18,7) uses
    `OBJ_EVENT_GFX_DEOXYS_TRIANGLE` (MOVEMENT_TYPE_NONE). Script `RouteX_EventScript_ReturnNPC`: "The triangle hums quietly... Cash out and
    leave this spin?" -> pixel-out effect (`DoSlotGlitchEffect`) -> warp to the Game Corner (11,6), which sharpens back in.
    Earlier notes on the choice (user's idea): the "return to the Hub?" boy at (18,7) in every route should fit the
    "inside the machine" RP. Options: Porygon as the machine's program (Claude's pick, `OBJ_EVENT_GFX_SPECIES(PORYGON)`), Rotom,
    a Game Corner attendant, or an object like a "CASH OUT" machine. The user also suggested an object like the **Deoxys triangle**
    (`OBJ_EVENT_GFX_DEOXYS_TRIANGLE`, dark stone pyramid from Birth Island; native Emerald sprite, can't turn to face the player),
    or the round glowing light (`OBJ_EVENT_GFX_LIGHT_SPRITE`). Casino wording ("Cash out?"), and the pixel effect on the way back.
  - **Fights at the table: the opponent appears and walks to the table** (user's idea). Feasibility notes: one hidden object event with a
    variable sprite (`OBJ_EVENT_GFX_VAR_0` + `setvar VAR_OBJ_GFX_ID_0`, then `addobject`/`applymovement`/`removeobject`) can show
    whichever leader is next, walk them to the table, then start `trainerbattle`. Open: does the battle then happen right at the table
    (arenas unused) or does it still warp to the arena afterwards?
  - Tutorials to update when this is built: the nurse's rule explanation (currently says the black machines are the boss arenas),
    plus lines for the tables and the gamble mechanic. Naming: "Spin" for slots; "wager"/"gamble" belongs to the right table.
- **Planned (not built yet): Scott's entrance, FRLG Rocket Hideout style.** After beating fight 8: screen shake, message
  like "A door opened somewhere...", and a hidden staircase appears in the Game Corner (like the FRLG Celadon Game Corner
  poster/secret stairs), leading down to the final room with Scott. Candidate name for that fight: "Jackpot".
  The user will test this later; do not implement until asked.
- Decided against: erasing the save on whiteout (players should be able to reflect on losses), autoheal, the "Norman rock type cap 16" note,
  Tate & Liza as a boss (double battles too hard to design, and Trick Room is already on Norman's team), an Elite Four.
- Vanilla maps still have 10 fishing slots (harmless: they are not reachable in this hack).
