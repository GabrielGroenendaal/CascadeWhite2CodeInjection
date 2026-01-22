#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	SetVarEqVar(0x8021, 0x8000);
	SetVarEqVar(0x8022, 0x8001);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(5);
	if (255) goto label0;
	Message(1024, 4, 0x8011, 2, 0);

label0: ;
	Compare(0x8021, 246);
	if (1) goto label1;
	Compare(0x8021, 245);
	if (1) goto label1;
	Compare(0x8021, 244);
	if (1) goto label1;
	Compare(0x8021, 243);
	if (1) goto label1;
	goto label2;

label1: ;
	Routine0();
	goto label3;

label2: ;
	Compare(0x8021, 254);
	if (1) goto label4;
	Compare(0x8021, 253);
	if (1) goto label4;
	goto label5;

label4: ;
	Routine1();
	goto label3;

label5: ;
	Routine2();

label3: ;
	ReturnGlobalScript();
	SetVarEqVal(0x8023, 0);
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8025, 0);
	StackPushVar(0x8022);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label6;
	Message(1024, 1, 0x8011, 2, 0);
	goto label7;

label6: ;
	Message(1024, 0, 0x8011, 2, 0);

label7: ;
	SetVarEqVal(0x8024, 1);
	SetVarEqVal(0x8025, 1);

label19: ;
	StackPushVar(0x8025);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label8;
	Compare(0x8024, 0);
	if (1) goto label9;
	goto label10;

label9: ;
	Message(1024, 2, 0x8011, 2, 0);
	SetVarEqVal(0x8024, 1);
	goto label11;

label10: ;
	Compare(0x8024, 1);
	if (1) goto label12;
	goto label13;

label12: ;
	Routine3();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label13: ;
	Compare(0x8024, 2);
	if (1) goto label14;
	goto label15;

label14: ;
	Routine4();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label15: ;
	Compare(0x8024, 3);
	if (1) goto label16;
	goto label17;

label16: ;
	Routine5();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label17: ;
	Compare(0x8024, 255);
	if (1) goto label18;
	goto label11;

label18: ;
	SetVarEqVal(0x8025, 0);
	goto label11;

label11: ;
	goto label19;

label8: ;
	Message(1024, 3, 0x8011, 2, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8023, 0);
	Return();
}

void Routine0()
{
	SetVarEqVal(0x8029, 0);
	Routine4();
	SetVarEqVal(0x8029, 0);
	Return();
}

void Routine1()
{
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8027, 0);
	SetVarEqVal(0x8028, 0);
	Message(1024, 8, 0x8011, 2, 0);
	YesNoBox(0x8026);
	StackPushVar(0x8026);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label20;
	Routine4();

label20: ;
	Message(1024, 9, 0x8011, 2, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8027, 0);
	SetVarEqVal(0x8026, 0);
	Return();
}

void Routine2()
{
	SetVarEqVal(0x8023, 0);
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8025, 0);
	StackPushVar(0x8022);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label6;
	Message(1024, 1, 0x8011, 2, 0);
	goto label7;

label6: ;
	Message(1024, 0, 0x8011, 2, 0);

label7: ;
	SetVarEqVal(0x8024, 1);
	SetVarEqVal(0x8025, 1);

label19: ;
	StackPushVar(0x8025);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label8;
	Compare(0x8024, 0);
	if (1) goto label9;
	goto label10;

label9: ;
	Message(1024, 2, 0x8011, 2, 0);
	SetVarEqVal(0x8024, 1);
	goto label11;

label10: ;
	Compare(0x8024, 1);
	if (1) goto label12;
	goto label13;

label12: ;
	Routine3();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label13: ;
	Compare(0x8024, 2);
	if (1) goto label14;
	goto label15;

label14: ;
	Routine4();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label15: ;
	Compare(0x8024, 3);
	if (1) goto label16;
	goto label17;

label16: ;
	Routine5();
	SetVarEqVar(0x8024, 0x8020);
	goto label11;

label17: ;
	Compare(0x8024, 255);
	if (1) goto label18;
	goto label11;

label18: ;
	SetVarEqVal(0x8025, 0);
	goto label11;

label11: ;
	goto label19;

label8: ;
	Message(1024, 3, 0x8011, 2, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8023, 0);
	Return();
}

void Routine3()
{
	SetVarEqVal(0x802A, 0);
	SetupDialogueSelection(31, 1, 0, 1, 0x802A);
	AddDialogueOption(5, 0xFFFF, 2);
	AddDialogueOption(6, 0xFFFF, 3);
	AddDialogueOption(7, 0xFFFF, 255);
	ShowDialogueSelection();
	StackPushVar(0x802A);
	StackPushConst(0xFFFE);
	StackCompare(1);
	if (255) goto label21;
	SetVarEqVal(0x8020, 255);
	goto label22;

label21: ;
	SetVarEqVar(0x8020, 0x802A);

label22: ;
	SetVarEqVal(0x802A, 0);
	Return();
}

void Routine4()
{
	SetVarEqVal(0x802B, 0);
	SetVarEqVal(0x802B, 1);
	CloseMessageBox();
	c0x149(0x8021, 0x802B);
	StackPushVar(0x802B);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label23;
	SetVarEqVal(0x8020, 255);
	goto label24;

label23: ;
	SetVarEqVal(0x8020, 0);

label24: ;
	SetVarEqVal(0x802B, 0);
	Return();
}

void Routine5()
{
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	FadeIntoBlack2();
	WaitFade();
	CloseMessageBox();
	c0x14B();
	c0x14E(0, 0x802C, 0x802D);
	c0x14A();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label25;
	SetVarEqVal(0x8020, 255);
	goto label26;

label25: ;
	SetVarEqVal(0x8020, 0);

label26: ;
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802C, 0);
	Return();
}
