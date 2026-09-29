BossThree_MapScripts::
	.byte 0

BossThree_EventScript_Wattson::
	trainerbattle_single TRAINER_WATTSON_1, BossThree_Text_Intro, BossThree_Text_Defeat, BossThree_EventScript_Defeated
	msgbox BossThree_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossThree_EventScript_Defeated::
	message BossThree_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE03_GET
	msgbox BossThree_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossThree_Text_Intro:
	.string "I am WATTSON, boss of stage 3!\n"
	.string "Show me what your team can do!$"

BossThree_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossThree_Text_ReceivedBadge:
	.string "{PLAYER} received the DYNAMO BADGE!$"

BossThree_Text_PostBattle:
	.string "You have mastered stage 3!\n"
	.string "Teleporting you back to the hub...$"
