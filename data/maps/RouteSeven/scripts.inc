RouteSeven_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RouteSeven_OnFrame
	.byte 0

RouteSeven_OnFrame:
	map_script_2 VAR_TEMP_0, 0, Route_EventScript_EncounterIntro
	.2byte 0

RouteSeven_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteSeven_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteSeven_EventScript_DeclinedReturn
	msgbox RouteSeven_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteSeven_EventScript_DeclinedReturn:
	msgbox RouteSeven_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteSeven_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteSeven_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteSeven_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
