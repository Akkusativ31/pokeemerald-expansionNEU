MauvilleCity_GameCorner_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MauvilleCity_GameCorner_OnFrame
	.byte 0

MauvilleCity_GameCorner_OnFrame:
	map_script_2 VAR_GAME_CORNER_INTRO, 0, MauvilleCity_GameCorner_EventScript_KidnapIntro
	.2byte 0

MauvilleCity_GameCorner_EventScript_KidnapIntro::
	lockall
	msgbox MauvilleCity_GameCorner_Text_Kidnapped, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_ToolsInTrash, MSGBOX_DEFAULT
	setvar VAR_GAME_CORNER_INTRO, 1
	fadedefaultbgm
	releaseall
	end

MauvilleCity_GameCorner_Text_Kidnapped:
	.string "Welcome to the GAME CORNER, {PLAYER}.\p"
	.string "You have been kidnapped!\p"
	.string "To escape, you must beat all 8 GYMS\n"
	.string "and the ELITE FOUR!$"

MauvilleCity_GameCorner_Text_ToolsInTrash:
	.string "Don't worry, we left you some tools\n"
	.string "in the trash can in the corner.\p"
	.string "Talk to the nurse first.$"

	@ Game Corner prices
	.set TM_DOUBLE_TEAM_COINS, 1500
	.set TM_PSYCHIC_COINS, 3500
	.set TM_FLAMETHROWER_COINS, 4000
	.set TM_THUNDERBOLT_COINS, 4000
	.set TM_ICE_BEAM_COINS, 4000
	.set DOLL_COINS, 1000

	.set COINS_PRICE_50,  1000
	.set COINS_PRICE_500, 10000

MauvilleCity_GameCorner_EventScript_CoinsClerk::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
	message MauvilleCity_GameCorner_Text_WereYouLookingForCoins
	waitmessage
	showmoneybox 0, 0
	showcoinsbox 0, 5
	goto MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50

MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50::
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 0, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

@ Unused
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault500::
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 1, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

MauvilleCity_GameCorner_EventScript_Buy50Coins::
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 50), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_50
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 50
	removemoney COINS_PRICE_50
	updatemoneybox
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_Buy500Coins::
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 500), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_500
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 500
	removemoney COINS_PRICE_500
	updatemoneybox
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_NeedCoinCase::
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_NotEnoughMoney::
	msgbox MauvilleCity_GameCorner_Text_DontHaveEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_CancelBuyCoins::
	msgbox MauvilleCity_GameCorner_Text_DontNeedCoinsThen, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_NoRoomForCoins::
	msgbox MauvilleCity_GameCorner_Text_CoinCaseIsFull, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerDolls::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 0, 0
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ChooseDollPrize::
	multichoice 12, 0, MULTI_GAME_CORNER_DOLLS, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_TreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_TorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_MudkipDoll
	case 3, MauvilleCity_GameCorner_EventScript_CancelDollSelect
	goto MauvilleCity_GameCorner_EventScript_CancelDollSelect
	end

MauvilleCity_GameCorner_EventScript_TreeckoDoll::
	setvar VAR_TEMP_1, 1
	bufferdecorationname STR_VAR_1, DECOR_TREECKO_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_TorchicDoll::
	setvar VAR_TEMP_1, 2
	bufferdecorationname STR_VAR_1, DECOR_TORCHIC_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_MudkipDoll::
	setvar VAR_TEMP_1, 3
	bufferdecorationname STR_VAR_1, DECOR_MUDKIP_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_ConfirmDollPrize::
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelDollSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll
	case 2, MauvilleCity_GameCorner_EventScript_BuyTorchicDoll
	case 3, MauvilleCity_GameCorner_EventScript_BuyMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TREECKO_DOLL
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTorchicDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TORCHIC_DOLL
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyMudkipDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_MUDKIP_DOLL
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForDoll::
	call Common_EventScript_NoRoomForDecor
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_CancelDollSelect::
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerTMs::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 0, 0
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize

MauvilleCity_GameCorner_EventScript_ChooseTMPrize::
	multichoice 12, 0, MULTI_GAME_CORNER_TMS, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_TMDoubleTeam
	case 1, MauvilleCity_GameCorner_EventScript_TMPsychic
	case 2, MauvilleCity_GameCorner_EventScript_TMFlamethrower
	case 3, MauvilleCity_GameCorner_EventScript_TMThunderbolt
	case 4, MauvilleCity_GameCorner_EventScript_TMIceBeam
	case 5, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end

