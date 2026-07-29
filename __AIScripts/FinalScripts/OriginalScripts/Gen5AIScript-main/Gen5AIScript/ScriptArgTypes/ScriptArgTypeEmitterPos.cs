namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeEmitterPos(string name = "pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "player_side" => 0,
            "enemy_side" => 1,
            "player_poke_1" => 2,
            "enemy_poke_1" => 3,
            "player_poke_2" => 4,
            "enemy_poke_2" => 5,
            "player_poke_3" => 6,
            "enemy_poke_3" => 7,
            "none" => 8,
            "attacking_side" => 9,
            "attacking_side_negative" => 10,
            "defending_side" => 11,
            "defending_side_negative" => 12,
            "orthographic_offset" => 13,
            "player_poke_1_double" => 14,
            "enemy_poke_1_double" => 15,
            "player_poke_2_double" => 16,
            "enemy_poke_2_double" => 17,
            "user_player_poke_1_double" => 18,
            "user_enemy_poke_1_double" => 19,
            "user_player_poke_2_double" => 20,
            "user_enemy_poke_2_double" => 21,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "player_side",
            1 => "enemy_side",
            2 => "player_poke_1",
            3 => "enemy_poke_1",
            4 => "player_poke_2",
            5 => "enemy_poke_2",
            6 => "player_poke_3",
            7 => "enemy_poke_3",
            8 => "none",
            9 => "attacking_side",
            10 => "attacking_side_negative",
            11 => "defending_side",
            12 => "defending_side_negative",
            13 => "orthographic_offset",
            14 => "player_poke_1_double",
            15 => "enemy_poke_1_double",
            16 => "player_poke_2_double",
            17 => "enemy_poke_2_double",
            18 => "user_player_poke_1_double",
            19 => "user_enemy_poke_1_double",
            20 => "user_player_poke_2_double",
            21 => "user_enemy_poke_2_double",
            _ => GetErrorStr(value)
        };
    }
}