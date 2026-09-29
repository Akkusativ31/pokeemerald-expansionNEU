RouteFive_MapScripts::
	.byte 0

RouteFive_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteFive_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteFive_EventScript_DeclinedReturn
	msgbox RouteFive_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteFive_EventScript_DeclinedReturn:
	msgbox RouteFive_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteFive_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteFive_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteFive_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