MauvilleCity_GameCorner_EventScript_TMDoubleTeam::
	setvar VAR_TEMP_1, 1
	bufferitemname STR_VAR_1, ITEM_TM_DOUBLE_TEAM
	setvar VAR_0x8004, ITEM_TM_DOUBLE_TEAM
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMPsychic::
	setvar VAR_TEMP_1, 2
	bufferitemname STR_VAR_1, ITEM_TM_PSYCHIC
	setvar VAR_0x8004, ITEM_TM_PSYCHIC
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMFlamethrower::
	setvar VAR_TEMP_1, 3
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMThunderbolt::
	setvar VAR_TEMP_1, 4
	bufferitemname STR_VAR_1, ITEM_TM_THUNDERBOLT
	setvar VAR_0x8004, ITEM_TM_THUNDERBOLT
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMIceBeam::
	setvar VAR_TEMP_1, 5
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_ConfirmTMPrize::
	special BufferTMHMMoveName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam
	case 2, MauvilleCity_GameCorner_EventScript_BuyTMPsychic
	case 3, MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower
	case 4, MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt
	case 5, MauvilleCity_GameCorner_EventScript_BuyTMIceBeam
	end

MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_DOUBLE_TEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_DOUBLE_TEAM
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_DOUBLE_TEAM_COINS
	additem ITEM_TM_DOUBLE_TEAM
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMPsychic::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_PSYCHIC_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_PSYCHIC
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_PSYCHIC_COINS
	additem ITEM_TM_PSYCHIC
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FLAMETHROWER
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDERBOLT_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_THUNDERBOLT_COINS
	additem ITEM_TM_THUNDERBOLT
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMIceBeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_ICE_BEAM
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForTM::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_CancelTMSelect::
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox
	release
	end

MauvilleCity_GameCorner_EventScript_Woman2::
	msgbox MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
	end

MauvilleCity_GameCorner_EventScript_Gentleman::
	msgbox MauvilleCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
	end

MauvilleCity_GameCorner_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_STARTER_DOLL, MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	msgbox MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_DeclineStarterDoll
	switch VAR_STARTER_MON
	case 0, MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_GiveTorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_GiveMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll::
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TREECKO_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTorchicDoll::
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TORCHIC_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveMudkipDoll::
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_MUDKIP_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll::
	call Common_EventScript_NoRoomForDecor
	msgbox MauvilleCity_GameCorner_Text_YouWantItButNotNow, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_DeclineStarterDoll::
	msgbox MauvilleCity_GameCorner_Text_DontBeNegative, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll::
	msgbox MauvilleCity_GameCorner_Text_CantWinJackpot, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_TryGive20Coins
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_TryGive20Coins::
	goto_if_set FLAG_RECEIVED_20_COINS, MauvilleCity_GameCorner_EventScript_PokefanMNormal
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_PokefanMNormal @ Only give 20 coins if player has no coins
	setflag FLAG_RECEIVED_20_COINS
	addcoins 20
	msgbox MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
	playse SE_SHOP
	goto MauvilleCity_GameCorner_EventScript_PokefanMNormal
	end

MauvilleCity_GameCorner_EventScript_PokefanMNormal::
	msgbox MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_OldMan::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Cook::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Man::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_NPCReturnToSlots::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_GameCorner_EventScript_Maniac::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_SlotMachine0::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine1::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine2::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine3::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine4::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine5::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 5
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine6::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 6
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine7::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 7
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine8::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 8
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine9::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 9
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine10::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 10
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine11::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 11
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_NoCoinCase::
	msgbox MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner:
	.string "This is MAUVILLE GAME CORNER.$"

MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins:
	.string "Okay, you wanted some COINS for\n"
	.string "the games?\p"
	.string "But you don't have a COIN CASE for\n"
	.string "stowing the COINS.$"

MauvilleCity_GameCorner_Text_WereYouLookingForCoins:
	.string "Were you looking for COINS?\p"
	.string "It's ¥1000 for 50 COINS.\n"
	.string "Would you like some?$"

MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins:
	.string "Thank you very much!\n"
	.string "Here are your COINS!$"

MauvilleCity_GameCorner_Text_DontHaveEnoughMoney:
	.string "Um… You don't appear to have\n"
	.string "enough money…$"

