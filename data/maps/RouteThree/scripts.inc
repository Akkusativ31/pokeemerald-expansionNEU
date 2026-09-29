RouteThree_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RouteThree_OnFrame
	.byte 0

RouteThree_OnFrame:
	map_script_2 VAR_TEMP_0, 0, Route_EventScript_EncounterIntro
	.2byte 0

RouteThree_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteThree_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteThree_EventScript_DeclinedReturn
	msgbox RouteThree_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteThree_EventScript_DeclinedReturn:
	msgbox RouteThree_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteThree_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteThree_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteThree_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
