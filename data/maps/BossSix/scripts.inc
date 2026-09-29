BossSix_MapScripts::
	.byte 0

BossSix_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, BossSix_Text_Intro, BossSix_Text_Defeat, BossSix_EventScript_Defeated
	msgbox BossSix_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossSix_EventScript_Defeated::
	message BossSix_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE06_GET
	msgbox BossSix_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossSix_Text_Intro:
	.string "I am WINONA, boss of stage 6!\n"
	.string "Show me what your team can do!$"

BossSix_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossSix_Text_ReceivedBadge:
	.string "{PLAYER} received the FEATHER BADGE!$"

BossSix_Text_PostBattle:
	.string "You have mastered stage 6!\n"
	.string "Teleporting you back to the hub...$"
