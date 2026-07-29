namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeAnimVar(string name = "var") : ScriptArgTypeStringBase(name)
{
    protected override string Prefix => "var";

    private static readonly string[] StaticValueNames =
    [
        "player_poke_weight", // 0
        "enemy_poke_weight",
        "player_poke_1_weight",
        "enemy_poke_1_weight",
        "player_poke_2_weight",
        "enemy_poke_2_weight",
        "player_poke_3_weight",
        "enemy_poke_3_weight",
        "attacking_poke_weight",
        "move_range",
        "turn_count", // 10
        "consecutive_use_count",
        "ball_count",
        "is_capture_success",
        "is_critical",
        "item",
        "general_use",
        "attacking_poke_pos",
        "attacking_poke_is_hidden",
        "attacking_poke_direction",
        "is_player_poke_shiny", // 20
        "is_enemy_poke_shiny",
        "is_player_poke_1_shiny",
        "is_enemy_poke_1_shiny",
        "is_player_poke_2_shiny",
        "is_enemy_poke_2_shiny",
        "is_player_poke_3_shiny",
        "is_enemy_poke_3_shiny",
        "is_attacking_poke_shiny",
        "can_player_poke_fall",
        "can_enemy_poke_fall", // 30
        "can_player_poke_1_fall",
        "can_enemy_poke_1_fall",
        "can_player_poke_2_fall",
        "can_enemy_poke_2_fall",
        "can_player_poke_3_fall",
        "can_enemy_poke_3_fall",
        "can_attacking_poke_fall",
        "is_multi",
        "battle_style",
        "player_trainer_class", // 40
        "enemy_1_trainer_class",
        "ally_trainer_class",
        "enemy_2_trainer_class",
        "is_player_poke_floating",
        "is_enemy_poke_floating",
        "is_player_poke_1_floating",
        "is_enemy_poke_1_floating",
        "is_player_poke_2_floating",
        "is_enemy_poke_2_floating",
        "is_player_poke_3_floating", // 50
        "is_enemy_poke_3_floating",
        "is_zoomed_out",
        "push_camera",
        "camera",
        "wcs_camera",
        "suppress_camera",
        "defending_poke_pos",
        "is_player_poke_n_poke",
        "is_enemy_poke_n_poke",
        "is_player_poke_1_n_poke", // 60
        "is_enemy_poke_1_n_poke",
        "is_player_poke_2_n_poke",
        "is_enemy_poke_2_n_poke",
        "is_player_poke_3_n_poke",
        "is_enemy_poke_3_n_poke",
        "is_attacking_poke_n_poke",
        "is_player_poke_star",
        "is_enemy_poke_star",
        "is_player_poke_1_star",
        "is_enemy_poke_1_star", // 70
        "is_player_poke_2_star",
        "is_enemy_poke_2_star",
        "is_player_poke_3_star",
        "is_enemy_poke_3_star",
        "is_attacking_poke_star"
    ];

    protected override string[] ValueNames => StaticValueNames;
    protected override ref string[]? SortedValueIdNames => ref _sortedValueIdNames;
    private static string[]? _sortedValueIdNames;
    protected override ref int[]? IdToAlpha => ref _idToAlpha;
    private static int[]? _idToAlpha;
    protected override ref int[]? AlphaToId => ref _alphaToId;
    private static int[]? _alphaToId;
}