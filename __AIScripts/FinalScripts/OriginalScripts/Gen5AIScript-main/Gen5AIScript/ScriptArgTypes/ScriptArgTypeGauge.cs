namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeGauge(string name = "gauge") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "player" => 0,
            "enemy" => 1,
            "all" => 2,
            "attacker" => 3,
            "defender" => 4,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "player",
            1 => "enemy",
            2 => "all",
            3 => "attacker",
            4 => "defender",
            _ => GetErrorStr(value)
        };
    }
}