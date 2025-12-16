namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeAbility(string name = "ability") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "ability";

    private static readonly string[] StaticValueNames =
    [
        "Null", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Bulletproof", "Corrosion", "Sand Veil", "Static", // 00
        "Volt Absorb", "Water Absorb", "Galvanize", "Cloud Nine", "Keen Senses", "Thunder Armor", "Ballistics", "Fluffy", "Flash Fire", "Resilient", // 10
        "Quick Draw", "Well Baked Body", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Strong Body", // 20
        "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Berserk", "Inner Focus", // 30
        "Pixilate", "Merciless", "Magnet Pull", "Amplifier", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Refrigerate", "Flame Body", // 40
        "Run Away", "Wind Rider", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Gooey", "Plus", "Minus", "Forecast", // 50
        "Aerilate", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Determined", // 60
        "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Neutraliziing Gas", "Slush Rush", "Motor Drive", "Rivalry", // 70
        "Colossal", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Exploit", "Iron Fist", // 80
        "Poison Heal", "Adaptability", "Skill Link", "Strong Jaw", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", // 90
        "Tough Claws", "Technician", "Fur Coat", "Distracting", "Mold Breaker", "Moisturize", "Aftermath", "Anticipation", "Forewarn", "Unaware", // 100
        "Tenacity", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", // 110
        "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", // 120
        "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Majestic Ward", "Toxic Boost", "Flare Boost", "Gourmand", // 130
        "Permafrost", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Savant", "Sand Rush", "Wonder Skin", "Patient", "Illusion", // 140
        "Imposter", "Infiltrator", "Contagious", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", // 150
        "Iron Barbs", "Zen Mode", "Illumination", "Turboblaze", "Teravolt" // 160

    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}