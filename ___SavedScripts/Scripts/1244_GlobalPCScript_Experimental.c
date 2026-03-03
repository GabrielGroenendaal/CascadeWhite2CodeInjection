#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	
// 	SetVarFlagStatus(732, 0x8024);
// 	Compare(0x8024, 1);
// 	if (1) goto label_gotPokeHelper;
// 	End();

// label_gotPokeHelper: ;
	LockAll();

	// Sequence10();
	Sequence12();
	Sequence16();

	
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8020, 0);
	SetVarEqVal(0x8021, 0);
	SetVarFlagStatus(2411, 0x8025);
	SetVarFlagStatus(2402, 0x8026);
	SetVarFlagStatus(2400, 0x8022);
	StoreEA(0x8023);
	PlaySound(1371);
	SetWordPlayerName(0);

	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label_NotAPokemonCenter;
	EventGreyMessage(0, 2);
	goto label32;
label_NotAPokemonCenter: ;
	EventGreyMessage(84, 2);

label32: ;
    SetVarFlagStatus(2411, 0x8025);
	SetVarFlagStatus(2402, 0x8026);
	SetVarFlagStatus(2400, 0x8022);
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	PlaySound(1372);
	SetWordNumber(1, 0x4052, 3);
	EventGreyMessage(178, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);


	Sequence16();
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label_NotAPokemonCenter2;

	SetVarFlagStatus(2401, 0x8028);
	Compare(0x8028, 1);
	if (0) goto label1;
	StackPushVar(0x8025);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label2;
	AddDialogueOption(2, 0xFFFF, 2);
	goto label1;

label_NotAPokemonCenter2: ;
	AddDialogueOption(85, 0xFFFF, 2);
	goto label1;

label2: ;
	AddDialogueOption(3, 0xFFFF, 3);

label1: ;
	Sequence16();
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label_SkipDialogueOption1;
	AddDialogueOption(4, 0xFFFF, 4);
	StackPushVar(0x8026);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	AddDialogueOption(5, 0xFFFF, 5);

label_SkipDialogueOption1: ;
	SetVarFlagStatus(3063, 0x8028);
	Compare(0x8028, 1);
	if (1) goto label4;
	goto label5;

label5: ;
	AddDialogueOption(42, 0xFFFF, 42);
	goto label3;

label4: ;
	AddDialogueOption(59, 0xFFFF, 42);
	goto label3;

label6: ;
	Storec0xD3(0x8028);
	Compare(0x8028, 337);
	if (1) goto label7;
	Compare(0x8028, 345);
	if (1) goto label7;
	Compare(0x8028, 368);
	if (1) goto label7;
	Compare(0x8028, 448);
	if (1) goto label7;
	Compare(0x8028, 456);
	if (1) goto label7;
	Compare(0x8028, 107);
	if (1) goto label7;
	Compare(0x8028, 113);
	if (1) goto label7;
	Compare(0x8028, 198);
	if (1) goto label7;
	Compare(0x8028, 199);
	if (1) goto label7;
	Compare(0x8028, 205);
	if (1) goto label7;
	Compare(0x8028, 206);
	if (1) goto label7;
	Compare(0x8028, 439);
	if (1) goto label7;
	Compare(0x8028, 444);
	if (1) goto label7;
	Compare(0x8028, 445);
	if (1) goto label7;
	Compare(0x8028, 446);
	if (1) goto label7;
	Compare(0x8028, 96);
	if (1) goto label8;
	Compare(0x8028, 331);
	if (1) goto label8;
	goto label3;

label7: ;
	SetVarEqVal(0x8027, 2);
	goto label3;

label8: ;
	SetVarEqVal(0x8027, 5);
	goto label3;

label3: ;
    // IF I WANT TO MOVE COMMON FUNCTIONS OUT 
	GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_DisablePokeHelperOptions;

    AddDialogueOption(43, 0xFFFF, 43);

    AddDialogueOption(171, 0xFFFF, 171);
    AddDialogueOption(194, 0xFFFF, 194);
    AddDialogueOption(71, 0xFFFF, 71);
label_DisablePokeHelperOptions: ;
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label9;

	AddDialogueOption(6, 0xFFFF, 6);

label9: ;
	// Didn't receive the ugprade from Hugh Yet
	SetVarEqVar(0x8022, 16759);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label_DisablingFlight;
	AddDialogueOption(86, 0xFFFF, 86);

label_DisablingFlight: ;

	AddDialogueOption(87, 0xFFFF, 87);

	AddDialogueOption(7, 0xFFFF, 7);

	AddDialogueOption(8, 0xFFFF, 8);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);
	Compare(0x8024, 2);
	if (1) goto label10;
	goto label11;

label10: ;
	GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_NoPokemon;
	Sequence1();
	goto label12;

label11: ;
	Compare(0x8024, 3);
	if (1) goto label13;
	goto label14;

label13: ;
	Sequence1();
	goto label12;

label14: ;
	Compare(0x8024, 4);
	if (1) goto label15;
	goto label16;

label15: ;
	Sequence2();
	goto label12;

label16: ;
	Compare(0x8024, 42);
	if (1) goto label17;
	goto label18;

label17: ;

	Sequence8();
	goto label12;

label18: ;
	Compare(0x8024, 5);
	if (1) goto label19;
	goto label20;

label19: ;
	Sequence3();
	goto label12;

label20: ;
	Compare(0x8024, 6);
	if (1) goto label21;
	goto label22;

label21: ;
	Sequence4();
	goto label12;

label22: ;
	Compare(0x8024, 75);
	if (1) goto label23;
	goto label24;

label23: ;
	Sequence14();
	goto label12;

label24: ;
	Compare(0x8024, 7);
	if (1) goto label25;
	goto label26;

label25: ;
	Sequence5();
	goto label12;

label26: ;
	Compare(0x8024, 8);
	if (1) goto label27;
	goto label28;

label27: ;
	SetVarEqVal(0x8020, 1);
	goto label12;

label28: ;
	Compare(0x8024, 0xFFFE);
	if (1) goto label29;
	goto label30;

label29: ;
	SetVarEqVal(0x8020, 1);
	goto label12;

label30: ;
	Compare(0x8024, 0xFFFD);
	if (1) goto label31;
	goto label33a;

label31: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	goto label12;

label33a: ;
	Compare(0x8024, 86);
	if (1) goto label34a;
	goto label35a;