MauvilleCity_GameCorner_Text_CoinCaseIsFull:
	.string "Oh?\n"
	.string "Your COIN CASE is full.$"

MauvilleCity_GameCorner_Text_DontNeedCoinsThen:
	.string "Oh… You don't need COINS, then?\n"
	.string "Good luck on your adventure!$"

MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes:
	.string "Welcome.\p"
	.string "You can exchange your COINS for\n"
	.string "prizes here.$"

MauvilleCity_GameCorner_Text_WhichPrize:
	.string "Which prize would you like?$"

MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX:
	.string "So your choice is\n"
	.string "the {STR_VAR_1} {STR_VAR_2}?$"

MauvilleCity_GameCorner_Text_SendToYourHomePC:
	.string "Thank you!\n"
	.string "We'll send it to your PC at home.$"

MauvilleCity_GameCorner_Text_NotEnoughCoins:
	.string "You don't have enough COINS.$"

@ Unused
MauvilleCity_GameCorner_Text_NoRoomForPlacingDecor:
	.string "There isn't any room available for\n"
	.string "placing {STR_VAR_1}.$"

MauvilleCity_GameCorner_Text_OhIsThatSo:
	.string "Oh, is that so? \n"
	.string "You need to save some COINS before\l"
	.string "coming back here.$"

MauvilleCity_GameCorner_Text_SoYourChoiceIsX:
	.string "So your choice is {STR_VAR_1}?$"

MauvilleCity_GameCorner_Text_HereYouGo:
	.string "Here you go!$"

@ Unused
MauvilleCity_GameCorner_Text_CantCarryAnyMore:
	.string "Oh, you can't carry any more than that.$"

MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne:
	.string "I made a mistake and got two of\n"
	.string "the same DOLLS.\p"
	.string "Would you like one of them?$"

MauvilleCity_GameCorner_Text_HereYouGo2:
	.string "Here you go!$"

MauvilleCity_GameCorner_Text_YouWantItButNotNow:
	.string "Huh?\n"
	.string "You want it, but not right now?$"

MauvilleCity_GameCorner_Text_DontBeNegative:
	.string "Oh, don't be so negative!\n"
	.string "You can have this!$"

MauvilleCity_GameCorner_Text_CantWinJackpot:
	.string "There's a prize I want, but I can't win\n"
	.string "the jackpot.$"

MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor:
	.string "Hey, kid, if you want to play here,\n"
	.string "you need a COIN CASE.\p"
	.string "I think the young lady next door\n"
	.string "had one. Go see her!$"

MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins:
	.string "My luck can only last so long.\n"
	.string "This is too much for me.\l"
	.string "Here, take some COINS!$"

MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone:
	.string "MAUVILLE has something for\n"
	.string "everyone.\p"
	.string "For me, it's the GAME CORNER.$"

MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates:
	.string "The ROULETTE tables have different\n"
	.string "rates.\p"
	.string "Check your COINS if you're going to\n"
	.string "pick a table.$"

MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime:
	.string "It's easy to lose track of time in here. \n"
	.string "I should get back to work.$"

MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay:
	.string "COINS are needed to play here\n"
	.string "in the GAME CORNER.$"

MauvilleCity_GameCorner_Text_RouletteOnlyLuck:
	.string "This ROULETTE thing…\n"
	.string "It's rather demanding.\p"
	.string "Win or lose, it's only by luck.$"

MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed:
	.string "Up to three COINS can be used to play\n"
	.string "the SLOTS.$"

MauvilleCity_GameCorner_Text_DifficultToStopOn7:
	.string "It's very difficult to make it stop\n"
	.string "right on “7.”\p"
	.string "If it stops on “7” during the REEL TIME\n"
	.string "bonus game, you'll receive extra COINS.$"

MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo:
	.string "Here's some information for you\n"
	.string "about the SLOTS.\p"
	.string "The more lightning bolts you stock,\n"
	.string "the more REEL TIME chances you get.\p"
	.string "In a game with the maximum five\n"
	.string "REEL TIME chances…\p"
	.string "It is possible to receive four regular\n"
	.string "bonuses, then a big bonus.\p"
	.string "That would total 660 COINS, but it's\n"
	.string "very difficult to get.$"

MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase:
	.string "You can't play if you don't have\n"
	.string "a COIN CASE.$"


MauvilleCity_GameCorner_EventScript_Nurse::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, MauvilleCity_GameCorner_EventScript_NurseHeal
	goto_if_unset FLAG_NURSE_INTRO_DONE, MauvilleCity_GameCorner_EventScript_NurseIntro
	goto MauvilleCity_GameCorner_EventScript_NurseHeal

