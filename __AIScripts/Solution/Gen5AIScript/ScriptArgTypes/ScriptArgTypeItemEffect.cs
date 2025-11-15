namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeItemEffect(string name = "item_effect") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "item_ef";

    private static readonly string[] StaticValueNames =
    [
        "None", "Restore HP", "Griseous Orb", "Drive + Adamant Orb", "Lustrous Orb", "Cheri Berry", "Chesto Berry", "Pecha Berry", "Rawst Berry",
        "Aspear Berry", "Leppa Berry", "Persim Berry", "Lum Berry", "Sitrus Berry", "Figy Berry", "Wiki Berry", "Mago Berry", "Aguav Berry", "Iapapa Berry",
        "Occa Berry", "Passho Berry", "Wacan Berry", "Rindo Berry", "Yache Berry", "Chople Berry", "Kebia Berry", "Shuca Berry", "Coba Berry", "Payapa Berry",
        "Tanga Berry", "Charti Berry", "Kasib Berry", "Haban Berry", "Colbur Berry", "Babiri Berry", "Chilan Berry", "Liechi Berry", "Ganlon Berry",
        "Salac Berry", "Petaya Berry", "Apicot Berry", "Lansat Berry", "Starf Berry", "Enigma Berry", "Micle Berry", "Custap Berry", "Jaboca Berry",
        "Rowap Berry", "Increase Evasion", "White Herb", "Macho Brace", "Exp. Share", "Quick Claw", "Soothe Bell", "Mental Herb", "Choice Band",
        "Increase Flinch", "Increase Bug", "Increase Money", "Cleanse Tag", "Pure Incense", "Soul Dew", "DeepSeaTooth", "DeepSeaScale", "Smoke Ball",
        "Everstone", "Focus Band", "Increase Crit", "Increase Steel", "Leftovers", "Dragon Scale", "Light Ball", "Increase Ground", "Increase Rock",
        "Increase Grass", "Increase Dark", "Increase Fighting", "Increase Electric", "Increase Water", "Increase Flying", "Increase Poison", "Increase Ice",
        "Increase Ghost", "Increase Psychic", "Increase Fire", "Increase Dragon", "Increase Normal", "Up-Grade", "Shell Bell", "Lucky Punch", "Metal Powder",
        "Thick Club", "Stick", "Increase Accuracy", "Increase Physical", "Increase Special", "Expert Belt", "Extend Screen", "Life Orb", "Power Herb",
        "Toxic Orb", "Flame Orb", "Quick Powder", "Focus Sash", "Zoom Lens", "Metronome", "Iron Ball", "Move Last", "Destiny Knot", "Black Sludge", "Icy Rock",
        "Smooth Rock", "Heat Rock", "Damp Rock", "Grip Claw", "Choice Scarf", "Sticky Barb", "Power Bracer", "Power Belt", "Power Lens", "Power Band",
        "Power Anklet", "Power Weight", "Shed Shell", "Big Root", "Choice Specs", "Flame Plate", "Splash Plate", "Zap Plate", "Meadow Plate", "Icicle Plate",
        "Fist Plate", "Toxic Plate", "Earth Plate", "Sky Plate", "Mind Plate", "Insect Plate", "Stone Plate", "Spooky Plate", "Draco Plate", "Dread Plate",
        "Iron Plate", "Protector", "Electirizer", "Magmarizer", "Dubious Disc", "Reaper Cloth", "Other"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}