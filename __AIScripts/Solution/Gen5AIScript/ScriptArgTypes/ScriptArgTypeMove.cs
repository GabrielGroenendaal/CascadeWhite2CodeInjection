namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMove(string name = "move") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "move";

    private static readonly string[] StaticValueNames =
    [
        "Null", "Concuss", "Karate Chop", "Double Slap", "Comet Punch", "Mega Punch", "Pay Day", "Fire Punch", "Ice Punch", "Thunder Punch", "Scratch", "Dual Wingbeat", "Guillotine",
        "Razor Winds", "Swords Dance", "Cut", "Gust", "Wing Attack", "Whirlwind", "Fly", "Bind", "Brutal Swing", "Vine Whip", "Stomp", "Double Kick", "High Horsepower", "Jump Kick",
        "Headlong Rush", "Sand Attack", "Headbutt", "Devour", "Fire Lash", "Horn Drill", "Tackle", "Body Slam", "Wrap", "Take Down", "Thrash", "Double-Edge",
        "Tail Whip", "Poison Sting", "Twineedle", "Pin Missile", "Leer", "Bite", "Growl", "Roar", "Sing", "Supersonic", "Scorching Swarm", "Disable", "Parabolic Zap", "Ember",
        "Flamethrower", "Mist", "Water Gun", "Hydro Pump", "Surf", "Ice Beam", "Blizzard", "Psybeam", "Bubble Beam", "Aurora Beam", "Hyper Beam", "Peck", "Drill Peck",
        "Submission", "Low Kick", "Counter", "Seismic Toss", "Strength", "Absorb", "Mega Drain", "Leech Seed", "Growth", "Razor Leaf", "Solar Beam", "Poison Powder", "Stun Spore",
        "Sleep Powder", "Petal Dance", "String Shot", "Dragon Rage", "Fire Spin", "Thunder Shock", "Thunderbolt", "Thunder Wave", "Thunder", "Rock Throw", "Earthquake", "Fissure",
        "Dig", "Toxic", "Confusion", "Psychic", "Hypnosis", "Meditate", "Agility", "Quick Attack", "Rage", "Teleport", "Night Shade", "Psychic Noise", "Screech", "Double Team", "Recover",
        "Harden", "Minimize", "Smokescreen", "Confuse Ray", "Breaking Swipe", "Defense Curl", "Barrier", "Light Screen", "Haze", "Reflect", "Focus Energy", "Hidden Force",
        "Metronome", "Mirror Move", "Self-Destruct", "Egg Bomb", "Lick", "Smog", "Sludge", "Bone Club", "Fire Blast", "Waterfall", "Clamp", "Swift", "Skull Bash", "Spike Cannon",
        "Infestation", "Amnesia", "Lunge", "Soft-Boiled", "High Jump Kick", "Glare", "Dream Eater", "Poison Gas", "Barrage", "Leech Life", "Lovely Kiss", "Sky Attack",
        "Phantom Strike", "Chilling Water", "Dizzy Punch", "Spore", "Sparkle", "Psywave", "Play Rough", "Acid Armor", "Crabhammer", "Explosion", "Fury Swipes", "Bonemerang",
        "Rest", "Rock Slide", "Hyper Fang", "Nuzzle", "Flip Turn", "Tri Attack", "Super Fang", "Slash", "Substitute", "Struggle", "Sketch", "Triple Kick", "Thief",
        "Infernal Parade", "Snap Trap", "Nightmare", "Flame Wheel", "Snore", "Curse", "Flail", "Spin Out", "Aeroblast", "Cotton Spore", "Reversal", "Diamond Storm", "Powder Snow",
        "Protect", "Mach Punch", "Scary Face", "Feint Attack", "Draining Kiss", "Belly Drum", "Sludge Bomb", "Mud-Slap", "Octazooka", "Spikes", "Zap Cannon", "Electro Shot",
        "Destiny Bond", "Perish Song", "Icy Wind", "Detect", "Bone Rush", "Parting Shot", "Outrage", "Sandstorm", "Giga Drain", "Endure", "Charm", "Rollout", "Body Press",
        "Swagger", "Milk Drink", "Spark", "Fury Cutter", "Steel Wing", "Mean Look", "Attract", "Sleep Talk", "Heal Bell", "Return", "Present", "Frustration", "Safeguard",
        "Seething Cold", "Mystical Fire", "Sticky Web", "Dynamic Punch", "Megahorn", "Dragon Breath", "Baton Pass", "Encore", "Pursuit", "Rapid Spin", "Sweet Scent", "Iron Tail",
        "Metal Claw", "Vital Throw", "Morning Sun", "Synthesis", "Moonlight", "Hidden Power", "Cross Chop", "Twister", "Rain Dance", "Sunny Day", "Crunch", "Mirror Coat",
        "Bitter Malice", "Extreme Speed", "Ancient Power", "Shadow Ball", "Future Sight", "Rock Smash", "Whirlpool", "Beat Up", "Fake Out", "Uproar", "Stockpile", "Spit Up",
        "Swallow", "Heat Wave", "Hail", "Torment", "Flatter", "Will-O-Wisp", "Obstruct", "Facade", "Focus Punch", "Psychic Fangs", "Follow Me", "Nature Power", "Charge",
        "Taunt", "Helping Hand", "Weather Crash", "Barb Barrage", "Wish", "Assist", "Ingrain", "Superpower", "Magic Coat", "Recycle", "Revenge", "Brick Break", "Yawn", "Knock Off",
        "Endeavor", "Eruption", "Skill Swap", "Imprison", "Refresh", "Grudge", "Victory Dance", "Secret Power", "Dive", "Arm Thrust", "Trop Kick", "Tail Glow", "Dazzling Gleam",
        "Moonblast", "Feather Dance", "Teeter Dance", "Blaze Kick", "Esper Wing", "Boomburst", "Needle Arm", "Slack Off", "Hyper Voice", "Poison Fang", "Crush Claw", "Blast Burn",
        "Hydro Cannon", "Meteor Mash", "Astonish", "Weather Ball", "Aromatherapy", "Fake Tears", "Air Cutter", "Overheat", "Eerie Impulse", "Rock Tomb", "Silver Wind",
        "Metal Sound", "Grass Whistle", "Tickle", "Cosmic Power", "Water Spout", "Signal Beam", "Shadow Punch", "Extrasensory", "Sky Uppercut", "Sand Tomb", "Sheer Cold",
        "Muddy Water", "Bullet Seed", "Aerial Ace", "Icicle Spear", "Iron Defense", "Block", "Howl", "Dragon Claw", "Frenzy Plant", "Bulk Up", "Bounce", "Mud Shot",
        "Poison Tail", "Covet", "Volt Tackle", "Magical Leaf", "Wicked Blow", "Calm Mind", "Leaf Blade", "Dragon Dance", "Rock Blast", "Shock Wave", "Water Pulse", "Doom Desire",
        "Psycho Boost", "Roost", "Gravity", "Freeze-Dry", "Wake-Up Slap", "Hammer Arm", "Gyro Ball", "Healing Wish", "Brine", "Natural Gift", "Confide", "Pluck", "Tailwind",
        "Acupressure", "Metal Burst", "U-turn", "Close Combat", "Payback", "Assurance", "First Impression", "Fling", "Psycho Shift", "Spiky Shield", "Alluring Voice", "Scale Shot",
        "Petal Blizzard", "Gastro Acid", "Lucky Chant", "Me First", "Copycat", "Psyblade", "Clanging Scales", "Wave Crash", "Last Resort", "Worry Seed", "Sucker Punch",
        "Toxic Spikes", "Heart Swap", "Aqua Ring", "Magnet Rise", "Flare Blitz", "Force Palm", "Aura Sphere", "Rock Polish", "Poison Jab", "Dark Pulse", "Night Slash", "Aqua Tail",
        "Seed Bomb", "Air Slash", "X-Scissor", "Bug Buzz", "Dragon Pulse", "Dragon Rush", "Power Gem", "Drain Punch", "Vacuum Wave", "Focus Blast", "Energy Ball", "Brave Bird",
        "Earth Power", "Switcheroo", "Giga Impact", "Nasty Plot", "Bullet Punch", "Avalanche", "Ice Shard", "Shadow Claw", "Thunder Fang", "Ice Fang", "Fire Fang", "Shadow Sneak",
        "Mud Bomb", "Psycho Cut", "Zen Headbutt", "Mirror Shot", "Flash Cannon", "Rock Climb", "Defog", "Trick Room", "Draco Meteor", "Discharge", "Lava Plume", "Leaf Storm",
        "Power Whip", "Rock Wrecker", "Cross Poison", "Gunk Shot", "Iron Head", "Magnet Bomb", "Stone Edge", "Captivate", "Stealth Rock", "Grass Knot", "Chatter", "Spirit Break",
        "Bug Bite", "Charge Beam", "Wood Hammer", "Aqua Jet", "Attack Order", "Defend Order", "Heal Order", "Head Smash", "Double Hit", "Starburst", "Steel Beam", "Pollen Puff",
        "Silk Trap", "Magma Storm", "Dark Void", "Seed Flare", "Ominous Wind", "Shadow Force", "Hone Claws", "Wide Guard", "Triple Axel", "Triple Dive", "Liquidation", "Psyshock",
        "Venoshock", "Autotomize", "Rage Powder", "Telekinesis", "Power Trip", "Accelerock", "Storm Throw", "Flame Burst", "Sludge Wave", "Quiver Dance", "Heavy Slam",
        "Scorching Sands", "Electro Ball", "Soak", "Flame Charge", "Coil", "Low Sweep", "Acid Spray", "Foul Play", "Stompin Tantrum", "Entrainment", "Ice Hammer", "Disarming Voice",
        "Echoed Voice", "Chip Away", "Clear Smog", "Stored Power", "Quick Guard", "Ally Switch", "Scald", "Shell Smash", "Heal Pulse", "Hex", "Sky Drop", "Shift Gear",
        "Circle Throw", "Incinerate", "Fairy Wind", "Acrobatics", "Reflect Type", "Retaliate", "Final Gambit", "Bestow", "Inferno", "Water Pledge", "Fire Pledge", "Grass Pledge",
        "Volt Switch", "Struggle Bug", "Bulldoze", "Frost Breath", "Dragon Tail", "Work Up", "Electroweb", "Wild Charge", "Drill Run", "Dual Chop", "Heart Stamp", "Horn Leech",
        "Sacred Sword", "Razor Shell", "Heat Crash", "Leaf Tornado", "Steamroller", "Cotton Guard", "Night Daze", "Psystrike", "Tail Slap", "Hurricane", "Head Charge",
        "Gear Grind", "Searing Shot", "Techno Blast", "Relic Song", "Secret Sword", "Glaciate", "Zing Zap", "Blue Flare", "Fiery Dance", "Solar Blade", "Meteor Beam", "Snarl",
        "Icicle Crash", "V-create", "Skitter Smack", "Baneful Bunker"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}