MauvilleCity_GameCorner_EventScript_NurseIntro:
	msgbox MauvilleCity_GameCorner_Text_NurseHello, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseZones, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseLimit, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseEncounterClause, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseDupesClause, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseBosses, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NursePC, MSGBOX_DEFAULT
	msgbox MauvilleCity_GameCorner_Text_NurseDeath, MSGBOX_DEFAULT
	setflag FLAG_NURSE_INTRO_DONE
	msgbox MauvilleCity_GameCorner_Text_NurseGoodLuck, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_NurseHeal:
	msgbox MauvilleCity_GameCorner_Text_HealPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_NurseDeclined
	message MauvilleCity_GameCorner_Text_TakeRest
	waitmessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	special HealPlayerParty
        setrespawn HEAL_LOCATION_MAUVILLE_CITY_GAME_CORNER
	waitfanfare
	fadescreen FADE_FROM_BLACK
	msgbox MauvilleCity_GameCorner_Text_PartyHealed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_NurseDeclined:
	msgbox MauvilleCity_GameCorner_Text_DeclineHeal, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_Text_HealPrompt:
	.string "Welcome! Would you like me to heal\n"
	.string "your Pokémon?$"

MauvilleCity_GameCorner_Text_TakeRest:
	.string "Okay, rest up for a moment...$"

MauvilleCity_GameCorner_Text_PartyHealed:
	.string "Your Pokémon are fully restored and\n"
	.string "ready for battle!$"

MauvilleCity_GameCorner_Text_DeclineHeal:
	.string "Good luck out there!$"


MauvilleCity_GameCorner_EventScript_StarterTrashCan::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, MauvilleCity_GameCorner_EventScript_TrashEmpty
	msgbox MauvilleCity_GameCorner_Text_LookInTrash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_DeclinedStarter
	special ChooseStarterNoBattle

MauvilleCity_GameCorner_FinishStarter:
	playfanfare MUS_OBTAIN_ITEM
	message MauvilleCity_GameCorner_Text_ObtainedStarter
	waitfanfare
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_POKEDEX_GET
	msgbox MauvilleCity_GameCorner_Text_TakeCare, MSGBOX_DEFAULT
	goto_if_eq VAR_STARTER_MON, 0, MauvilleCity_GameCorner_EventScript_GiveSceptilite
	goto_if_eq VAR_STARTER_MON, 1, MauvilleCity_GameCorner_EventScript_GiveCharizarditeX
	giveitem ITEM_FERALIGITE
	release
	end

MauvilleCity_GameCorner_EventScript_GiveSceptilite:
	giveitem ITEM_SCEPTILITE
	release
	end

MauvilleCity_GameCorner_EventScript_GiveCharizarditeX:
	giveitem ITEM_CHARIZARDITE_X
	release
	end

MauvilleCity_GameCorner_EventScript_TrashEmpty:
	msgbox MauvilleCity_GameCorner_Text_TrashIsEmpty, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_DeclinedStarter:
	msgbox MauvilleCity_GameCorner_Text_LeftTrashAlone, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_Text_LookInTrash:
	.string "There are three Poké Balls tucked in\n"
	.string "the trash can! Take one?$"

MauvilleCity_GameCorner_Text_WhichStarter:
	.string "Which Pokémon will you choose?$"

MauvilleCity_GameCorner_Text_Turtwig:
	.string "TURTWIG$"

MauvilleCity_GameCorner_Text_Chimchar:
	.string "CHIMCHAR$"

MauvilleCity_GameCorner_Text_Piplup:
	.string "PIPLUP$"

MauvilleCity_GameCorner_Text_ObtainedStarter:
	.string "You retrieved your starting Pokémon!$"

MauvilleCity_GameCorner_Text_TakeCare:
	.string "Take good care of your new partner!$"

MauvilleCity_GameCorner_Text_TrashIsEmpty:
	.string "It's just a dirty trash can.$"

MauvilleCity_GameCorner_Text_LeftTrashAlone:
	.string "Better leave it alone...$"

@ --- Encounter slots (left machines) and boss slots (right machines) ---
@ Encounter room N: unlocked by badge N-1, can be entered only once.
@ Boss room N: unlocked by badge N-1, closed once badge N is earned.

