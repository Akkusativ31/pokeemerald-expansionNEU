RouteSix_MapScripts::
	.byte 0

RouteSix_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteSix_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteSix_EventScript_DeclinedReturn
	msgbox RouteSix_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteSix_EventScript_DeclinedReturn:
	msgbox RouteSix_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteSix_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteSix_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteSix_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
