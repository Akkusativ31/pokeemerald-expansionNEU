RouteSix_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RouteSix_OnFrame
	.byte 0

RouteSix_OnFrame:
	map_script_2 VAR_TEMP_0, 0, Route_EventScript_EncounterIntro
	.2byte 0

RouteSix_EventScript_ReturnNPC::
	lock
	msgbox RouteSix_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteSix_EventScript_DeclinedReturn
	closemessage
	special DoSlotGlitchEffect
	waitstate
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteSix_EventScript_DeclinedReturn:
	msgbox RouteSix_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteSix_Text_ReturnPrompt:
	.string "The triangle hums quietly...\p"
	.string "Cash out and leave this spin?$"

RouteSix_Text_DeclinedReturn:
	.string "The hum fades.$"
