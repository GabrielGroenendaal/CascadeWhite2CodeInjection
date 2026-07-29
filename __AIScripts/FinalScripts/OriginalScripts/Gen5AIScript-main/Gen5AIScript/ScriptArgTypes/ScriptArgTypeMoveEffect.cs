namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMoveEffect(string name = "move_effect") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "move_ef";

    private static readonly string[] StaticValueNames =
    [
        "dmg", "target_slp", "dmg_target_psn", "dmg_target_absorb", "dmg_target_brn", "dmg_target_frz", "dmg_target_par", "explosion", "dream_eater",
        "mirror_move", "user_atk+1", "user_def+1", "user_spe+1", "user_spa+1", "user_spd+1", "user_acc+1", "user_eva+1", "no_miss", "target_atk-1",
        "target_def-1", "target_spe-1", "target_spa-1", "target_spd-1", "target_acc-1", "target_eva-1", "haze", "bide", "thrash", "force_switch",
        "multi-strike_2-5", "conversion", "dmg_flinch", "heal_50", "target_tox", "dmg_money", "light_screen", "tri_attack", "rest", "ohko", "razor_wind",
        "direct_half", "direct_40", "dmg_trap", "increased_crit", "multi-strike_2", "jump_kick", "mist", "focus_energy", "dmg_recoil_25", "target_confusion",
        "user_atk+2", "user_def+2", "user_spe+2", "user_spa+2", "user_spd+2", "user_acc+2", "user_eva+2", "transform", "target_atk-2", "target_def-2",
        "target_spe-2", "target_spa-2", "target_spd-2", "target_acc-2", "target_eva-2", "reflect", "target_psn", "target_par", "dmg_target_atk-1",
        "dmg_target_def-1", "dmg_target_spe-1", "dmg_target_spa-1", "dmg_target_spd-1", "dmg_target_acc-1", "dmg_target_eva-1", "sky_attack",
        "dmg_target_confuse", "twineedle", "vital_throw", "substitute", "recharge", "rage", "mimic", "metronome", "leech_seed", "splash", "disable",
        "direct_level", "psywave", "counter", "encore", "pain_split", "snore", "conversion_2", "mind_reader", "sketch", "unknown_0x0060", "sleep_talk",
        "destiny_bond", "flail", "spite", "false_swipe", "team_heal", "increased_priority", "triple_kick", "theif", "spider_web", "nightmare", "minimize",
        "curse", "unknown_0x006e", "protect", "spikes", "foresight", "perish_song", "sandstorm", "endure", "rollout", "swagger", "fury_cutter", "attract",
        "return", "present", "frustration", "safeguard", "flame_wheel",

#if CASCADE
        "sticky_web",
#else
        "magnitude",
#endif

        "baton_pass", "pursuit", "rapid_spin", "direct_30", "unknown_0x0083", "morning_sun", "unknown0x0085", "unknown0x0086", "hidden_power", "rain_dance", "sunny_day",
        "dmg_user_def+1", "dmg_user_atk+1", "ancient_power", "unknown_0x008d", "belly_drum", "psych_up", "mirror_coat", "skull_bash", "twister", "earthquake", "future_sight",
        "gust", "stomp", "solar_beam", "thunder", "teleport", "beat_up", "fly", "defense_curl", "unknown_0x009d", "fake_out", "uproar", "stockpile", "spit_up", "swallow",
        "unknown_0x00a3", "hail", "torment", "flatter", "will-o-wisp", "memento", "facade", "focus_punch", "smelling_salts", "follow_me", "nature_power", "charge_electric",
        "taunt", "helping_hand", "trick", "roleplay", "wish", "assist", "ingrain", "dmg_user_atk_def-1", "magic_coat", "recycle", "revenge", "brick_break", "yawn", "knock_off",
        "endeavor", "dmg_user_hp_pct", "skill_swap", "imprison", "refresh", "grudge", "snatch", "low_kick", "secret_power", "dmg_recoil_33", "teeter_dance",
        "dmg_target_brn_highcrit", "mud_sport", "dmg_target_tox", "weather_ball", "dmg_user_spa-2", "target_atk_def-1", "user_def_spd+1", "sky_uppercut", "user_atk_def+1",
        "dmg_target_psn_highcrit", "water_sport", "user_spa_spd+1", "user_atk_spe+1", "camouflage", "roost", "gravity", "miracle_eye", "wake-up_slap", "dmg_user_spe-1",
        "gyro_ball", "healing_wish", "brine", "natural_gift", "feint", "pluck", "tailwind", "acupressure", "metal_burst", "dmg_user_switch", "dmg_user_def_spd-1", "payback",
        "assurance", "embargo", "fling", "psycho_shift", "trump_card", "heal_block", "dmg_target_hp_pct", "power_trick", "gastro_acid", "lucky_chant", "me_first", "copycat",
        "power_swap", "guard_swap", "punishment", "last_resort", "worry_seed", "sucker_punch", "toxic_spikes", "heart_swap", "aqua_ring", "magnet_rise", "flare_blitz", "struggle",
        "dive", "dig", "surf", "defog", "trick_room", "blizzard", "whirlpool", "volt_tackle", "bounce", "unknown_0x0108", "captivate", "stealth_rock", "chatter", "judgment",
        "dmg_recoil_50", "lunar_dance", "dmg_target_spd-2", "shadow_force", "dmg_target_brn_flinch", "dmg_target_frz_flinch", "dmg_target_par_flinch", "dmg_user_spa+1",
        "user_atk_acc+1", "wide_guard", "guard_split", "power_split", "wonder_room", "dmg_physical", "venoshock", "autotomize", "telekinesis", "magic_room", "smack_down",
        "dmg_alwayscrit", "flame_burst", "user_spa_spd_spe+2", "heavy_slam", "synchronoise", "electro_ball", "soak", "dmg_user_spe+1", "acid_spray", "foul_play", "simple_beam",
        "entrainment", "after_you", "round", "echoed_voice", "chip_away", "clear_smog", "stored_power", "quick_guard", "ally_switch", "shell_smash", "heal_pulse", "hex",
        "sky_drop", "user_spe+2_atk+1", "dmg_force_switch", "incinerate", "quash", "growth", "acrobatics", "reflect_type", "retaliate", "final_gambit", "user_spa+3",
        "user_atk_def_acc+1", "bestow", "water_pledge", "fire_pledge", "grass_pledge", "work_up", "cotton_guard", "relic_song", "glaciate", "freeze_shock", "ice_burn",
        "unknown_0x014d", "v-create", "fusion_flare", "fusion_bolt", "hurricane"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}