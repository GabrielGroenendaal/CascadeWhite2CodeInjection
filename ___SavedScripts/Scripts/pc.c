#include "ScriptHeaders/BeaterScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	ActorPauseAll();
	Sequence10();
	Sequence12();
	WorkSetConst(0x8024, 0);
	WorkSetConst(0x8025, 0);
	WorkSetConst(0x8026, 0);
	WorkSetConst(0x8020, 0);
	WorkSetConst(0x8021, 0);
	FlagGet(2411, 0x8025);
	FlagGet(2402, 0x8026);
	FlagGet(2400, 0x8022);
	HOFCheckIntegrity(0x8023);
	SEPlay(1371);
	WordSetPlayerName(0);
	MsgSystem(0, 2);

label27: ;
	StackPush(0x8020);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label0;
	SEPlay(1372);
	MsgSystem(1, 2);
	ListMenuInitTR(31, 1, 0, 1, 0x8024);
	FlagGet(2401, 0x8028);
	WorkCmpConst(0x8028, 1);
	if (0) goto label1;
	StackPush(0x8025);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label2;
	ListMenuAdd(2, 0xFFFF, 2);
	goto label1;

label2: ;
	ListMenuAdd(3, 0xFFFF, 3);

label1: ;
	WordSetPlayerName(0);
	ListMenuAdd(4, 0xFFFF, 4);
	StackPush(0x8026);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label3;
	ListMenuAdd(5, 0xFFFF, 5);
	FlagGet(3063, 0x8028);
	WorkCmpConst(0x8028, 1);
	if (1) goto label5;
	goto label4;

label4: ;
	ListMenuAdd(42, 0xFFFF, 42); // Repel is DISABLED
	goto label92;

label5: ;
	ListMenuAdd(59, 0xFFFF, 42); // Repel is ENABLED
	goto label92;

label92:;
	// check for applicable zone for weather toggle
	FieldGetZoneID(0x8028);
	WorkCmpConst(0x8028, 337); // route 7: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 345); // route 8: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 368); // route 12: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 448); // virbank city: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 456); // virbank complex: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 107); // mistralton city: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 113); // icirrus city: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 198); // twist mountain: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 199); // twist mountain: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 205); // dragonspiral tower: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 206); // dragonspiral tower: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 439); // flocessy town: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 444); // flocessy ranch: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 445); // flocessy ranch: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 446); // route 20: rain
	if (1) goto label87;
	WorkCmpConst(0x8028, 96); // driftveil city: hail
	if (1) goto label88;
	WorkCmpConst(0x8028, 331); // route 6: hail
	if (1) goto label88;
	goto label3;

label87:;
	WorkSetConst(0x8027, 2); // placeholder for rain
	ListMenuAdd(75, 0xFFFF, 75); // Toggle weather (rain)
	goto label3;

label88:;
	WorkSetConst(0x8027, 5); // placeholder for hail
	ListMenuAdd(75, 0xFFFF, 75); // Toggle weather (hail)
	goto label3;

label3: ;
	StackPush(0x8022);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label6;
	ListMenuAdd(6, 0xFFFF, 6);

label6: ;
	ListMenuAdd(7, 0xFFFF, 7);
	ListMenuAdd(8, 0xFFFF, 8);
	ListMenuShow2();
	MsgSystemClose();
	VMSleep(3);
	WorkCmpConst(0x8024, 2);
	if (1) goto label7;
	goto label8;

label7: ;
	Sequence1();
	goto label9;

label8: ;
	WorkCmpConst(0x8024, 3);
	if (1) goto label10;
	goto label11;

label10: ;
	Sequence1();
	goto label9;

label11: ;
	WorkCmpConst(0x8024, 4);
	if (1) goto label12;
	goto label13;

label12: ;
	Sequence2();
	goto label9;

label13: ;
	WorkCmpConst(0x8024, 42);
	if (1) goto label14;
	goto label15;

label14: ;
	Sequence8();
	goto label9;

label15: ;
	WorkCmpConst(0x8024, 5);
	if (1) goto label16;
	goto label17;

