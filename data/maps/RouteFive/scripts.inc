RouteFive_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RouteFive_OnFrame
	.byte 0

RouteFive_OnFrame:
	map_script_2 VAR_TEMP_0, 0, Route_EventScript_EncounterIntro
	.2byte 0

RouteFive_EventScript_ReturnNPC::
	lock
	msgbox RouteFive_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteFive_EventScript_DeclinedReturn
	closemessage
	special DoSlotGlitchEffect
	waitstate
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteFive_EventScript_DeclinedReturn:
	msgbox RouteFive_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteFive_Text_ReturnPrompt:
	.string "The triangle hums quietly...\p"
	.string "Cash out and leave this spin?$"

RouteFive_Text_DeclinedReturn:
	.string "The hum fades.$"
