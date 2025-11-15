namespace Gen5AIScript.ScriptArgTypes;


public class ScriptArgTypeConditionFlag(string name = "cond_flag") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "cond_flag";

    private static readonly string[] StaticValueNames =
    [
        "Action Done", "No Switch", "Charge", "Fly", "Dive", "Dig", "Shadow Force", "Defense Curl", "Minimize", "Focus Energy", "Power Trick", "Micle Berry", "No Action",
        "Flash Fire", "Baton Pass", "Null"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}