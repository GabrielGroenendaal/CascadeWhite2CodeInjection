namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypePokePos(string name = "poke_pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "defender" => 0,
            "attacker" => 1,
            "defender_ally" => 2,
            "attacker_ally" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "defender",
            1 => "attacker",
            2 => "defender_ally",
            3 => "attacker_ally",
            _ => GetErrorStr(value)
        };
    }
}