label16: ;
	Sequence3();
	goto label9;

label17: ;
	WorkCmpConst(0x8024, 6);
	if (1) goto label18;
	goto label89;

label18: ;
	Sequence4();
	goto label9;

label89:;
	WorkCmpConst(0x8024, 75);
	if (1) goto label90;
	goto label19;

label90: ;
	Sequence14();
	goto label9;

label19: ;
	WorkCmpConst(0x8024, 7);
	if (1) goto label20;
	goto label21;

label20: ;
	Sequence5();
	goto label9;

label21: ;
	WorkCmpConst(0x8024, 8);
	if (1) goto label22;
	goto label23;

label22: ;
	WorkSetConst(0x8020, 1);
	goto label9;

label23: ;
	WorkCmpConst(0x8024, 0xFFFE);
	if (1) goto label24;
	goto label25;

label24: ;
	WorkSetConst(0x8020, 1);
	goto label9;

label25: ;
	WorkCmpConst(0x8024, 0xFFFD);
	if (1) goto label26;
	goto label9;

label26: ;
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);
	goto label9;

label9: ;
	goto label27;

label0: ;
	SEPlay(1373);
	WorkSetConst(0x8026, 0);
	WorkSetConst(0x8025, 0);
	WorkSetConst(0x8024, 0);
	RTFinishSubEvents();
	ActorUnlockAll();
	VMHalt();
}

void Sequence1()
{
	WorkSetConst(0x8027, 0);
	WorkSetConst(0x8028, 0);
	WorkSetConst(0x8029, 0);
	WorkSetConst(0x802A, 0);
	WorkSetConst(0x802B, 0);
	FlagGet(2400, 0x802A);
	FlagGet(249, 0x802B);
	SEPlay(1372);
	MsgSystem(14, 2);
	StackPush(0x802A);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label28;
	FlagGet(246, 0x8010);
	StackPush(0x8010);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label28;
	MEPlay(1308);
	MEWait();
	MsgSystem(12, 2);
	FlagSet(246);

label28: ;
	StackPush(0x802B);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label29;
	FlagGet(247, 0x8010);
	StackPush(0x8010);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label29;
	MEPlay(1308);
	MEWait();
	MsgSystem(13, 2);
	FlagSet(247);

label29: ;
	WorkSetConst(0x8027, 0);

label57: ;
	StackPush(0x8027);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label30;
	MsgSystem(41, 2);
	ListMenuInitTR(31, 1, 0, 1, 0x8028);
	ListMenuAdd(15, 21, 15);
	ListMenuAdd(16, 22, 16);
	ListMenuAdd(17, 23, 17);
	ListMenuAdd(20, 26, 20);
	ListMenuAdd(18, 24, 18);
	ListMenuAdd(43, 44, 43);
	ListMenuAdd(45, 46, 45);
	ListMenuAdd(71, 72, 71);
	FlagGet(124, 0x802B);
	WorkCmpConst(0x802B, 1);
	if (0) goto label31;
	ListMenuAdd(47, 48, 47);

label31: ;
	ListMenuAdd(19, 25, 19);
	ListMenuShow2();
	MsgSystemClose();
	WorkCmpConst(0x8028, 19);
	if (1) goto label32;
	goto label33;

label32: ;
	VMReturn();
	goto label34;

label33: ;
	WorkCmpConst(0x8028, 0xFFFE);
	if (1) goto label35;
	goto label36;

label35: ;
	VMReturn();
	goto label34;

label36: ;
	WorkCmpConst(0x8028, 0xFFFD);
	if (1) goto label37;
	goto label34;

label37: ;
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);
	VMReturn();
	goto label34;

label34: ;
	WorkCmpConst(0x8028, 45);
	if (0) goto label38;
	goto label39;

label38: ;
	FadeOutBlackQ();
	FadeWait();
	WorkCmpConst(0x8028, 15);
	if (1) goto label40;
	goto label39;

label40: ;
	CallPC(0x8029, 0);
	goto label41;