label34a: ;
    // Castelia Sewers and Associated Areas
	Storec0xD3(0x8028);
	Compare(0x8028, 495);
	if (1) goto label_cantFlyHere;
	Storec0xD3(0x8028);
	Compare(0x8028, 161);
	if (1) goto label_cantFlyHere;
	Storec0xD3(0x8028);
	Compare(0x8028, 502);
	if (1) goto label_cantFlyHere;

    // PWT Interior
    Storec0xD3(0x8028);
	Compare(0x8028, 192);
	if (1) goto label_cantFlyHere;


    // Plasma Frigate
    Storec0xD3(0x8028);
	Compare(0x8028, 552);
	if (1) goto label_cantFlyHere;

    // Iron Chamber
    Storec0xD3(0x8028);
	Compare(0x8028, 613);
	if (1) goto label_cantFlyHere;
	
    // Reversal Mountain
    Storec0xD3(0x8028);
	Compare(0x8028, 538);
	if (1) goto label_cantFlyHere;
	Compare(0x8028, 539);
	if (1) goto label_cantFlyHere;
	Compare(0x8028, 540);
	if (1) goto label_cantFlyHere;
	Compare(0x8028, 541);
	if (1) goto label_cantFlyHere;
	Compare(0x8028, 542);
	if (1) goto label_cantFlyHere;
	
	// Pinwheel Forest
	Compare(0x8028, 155);
	if (1) goto label_cantFlyHere;
	Compare(0x8028, 156);
	if (1) goto label_cantFlyHere;

    // Route 14
    Compare(0x8028, 374);
	if (1) goto label_cantFlyHere;

    // Marine Tube
    Compare(0x8028, 464);
	if (1) goto label_cantFlyHere;

    // Humilau Gym 
    Compare(0x8028, 473);
	if (1) goto label_cantFlyHere;

    // Nimbasa Gym 
    Compare(0x8028, 63);
	if (1) goto label_cantFlyHere;

	Sequence17();
	goto label12;
label_cantFlyHere: ;
	EventGreyMessage(196, 2);
	goto label12;

label35a: ;
	Compare(0x8024, 87);
	if (1) goto label36a;
	goto label_MainHealFunction;

label36a: ;
	Sequence18();
	goto label12;	

label_MainHealFunction: ;
    Compare(0x8024, 43);
    if (1) goto label_MainHealFunctionA;
    goto label_MainRemoveItemFunction;

label_MainHealFunctionA: ; 
    GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_NoPokemon;
    Sequence6();
    goto label12;

    
label_MainRemoveItemFunction: ;
    Compare(0x8024, 171);
    if (1) goto label_MainRemoveItemFunctionA;
    goto label_MainEdgeFunction;
    

label_MainRemoveItemFunctionA: ;
    GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_NoPokemon;
    EventGreyMessage(173, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label12;
	Sequence20();
	goto label12;

label_MainEdgeFunction: ;
    Compare(0x8024, 71);
    if (1) goto label_MainEdgeFunctionA;
    goto label_MainPreDamageFunction;

label_MainEdgeFunctionA: ;
    GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_NoPokemon;
    EventGreyMessage(73, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label12;
	Sequence21();
	goto label12;

label_MainPreDamageFunction: ;
    Compare(0x8024, 194);
    if (1) goto label_MainPreDamageFunctionA;
    goto label12;

label_MainPreDamageFunctionA: ;
    GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label_NoPokemon;
	Sequence19();
	goto label12;

label12: ;
	goto label32;

label_NoPokemon: ;
	EventGreyMessage(170,2);
	goto label32;


label0: ;
	PlaySound(1373);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	UnlockAll();
	End();


}

/* MANAGE POKEMON */
void Sequence1()
{
	SetVarEqVal(0x8027, 0);
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x802B, 0);
	SetVarFlagStatus(2400, 0x802A);
	SetVarFlagStatus(249, 0x802B);
	PlaySound(1372);
	EventGreyMessage(14, 2);
	StackPushVar(0x802A);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label33;
	SetVarFlagStatus(246, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label33;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(12, 2);
	SetFlag(246);

label33: ;
	StackPushVar(0x802B);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label34;
	SetVarFlagStatus(247, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label34;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(13, 2);
	SetFlag(247);

label34: ;
	SetVarEqVal(0x8027, 0);

label64: ;
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label35;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8028);
	AddDialogueOption(15, 21, 15);
	AddDialogueOption(16, 22, 16);
	AddDialogueOption(17, 23, 17);
	AddDialogueOption(20, 26, 20);
	AddDialogueOption(18, 24, 18);
	// AddDialogueOption(43, 44, 43);
	AddDialogueOption(45, 46, 45);
	AddDialogueOption(71, 72, 71);
	AddDialogueOption(171, 172, 171);
	SetVarFlagStatus(124, 0x802B);
	Compare(0x802B, 1);
	if (0) goto label36;
	// AddDialogueOption(47, 48, 47);

label36: ;
	AddDialogueOption(19, 25, 19);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8028, 19);
	if (1) goto label37;
	goto label38;

label37: ;
	Return();
	goto label39;

label38: ;
	Compare(0x8028, 0xFFFE);
	if (1) goto label40;
	goto label41;

label40: ;
	Return();
	goto label39;

label41: ;
	Compare(0x8028, 0xFFFD);
	if (1) goto label42;
	goto label39;

label42: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label39;

label39: ;
	Compare(0x8028, 45);
	if (0) goto label43;
	goto label44;

label43: ;
	FadeIntoBlack2();
	WaitFade();
	Compare(0x8028, 15);
	if (1) goto label45;
	goto label44;

label45: ;
	c0x14F(0x8029, 0);
	goto label46;

label44: ;
	Compare(0x8028, 16);
	if (1) goto label47;
	goto label48;

label47: ;
	c0x14F(0x8029, 1);
	goto label46;

label48: ;
	Compare(0x8028, 17);
	if (1) goto label49;
	goto label50;

label49: ;
	c0x14F(0x8029, 2);
	goto label46;

label50: ;
	Compare(0x8028, 20);
	if (1) goto label51;
	goto label52;

label51: ;
	c0x14F(0x8029, 4);
	goto label46;

label52: ;
	Compare(0x8028, 18);
	if (1) goto label53;
	goto label54;

label53: ;
	c0x14F(0x8029, 3);
	goto label46;

label54: ;
	Compare(0x8028, 43);
	if (1) goto label55;
	goto label56;

label55: ;
	Sequence6();
	goto label57;

label56: ;
	Compare(0x8028, 45);
	if (1) goto label58;
	goto label59;

label58: ;
	Sequence7();
	goto label57;

label59: ;
	Compare(0x8028, 47);
	if (1) goto label60;
	goto label61;

label60: ;
	Sequence9();
	PlaySound(1372);
	goto label57;

label61: ;
	Compare(0x8028, 71);
	if (1) goto label62;
	goto label_RemoveItems_checked;

label62: ;
	EventGreyMessage(73, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label57;
	Sequence21();
	goto label57;

label_RemoveItems_checked: ;
	Compare(0x8028, 171);
	if (1) goto label_RemoveItems_clicked;
	goto label46;

label_RemoveItems_clicked: ;
	EventGreyMessage(173, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label57;
	Sequence20();
	goto label57;

label46: ;
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x8029);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label63;
	PlaySound(1372);
	goto label57;

label63: ;
	SetVarEqVal(0x8027, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label57: ;
	goto label64;

label35: ;
	SetVarEqVal(0x802B, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8027, 0);
	Return();
}

void Sequence2()
{
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802E, 0);
	PlaySound(1372);
	SetWordPlayerName(0);
	EventGreyMessage(27, 2);
	CloseEventGreyMessage();
	SetVarEqVal(0x802C, 0);

label74: ;
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label65;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x802D);
	AddDialogueOption(28, 30, 28);
	AddDialogueOption(29, 31, 29);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x802D, 29);
	if (1) goto label66;
	goto label67;

