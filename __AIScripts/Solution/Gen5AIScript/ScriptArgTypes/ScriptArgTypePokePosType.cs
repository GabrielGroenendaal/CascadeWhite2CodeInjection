namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypePokePosType(string name = "poke_pos_type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "defender_type1" => 0,
            "attacker_type1" => 1,
            "defender_type2" => 2,
            "attacker_type2" => 3,
            "move_type" => 4,
            "defender_ally_type1" => 5,
            "attacker_ally_type1" => 6,
            "defender_ally_type2" => 7,
            "attacker_ally_type2" => 8,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "defender_type1",
            1 => "attacker_type1",
            2 => "defender_type2",
            3 => "attacker_type2",
            4 => "move_type",
            5 => "defender_ally_type1",
            6 => "attacker_ally_type1",
            7 => "defender_ally_type2",
            8 => "attacker_ally_type2",
            _ => GetErrorStr(value)
        };
    }
}