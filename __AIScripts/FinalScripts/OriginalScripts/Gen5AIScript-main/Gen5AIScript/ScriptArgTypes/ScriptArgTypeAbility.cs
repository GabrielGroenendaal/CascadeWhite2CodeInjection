namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeAbility(string name = "ability") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "ability";

    private static readonly string[] StaticValueNames =
    [
#if PARAGONLITE
        "Null", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Damp", "Limber", "Sand Veil", "Static", // 00
        "Volt Absorb", "Water Absorb", "Oblivious", "Cloud Nine", "Compound Eyes", "Insomnia", "Color Change", "Immunity", "Flash Fire", "Shield Dust", // 10
        "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", // 20
        "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", // 30
        "Magma Armor", "Water Veil", "Magnet Pull", "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body", // 40
        "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus", "Minus", "Forecast", // 50
        "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", // 60
        "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", // 70
        "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Download", "Iron Fist", // 80
        "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", // 90
        "Stall", "Technician", "Leaf Guard", "Klutz", "Mold Breaker", "Super Luck", "Aftermath", "Anticipation", "Forewarn", "Unaware", // 100
        "Tinted Lens", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "X-ray Vision", // 110
        "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", // 120
        "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Multiscale", "Toxic Boost", "Flare Boost", "Harvest", // 130
        "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Analytic", "Illusion", // 140
        "Imposter", "Infiltrator", "Mummy", "Moxie", "Justified", "Rattled", "Magic Bounce", "Herbivore", "Prankster", "Sand Force", // 150
        "Iron Barbs", "Zen Mode", "Victory Star", "Turboblaze", "Teravolt", "Aroma Veil", "Flower Veil", "Cheek Pouch", "Protean", "Fur Coat", // 160
        "Magician", "Bulletproof", "Competitive", "Strong Jaw", "Refrigerate", "Sweet Veil", "Stance Change", "Gale Wings", "Mega Launcher", "Grass Pelt", // 170
        "Symbiosis", "Tough Claws", "Pixilate", "Gooey", "Aerilate", "Parental Bond", "Dark Aura", "Fairy Aura", "Aura Break", "Primordial Sea", // 180
        "Desolate Land", "Delta Stream", "Stamina", "Wimp Out", "Emergency Exit", "Water Compaction", "Merciless", "Shields Down", "Stakeout", "Water Bubble", // 190
        "Steelworker", "Berserk", "Slush Rush", "Long Reach", "Liquid Voice", "Triage", "Galvanize", "Surge Surfer", "Schooling", "Disguise", // 200
        "Battle Bond", "Power Construct", "Corrosion", "Comatose", "Queenly Magesty", "Innards Out", "Dancer", "Battery", "Fluffy", "Dazzling", // 210
        "Soul-Heart", "Tangling Hair", "Receiver", "Power of Alchemy", "Beast Boost", "RKS System", "Electric Surge", "Psychic Surge", "Misty Surge", "Grassy Surge", // 220
        "Full Metal Body", "Shadow Shield", "Prism Armor", "Neuroforce", "Intrepid Sword", "Dauntless Shield", "Libero", "Ball Fetch", "Cotton Down", "Propeller Tail", // 230
        "Mirror Armor", "Gulp Missile", "Stalwart", "Steam Engine", "Punk Rock", "Sand Spit", "Ice Scales", "Ripen", "Ice Face", "Power Spot", // 240,
        "Mimicry", "Screen Cleaner", "Steely Spirit", "Perish Body", "Wandering Spirit", "Gorilla Tactics", "Neutralizing Gas", "Pastel Veil", "Hunger Switch", "Quick Draw", // 250
        "Unseen Fist", "Curious Medicine", "Transistor", "Dragon's Maw", "Chilling Neigh", "Grim Neigh", "As One Chilling Neigh", "As One Grim Neigh", "Lingering Aroma", // 260
        "Seed Sower", // 269
        "Thermal Exchange", "Anger Shell", "Purifying Salt", "Well-Baked Body", "Wind Rider", "Guard Dog", "Rocky Payload", "Wind Power", "Zero to Hero", "Commander", // 270
        "Electromorphosis", "Protosythesis", "Quark Drive", "Good as Gold", "Vessel of Ruin", "Sword of Ruin", "Tablets of Ruin", "Beads of Ruin", "Orichalcum Pulse", // 280
        "Hadron Engine", // 289
        "Opportunist", "Cud Chew", "Sharpness", "Supreme Overlord", "Costar", "Toxic Debris", "Armor Tail", "Earth Eater", "Mycelium Might", "Hospitality", // 290
        "Mind's Eye", "Embody Aspect Teal", "Embody Aspect Hearthflame", "Embody Aspect Wellspring", "Embody Aspect Cornerstone", "Toxic Chain", "Supersweet Syrup", // 300
        "Tera Shift", "Tera Shell", "Teraform Zero", "Poison Puppeteer", // 307
        "Ability 311", "Ability 312", "Ability 313", "Ability 314", "Ability 315", "Ability 316", "Ability 317", "Ability 318", "Ability 319", // 311
        "Ability 320", "Ability 321", "Ability 322", "Ability 323", "Ability 324", "Ability 325", "Ability 326", "Ability 327", "Ability 328", "Ability 329", // 320
        "Ability 330", "Ability 331", "Ability 332", "Ability 333", "Ability 334", "Ability 335", "Ability 336", "Ability 337", "Ability 338", "Ability 339", // 330
        "Ability 340", "Ability 341", "Ability 342", "Ability 343", "Ability 344", "Ability 345", "Ability 346", "Ability 347", "Ability 348", "Ability 349", // 340
        "Ability 350", "Ability 351", "Ability 352", "Ability 353", "Ability 354", "Ability 355", "Ability 356", "Ability 357", "Ability 358", "Ability 359", // 350
        "Ability 360", "Ability 361", "Ability 362", "Ability 363", "Ability 364", "Ability 365", "Ability 366", "Ability 367", "Ability 368", "Ability 369", // 360
        "Ability 370", "Ability 371", "Ability 372", "Ability 373", "Ability 374", "Ability 375", "Ability 376", "Ability 377", "Ability 378", "Ability 379", // 370
        "Ability 380", "Ability 381", "Ability 382", "Ability 383", "Ability 384", "Ability 385", "Ability 386", "Ability 387", "Ability 388", "Ability 389", // 380
        "Ability 390", "Ability 391", "Ability 392", "Ability 393", "Ability 394", "Ability 395", "Ability 396", "Ability 397", "Ability 398", "Ability 399", // 390
        "Ability 400", "Ability 401", "Ability 402", "Ability 403", "Ability 404", "Ability 405", "Ability 406", "Ability 407", "Ability 408", "Ability 409", // 400
        "Ability 410", "Ability 411", "Ability 412", "Ability 413", "Ability 414", "Ability 415", "Ability 416", "Ability 417", "Ability 418", "Ability 419", // 410
        "Ability 420", "Ability 421", "Ability 422", "Ability 423", "Ability 424", "Ability 425", "Ability 426", "Ability 427", "Ability 428", "Ability 429", // 420
        "Ability 430", "Ability 431", "Ability 432", "Ability 433", "Ability 434", "Ability 435", "Ability 436", "Ability 437", "Ability 438", "Ability 439", // 430
        "Ability 440", "Ability 441", "Ability 442", "Ability 443", "Ability 444", "Ability 445", "Ability 446", "Ability 447", "Ability 448", "Ability 449", // 440
        "Ability 450", "Ability 451", "Ability 452", "Ability 453", "Ability 454", "Ability 455", "Ability 456", "Ability 457", "Ability 458", "Ability 459", // 450
        "Ability 460", "Ability 461", "Ability 462", "Ability 463", "Ability 464", "Ability 465", "Ability 466", "Ability 467", "Ability 468", "Ability 469", // 460
        "Ability 470", "Ability 471", "Ability 472", "Ability 473", "Ability 474", "Ability 475", "Ability 476", "Ability 477", "Ability 478", "Ability 479", // 470
        "Ability 480", "Ability 481", "Ability 482", "Ability 483", "Ability 484", "Ability 485", "Ability 486", "Ability 487", "Ability 488", "Ability 489", // 480
        "Ability 490", "Ability 491", "Ability 492", "Ability 493", "Ability 494", "Ability 495", "Ability 496", "Ability 497", "Ability 498", "Ability 499", // 490

        "Heavy Wing", "Specialized", "Insectivore", "Prestige", "Lucky Foot", "Assimilate", "Stone Home", "Cacophony", "Rip Tide", "Wind Whipper", // 500
        "Glazeware", "Sun-Soaked", "Colossal", "Final Thread", "Homegrown", "Ravenous Torque", "Superconductor", "Somatic Reflex", "Incendiate", "Liquidate", // 510
        "Florilate", "Contaminate", "Volcanic Fury", "Pastoral Aroma", "Heal Spore", "Warp Drive" // 520

#elif REDUX
        "Null", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Damp", "Limber", "Sand Veil", "Static", // 00
        "Volt Absorb", "Water Absorb", "Oblivious", "Cloud Nine", "Compound Eyes", "Insomnia", "Color Change", "Immunity", "Flash Fire", "Shield Dust", // 10
        "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", // 20
        "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", // 30
        "Magma Armor", "Water Veil", "Magnet Pull", "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body", // 40
        "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus", "Minus", "Forecast", // 50
        "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", // 60
        "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", // 70
        "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Download", "Iron Fist", // 80
        "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", // 90
        "Stall", "Technician", "Leaf Guard", "Klutz", "Mold Breaker", "Super Luck", "Aftermath", "Anticipation", "Forewarn", "Unaware", // 100
        "Tinted Lens", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", // 110
        "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", // 120
        "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Multiscale", "Toxic Boost", "Flare Boost", "Harvest", // 130
        "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Analytic", "Illusion", // 140
        "Imposter", "Infiltrator", "Mummy", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", // 150
        "Iron Barbs", "Zen Mode", "Victory Star", "Turboblaze", "Teravolt", "Aroma Veil", "Flower Veil", "Cheek Pouch", "Protean", "Fur Coat", // 160
        "Magician", "Bulletproof", "Competitive", "Strong Jaw", "Refrigerate", "Sweet Veil", "Stance Change", "Gale Wings", "Mega Launcher", "Grass Pelt", // 170
        "Symbiosis", "Tough Claws", "Pixilate", "Gooey", "Aerilate", "Parental Bond", "Dark Aura", "Fairy Aura", "Aura Break", "Primordial Sea", // 180
        "Desolate Land", "Delta Stream", "Stamina", "Wimp Out", "Emergency Exit", "Water Compaction", "Merciless", "Shields Down", "Stakeout", "Water Bubble", // 190
        "Steelworker", "Berserk", "Slush Rush", "Long Reach", "Liquid Voice", "Triage", "Galvanize", "Surge Surfer", "Schooling", "Disguise", // 200
        "Battle Bond", "Power Construct", "Corrosion", "Comatose", "Queenly Magesty", "Innards Out", "Dancer", "Battery", "Fluffy", "Dazzling", // 210
        "Soul-Heart", "Tangling Hair", "Receiver", "Power of Alchemy", "Beast Boost", "RKS System", "Electric Surge", "Psychic Surge", "Misty Surge", "Grassy Surge", // 220
        "Full Metal Body", "Shadow Shield", "Prism Armor", "Neuroforce", "Intrepid Sword", "Dauntless Shield", "Libero", "Ball Fetch", "Cotton Down", "Propeller Tail", // 230
        "Mirror Armor", "Gulp Missile", "Stalwart", "Steam Engine", "Punk Rock", "Sand Spit", "Ice Scales", "Ripen", "Ice Face", "Power Spot", // 240,
        "Mimicry", "Screen Cleaner", "Steely Spirit", "Perish Body", "Wandering Spirit", "Gorilla Tactics", "Neutralizing Gas", "Pastel Veil", "Hunger Switch", "Quick Draw", // 250
        "Unseen Fist", "Curious Medicine", "Transistor", "Dragon's Maw", "Chilling Neigh", "Grim Neigh", "As One Chilling Neigh", "As One Grim Neigh", "Lingering Aroma", // 260
        "Seed Sower", // 269
        "Thermal Exchange", "Anger Shell", "Purifying Salt", "Well-Baked Body", "Wind Rider", "Guard Dog", "Rocky Payload", "Wind Power", "Zero to Hero", "Commander", // 270
        "Electromorphosis", "Protosythesis", "Quark Drive", "Good as Gold", "Vessel of Ruin", "Sword of Ruin", "Tablets of Ruin", "Beads of Ruin", "Orichalcum Pulse", // 280
        "Hadron Engine", // 289
        "Opportunist", "Cud Chew", "Sharpness", "Supreme Overlord", "Costar", "Toxic Debris", "Armor Tail", "Earth Eater", "Mycelium Might", "Hospitality", // 290
        "Mind's Eye", "Embody Aspect Teal", "Embody Aspect Hearthflame", "Embody Aspect Wellspring", "Embody Aspect Cornerstone", "Toxic Chain", "Supersweet Syrup", // 300
        "Tera Shift", "Tera Shell", "Teraform Zero", "Poison Puppeteer", // 307
        "Ability 311", "Ability 312", "Ability 313", "Ability 314", "Ability 315", "Ability 316", "Ability 317", "Ability 318", "Ability 319", // 311
        "Ability 320", "Ability 321", "Ability 322", "Ability 323", "Ability 324", "Ability 325", "Ability 326", "Ability 327", "Ability 328", "Ability 329", // 320
        "Ability 330", "Ability 331", "Ability 332", "Ability 333", "Ability 334", "Ability 335", "Ability 336", "Ability 337", "Ability 338", "Ability 339", // 330
        "Ability 340", "Ability 341", "Ability 342", "Ability 343", "Ability 344", "Ability 345", "Ability 346", "Ability 347", "Ability 348", "Ability 349", // 340
        "Ability 350", "Ability 351", "Ability 352", "Ability 353", "Ability 354", "Ability 355", "Ability 356", "Ability 357", "Ability 358", "Ability 359", // 350
        "Ability 360", "Ability 361", "Ability 362", "Ability 363", "Ability 364", "Ability 365", "Ability 366", "Ability 367", "Ability 368", "Ability 369", // 360
        "Ability 370", "Ability 371", "Ability 372", "Ability 373", "Ability 374", "Ability 375", "Ability 376", "Ability 377", "Ability 378", "Ability 379", // 370
        "Ability 380", "Ability 381", "Ability 382", "Ability 383", "Ability 384", "Ability 385", "Ability 386", "Ability 387", "Ability 388", "Ability 389", // 380
        "Ability 390", "Ability 391", "Ability 392", "Ability 393", "Ability 394", "Ability 395", "Ability 396", "Ability 397", "Ability 398", "Ability 399", // 390
        "Ability 400", "Ability 401", "Ability 402", "Ability 403", "Ability 404", "Ability 405", "Ability 406", "Ability 407", "Ability 408", "Ability 409", // 400
        "Ability 410", "Ability 411", "Ability 412", "Ability 413", "Ability 414", "Ability 415", "Ability 416", "Ability 417", "Ability 418", "Ability 419", // 410
        "Ability 420", "Ability 421", "Ability 422", "Ability 423", "Ability 424", "Ability 425", "Ability 426", "Ability 427", "Ability 428", "Ability 429", // 420
        "Ability 430", "Ability 431", "Ability 432", "Ability 433", "Ability 434", "Ability 435", "Ability 436", "Ability 437", "Ability 438", "Ability 439", // 430
        "Ability 440", "Ability 441", "Ability 442", "Ability 443", "Ability 444", "Ability 445", "Ability 446", "Ability 447", "Ability 448", "Ability 449", // 440
        "Ability 450", "Ability 451", "Ability 452", "Ability 453", "Ability 454", "Ability 455", "Ability 456", "Ability 457", "Ability 458", "Ability 459", // 450
        "Ability 460", "Ability 461", "Ability 462", "Ability 463", "Ability 464", "Ability 465", "Ability 466", "Ability 467", "Ability 468", "Ability 469", // 460
        "Ability 470", "Ability 471", "Ability 472", "Ability 473", "Ability 474", "Ability 475", "Ability 476", "Ability 477", "Ability 478", "Ability 479", // 470
        "Ability 480", "Ability 481", "Ability 482", "Ability 483", "Ability 484", "Ability 485", "Ability 486", "Ability 487", "Ability 488", "Ability 489", // 480
        "Ability 490", "Ability 491", "Ability 492", "Ability 493", "Ability 494", "Ability 495", "Ability 496", "Ability 497", "Ability 498", "Ability 499", // 490

        "Heavy Wing", "Specialized", "Insectivore", "Prestige", "Steel Toecap", "Assimilate", "Stone Home", "Cacophony", "Rip Tide", "Wind Whipper", // 500
        "Glazeware", "Sun-Soaked", "Colossal", "Final Thread", "Homegrown", "Ravenous Torque", "Coolant Boost", "Somatic Reflex", "Incendiate", "Liquidate", // 510
        "Florilate", "Contaminate", "Volcanic Fury", "Pastoral Aroma", "Heal Spore", "Warp Drive" // 520
#elif CASCADE
        "Null", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Bulletproof", "Corrosion", "Sand Veil", "Static", // 00
        "Volt Absorb", "Water Absorb", "Galvanize", "Cloud Nine", "Keen Senses", "Thunder Armor", "Color Change", "Fluffy", "Flash Fire", "Resilient", // 10
        "Own Tempo", "Well-Baked Body", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Strong Body", // 20
        "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", // 30
        "Magma Armor", "Water Veil", "Magnet Pull", "Amplifier", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Refrigerate", "Flame Body", // 40
        "Permafrost", "Wind Rider", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Gooey", "Plus", "Minus", "Forecast", // 50
        "Aerilate", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Determined", // 60
        "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", // 70
        "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Exploit", "Iron Fist", // 80
        "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", // 90
        "Stall", "Technician", "Leaf Guard", "Distracting", "Mold Breaker", "Super Luck", "Aftermath", "Pixilate", "Forewarn", "Unaware", // 100
        "Tenacity", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", // 110
        "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", // 120
        "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Slush Rush", "Tough Claws", "Majestic Ward", "Toxic Boost", "Flare Boost", "Gourmand", // 130
        "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Patient", "Illusion", // 140
        "Imposter", "Infiltrator", "Contagious", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", // 150
        "Iron Barbs", "Zen Mode", "Illumination", "Turboblaze", "Teravolt" // 160
#else
        "Null", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Damp", "Limber", "Sand Veil", "Static", // 00
        "Volt Absorb", "Water Absorb", "Oblivious", "Cloud Nine", "Compound Eyes", "Insomnia", "Color Change", "Immunity", "Flash Fire", "Shield Dust", // 10
        "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", // 20
        "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", // 30
        "Magma Armor", "Water Veil", "Magnet Pull", "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body", // 40
        "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus", "Minus", "Forecast", // 50
        "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", // 60
        "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", // 70
        "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Download", "Iron Fist", // 80
        "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", // 90
        "Stall", "Technician", "Leaf Guard", "Klutz", "Mold Breaker", "Super Luck", "Aftermath", "Anticipation", "Forewarn", "Unaware", // 100
        "Tinted Lens", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", // 110
        "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", // 120
        "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Multiscale", "Toxic Boost", "Flare Boost", "Harvest", // 130
        "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Analytic", "Illusion", // 140
        "Imposter", "Infiltrator", "Mummy", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", // 150
        "Iron Barbs", "Zen Mode", "Victory Star", "Turboblaze", "Teravolt" // 160
#endif
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}