label66: ;
	Return();
	goto label68;

label67: ;
	Compare(0x802D, 0xFFFE);
	if (1) goto label69;
	goto label70;

label69: ;
	Return();
	goto label68;

label70: ;
	Compare(0x802D, 0xFFFD);
	if (1) goto label71;
	goto label68;

label71: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label68;

label68: ;
	FadeIntoBlack2();
	WaitFade();
	c0x150(0x802E);
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x802E);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label72;
	PlaySound(1372);
	goto label73;

label72: ;
	SetVarEqVal(0x802C, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label73: ;
	goto label74;

label65: ;
	SetVarEqVal(0x802E, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802C, 0);
	Return();
}

void Sequence3()
{
	PlaySound(1372);
	EventGreyMessage(39, 2);
	CallGlobalScript(10382);
	Return();
}

void Sequence4()
{
	SetVarEqVal(0x802F, 0);
	SetVarEqVal(0x8030, 0);
	PlaySound(1372);
	EventGreyMessage(35, 2);
	CloseEventGreyMessage();
	StackPushVar(0x8023);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label84;
	c0x14D(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label75;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label75: ;
	goto label76;

label84: ;
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();

label76: ;
	SetVarEqVal(0x8030, 0);
	SetVarEqVal(0x802F, 0);
	Return();
}

void Sequence5()
{
	PlaySound(1372);
	EventGreyMessage(40, 2);
	CloseEventGreyMessage();
	c0x231(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label77;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label77: ;
	Return();
}

/* HEAL POKEMON */
/* This function simply lets you Heal your whole Party */
void Sequence6()
{
	HealPokemon();
	PlayFanfare(1300);
	WaitFanfare();
	PC_131();
	// FadeFromBlack2();
	// WaitFade();
	EventGreyMessage(50, 2);
	CloseEventGreyMessage();
	PlaySound(1372);
	Return();
}

/* PRE-STATUS POKEMON */
/* This function simply lets you apply prestatus to Pokemon */
void Sequence7()
{
	EventGreyMessage(51, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
	AddDialogueOption(53, 0xFFFF, 53);
	AddDialogueOption(54, 0xFFFF, 54);
	AddDialogueOption(55, 0xFFFF, 55);
	AddDialogueOption(56, 0xFFFF, 56);
	AddDialogueOption(57, 0xFFFF, 57);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8024, 0xFFFE);
	if (1) goto label78;
	Compare(0x8024, 57);
	if (1) goto label78;
	Compare(0x8024, 53);
	if (1) goto label79;
	Compare(0x8024, 54);
	if (1) goto label80;
	Compare(0x8024, 55);
	if (1) goto label81;
	Compare(0x8024, 56);
	if (1) goto label82;
	goto label78;

label79: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 5);
	PlaySound(1372);
    EventGreyMessage(193, 2);
    WaitForButton();
	goto label78;

label80: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 1);
	PlaySound(1372);
    EventGreyMessage(193, 2);
    WaitForButton();
	goto label78;

label81: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 2);
	PlaySound(1372);
    EventGreyMessage(193, 2);
    WaitForButton();
	goto label78;

label82: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 4);
	PlaySound(1372);
    EventGreyMessage(193, 2);
    WaitForButton();
	goto label78;

label78: ;
	Return();
}

void Sequence8()
{
	SetVarFlagStatus(3063, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label85;
	goto label83;

label85: ;
	EventGreyMessage(60, 2);
	CloseEventGreyMessage();
	ClearFlag(3063);
	Return();

label83: ;
	EventGreyMessage(49, 2);
	CloseEventGreyMessage();
	SetFlag(3063);
	Return();
}

void Sequence9()
{
	EventGreyMessage(66, 2);
	CloseEventGreyMessage();
	OpenChoosePokemonMenu(0, 0x8028, 0x8024, 0);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label86;
	Return();

label86: ;
	GetPartyIsEgg(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label87;
	EventGreyMessage(64, 2);
	CloseEventGreyMessage();
	Return();

label87: ;
	c0x1D5(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label88;
	EventGreyMessage(65, 2);
	CloseEventGreyMessage();
	Return();

label88: ;
	SetWordPartyNickname(0, 0x8024);
	EventGreyMessage(67, 2);
	CloseEventGreyMessage();
	c0x1D6(0x802B, 0x8024);
	Compare(0x802B, 0);
	if (1) goto label89;
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	Return();

label89: ;
	WaitMoment();
	EventGreyMessage(69, 2);
	CloseEventGreyMessage();
	Return();
}

/* RARE CANDY REFILL */
/* This function is currently out of use */
void Sequence10()
{
	SetVarEqVal(0x8027, 50);
	SetVarEqVal(0x8028, 499);
	Sequence11();
	SetVarEqVal(0x8028, 249);
	Sequence11();
	SetVarEqVal(0x8028, 124);
	Sequence11();
	SetVarEqVal(0x8028, 62);
	Sequence11();
	SetVarEqVal(0x8028, 31);
	Sequence11();
	SetVarEqVal(0x8028, 15);
	Sequence11();
	SetVarEqVal(0x8028, 7);
	Sequence11();
	SetVarEqVal(0x8028, 3);
	Sequence11();
	SetVarEqVal(0x8028, 1);
	Sequence11();
	Return();
}

void Sequence11()
{

label91: ;
	GiveItem(0x8027, 0x8028, 0x8029);
	Compare(0x8029, 1);
	if (1) goto label91;
	Return();
}

/* DISABLE POKEHELPER */
/* This function determined whether the PokeHelper should be usable at all */
void Sequence12()
{
	// Elite 4
	Storec0xD3(0x8027);
	Compare(0x8027, 137);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 138);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 139);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 140);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 141);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 142);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 143);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 144);
	if (1) goto label90;

    // ChargestoneCave
	Storec0xD3(0x8031);
	Compare(0x8031, 195);
	if (1) goto label_isGauntlet;
	Storec0xD3(0x8031);
	Compare(0x8031, 196);
	if (1) goto label_isGauntlet;
	Storec0xD3(0x8031);
	Compare(0x8031, 197);
	if (1) goto label_isGauntlet;

	// DriftveilDrawbridge
	Storec0xD3(0x8031);
	Compare(0x8031, 253);
	if (1) goto label_isGauntlet;

	// JoinAvenue
	Storec0xD3(0x8031);
	Compare(0x8031, 490);
	if (1) goto label_isGauntlet;

