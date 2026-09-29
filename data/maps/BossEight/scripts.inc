BossEight_MapScripts::
	.byte 0

BossEight_EventScript_Wally::
	trainerbattle_single TRAINER_WALLY_VR_5, BossEight_Text_Intro, BossEight_Text_Defeat, BossEight_EventScript_Defeated
	msgbox BossEight_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossEight_EventScript_Defeated::
	message BossEight_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE08_GET
	msgbox BossEight_Text_LevelCap, MSGBOX_DEFAULT
	msgbox BossEight_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossEight_Text_Intro:
	.string "I am WALLY, boss of stage 8!\n"
	.string "Show me what your team can do!$"

BossEight_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossEight_Text_ReceivedBadge:
	.string "{PLAYER} received the RAIN BADGE!$"

BossEight_Text_PostBattle:
	.string "You have mastered stage 8!\n"
	.string "Teleporting you back to the hub...$"

BossEight_Text_LevelCap:
	.string "The level cap is lifted!$"