label39: ;
	WorkCmpConst(0x8028, 16);
	if (1) goto label42;
	goto label43;

label42: ;
	CallPC(0x8029, 1);
	goto label41;

label43: ;
	WorkCmpConst(0x8028, 17);
	if (1) goto label44;
	goto label45;

label44: ;
	CallPC(0x8029, 2);
	goto label41;

label45: ;
	WorkCmpConst(0x8028, 20);
	if (1) goto label46;
	goto label47;

label46: ;
	CallPC(0x8029, 4);
	goto label41;

label47: ;
	WorkCmpConst(0x8028, 18);
	if (1) goto label48;
	goto label49;

label48: ;
	CallPC(0x8029, 3);
	goto label41;

label49: ;
	WorkCmpConst(0x8028, 43);
	if (1) goto label50;
	goto label51;

label50: ;
	Sequence6();
	goto label52;

label51: ;
	WorkCmpConst(0x8028, 45);
	if (1) goto label53;
	goto label54;

label53: ;
	Sequence7();
	goto label52;

label54: ;
	WorkCmpConst(0x8028, 47);
	if (1) goto label55;
	goto label85;

label55: ;
	Sequence9();
	SEPlay(1372);
	goto label52;


label85: ;
	WorkCmpConst(0x8028, 71);
	if (1) goto label86;
	goto label41;

label86: 
	MsgSystem(73, 2);
	YesNoWin(0x8000);
	WorkCmpConst(0x8000, 1);
	if (1) goto label52;
	Sequence13();
	goto label52;

label41: ;
	PokecenPCIdle();
	FadeInBlackQ();
	FadeWait();
	StackPush(0x8029);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label56;
	SEPlay(1372);
	goto label52;

label56: ;
	WorkSetConst(0x8027, 1);
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);

label52: ;
	goto label57;

label30: ;
	WorkSetConst(0x802B, 0);
	WorkSetConst(0x802A, 0);
	WorkSetConst(0x8029, 0);
	WorkSetConst(0x8028, 0);
	WorkSetConst(0x8027, 0);
	VMReturn();
}

void Sequence2()
{
	WorkSetConst(0x802C, 0);
	WorkSetConst(0x802D, 0);
	WorkSetConst(0x802E, 0);
	SEPlay(1372);
	WordSetPlayerName(0);
	MsgSystem(27, 2);
	MsgSystemClose();
	WorkSetConst(0x802C, 0);

label67: ;
	StackPush(0x802C);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label58;
	MsgSystem(41, 2);
	ListMenuInitTR(31, 1, 0, 1, 0x802D);
	ListMenuAdd(28, 30, 28);
	ListMenuAdd(29, 31, 29);
	ListMenuShow2();
	MsgSystemClose();
	WorkCmpConst(0x802D, 29);
	if (1) goto label59;
	goto label60;

label59: ;
	VMReturn();
	goto label61;

label60: ;
	WorkCmpConst(0x802D, 0xFFFE);
	if (1) goto label62;
	goto label63;

label62: ;
	VMReturn();
	goto label61;

label63: ;
	WorkCmpConst(0x802D, 0xFFFD);
	if (1) goto label64;
	goto label61;

label64: ;
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);
	VMReturn();
	goto label61;

label61: ;
	FadeOutBlackQ();
	FadeWait();
	CallMailbox(0x802E);
	PokecenPCIdle();
	FadeInBlackQ();
	FadeWait();
	StackPush(0x802E);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label65;
	SEPlay(1372);
	goto label66;

label65: ;
	WorkSetConst(0x802C, 1);
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);

label66: ;
	goto label67;

label58: ;
	WorkSetConst(0x802E, 0);
	WorkSetConst(0x802D, 0);
	WorkSetConst(0x802C, 0);
	VMReturn();
}

void Sequence3()
{
	SEPlay(1372);
	MsgSystem(39, 2);
	RTCallGlobal(10382);
	VMReturn();
}

