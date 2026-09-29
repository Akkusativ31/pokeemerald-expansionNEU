RouteFour_MapScripts::
	.byte 0

RouteFour_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteFour_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteFour_EventScript_DeclinedReturn
	msgbox RouteFour_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteFour_EventScript_DeclinedReturn:
	msgbox RouteFour_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteFour_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteFour_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteFour_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
