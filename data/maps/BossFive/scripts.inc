BossFive_MapScripts::
	.byte 0

BossFive_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN_1, BossFive_Text_Intro, BossFive_Text_Defeat, BossFive_EventScript_Defeated
	msgbox BossFive_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

BossFive_EventScript_Defeated::
	message BossFive_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE05_GET
	msgbox BossFive_Text_PostBattle, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

BossFive_Text_Intro:
	.string "I am NORMAN, boss of stage 5!\n"
	.string "Show me what your team can do!$"

BossFive_Text_Defeat:
	.string "Impressive... You have earned\n"
	.string "this badge!$"

BossFive_Text_ReceivedBadge:
	.string "{PLAYER} received the BALANCE BADGE!$"

BossFive_Text_PostBattle:
	.string "You have mastered stage 5!\n"
	.string "Teleporting you back to the hub...$"