label_end: ;
	Return();
    
label_isGauntlet: ;
    SetVarFlagStatus(522, 0x8024);
    Compare(0x8024, 1);
	if (0) goto label_end;
	EventGreyMessage(68, 2);
	CloseEventGreyMessage();
	UnlockAll();
	End();	

label90: ;
	EventGreyMessage(68, 2);
	CloseEventGreyMessage();
	UnlockAll();
	End();
}

/* EDGE POKEMON PARTY */
/* 
	This script I left out because it was a custom script command and I hadn't yet learned how to implement those 
	If I can figure it out, I'd like to.
*/
void Sequence13()
{
	EventGreyMessage(69, 2);
	Return();
}

/* TOGGLE WEATHER */
/* This function is currently out of use */
void Sequence14()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label92;
	goto label93;

label92: ;
	ClearFlag(3062);
	SetWeather(0, 0);
	Return();

label93: ;
	SetFlag(3062);
	SetWeather(2, 2);
	Return();
}

/* TOGGLE WEATHER */
/* This function is currently out of use */
void Sequence15()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label95;
	goto label94;

label95: ;
	SetWeather(0, 0);
	ClearFlag(3062);
	Return();

label94: ;
	SetFlag(3062);
	SetWeather(5, 5);
	Return();
}

/* CHECK FOR POKEMON CENTER */
/* This function simply checks if we're in a Pokemon Center. If so we display more options */
void Sequence16()
{
	Storec0xD3(0x8027);
	Compare(0x8027, 435);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 454);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 443);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 41);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 65);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 99);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 109);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 460);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 413);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 407);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 122);
	if (1) goto label_isPokemonCenter;
	Storec0xD3(0x8027);
	Compare(0x8027, 472);
	if (1) goto label_isPokemonCenter;
	
	SetVarEqVal(0x8027, 0);
	Return();

label_isPokemonCenter: ;
	Storec0xD3(0x8027);
	Return();
}


