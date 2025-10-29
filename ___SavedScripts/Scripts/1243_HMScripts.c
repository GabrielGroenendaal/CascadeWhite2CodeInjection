#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	PlaySound(1351);
	SetVarFlagStatus(2404, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label0;
	Routine0();
	goto label1;

label0: ;
	SetVarPartyHasMove(0x8010, 70);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label2;
	StoreItemCount(423, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(5);
	StackCompare(4);
	if (255) goto label2;
	Routine1();
	goto label1;

label2: ;
	EventGreyMessage(6, 2);
	YesNoBox(0x8010);
	CloseEventGreyMessage();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label1;
	Routine2();

label1: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence1()
{
	LockAll();
	SetVarFlagStatus(2404, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	Routine0();
	goto label4;

label3: ;
	SetFlag(2404);
	c0x1DD(1, 70, 0);
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	EventGreyMessage(11, 2);
	WaitForButton();
	CloseEventGreyMessage();

label4: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence2()
{
	LockAll();
	PlaySound(1351);
	SetVarPartyHasMove(0x8010, 57);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label5;
	StoreItemCount(422, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label5;
	Routine5();
	goto label6;

label5: ;
	StoreFlag(2406);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label7;
	SetWordMove(0, 57);
	Routine6();
	goto label6;

label7: ;
	EventGreyMessage(13, 2);
	YesNoBox(0x8010);
	CloseEventGreyMessage();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label6;
	Routine7();

label6: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence3()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(14, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	UseSurf();
	c0x1DD(1, 57, 0);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence4()
{
	LockAll();
	PlaySound(1351);
	SetVarPartyHasMove(0x8010, 15);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label8;
	StoreItemCount(420, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label8;
	Routine8();
	goto label9;

label8: ;
	EventGreyMessage(0, 2);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label10;
	Routine9();
	goto label9;

label10: ;
	CloseEventGreyMessage();

label9: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence5()
{
	LockAll();
	PlaySound(1351);
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(1, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	UseCut();
	c0x1DD(1, 15, 0);
	ReturnAfterDelay(3);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	GetNPCInFrontOfPlayer(0x8022, 0x8023);
	StackPushVar(0x8023);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label11;
	RemoveNPC(0x8022);

label11: ;
	SetVarEqVal(0x8023, 0);
	SetVarEqVal(0x8022, 0);
	PlaySound(1651);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence6()
{
	LockAll();
	PlaySound(1351);
	SetVarPartyHasMove(0x8010, 127);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label12;
	StoreItemCount(425, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(4);
	if (255) goto label12;
	Routine10();
	goto label13;

label12: ;
	StoreFlag(2406);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label14;
	SetWordMove(0, 127);
	Routine6();
	goto label13;

label14: ;
	EventGreyMessage(23, 2);
	YesNoBox(0x8010);
	CloseEventGreyMessage();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label13;
	Routine11();

label13: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence7()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(24, 2);
	CloseEventGreyMessage();
	c0x19C(0x8000);
	UseWaterfall(0x8000);
	c0x1DD(1, 127, 0);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence8()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(27, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence9()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(28, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence10()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(29, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence11()
{
	LockAll();
	SetVarPartyHasMove(0x8010, 291);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label15;
	EventGreyMessage(30, 2);
	WaitForButton();
	CloseEventGreyMessage();
	goto label16;

label15: ;
	StoreFlag(2406);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label17;
	SetWordMove(0, 291);
	Routine6();
	goto label16;

label17: ;
	EventGreyMessage(31, 2);
	YesNoBox(0x8010);
	CloseEventGreyMessage();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label16;
	SetVarPartyHasMove(0x8010, 291);
	SetVarEqVar(0x8008, 0x8010);
	SetWordPartyNickname(0, 0x8010);
	Routine12();

label16: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence12()
{
	LockAll();
	SetWordPartyNickname(0, 0x8000);
	SetVarEqVar(0x8008, 0x8000);
	Routine12();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence13()
{
	LockAll();
	SetVarFlagStatus(215, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label18;
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(27, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();

label18: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence14()
{
	LockAll();
	SetVarFlagStatus(214, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label19;
	SetWordPartyNickname(0, 0x8000);
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8000);
	Routine4();

label19: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence15()
{
	LockAll();
	UseWaterfall(0);
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	EventGreyMessage(9, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine1()
{
	EventGreyMessage(8, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine2()
{
	SetVarEqVal(0x8021, 0);
	SetFlag(2404);
	c0x1DD(1, 70, 0);
	SetVarPartyHasMove(0x8021, 70);
	StackPushVar(0x8021);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto labelFixVars_Strength;
	SetVarEqVal(0x8021, 0);
	goto labelContinue_Strength;

	labelFixVars_Strength:
	SetVarPartyHasMove(0x8021, 70);

	labelContinue_Strength:
	SetWordPartyNickname(0, 0x8021);
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8021);
	Routine4();
	EventGreyMessage(11, 2);
	WaitForButton();
	CloseEventGreyMessage();
	SetVarEqVal(0x8021, 0);
	Return();
}

void Routine3()
{
	PlayerPlaySequence(128);

	Movement m[] = { //255
		0xA2, 1,
	};

	WaitMovement();
	Return();
}

void Routine4()
{
	PlayerPlaySequence(8);
	Return();
}

void Routine5()
{
	EventGreyMessage(15, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine6()
{
	EventGreyMessage(33, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine7()
{
	SetVarPartyHasMove(0x8010, 57);
	SetVarEqVar(0x8008, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto labelFixVars;
	SetVarEqVal(0x8010, 0);
	SetVarEqVar(0x8008, 0x8010);
	goto labelContinue;

	labelFixVars:
	SetVarPartyHasMove(0x8010, 57);
	SetVarEqVar(0x8008, 0x8010);

	labelContinue:
	SetWordPartyNickname(0, 0x8010);
	EventGreyMessage(14, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8008);
	PlayerPlaySequence(1);
	UseSurf();
	c0x1DD(1, 57, 0);
	Return();
}

void Routine8()
{
	EventGreyMessage(2, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine9()
{
	SetVarPartyHasMove(0x8010, 15);
	SetVarEqVar(0x8008, 0x8010);

	StackPushVar(0x8010);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto labelFixVars_cut;
	SetVarEqVal(0x8010, 0);
	SetVarEqVar(0x8008, 0x8010);
	goto labelContinue_cut;

	labelFixVars_cut:
	SetVarPartyHasMove(0x8010, 15);
	SetVarEqVar(0x8008, 0x8010);

	labelContinue_cut:
	SetWordPartyNickname(0, 0x8010);
	EventGreyMessage(1, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8008);
	Routine4();
	UseCut();
	c0x1DD(1, 15, 0);
	ReturnAfterDelay(3);
	RemoveNPC(0x8011);
	PlaySound(1651);
	ReturnAfterDelay(1);
	Return();
}

void Routine10()
{
	EventGreyMessage(25, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine11()
{
	SetVarEqVal(0x8024, 0);
	SetVarPartyHasMove(0x8024, 127);

	StackPushVar(0x8024);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto labelFixVars_Waterfall;
	SetVarEqVal(0x8024, 0);
	goto labelContinue_Waterfall;

	labelFixVars_Waterfall:
	SetVarPartyHasMove(0x8024, 127);

	labelContinue_Waterfall:
	SetWordPartyNickname(0, 0x8024);
	EventGreyMessage(24, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8024);
	Routine4();
	UseWaterfall(0x8024);
	c0x1DD(1, 127, 0);
	SetVarEqVal(0x8024, 0);
	Return();
}

void Routine12()
{
	EventGreyMessage(32, 2);
	CloseEventGreyMessage();
	Routine3();
	c0x19C(0x8008);
	Routine4();
	UseDive(0);
	c0x1DD(1, 291, 0);
	Return();
}
