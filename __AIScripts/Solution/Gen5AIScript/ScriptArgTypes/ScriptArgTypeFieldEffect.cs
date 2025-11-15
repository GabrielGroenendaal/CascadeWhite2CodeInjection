namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeFieldEffect(string name = "field_effect") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "field_ef";

    private static readonly string[] StaticValueNames =
    [
        "Unknown 0x00", "Trick Room", "Gravity", "Imprison", "Water Sport", "Mud Sport", "Wonder Room", "Magic Room"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}