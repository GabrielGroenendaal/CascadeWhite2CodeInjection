namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCapturePos(string name = "pos") : ScriptArgType(name)
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
            "throw" => 8,
            "attacking_poke" => 9,
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
            8 => "throw",
            9 => "attacking_poke",
            _ => GetErrorStr(value)
        };
    }
}