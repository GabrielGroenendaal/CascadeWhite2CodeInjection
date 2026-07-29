namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeWeather(string name = "weather") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "weather";

    private static readonly string[] StaticValueNames =
    [
        "None", "Sun", "Rain", "Hail", "Sand"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}