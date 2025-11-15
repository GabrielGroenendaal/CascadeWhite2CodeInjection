namespace Gen5AIScript.ScriptArgTypes;


public class ScriptArgTypeSideCondition(string name = "side_condition") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "side_cond";

    private static readonly string[] StaticValueNames =
    [
        "Reflect", "Light Screen", "Safeguard", "Mist", "Tailwind", "Lucky Chant", "Spikes", "Toxic Spikes", "Stealth Rock", "Wide Guard", "Quick Guard", "Rainbow", "Sea of Fire",
        "Swamp", "Sticky Web", "Oppressive"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}