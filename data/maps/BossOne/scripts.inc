BossOne_MapScripts::
	.byte 0

BossOne_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, BossOne_Text_Intro, BossOne_Text_Defeat, BossOne_EventScript_Defeated
	msgbox BossOne_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossOne_EventScript_Defeated::
	message BossOne_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE01_GET
	msgbox BossOne_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossOne_Text_Intro:
	.string "I am ROXANNE, boss of stage 1!\n"
	.string "Show me what your team can do!$"

BossOne_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossOne_Text_ReceivedBadge:
	.string "{PLAYER} received the STONE BADGE!$"

BossOne_Text_PostBattle:
	.string "You have mastered stage 1!\n"
	.string "Teleporting you back to the hub...$"
