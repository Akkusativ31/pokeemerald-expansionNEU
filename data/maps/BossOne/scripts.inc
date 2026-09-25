BossOne_MapScripts::
	.byte 0

BossOne_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN_1, BossOne_Text_NormanIntro, BossOne_Text_NormanDefeat, BossOne_EventScript_NormanDefeated
	msgbox BossOne_Text_NormanPostBattle, MSGBOX_DEFAULT
	release
	end

BossOne_EventScript_NormanDefeated::
	lock
	faceplayer
	msgbox BossOne_Text_NormanPostBattle, MSGBOX_DEFAULT
	closemessage
	setvar VAR_LOOP_STAGE, 2  @ Schaltet Boss 1 ab und schaltet Stage 2 Encounter frei!
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossOne_Text_NormanIntro:
	.string "Willkommen in der Boss-Arena!\n"
	.string "Zeige mir, was dein Team draufhat!$"

BossOne_Text_NormanDefeat:
	.string "Unglaublich... Eine hervorragende\n"
	.string "Strategie!$"

BossOne_Text_NormanPostBattle:
	.string "Du hast Stage 1 gemeistert!\n"
	.string "Teleportiere zurück zum Hub...$"