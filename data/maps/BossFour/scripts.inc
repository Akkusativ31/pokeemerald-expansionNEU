BossFour_MapScripts::
	.byte 0

BossFour_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, BossFour_Text_Intro, BossFour_Text_Defeat, BossFour_EventScript_Defeated
	msgbox BossFour_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossFour_EventScript_Defeated::
	message BossFour_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE04_GET
	msgbox BossFour_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossFour_Text_Intro:
	.string "I am FLANNERY, boss of stage 4!\n"
	.string "Show me what your team can do!$"

BossFour_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossFour_Text_ReceivedBadge:
	.string "{PLAYER} received the HEAT BADGE!$"

BossFour_Text_PostBattle:
	.string "You have mastered stage 4!\n"
	.string "Teleporting you back to the hub...$"