void Sequence17()
{
	PlaySound(1351);
	SetVarEqVal(0x8034, 0);
label_travelOptions: ;
	StackPushVar(0x8034);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label_goBack;

	EventGreyMessage(102, 2);
	

	SetupDialogueSelection(31, 1, 0, 1, 0x8029);
	
	
	// ======== ASPERTIA CITY ======== 
	AddDialogueOption(88, 0xFFFF, 427);


	// ======== FLOCESSY TOWN ======== 
	Compare(16549, 0);
	if (1) goto label_skipFlocessy;
	AddDialogueOption(89, 0xFFFF, 439);

label_skipFlocessy: ;

// ======== VIRBANK CITY ======== */
	Compare(16556, 0);
	if (1) goto label_skipVirbank;
	AddDialogueOption(90, 0xFFFF, 448);

label_skipVirbank: ;

// // ======== CASTELIA CITY ======== */
	SetVarFlagStatus(748, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label_skipCastelia;
	AddDialogueOption(91, 0xFFFF, 28);

label_skipCastelia: ;

// ======== JOIN AVENUE ======== */
	Compare(16733, 0);
	if (1) goto label_skipJoinAvenue;
	AddDialogueOption(92, 0xFFFF, 551);

label_skipJoinAvenue: ;

// ======== NIMBASA CITY ======== */
	Compare(16733, 0);
	if (1) goto label_skipNimbasa;
	AddDialogueOption(93, 0xFFFF, 62);

label_skipNimbasa: ;

// ======== DRIFTVEIL CITY  ======== */
	Compare(16579, 0);
	if (1) goto label_skipDriftveil;
	AddDialogueOption(94, 0xFFFF, 96);

label_skipDriftveil: ;

// ======== POKEMON WORLD TOURNAMENT ======== */
	Compare(16582, 0);
	if (1) goto label_skipPWT;
	AddDialogueOption(95, 0xFFFF, 191);

label_skipPWT: ;

// // ======== MISTRALTON CITY ======== */
	SetVarFlagStatus(521, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label_skipMistralton;
	AddDialogueOption(96, 0xFFFF, 107);

label_skipMistralton: ;

// ======== LENTIMAS TOWN ======== */
	SetVarFlagStatus(777, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label_skipLentimas;
	AddDialogueOption(97, 0xFFFF, 458);

label_skipLentimas: ;
// ======== LENTIMAS TOWN ======== */
	SetVarFlagStatus(545, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label_skipUndella;
	AddDialogueOption(98, 0xFFFF, 412);

label_skipUndella: ;
// ======== HUMILAU TOWN ======== */
	Compare(16462, 0);
	if (1) goto label_skipHumilau;
	AddDialogueOption(174, 0xFFFF, 465);

label_skipHumilau: ;
// // ======== LACUNOSA TOWN ======== */
// 	Compare(16462, 0);
// 	if (1) goto label_skipLacunosa;
// 	AddDialogueOption(175, 0xFFFF, lacunosaZone); // Put the Lacunosa Town ID here

// label_skipLacunosa: ;
// // ======== OPELUCID TOWN ======== */
// 	Compare(16462, 0);
// 	if (1) goto label_skipOpelucid;
// 	AddDialogueOption(176, 0xFFFF, opelucidZone); // Put the opelucid Town ID here

// label_skipOpelucid: ;
// // ======== LEAGUE ======== */
// 	Compare(16462, 0);
// 	if (1) goto label_skipLeague;
// 	AddDialogueOption(177, 0xFFFF, leagueZone); // Put the League Zone ID here

// label_skipLeague: ;
	AddDialogueOption(112, 0xFFFF, 112);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);

// Checking the values 
	Compare(0x8029, 0);
	if (1) goto label_returnToMenu;
	Compare(0x8029, 0xFFFE);
	if (1) goto label_returnToMenu;
	Compare(0x8029, 112);
	if (1) goto label_returnToMenu;
	EventGreyMessage(101, 2);
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label_letsFly;
	goto label_travelOptions;

label_returnToMenu: ;
	SetVarEqVal(0x8034, 1);
	goto label_travelOptions;

label_letsFly: ;
	CloseAllMessageBoxes();
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8034, 1);
	Compare(0x8029, 427);
	if (1) goto label_mapAspertia;
	Compare(0x8029, 439);
	if (1) goto label_mapFlocessy;
	Compare(0x8029, 448);
	if (1) goto label_mapVirbank;
	Compare(0x8029, 28);
	if (1) goto label_mapCastelia;
	Compare(0x8029, 551);
	if (1) goto label_mapJoinAvenue;
	Compare(0x8029, 62);
	if (1) goto label_mapNimbasa;
	Compare(0x8029, 96);
	if (1) goto label_mapDriftveil;
	Compare(0x8029, 191);
	if (1) goto label_mapPWT;
	Compare(0x8029, 107);
	if (1) goto label_mapMistralton;
	Compare(0x8029, 458);
	if (1) goto label_mapLentimas;
	Compare(0x8029, 412);
	if (1) goto label_mapUndella;
	Compare(0x8029, 465);
	if (1) goto label_mapHumilau;
//  Compare(0x8029, lacunosaZone);
//	if (1) goto label_mapLacunosa;
//  Compare(0x8029, opelucidZone);
//	if (1) goto label_mapOpelucid;
//  Compare(0x8029, leagueZone);
//	if (1) goto label_mapLeague;
	goto label_goBack;

label_mapAspertia: ;
	c0x28A(427, 1);
	goto label_travelOptions;
	
label_mapFlocessy: ;
	c0x28A(439, 1);
	goto label_travelOptions;
	
label_mapVirbank: ;
	c0x28A(448, 1);
	goto label_travelOptions;
	
label_mapCastelia: ;
	RailWarp(28, 3, 8, 8, 1);
	//c0x28A(37, 1);
	goto label_travelOptions;
	
label_mapJoinAvenue: ;
	c0x28A(551, 1);
	goto label_travelOptions;
	
label_mapNimbasa: ;
	c0x28A(62, 1);
	goto label_travelOptions;
	
label_mapDriftveil: ;
	c0x28A(96, 1);
	goto label_travelOptions;
	
label_mapPWT: ;
	c0x28A(191, 1);
	goto label_travelOptions;
	
label_mapMistralton: ;
	c0x28A(107, 1);
	goto label_travelOptions;
	
label_mapLentimas: ;
	c0x28A(458, 1);
	goto label_travelOptions;

label_mapUndella: ;
	c0x28A(412, 1);
	goto label_travelOptions;

label_mapHumilau: ;
	c0x28A(465, 1);
	goto label_travelOptions;

//label_mapLacunosa: ;
//	c0x28A(lacunosaZone, 1);
//	goto label_travelOptions;

//label_mapOpelucid: ;
//	c0x28A(opelucidZone, 1);
//	goto label_travelOptions;

//label_mapLeague: ;
//	c0x28A(leagueZone, 1);
//	goto label_travelOptions;

label_goBack: ;
	Return();
	// // ======== UNDELLA TOWN ======== */
	// 	SetVarFlagStatus(0x8030, XXXX);
	// 	Compare(0x8030, 0);
	// 	if (255) goto label_skipLentimas;
	// 	AddDialogueOption(98, 0xFFFF, 412);

	// label_skipLentimas: ;

	// // ======== LACUNOSA TOWN ======== */
	// 	SetVarFlagStatus(0x8030, XXXX);
	// 	Compare(0x8030, 0);
	// 	if (255) goto label_skipLacunosa;
	// 	AddDialogueOption(99, 0xFFFF, 406);

	// label_skipLacunosa: ;

	// // ======== OPELUCID CITY  ======== */
	// 	SetVarFlagStatus(0x8030, XXXX);
	// 	Compare(0x8030, 0);
	// 	if (255) goto label_skipOpelucid;
	// 	AddDialogueOption(100, 0xFFFF, 120);

	// label_skipOpelucid: ;
}

/* GLOBAL CONFIG SCRIPT */
/* 
	This script handles the setting and toggling of all the global config settings that affect a player's playthrough. 
	These settings, and their default (D) values, are:
		- Critical Hit Settings: 
			2x Damage (D)
			1.5x Damage 
		- Wild Pokemon IVs:
			Normal (D)
			3 Randomized 31 IVs
			Perfect IVs
		- Trainer Placements: 
			Normal (D)
			Vanilla (reverts Trainers to vanilla placements and movecodes)
		- Wild Pokemon EVs:
			0x EVs (D)
			1x EVs
			2x EVs
			4x EVs
		- Animated Backgrounds:
			Off (D)
			On
		- Advanced Enemy Switch Logic 
			On (D)
			Off
		- Limited TMs
			Limited (D)
			Unlimited
		- Battle Scan
			Normal (D)
			Complete (shows all information about an enemy trainer's team)
		- Anti-Yap Options
			Off (D)
			On
        - Hard Level Caps 
            Off (D)
            On 

*/
void Sequence18()
{
	PlaySound(1351);
	EventGreyMessage(103, 2);
	WaitForButton();

label49_options: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8004);
	// Critical Hits
	AddDialogueOption(104, 103, 0);
	// IVS
	AddDialogueOption(105, 103, 1);
	// Trainer Placements
	AddDialogueOption(106, 103, 6);
	// Wild Pokemon EVs
	// AddDialogueOption(107, 103, 2);
	// Animated Backgrounds
	AddDialogueOption(108, 103, 3);
	// Advanced Enemy Switch In Logic
	AddDialogueOption(109, 103, 4);
	

    // Exp Modes
	AddDialogueOption(197, 103, 13);

    // Limited TMs
	// AddDialogueOption(110, 103, 5);

	// Battle Scan
	AddDialogueOption(111, 103, 9);
	
    // Anti-Yap Options
	// AddDialogueOption(164, 103, 10);

    // Level Caps 
    AddDialogueOption(179, 103, 11);

	// Restore Defaults
	AddDialogueOption(113, 214, 8);

    // Casual Preset
    AddDialogueOption(211, 212, 12);

	// Quit
	AddDialogueOption(112, 103, 7);

	ShowDialogueSelection2();


//
//	CRITICAL HITS
//

	Compare(0x8004, 0);
	if (5) goto label_LevelCapOptions;
	// CloseAllMessageBoxes();
	Compare(0x401F, 0);
	if (5) goto label46_options;
	EventGreyMessage(114, 2);
	goto label47_options;

label46_options: ;
	EventGreyMessage(115, 2);

label47_options: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label48_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

// Toggling the Critical Hit Settings
label48_options: ;
	// CloseAllMessageBoxes();
	Compare(0x401F, 0);
	if (5) goto label50_options;
	EventGreyMessage(117, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 1);
	goto label51_options;

label50_options: ;
	EventGreyMessage(118, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

label51_options: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;







//

//	Level Caps

//

label_LevelCapOptions: ;
	Compare(0x8004, 11);
	if (5) goto label45_options;
	// CloseAllMessageBoxes();
	Compare(0x4051, 0);
	if (5) goto levelCapOptionsA;
	EventGreyMessage(180, 2);
	goto levelCapOptionsB;

levelCapOptionsA: ;
	EventGreyMessage(181, 2);

levelCapOptionsB: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto levelCapOptionsC;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

// Toggling the Level Cap Settings
levelCapOptionsC: ;
	// CloseAllMessageBoxes();
	Compare(0x4051, 0);
	if (5) goto levelCapOptionsD;
	EventGreyMessage(182, 2);
	WaitForButton();
	SetVarEqVar2(0x4051, 1);
	goto levelCapOptionsE;

levelCapOptionsD: ;
	EventGreyMessage(183, 2);
	WaitForButton();
	SetVarEqVar2(0x4051, 0);

levelCapOptionsE: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


//

//	Wild Pokemon IVs

//*/

label45_options: ;
	Compare(0x8004, 1);
	if (5) goto label52_options;
	// CloseAllMessageBoxes();
	Compare(0x4031, 0);
	if (5) goto label53_options;
	EventGreyMessage(120, 2);
	goto label54_options;

label53_options: ;
	Compare(0x4031, 1);
	if (5) goto label55_options;
	EventGreyMessage(124, 2);
	goto label54_options;

label55_options: ;
	EventGreyMessage(121, 2);

label54_options: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(125, 0xFFFF, 0);
	AddDialogueOption(126, 0xFFFF, 1);
	AddDialogueOption(127, 0xFFFF, 2);
	AddDialogueOption(112, 0xFFFF, 3);
	ShowDialogueSelection2();
	Compare(0x8006, 0);
	if (5) goto label56_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(123, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label56_options: ;
	Compare(0x8006, 1);
	if (5) goto label57_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(128, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 1);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label57_options: ;
	Compare(0x8006, 2);
	if (5) goto label58_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(122, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 2);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label58_options: ;
	Compare(0x8006, 3);
	if (5) goto label59_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label59_options: ;
	// CloseAllMessageBoxes();
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


//

//	Wild Pokemon Effort Values

///
label52_options: ;
	Compare(0x8004, 2);
	if (5) goto label60_options;
	// CloseAllMessageBoxes();
	Compare(0x4032, 0);
	if (5) goto label61_options;
	EventGreyMessage(129, 2);
	goto label62_options;

label61_options: ;
	Compare(0x4032, 1);
	if (5) goto label63_options;
	EventGreyMessage(130, 2);
	goto label62_options;

label63_options: ;
	Compare(0x4032, 2);
	if (5) goto label64_options;
	EventGreyMessage(131, 2);
	goto label62_options;

label64_options: ;
	EventGreyMessage(132, 2);

label62_options: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(133, 0xFFFF, 0);
	AddDialogueOption(134, 0xFFFF, 1);
	AddDialogueOption(135, 0xFFFF, 2);
	AddDialogueOption(136, 0xFFFF, 3);
	AddDialogueOption(112, 0xFFFF, 4);
	ShowDialogueSelection2();
	Compare(0x8006, 0);
	if (5) goto label65_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(137, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label65_options: ;
	Compare(0x8006, 1);
	if (5) goto label66_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(138, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 1);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label66_options: ;
	Compare(0x8006, 2);
	if (5) goto label67_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(139, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 2);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label67_options: ;
	Compare(0x8006, 3);
	if (5) goto label68_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(140, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 4);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label68_options: ;
	Compare(0x8006, 4);
	if (5) goto label69_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label69_options: ;
	// CloseAllMessageBoxes();
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

// 

//	ANIMATED BACKGROUNDS

//*/
label60_options: ;
	Compare(0x8004, 3);
	if (5) goto label70_options;
	// CloseAllMessageBoxes();
	Compare(0x4033, 0);
	if (5) goto label71_options;
	EventGreyMessage(143, 2);
	goto label72_options;

label71_options: ;
	EventGreyMessage(142, 2);

label72_options: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label73_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label73_options: ;
	// CloseAllMessageBoxes();
	Compare(0x4033, 0);
	if (5) goto label74_options;
	EventGreyMessage(145, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 1);
	goto label75_options;

label74_options: ;
	EventGreyMessage(144, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

label75_options: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


// 

//	ADVANCED SWITCH AI 

//*/
label70_options: ;
	Compare(0x8004, 4);
	if (5) goto label76_options;
	// CloseAllMessageBoxes();
	Compare(0x4034, 0);
	if (5) goto label77_options;
	EventGreyMessage(146, 2);
	goto label78_options;

label77_options: ;
	EventGreyMessage(147, 2);

label78_options: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label79_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label79_options: ;
	// CloseAllMessageBoxes();
	Compare(0x4034, 0);
	if (5) goto label80_options;
	EventGreyMessage(149, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 1);
	goto label81_options;

label80_options: ;
	EventGreyMessage(148, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

label81_options: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


// 

//	LIMITED TMS 

//*/

label76_options: ;
	Compare(0x8004, 5);
	if (5) goto label82_options;
	// CloseAllMessageBoxes();
	Compare(0x4035, 0);
	if (5) goto label83_options;
	EventGreyMessage(150, 2);
	goto label84_options;

label83_options: ;
	EventGreyMessage(151, 2);

label84_options: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label85_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49_options;

label85_options: ;
	// CloseAllMessageBoxes();
	Compare(0x4035, 0);
	if (5) goto label86_options;
	EventGreyMessage(153, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 1);
	goto label87_options;

label86_options: ;
	EventGreyMessage(152, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 0);

label87_options: ;
	EventGreyMessage(19, 2);
	WaitForButton();
	goto label49_options;


// 

//	TRAINER PLACEMENTS

//*/
label82_options: ;
	Compare(0x8004, 6);
	if (5) goto label_BattleScan_1;
	// CloseAllMessageBoxes();
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label89_options;
	SetVarEqVal(0x8000, 0);
	goto label89_options;

label89_options: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label90_options;
	EventGreyMessage(154, 2);
	goto label91_options;

label90_options: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label92_options;
	SetVarEqVal(0x8000, 0);
	goto label92_options;

label92_options: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label93_options;
	EventGreyMessage(155, 2);
	goto label91_options;

label93_options: ;
	EventGreyMessage(158, 2);
	WaitForButton();
	goto label49_options;

label91_options: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label94_options;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label94_options: ;
	// CloseAllMessageBoxes();
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label95_options;
	SetVarEqVal(0x8000, 0);
	goto label95_options;

label95_options: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label96_options;
	EventGreyMessage(156, 2);
	WaitForButton();
	ClearFlag(525);
	SetFlag(524);
	goto label97_options;

label96_options: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label98_options;
	SetVarEqVal(0x8000, 0);
	goto label98_options;

label98_options: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label99options;
	EventGreyMessage(157, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);
	goto label97_options;

label99options: ;
	EventGreyMessage(158, 2);
	WaitForButton();
	goto label49_options;

label97_options: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;



//

//  BATTLE SCAN

//
label_BattleScan_1: ;
	Compare(0x8004, 9);
	if (5) goto label_AntiYap_1;
	// CloseAllMessageBoxes();
	Compare(16438, 0);
	if (5) goto label_BattleScan_2;
	EventGreyMessage(161, 2);
	goto label_BattleScan_3;

label_BattleScan_2: ;
	EventGreyMessage(160, 2);

label_BattleScan_3: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label_BattleScan_4;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label_BattleScan_4: ;
	// CloseAllMessageBoxes();
	Compare(16438, 0);
	if (5) goto label_BattleScan_5;
	EventGreyMessage(163, 2);
	WaitForButton();
	SetVarEqVar2(16438, 1);
	goto label_BattleScan_6;

label_BattleScan_5: ;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(16438, 0);

label_BattleScan_6: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;



//

//  ANTI YAP

//
label_AntiYap_1:
	Compare(0x8004, 10);
	if (5) goto label_ExpBoost_1;
	// CloseAllMessageBoxes();
	Compare(16439, 0);
	if (5) goto label_AntiYap_2;
	EventGreyMessage(165, 2);
	goto label_AntiYap_3;

label_AntiYap_2: ;
	EventGreyMessage(166, 2);

label_AntiYap_3: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label_AntiYap_4;
	// CloseAllMessageBoxes();
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label_AntiYap_4: ;
	// CloseAllMessageBoxes();
	Compare(16439, 0);
	if (5) goto label_AntiYap_5;
	EventGreyMessage(167, 2);
	WaitForButton();
	SetVarEqVar2(16439, 1);
	goto label_AntiYap_6;

label_AntiYap_5: ;
	EventGreyMessage(168, 2);
	WaitForButton();
	SetVarEqVar2(16439, 0);

label_AntiYap_6: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


//

//  EXP BOOST 

//
label_ExpBoost_1: ;
	Compare(0x8004, 13);
	if (5) goto label_CasualPreset_1;
	Compare(0x4053, 0);
	if (5) goto label_ExpBoost_2;
	EventGreyMessage(198, 2);
	goto label_ExpBoost_5;

label_ExpBoost_2: ;
	Compare(0x4053, 1);
	if (5) goto label_ExpBoost_3;
	EventGreyMessage(199, 2);
	goto label_ExpBoost_5;

label_ExpBoost_3: ;
	EventGreyMessage(200, 2);

label_ExpBoost_5: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(201, 202, 0);
	AddDialogueOption(203, 204, 1);
	AddDialogueOption(205, 206, 2);
	AddDialogueOption(207, 0xFFFF, 2);
	ShowDialogueSelection2();
	Compare(0x8006, 0);
	if (5) goto label_ExpBoost_6;
	EventGreyMessage(208, 2);
	WaitForButton();
	SetVarEqVar2(0x4053, 0);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label_ExpBoost_6: ;
	Compare(0x8006, 1);
	if (5) goto label_ExpBoost_7;
	EventGreyMessage(209, 2);
	WaitForButton();
	SetVarEqVar2(0x4053, 1);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label_ExpBoost_7: ;
	Compare(0x8006, 2);
	if (5) goto label_ExpBoost_8;
	EventGreyMessage(210, 2);
	WaitForButton();
	SetVarEqVar2(0x4053, 2);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

label_ExpBoost_8: ;
label_ExpBoost_9: ;
	Compare(0x8006, 3);
	if (5) goto label_ExpBoost_10;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

label_ExpBoost_10: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


// 

//	Apply Casual Presets

//
label_CasualPreset_1: ;
	Compare(0x8004, 12);
	if (5) goto label_RestoreDefaults_1;
	EventGreyMessage(213, 2);
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto Label_CriticalHitCasualSetting;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

Label_CriticalHitCasualSetting: ;
	Compare(0x401F, 0);
	if (1) goto Label_WildPokemonIVCasualSettings;
	EventGreyMessage(118, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

Label_WildPokemonIVCasualSettings: ;
	Compare(0x4031, 0);
	if (1) goto Label_WildPokemonEVCasualSettings;
	EventGreyMessage(123, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);

Label_WildPokemonEVCasualSettings: ;
	Compare(0x4032, 0);
	if (1) goto label_CasualLevelCapSetting;
	EventGreyMessage(137, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);

label_CasualLevelCapSetting: ;
	Compare(0x4051, 0);
	if (1) goto Label_CasualExpModeSetting;
	EventGreyMessage(183, 2);
	WaitForButton();
	SetVarEqVar2(0x4051, 0);

Label_CasualExpModeSetting: ;
    Compare(0x4053, 1);
    if (1) goto Label_CasualTrainerPlacementSetting;
    EventGreyMessage(209, 2);
    WaitForButton();
    SetVarEqVar2(0x4053, 1);

Label_CasualTrainerPlacementSetting: ;
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto Label_CasualBattleScanSettings;
	EventGreyMessage(157, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);

Label_CasualBattleScanSettings: ;
	Compare(16438, 0);
	if (1) goto Label_RestoredCasuals;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(16438, 0);

Label_RestoredCasuals: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;


// 

//	RESTORE DEFAULTS

//
label_RestoreDefaults_1: ;
	Compare(0x8004, 8);
	if (5) goto Label_RestoreDefaultsExit;
	EventGreyMessage(159, 2);
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto Label_CriticalHitDefaultSetting;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label49_options;

Label_CriticalHitDefaultSetting: ;
	Compare(0x401F, 0);
	if (1) goto Label_WildPokemonIVDefeaultSettings;
	EventGreyMessage(118, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

Label_WildPokemonIVDefeaultSettings: ;
	Compare(0x4031, 0);
	if (1) goto Label_WildPokemonEVDefaultSettings;
	EventGreyMessage(123, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);

Label_WildPokemonEVDefaultSettings: ;
	Compare(0x4032, 0);
	if (1) goto label_DefaultLevelCapSetting;
	EventGreyMessage(137, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);

label_DefaultLevelCapSetting: ;
	Compare(0x4051, 0);
	if (1) goto Label_DefaultANimatedBackgroundSetting;
	EventGreyMessage(183, 2);
	WaitForButton();
	SetVarEqVar2(0x4051, 0);

Label_DefaultANimatedBackgroundSetting: ;
	Compare(0x4033, 0);
	if (1) goto Label_DefaultAdvancedSwitchAI;
	EventGreyMessage(144, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

Label_DefaultAdvancedSwitchAI: ;
	Compare(0x4034, 0);
	if (1) goto Label_DefaultExpModeSetting;
	EventGreyMessage(148, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

Label_DefaultExpModeSetting: ;
    Compare(0x4053, 0);
    if (1) goto Label_DefaultTrainerPlacementSetting;
    EventGreyMessage(208, 2);
    WaitForButton();
    SetVarEqVar2(0x4053, 0);

// Label_LimitedTMDefaultSettings :;
	// Compare(0x4035, 0);
	// if (1) goto Label_DefaultTrainerPlacementSetting;
	// // CloseAllMessageBoxes();
	// EventGreyMessage(152, 2);
	// WaitForButton();
	// SetVarEqVar2(0x4035, 0);

Label_DefaultTrainerPlacementSetting: ;
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto Label_DefaultBattleScanSettings;
	EventGreyMessage(157, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);

Label_DefaultBattleScanSettings: ;
	Compare(16438, 0);
	if (1) goto Label_DialogueSkipsDefaultSettting;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(16438, 0);

Label_DialogueSkipsDefaultSettting: ;
	Compare(16439, 0);
	if (1) goto Label_RestoredDefaults;
	EventGreyMessage(168, 2);
	WaitForButton();
	SetVarEqVar2(16439, 0);

Label_RestoredDefaults: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label49_options;

Label_RestoreDefaultsExit: ;
	WaitMoment();
	SetVarEqVal(0x8000, 0);
	Return();
}

/* PRE-DAMAGE SCRIPT */
void Sequence19(){
    EventGreyMessage(184, 2);
	CloseEventGreyMessage();
    OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
    // Stores Now HP
    GetPokemonParam(0x8001, 0x8004, 160);
	SetVarEqVar(0x8035, 0x8001);
    // Stores Max HP
    GetPokemonParam(0x8002, 0x8004, 161);
	SetVarEqVar(0x8037, 0x8002);
    SetVarEqVar(0x8036, 0x8035);
Label_StartSelection: ;
    SetWordPartyNickname(0, 0x8004);
    SetWordNumber(1, 0x8036, 3);
    EventGreyMessage(185, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
    Compare(0x8036, 1);
    if (3) goto Label_NotEnoughHP;
	AddDialogueOption(186, 0xFFFF, 1);
    Compare(0x8036, 5);
    if (3) goto Label_NotEnoughHP;
	AddDialogueOption(187, 0xFFFF, 5);
    Compare(0x8036, 10);
    if (3) goto Label_NotEnoughHP;
	AddDialogueOption(188, 0xFFFF, 10);
    Compare(0x8036, 20);
    if (3) goto Label_NotEnoughHP;
	AddDialogueOption(189, 0xFFFF, 20);
    Compare(0x8036, 50);
    if (3) goto Label_NotEnoughHP;
	AddDialogueOption(190, 0xFFFF, 50);
    Compare(0x8036, 100);
    if (3) goto Label_NotEnoughHP;
    AddDialogueOption(191, 0xFFFF, 100);
Label_NotEnoughHP: ;
    AddDialogueOption(193, 0xFFFF, 193);
	ShowDialogueSelection2();
	Compare(0x8024, 0xFFFE);
	if (1) goto label_EndPreDamageScript;
	Compare(0x8024, 193);
	if (1) goto label_EndPreDamageScript;
    SubtractVar(0x8036, 0x8024);
    goto Label_StartSelection;

label_EndPreDamageScript: ;
	SetPokemonIV(0x8004, 160, 0x8036);
	PlaySound(1372);
    EventGreyMessage(193, 2);
    WaitForButton();
    Return();
}


/* REMOVE ALL ITEMS FROM POKEMON SCRIPT */
/* REPLACE WITH 133 */
void Sequence20(){
    PC_131();
	EventGreyMessage(69, 2);
    SetVarEqVal(0x8036, 0x8035);
	Return();
}

/* EDGE POKEMON SCRIPT */
/* REPLACE WITH 135 */
void Sequence21()
{
    PC_131();
	EventGreyMessage(69, 2);
	Return();
}