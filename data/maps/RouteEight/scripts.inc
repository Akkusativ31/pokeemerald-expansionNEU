RouteEight_MapScripts::
	.byte 0

RouteEight_EventScript_ReturnNPC::
	lock
	faceplayer
	msgbox RouteEight_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RouteEight_EventScript_DeclinedReturn
	msgbox RouteEight_Text_Returning, MSGBOX_DEFAULT
	warpsilent MAP_MAUVILLE_CITY_GAME_CORNER, 11, 6
	waitstate
	release
	end

RouteEight_EventScript_DeclinedReturn:
	msgbox RouteEight_Text_DeclinedReturn, MSGBOX_DEFAULT
	release
	end

RouteEight_Text_ReturnPrompt:
	.string "Finished with your encounter?\n"
	.string "Would you like to return to the Hub?$"

RouteEight_Text_Returning:
	.string "Alright, teleporting back now!$"

RouteEight_Text_DeclinedReturn:
	.string "Good luck with your catch! Let me\n"
	.string "know when you are ready to return.$"