MauvilleCity_GameCorner_EventScript_EncounterSlot1::
	lock
	goto_if_set FLAG_ENCOUNTER_1_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_1_USED
	warpsilent MAP_ROUTE_ONE, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot1::
	lock
	goto_if_set FLAG_BADGE01_GET, MauvilleCity_GameCorner_EventScript_BossDone
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_ONE, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter1:
	.string "Enter the encounter zone of\n"
	.string "stage 1? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss1:
	.string "Challenge ROXANNE in the\n"
	.string "stage 1 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot2::
	lock
	goto_if_set FLAG_ENCOUNTER_2_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE01_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_2_USED
	warpsilent MAP_ROUTE_TWO, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot2::
	lock
	goto_if_set FLAG_BADGE02_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE01_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_TWO, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter2:
	.string "Enter the encounter zone of\n"
	.string "stage 2? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss2:
	.string "Challenge BRAWLY in the\n"
	.string "stage 2 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot3::
	lock
	goto_if_set FLAG_ENCOUNTER_3_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE02_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_3_USED
	warpsilent MAP_ROUTE_THREE, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot3::
	lock
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE02_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_THREE, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter3:
	.string "Enter the encounter zone of\n"
	.string "stage 3? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss3:
	.string "Challenge WATTSON in the\n"
	.string "stage 3 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot4::
	lock
	goto_if_set FLAG_ENCOUNTER_4_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE03_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_4_USED
	warpsilent MAP_ROUTE_FOUR, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot4::
	lock
	goto_if_set FLAG_BADGE04_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE03_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_FOUR, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter4:
	.string "Enter the encounter zone of\n"
	.string "stage 4? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss4:
	.string "Challenge FLANNERY in the\n"
	.string "stage 4 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot5::
	lock
	goto_if_set FLAG_ENCOUNTER_5_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE04_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_5_USED
	warpsilent MAP_ROUTE_FIVE, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot5::
	lock
	goto_if_set FLAG_BADGE05_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE04_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_FIVE, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter5:
	.string "Enter the encounter zone of\n"
	.string "stage 5? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss5:
	.string "Challenge NORMAN in the\n"
	.string "stage 5 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot6::
	lock
	goto_if_set FLAG_ENCOUNTER_6_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE05_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter6, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_6_USED
	warpsilent MAP_ROUTE_SIX, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot6::
	lock
	goto_if_set FLAG_BADGE06_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE05_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss6, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_SIX, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter6:
	.string "Enter the encounter zone of\n"
	.string "stage 6? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss6:
	.string "Challenge WINONA in the\n"
	.string "stage 6 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot7::
	lock
	goto_if_set FLAG_ENCOUNTER_7_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE06_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter7, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_7_USED
	warpsilent MAP_ROUTE_SEVEN, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot7::
	lock
	goto_if_set FLAG_BADGE07_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE06_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss7, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_SEVEN, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter7:
	.string "Enter the encounter zone of\n"
	.string "stage 7? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss7:
	.string "Challenge WALLACE in the\n"
	.string "stage 7 boss arena?$"

MauvilleCity_GameCorner_EventScript_EncounterSlot8::
	lock
	goto_if_set FLAG_ENCOUNTER_8_USED, MauvilleCity_GameCorner_EventScript_EncounterUsed
	goto_if_unset FLAG_BADGE07_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmEncounter8, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	setflag FLAG_ENCOUNTER_8_USED
	warpsilent MAP_ROUTE_EIGHT, 15, 6
	waitstate
	release
	end

MauvilleCity_GameCorner_EventScript_BossSlot8::
	lock
	goto_if_set FLAG_BADGE08_GET, MauvilleCity_GameCorner_EventScript_BossDone
	goto_if_unset FLAG_BADGE07_GET, MauvilleCity_GameCorner_EventScript_SlotLocked
	msgbox MauvilleCity_GameCorner_Text_ConfirmBoss8, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_SlotCancel
	warpsilent MAP_BOSS_EIGHT, 5, 5
	waitstate
	release
	end

MauvilleCity_GameCorner_Text_ConfirmEncounter8:
	.string "Enter the encounter zone of\n"
	.string "stage 8? You can only visit it once!$"

MauvilleCity_GameCorner_Text_ConfirmBoss8:
	.string "Challenge WALLY in the\n"
	.string "stage 8 boss arena?$"

