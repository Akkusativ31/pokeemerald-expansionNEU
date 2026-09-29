GameOverRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GameOverRoom_OnFrame
	.byte 0

GameOverRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, GameOverRoom_EventScript_GameOver
	.2byte 0

GameOverRoom_EventScript_GameOver::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	delay 60
	msgbox GameOverRoom_Text_Disappointed, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	special DoSoftReset
	waitstate
	end

GameOverRoom_EventScript_Stranger::
	msgbox GameOverRoom_Text_Disappointed, MSGBOX_DEFAULT
	release
	end

GameOverRoom_Text_Disappointed:
	.string "Hmph...\p"
	.string "I'm disappointed...$"