void Sequence4()
{
	WorkSetConst(0x802F, 0);
	WorkSetConst(0x8030, 0);
	SEPlay(1372);
	MsgSystem(35, 2);
	MsgSystemClose();
	StackPush(0x8023);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label77;
	CallRecordSystem(1, 0x8010);
	StackPush(0x8010);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label68;
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);

label68: ;
	goto label69;

label77: ;
	MsgSystem(10, 2);
	MsgSystemClose();

label69: ;
	WorkSetConst(0x8030, 0);
	WorkSetConst(0x802F, 0);
	VMReturn();
}

void Sequence5()
{
	SEPlay(1372);
	MsgSystem(40, 2);
	MsgSystemClose();
	CMD_231(0x8010);
	StackPush(0x8010);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label70;
	WorkSetConst(0x8020, 1);
	WorkSetConst(0x8021, 1);

label70: ;
	VMReturn();
}

void Sequence6()
{
	PokePartyRecoverAll();
	MEPlay(1300);
	MEWait();
	PokecenPCIdle();
	FadeInBlackQ();
	FadeWait();
	MsgSystem(50, 2);
	MsgSystemClose();
	SEPlay(1372);
	VMReturn();
}

void Sequence7()
{
	MsgSystem(51, 2);
	ListMenuInitTR(31, 1, 0, 1, 0x8024);
	ListMenuAdd(53, 0xFFFF, 53);
	ListMenuAdd(54, 0xFFFF, 54);
	ListMenuAdd(55, 0xFFFF, 55);
	ListMenuAdd(56, 0xFFFF, 56);
	ListMenuAdd(57, 0xFFFF, 57);
	ListMenuShow2();
	MsgSystemClose();
	WorkCmpConst(0x8024, 0xFFFE);
	if (1) goto label71;
	WorkCmpConst(0x8024, 57);
	if (1) goto label71;
	WorkCmpConst(0x8024, 53);
	if (1) goto label72;
	WorkCmpConst(0x8024, 54);
	if (1) goto label73;
	WorkCmpConst(0x8024, 55);
	if (1) goto label74;
	WorkCmpConst(0x8024, 56);
	if (1) goto label75;
	goto label71;


// MON_CONDITION_NONE            0
// MON_CONDITION_SLEEP_0         (1 << 0)
// MON_CONDITION_SLEEP_1         (1 << 1)
// MON_CONDITION_SLEEP_2         (1 << 2)
// MON_CONDITION_POISON          (1 << 3)
// MON_CONDITION_BURN            (1 << 4)
// MON_CONDITION_FREEZE          (1 << 5)
// MON_CONDITION_PARALYSIS       (1 << 6)
// MON_CONDITION_TOXIC           (1 << 7)
// MON_CONDITION_TOXIC_COUNTER_0 (1 << 8)
// MON_CONDITION_TOXIC_COUNTER_1 (1 << 9)
// MON_CONDITION_TOXIC_COUNTER_2 (1 << 10)
// MON_CONDITION_TOXIC_COUNTER_3 (1 << 11)

label72: ;
	// Poisoned
	CallPokeSelect(0, 0x8000, 0x8004, 0);
	PokePartySetIV(0x8004, 157, 5);
	SEPlay(1372);
	goto label71;

label73: ;
	// Paralyzed
	CallPokeSelect(0, 0x8000, 0x8004, 0);
	PokePartySetIV(0x8004, 157, 1);
	SEPlay(1372);
	goto label71;

label74: ;
	// Asleep
	CallPokeSelect(0, 0x8000, 0x8004, 0);
	PokePartySetIV(0x8004, 157, 2);
	SEPlay(1372);
	goto label71;

label75: ;
	// Burned
	CallPokeSelect(0, 0x8000, 0x8004, 0);
	PokePartySetIV(0x8004, 157, 4);
	SEPlay(1372);
	goto label71;

label71: ;
	VMReturn();
}

void Sequence8()
{
	FlagGet(3063, 0x8024);
	WorkCmpConst(0x8024, 1);
	if (1) goto label78;
	goto label76;

label78: ;
	MsgSystem(60, 2);
	MsgSystemClose();
	FlagReset(3063);
	VMReturn();

label76: ;
	MsgSystem(49, 2);
	MsgSystemClose();
	FlagSet(3063);
	VMReturn();
}

