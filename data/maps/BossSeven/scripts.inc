BossSeven_MapScripts::
	.byte 0

BossSeven_EventScript_Wallace::
	trainerbattle_single TRAINER_WALLACE, BossSeven_Text_Intro, BossSeven_Text_Defeat, BossSeven_EventScript_Defeated
	msgbox BossSeven_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossSeven_EventScript_Defeated::
	message BossSeven_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE07_GET
	msgbox BossSeven_Text_LevelCap, MSGBOX_DEFAULT
	msgbox BossSeven_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossSeven_Text_Intro:
	.string "I am WALLACE, boss of stage 7!\n"
	.string "Show me what your team can do!$"

BossSeven_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossSeven_Text_ReceivedBadge:
	.string "{PLAYER} received the MIND BADGE!$"

BossSeven_Text_PostBattle:
	.string "You have mastered stage 7!\n"
	.string "Teleporting you back to the hub...$"

BossSeven_Text_LevelCap:
	.string "The level cap is now 62!$"
