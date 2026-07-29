namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCameraPos(string name = "pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "player_team" => 0,
            "enemy_team" => 1,
            "player_poke_1" => 2,
            "enemy_poke_1" => 3,
            "player_poke_2" => 4,
            "enemy_poke_2" => 5,
            "player_poke_3" => 6,
            "enemy_poke_3" => 7,
            "initial" => 8,
            "attack" => 9,
            "attack_2" => 10,
            "defend" => 11,
            "defend_2" => 12,
            "push" => 13,
            "zoom_out" => 14,
            "multi_attack" => 15,
            "multi_defend" => 16,
            "initial_orthographic" => 17,
            "orthographic" => 18,
            "zoom_out_rotation" => 19,
            "zoom_out_perspective" => 20,
            "zoom_out_attack" => 21,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "player_team",
            1 => "enemy_team",
            2 => "player_poke_1",
            3 => "enemy_poke_1",
            4 => "player_poke_2",
            5 => "enemy_poke_2",
            6 => "player_poke_3",
            7 => "enemy_poke_3",
            8 => "initial",
            9 => "attack",
            10 => "attack_2",
            11 => "defend",
            12 => "defend_2",
            13 => "push",
            14 => "zoom_out",
            15 => "multi_attack",
            16 => "multi_defend",
            17 => "initial_orthographic",
            18 => "orthographic",
            19 => "zoom_out_rotation",
            20 => "zoom_out_perspective",
            21 => "zoom_out_attack",
            _ => GetErrorStr(value)
        };
    }
}