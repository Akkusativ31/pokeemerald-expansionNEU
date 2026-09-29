BossTwo_MapScripts::
	.byte 0

BossTwo_EventScript_Brawly::
	trainerbattle_single TRAINER_BRAWLY_1, BossTwo_Text_Intro, BossTwo_Text_Defeat, BossTwo_EventScript_Defeated
	msgbox BossTwo_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossTwo_EventScript_Defeated::
	message BossTwo_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE02_GET
	msgbox BossTwo_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossTwo_Text_Intro:
	.string "I am BRAWLY, boss of stage 2!\n"
	.string "Show me what your team can do!$"

BossTwo_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossTwo_Text_ReceivedBadge:
	.string "{PLAYER} received the KNUCKLE BADGE!$"

BossTwo_Text_PostBattle:
	.string "You have mastered stage 2!\n"
	.string "Teleporting you back to the hub...$"
