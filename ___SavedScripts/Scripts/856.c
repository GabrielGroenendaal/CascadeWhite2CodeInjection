#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"
#include "ScriptHeaders/CommandOverlay65.h"

void Sequence0()
{
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence1()
{
	SetVarEqVal(0x8001, 1);
	SetVarEqVar(0x8000, 0x40A3);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(0);
	StackPop(0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(739, 0x8000);
	SetVarEqVar(0x8001, 0x8000);
	StackPop(0x8000);
	BitwiseOrVar(0x8000, 0x8001);
	Compare(0x8000, 0);
	if (1) goto label0;
	goto label1;

label0: ;
	SetNPCPosition(0, 4, 0, 5, 3);

label1: ;
	Routine0();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence2()
{
	LockAll();
	NPCPathFind(0, 9, 8, 1, 8, 1);
	WaitMovement();
	Message(1024, 1, 0, 1, 0);
	SetWordPlayerName(0);
	Message(1024, 2, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 1);
	if (1) goto label5;
	goto label6;

label5: ;
	SetVarEqVal(0x8005, 1);

label8: ;
	Compare(0x8005, 1);
	if (1) goto label7;
	goto label6;

label7: ;
	CloseAllMessageBoxes();

	Movement m[] = { //0
		Exclaimation, 1,
	};

	WaitMovement();

	Movement m[] = { //0
		LockDirection, 1,
		WalkLeft, 1,
		UnlockDirection, 1,
	};

	WaitMovement();
	Message(1024, 4, 0, 1, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //0
		WalkRight, 1,
	};

	WaitMovement();
	Message(1024, 3, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8005, 0x8000);
	goto label8;

label6: ;
	Message(1024, 5, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 0);
	if (1) goto label9;
	Message(1024, 7, 0, 1, 0);
	goto label10;

label9: ;
	Message(1024, 6, 0, 1, 0);

label10: ;
	Message(1024, 8, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 1);
	if (1) goto label11;
	goto label12;

label11: ;
	SetVarEqVal(0x8005, 1);

label14: ;
	Compare(0x8005, 1);
	if (1) goto label13;
	goto label12;

label13: ;
	Message(1024, 10, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8005, 0x8000);
	goto label14;

label12: ;
	Message(1024, 9, 0, 1, 0);
	SetVarFlagStatus(1, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label15;
	SetVarEqVal(0x8000, 0);
	goto label16;

label15: ;
	SetVarEqVal(0x8000, 1);

label16: ;
	Compare(0x8000, 0);
	if (1) goto label17;
	SetWordPlayerName(0);
	Message(1024, 12, 0, 1, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 0);
	if (1) goto label18;
	goto label19;

label18: ;
	Message(1024, 14, 0, 1, 0);
	WaitMessage();
	CloseAllMessageBoxes();
	goto label20;

label17: ;
	SetWordPlayerName(0);
	Message(1024, 11, 0, 1, 0);
	WaitMessage();
	CloseAllMessageBoxes();
	goto label20;

label19: ;
	Message(1024, 13, 0, 1, 0);
	WaitMessage();
	CloseAllMessageBoxes();

label20: ;
	NPCPathFind(0, 8, 7, 1, 8, 0);
	WaitMovement();

	Movement m[] = { //0
		TurnDown, 1,
	};

	WaitMovement();
	SetVarEqVar2(0x40A0, 1);
	c0x263(4);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence3()
{
	LockAll();
	SetVarFlagStatus(2400, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label21;
	SetVarEqVal(0x8000, 0);
	goto label22;

label21: ;
	SetVarEqVal(0x8000, 1);

label22: ;
	Compare(0x8000, 0);
	if (1) goto label23;
	SetVarFlagStatus(2406, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label24;
	SetVarEqVal(0x8000, 0);
	goto label25;

label24: ;
	SetVarEqVal(0x8000, 1);

label25: ;
	Compare(0x8000, 0);
	if (1) goto label26;
	goto label27;

label26: ;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 15, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label28;

label23: ;
	Routine1();
	goto label28;

label27: ;
	Compare(0x40A1, 2);
	if (0) goto label29;
	Routine1();
	goto label28;

label29: ;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 14, 0, 0);
	WaitForButton();
	CloseMessageBox();

label28: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence4()
{
	LockAll();
	SetVarEqVal(0x8001, 2);
	SetVarEqVar(0x8000, 0x4115);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(5);
	StackPop(0x8000);
	StackPushVar(0x8000);
	SetVarEqVal(0x8001, 3);
	SetVarEqVar(0x8000, 0x4115);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(5);
	StackPop(0x8000);
	SetVarEqVar(0x8001, 0x8000);
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 0x8001);
	Compare(0x8000, 0);
	if (1) goto label36;
	Compare(0x4115, 4);
	if (1) goto label37;
	goto label38;

label37: ;
	Routine2();
	goto label39;

label36: ;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 49, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label39;

label38: ;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 16, 0, 0);
	WaitForButton();
	CloseMessageBox();

label39: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence5()
{
	LockAll();
	PlaySound(1351);
	EventGreyMessage(39, 2);
	WaitForButton();

label49: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8004);
	AddDialogueOption(63, 0xFFFF, 0);
	AddDialogueOption(64, 0xFFFF, 1);
	AddDialogueOption(74, 0xFFFF, 2);
	AddDialogueOption(75, 0xFFFF, 3);
	AddDialogueOption(76, 0xFFFF, 4);
	AddDialogueOption(77, 0xFFFF, 5);
	AddDialogueOption(65, 0xFFFF, 6);
	AddDialogueOption(66, 0xFFFF, 7);
	AddDialogueOption(100, 0xFFFF, 8);
	ShowDialogueSelection();
	Compare(0x8004, 0);
	if (5) goto label45;
	CloseAllMessageBoxes();
	Compare(0x401F, 0);
	if (5) goto label46;
	EventGreyMessage(57, 2);
	goto label47;

label46: ;
	EventGreyMessage(58, 2);

label47: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label48;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label48: ;
	CloseAllMessageBoxes();
	Compare(0x401F, 0);
	if (5) goto label50;
	EventGreyMessage(60, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 1);
	goto label51;

label50: ;
	EventGreyMessage(67, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

label51: ;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label45: ;
	Compare(0x8004, 1);
	if (5) goto label52;
	CloseAllMessageBoxes();
	Compare(0x4031, 0);
	if (5) goto label53;
	EventGreyMessage(69, 2);
	goto label54;

label53: ;
	Compare(0x4031, 1);
	if (5) goto label55;
	EventGreyMessage(95, 2);
	goto label54;

label55: ;
	EventGreyMessage(70, 2);

label54: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(92, 0xFFFF, 0);
	AddDialogueOption(93, 0xFFFF, 1);
	AddDialogueOption(94, 0xFFFF, 2);
	AddDialogueOption(66, 0xFFFF, 3);
	ShowDialogueSelection();
	Compare(0x8006, 0);
	if (5) goto label56;
	CloseAllMessageBoxes();
	EventGreyMessage(72, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label56: ;
	Compare(0x8006, 1);
	if (5) goto label57;
	CloseAllMessageBoxes();
	EventGreyMessage(91, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 1);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label57: ;
	Compare(0x8006, 2);
	if (5) goto label58;
	CloseAllMessageBoxes();
	EventGreyMessage(71, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 2);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label58: ;
	Compare(0x8006, 3);
	if (5) goto label59;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label59: ;
	CloseAllMessageBoxes();
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label52: ;
	Compare(0x8004, 2);
	if (5) goto label60;
	CloseAllMessageBoxes();
	Compare(0x4032, 0);
	if (5) goto label61;
	EventGreyMessage(78, 2);
	goto label62;

label61: ;
	Compare(0x4032, 1);
	if (5) goto label63;
	EventGreyMessage(79, 2);
	goto label62;

label63: ;
	Compare(0x4032, 2);
	if (5) goto label64;
	EventGreyMessage(80, 2);
	goto label62;

label64: ;
	EventGreyMessage(81, 2);

label62: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(83, 0xFFFF, 0);
	AddDialogueOption(84, 0xFFFF, 1);
	AddDialogueOption(85, 0xFFFF, 2);
	AddDialogueOption(86, 0xFFFF, 3);
	AddDialogueOption(66, 0xFFFF, 4);
	ShowDialogueSelection();
	Compare(0x8006, 0);
	if (5) goto label65;
	CloseAllMessageBoxes();
	EventGreyMessage(87, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label65: ;
	Compare(0x8006, 1);
	if (5) goto label66;
	CloseAllMessageBoxes();
	EventGreyMessage(88, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 1);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label66: ;
	Compare(0x8006, 2);
	if (5) goto label67;
	CloseAllMessageBoxes();
	EventGreyMessage(89, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 2);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label67: ;
	Compare(0x8006, 3);
	if (5) goto label68;
	CloseAllMessageBoxes();
	EventGreyMessage(90, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 4);
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label68: ;
	Compare(0x8006, 4);
	if (5) goto label69;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label69: ;
	CloseAllMessageBoxes();
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label60: ;
	Compare(0x8004, 3);
	if (5) goto label70;
	CloseAllMessageBoxes();
	Compare(0x4033, 0);
	if (5) goto label71;
	EventGreyMessage(119, 2);
	goto label72;

label71: ;
	EventGreyMessage(120, 2);

label72: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label73;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label73: ;
	CloseAllMessageBoxes();
	Compare(0x4033, 0);
	if (5) goto label74;
	EventGreyMessage(121, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 1);
	goto label75;

label74: ;
	EventGreyMessage(122, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

label75: ;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label70: ;
	Compare(0x8004, 4);
	if (5) goto label76;
	CloseAllMessageBoxes();
	Compare(0x4034, 0);
	if (5) goto label77;
	EventGreyMessage(101, 2);
	goto label78;

label77: ;
	EventGreyMessage(102, 2);

label78: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label79;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label79: ;
	CloseAllMessageBoxes();
	Compare(0x4034, 0);
	if (5) goto label80;
	EventGreyMessage(104, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 1);
	goto label81;

label80: ;
	EventGreyMessage(103, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

label81: ;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label76: ;
	Compare(0x8004, 5);
	if (5) goto label82;
	CloseAllMessageBoxes();
	Compare(0x4035, 0);
	if (5) goto label83;
	EventGreyMessage(105, 2);
	goto label84;

label83: ;
	EventGreyMessage(106, 2);

label84: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label85;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label85: ;
	CloseAllMessageBoxes();
	Compare(0x4035, 0);
	if (5) goto label86;
	EventGreyMessage(108, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 1);
	goto label87;

label86: ;
	EventGreyMessage(107, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 0);

label87: ;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label82: ;
	Compare(0x8004, 6);
	if (5) goto label88;
	CloseAllMessageBoxes();
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label89;
	SetVarEqVal(0x8000, 0);
	goto label89;

label89: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label90;
	EventGreyMessage(114, 2);
	goto label91;

label90: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label92;
	SetVarEqVal(0x8000, 0);
	goto label92;

label92: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label93;
	EventGreyMessage(115, 2);
	goto label91;

label93: ;
	EventGreyMessage(118, 2);
	WaitForButton();
	goto label49;

label91: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label94;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label94: ;
	CloseAllMessageBoxes();
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label95;
	SetVarEqVal(0x8000, 0);
	goto label95;

label95: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label96;
	EventGreyMessage(116, 2);
	WaitForButton();
	ClearFlag(525);
	SetFlag(524);
	goto label97;

label96: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label98;
	SetVarEqVal(0x8000, 0);
	goto label98;

label98: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label99;
	EventGreyMessage(117, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);
	goto label97;

label99: ;
	EventGreyMessage(118, 2);
	WaitForButton();
	goto label49;

label97: ;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label88: ;
	Compare(0x8004, 8);
	if (5) goto label100;
	CloseAllMessageBoxes();
	EventGreyMessage(109, 2);
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label101;
	CloseAllMessageBoxes();
	EventGreyMessage(59, 2);
	WaitForButton();
	goto label49;

label101: ;
	CloseAllMessageBoxes();
	Compare(0x401F, 0);
	if (1) goto label102;
	CloseAllMessageBoxes();
	EventGreyMessage(67, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

label102: ;
	Compare(0x4031, 0);
	if (1) goto label103;
	CloseAllMessageBoxes();
	EventGreyMessage(72, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);

label103: ;
	Compare(0x4032, 0);
	if (1) goto label104;
	CloseAllMessageBoxes();
	EventGreyMessage(87, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);

label104: ;
	Compare(0x4033, 0);
	if (1) goto label105;
	CloseAllMessageBoxes();
	EventGreyMessage(122, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

label105: ;
	Compare(0x4034, 0);
	if (1) goto label106;
	CloseAllMessageBoxes();
	EventGreyMessage(103, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

label106: ;
	Compare(0x4035, 0);
	if (1) goto label107;
	CloseAllMessageBoxes();
	EventGreyMessage(107, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 0);

label107: ;
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label108;
	ClearFlag(524);
	SetFlag(525);

label108: ;
	CloseAllMessageBoxes();
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label49;

label100: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence6()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(40, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence7()
{
	LockAll();
	SetWordPlayerName(0);
	PlaySound(1351);
	BubbleMessage(41, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence8()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(42, 2);
	CloseAllMessageBoxes();
	FadeIntoBlack2();
	WaitFade();
	c0x14B();
	c0x151(0, 1);
	c0x14A();
	FadeFromBlack2();
	WaitFade();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8004, 0);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence9()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(43, 2);
	CloseAllMessageBoxes();
	FadeIntoBlack2();
	WaitFade();
	c0x14B();
	c0x151(1, 1);
	c0x14A();
	FadeFromBlack2();
	WaitFade();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8004, 0);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence10()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(44, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence11()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(45, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence12()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(46, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence13()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(47, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence14()
{
	LockAll();
	PlaySound(1351);
	BubbleMessage(48, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence15()
{
	LockAll();
	SetWordPlayerName(0);

	Movement m[] = { //0
		Exclaimation, 1,
	};

	WaitMovement();
	NPCPathFind(0, 9, 8, 1, 8, 1);
	WaitMovement();
	Message(1024, 25, 0, 0, 0);
	Message(1024, 26, 0, 0, 0);
	CloseAllMessageBoxes();
	NPCPathFind(255, 5, 6, 1, 8, 0);
	NPCPathFind(0, 4, 6, 1, 8, 0);
	WaitMovement();

	Movement m[] = { //0
		TurnDown, 1,
	};


	Movement m[] = { //255
		TurnDown, 1,
	};

	WaitMovement();
	PlaySound(1369);
	CreateNPC(5, 10, 0, 251, 104, 0);
	WaitSound();
	ChangeMusic(1090);
	NPCPathFind(251, 5, 8, 1, 8, 0);
	WaitMovement();
	Message(1024, 27, 251, 2, 0);
	CloseAllMessageBoxes();
	Message(1024, 28, 0, 1, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //251
		QuestionMark, 1,
	};

	WaitMovement();
	Message(1024, 29, 251, 2, 0);
	CloseAllMessageBoxes();
	NPCPathFind(251, 5, 7, 1, 8, 0);
	WaitMovement();
	Message(1024, 30, 251, 2, 0);
	CloseAllMessageBoxes();
	PlayFanfare(1303);
	SetWordPlayerName(0);
	EventGreyMessage(31, 2);
	WaitFanfare();
	WaitMessage();
	CloseAllMessageBoxes();
	EnableNationalDex();

	Movement m[] = { //251
		LockDirection, 1,
		WalkDown, 1,
		UnlockDirection, 1,
	};

	WaitMovement();
	Message(1024, 32, 251, 2, 0);
	CloseAllMessageBoxes();
	Message(1024, 33, 0, 1, 0);
	CloseAllMessageBoxes();
	Message(1024, 34, 251, 2, 0);
	Message(1024, 35, 251, 2, 0);
	CloseAllMessageBoxes();
	NPCPathFind(251, 5, 10, 1, 8, 0);
	WaitMovement();
	PlaySound(1369);
	RemoveNPC(251);
	WaitSound();
	FadeToDefaultMusic();

	Movement m[] = { //0
		TurnRight, 1,
	};

	ReturnAfterDelay(8);

	Movement m[] = { //255
		TurnLeft, 1,
	};

	WaitMovement();
	Message(1024, 36, 0, 1, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8004);
	StackPushVar(0x8005);
	SetVarEqVal(0x8006, 29);
	SetVarEqVal(0x8007, 2);
	SetVarEqVar(0x8000, 0x8006);
	SetVarEqVar(0x8001, 0x8007);
	CallGlobalScript(2805);
	StackPop(0x8005);
	StackPop(0x8004);
	Message(1024, 37, 0, 1, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVar2(0x40A0, 3);
	ClearFlag(745);
	ClearFlag(744);
	SetVarEqVar2(0x4115, 1);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence16()
{
	LockAll();
	StartCameraEvent();
	LockCamera();
	MoveCamera(9688, 0, 0xED000, 0x58000, 0, 0xA8000, 1);
	EndCameraEvent();
	ClearFlag(740);
	AddNPC(0);
	SetNPCPosition(0, 5, 0, 10, 0);
	FadeFromBlack2();
	WaitFade();
	PlaySound(1369);
	WaitSound();
	NPCPathFind(0, 5, 8, 0, 8, 1);
	WaitMovement();

	Movement m[] = { //0
		TurnRight, 1,
	};

	WaitMovement();
	SetWordPlayerName(0);
	Message(1024, 0, 0, 1, 0);
	CloseAllMessageBoxes();
	c0x144(40);
	EndCameraEvent();
	ReleaseCamera();
	StopCameraEvent();

	Movement m[] = { //255
		TurnDown, 1,
	};

	WaitMovement();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence17()
{
	Routine0();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence18()
{
	LockAll();

	Movement m[] = { //0
		Exclaimation, 1,
	};

	WaitMovement();
	Message(1024, 55, 0, 1, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVar2(0x402F, 1);
	ClearFlag(524);
	SetFlag(525);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine0()
{
	SetVarFlagStatus(736, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label2;
	goto label3;

label2: ;
	c0x1D7(7, 11, 0, 1);

label3: ;
	SetVarFlagStatus(737, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label4;
	SetVarEqVal(0x8000, 0);
	Return();

label4: ;
	c0x1D7(8, 12, 0, 1);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine1()
{
	PlaySound(1351);
	FacePlayer();
	Compare(0x400F, 999);
	if (1) goto label30;
	SetWordPlayerName(0);
	Message2(1024, 17, 0, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8004);
	Routine3();
	StackPop(0x8004);
	StoreRandomNumber(0x8000, 5);
	SetVarEqVar(0x8005, 0x8000);
	SetVarEqVar2(0x400A, 0x8005);
	StackPushVar(0x8004);
	Routine4();
	StackPop(0x8004);
	Message2(1024, 0x8004, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVal(0x8000, 0);
	Return();

label30: ;
	SetWordPlayerName(0);
	StackPushVar(0x8004);
	Routine4();
	StackPop(0x8004);
	Message2(1024, 0x8004, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine2()
{
	StoreRandomNumber(0x8000, 5);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 0);
	if (5) goto label40;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 50, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8000, 0);
	Return();

label40: ;
	Compare(0x8004, 1);
	if (5) goto label41;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 51, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8000, 0);
	Return();

label41: ;
	Compare(0x8004, 2);
	if (5) goto label42;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8000, 0);
	Return();

label42: ;
	Compare(0x8004, 3);
	if (5) goto label43;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 53, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8000, 0);
	Return();

label43: ;
	Compare(0x8004, 4);
	if (5) goto label44;
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 54, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8000, 0);
	Return();

label44: ;
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine3()
{
	FadeScreen(3, 0, 16, 2);
	ResetScreen();
	HealPokemon();
	PlayFanfare(1300);
	WaitFanfare();
	FadeScreen(3, 16, 0, 2);
	ResetScreen();
	SetVarEqVar2(0x400F, 999);
	c0x227(72, 1);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine4()
{
	SetWordPlayerName(0);
	Compare(0x400A, 0);
	if (5) goto label31;
	SetVarEqVal(0x8004, 18);
	SetVarEqVal(0x8000, 0);
	Return();

label31: ;
	Compare(0x400A, 1);
	if (5) goto label32;
	SetVarEqVal(0x8004, 19);
	SetVarEqVal(0x8000, 0);
	Return();

label32: ;
	Compare(0x400A, 2);
	if (5) goto label33;
	SetVarEqVal(0x8004, 20);
	SetVarEqVal(0x8000, 0);
	Return();

label33: ;
	Compare(0x400A, 3);
	if (5) goto label34;
	SetVarEqVal(0x8004, 21);
	SetVarEqVal(0x8000, 0);
	Return();

label34: ;
	Compare(0x400A, 4);
	if (5) goto label35;
	SetVarEqVal(0x8004, 22);
	SetVarEqVal(0x8000, 0);
	Return();

label35: ;
	SetVarEqVal(0x8000, 0);
	Return();
}