void Sequence9()
{
	MsgSystem(66, 2);
	MsgSystemClose();
	CallPokeSelect(0, 0x8028, 0x8024, 0);
	StackPush(0x8028);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label79;
	VMReturn();

label79: ;
	PokePartyIsEgg(0x8028, 0x8024);
	StackPush(0x8028);
	StackPushConst(1);
	StackCmp(1);
	if (255) goto label80;
	MsgSystem(64, 2);
	MsgSystemClose();
	VMReturn();

label80: ;
	MoveReminderCheckPkm(0x8028, 0x8024);
	StackPush(0x8028);
	StackPushConst(0);
	StackCmp(1);
	if (255) goto label81;
	MsgSystem(65, 2);
	MsgSystemClose();
	VMReturn();

label81: ;
	WordSetPartyPokeName(0, 0x8024);
	MsgSystem(67, 2);
	MsgSystemClose();
	MoveReminderCallMoveSelect(0x802B, 0x8024);
	WorkCmpConst(0x802B, 0);
	if (1) goto label82;
	WorkSetConst(0x8024, 0);
	RTFinishSubEvents();
	VMReturn();

label82: ;
	RTFinishSubEvents();
	MsgSystem(69, 2);
	MsgSystemClose();
	VMReturn();
}

void Sequence10()
{
	WorkSetConst(0x8027, 50);
	WorkSetConst(0x8028, 499);
	Sequence11();
	WorkSetConst(0x8028, 249);
	Sequence11();
	WorkSetConst(0x8028, 124);
	Sequence11();
	WorkSetConst(0x8028, 62);
	Sequence11();
	WorkSetConst(0x8028, 31);
	Sequence11();
	WorkSetConst(0x8028, 15);
	Sequence11();
	WorkSetConst(0x8028, 7);
	Sequence11();
	WorkSetConst(0x8028, 3);
	Sequence11();
	WorkSetConst(0x8028, 1);
	Sequence11();
	VMReturn();
}

void Sequence11()
{

label84: ;
	ItemAdd(0x8027, 0x8028, 0x8029);
	WorkCmpConst(0x8029, 1);
	if (1) goto label84;
	VMReturn();
}

void Sequence12()
{
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 137);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 138);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 139);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 140);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 141);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 142);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 143);
	if (1) goto label83;
	FieldGetZoneID(0x8027);
	WorkCmpConst(0x8027, 144);
	if (1) goto label83;
	VMReturn();

label83: ;
	MsgSystem(68, 2);
	MsgSystemClose();
	ActorUnlockAll();
	VMHalt();
}

void Sequence13()
{
	//0x8000, 0x8004
	//PokePartyGetParam(0x8000, 0, 8) // Get the first party Pokemon's xp
	//WorkSet(0x8004, 1323)
	//WorkAdd(0x8004, 0x8000) // Add the xp to the value in 0x8004
	//PokePartySetIV(0, 8, 0x8004);
	VMReturn();
	MsgSystem(69, 2);
	VMReturn();
}

void Sequence14() // weather toggle
{
	FlagGet(3062, 0x8024);
	WorkCmpConst(0x8024, 1);
	if (1) goto label91;
	goto label93;

label91: ;
	FlagReset(3062);
	FieldSetWeather(0, 0)
	//MsgSystem(77, 2);
	VMReturn();

label93: ;
	FlagSet(3062);
	FieldSetWeather(2, 2)
	//MsgSystem(77, 2);
	VMReturn();
}

void Sequence15() // weather toggle
{
	FlagGet(3062, 0x8024);
	WorkCmpConst(0x8024, 1);
	if (1) goto label94;
	goto label95;

label94: ;
	FieldSetWeather(0, 0)
	FlagReset(3062);
	//MsgSystem(77, 2);
	VMReturn();

label95: ;
	FlagSet(3062);
	//MsgSystem(77, 2);
	FieldSetWeather(5, 5)
	VMReturn();
}