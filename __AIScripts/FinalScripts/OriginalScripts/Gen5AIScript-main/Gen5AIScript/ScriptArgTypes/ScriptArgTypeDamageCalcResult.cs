namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeDamageCalcResult(string name = "result") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "no_damage" => 0,
            "not_strongest" => 1,
            "is_strongest" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "no_damage",
            1 => "not_strongest",
            2 => "is_strongest",
            _ => GetErrorStr(value)
        };
    }
}