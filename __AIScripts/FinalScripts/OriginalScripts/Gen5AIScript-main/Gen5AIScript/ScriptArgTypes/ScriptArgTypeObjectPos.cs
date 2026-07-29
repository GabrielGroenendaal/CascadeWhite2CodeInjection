namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeObjectPos(string name = "pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "player_poke" => 0,
            "enemy_poke" => 1,
            "player_poke_1" => 2,
            "enemy_poke_1" => 3,
            "player_poke_2" => 4,
            "enemy_poke_2" => 5,
            "player_poke_3" => 6,
            "enemy_poke_3" => 7,
            "player_trainer" => 8,
            "enemy_trainer" => 9,
            "player_trainer_1" => 10,
            "enemy_trainer_1" => 11,
            "player_trainer_2" => 12,
            "enemy_trainer_2" => 13,
            "attacking_poke" => 14,
            "attacking_pokes" => 15,
            "defending_poke" => 16,
            "defending_pokes" => 17,
            "all_pokes" => 18,
            "player_side" => 19,
            "enemy_side" => 20,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "player_poke",
            1 => "enemy_poke",
            2 => "player_poke_1",
            3 => "enemy_poke_1",
            4 => "player_poke_2",
            5 => "enemy_poke_2",
            6 => "player_poke_3",
            7 => "enemy_poke_3",
            8 => "player_trainer",
            9 => "enemy_trainer",
            10 => "player_trainer_1",
            11 => "enemy_trainer_1",
            12 => "player_trainer_2",
            13 => "enemy_trainer_2",
            14 => "attacking_poke",
            15 => "attacking_pokes",
            16 => "defending_poke",
            17 => "defending_pokes",
            18 => "all_pokes",
            19 => "player_side",
            20 => "enemy_side",
            _ => GetErrorStr(value)
        };
    }
}