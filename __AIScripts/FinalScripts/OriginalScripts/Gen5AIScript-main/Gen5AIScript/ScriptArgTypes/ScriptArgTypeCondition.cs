using System.Collections;

namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCondition(string name = "condition") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "cond";

    private static readonly string[] StaticValueNames =
    [
        "None", "Paralysis", "Sleep", "Freeze", "Burn", "Poison", "Confusion", "Infatuation", "Bind", "Nightmare", "Curse", "Taunt", "Torment",
        "Disable", "Yawn", "Heal Block", "Gastro Acid", "Foresight", "Leech Seed", "Embargo", "Perish Song", "Ingrain", "Block", "Encore",
        "Roost", "Move Lock", "Charge Lock", "Choice Lock", "Must Hit", "Lock-On", "Floating", "Knocked Down", "Telekinesis", "Sky Drop",
        "Accuracy Up", "Aqua Ring"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}