MauvilleCity_GameCorner_EventScript_SlotLocked::
	msgbox MauvilleCity_GameCorner_Text_SlotLocked, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_EncounterUsed::
	msgbox MauvilleCity_GameCorner_Text_EncounterUsed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_BossDone::
	msgbox MauvilleCity_GameCorner_Text_BossDone, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_SlotCancel::
	release
	end

MauvilleCity_GameCorner_Text_SlotLocked:
	.string "This machine is locked.\n"
	.string "Earn the previous badge first.$"

MauvilleCity_GameCorner_Text_EncounterUsed:
	.string "You already used this encounter\n"
	.string "zone.$"

MauvilleCity_GameCorner_Text_BossDone:
	.string "You already defeated this boss.\n"
	.string "Move on to the next stage!$"


@ --- Nurse explanation (first talk) ---
MauvilleCity_GameCorner_Text_NurseHello:
	.string "Oh, a new face...\p"
	.string "Don't look at me like that. I don't\n"
	.string "know why you're here.\p"
	.string "I'm just doing my job.$"

MauvilleCity_GameCorner_Text_NurseZones:
	.string "Here's how it works. Every machine\n"
	.string "on the left leads to an encounter\l"
	.string "zone, a route full of wild POKéMON.\p"
	.string "You can only go to each route once.\n"
	.string "There is no coming back!$"

MauvilleCity_GameCorner_Text_NurseLimit:
	.string "You can't catch everything.\n"
	.string "Only the first few encounters on a\l"
	.string "route can be caught.\p"
	.string "On ROUTE ONE that's 5 encounters.\n"
	.string "Later routes may allow even fewer!$"

MauvilleCity_GameCorner_Text_NurseEncounterClause:
	.string "That's the ENCOUNTER CLAUSE. Every\n"
	.string "wild battle uses up one encounter.\p"
	.string "Every ball is a guaranteed catch.$"

MauvilleCity_GameCorner_Text_NurseDupesClause:
	.string "And there's the DUPES CLAUSE.\n"
	.string "If you already caught a POKéMON's\l"
	.string "family, you can't catch another.\p"
	.string "Duplicates don't use up an encounter,\n"
	.string "so don't worry about those.$"

MauvilleCity_GameCorner_Text_NurseBosses:
	.string "The machines on the right, the black\n"
	.string "ones, are the boss arenas.\p"
	.string "Beat a boss to earn a badge. Each\n"
	.string "badge unlocks the next route and boss.$"

MauvilleCity_GameCorner_Text_NursePC:
	.string "There's a PC in the top left corner.\n"
	.string "Use it to store POKéMON.\p"
	.string "Its LEVEL TO CAP option raises a\n"
	.string "POKéMON straight to the level cap.$"

MauvilleCity_GameCorner_Text_NurseDeath:
	.string "One more thing: a POKéMON that\n"
	.string "faints is gone for good. I can heal\l"
	.string "the living, but I can't revive anyone.$"

MauvilleCity_GameCorner_Text_NurseGoodLuck:
	.string "That's all I'm allowed to say.\n"
	.string "Come back if your team needs a rest.$"

@ --- Shown every time the player enters an encounter zone ---
Route_EventScript_EncounterIntro::
	lockall
	special BufferRouteEncounterLimit
	random 3
	switch VAR_RESULT
	case 0, Route_EventScript_EncounterIntro1
	case 1, Route_EventScript_EncounterIntro2
	msgbox Route_Text_EncounterIntro3, MSGBOX_DEFAULT
	goto Route_EventScript_EncounterIntroDone

Route_EventScript_EncounterIntro1:
	msgbox Route_Text_EncounterIntro1, MSGBOX_DEFAULT
	goto Route_EventScript_EncounterIntroDone

Route_EventScript_EncounterIntro2:
	msgbox Route_Text_EncounterIntro2, MSGBOX_DEFAULT
	goto Route_EventScript_EncounterIntroDone

Route_EventScript_EncounterIntroDone:
	setvar VAR_TEMP_0, 1
	releaseall
	end

Route_Text_EncounterIntro1:
	.string "You have entered an encounter zone.\p"
	.string "Only the first {STR_VAR_1} encounters here\n"
	.string "can be caught.$"

Route_Text_EncounterIntro2:
	.string "Careful! This route only allows\n"
	.string "{STR_VAR_1} catches, and you can't return.$"

Route_Text_EncounterIntro3:
	.string "Remember: the first {STR_VAR_1} encounters\n"
	.string "are your only chance on this route.$"
