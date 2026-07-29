namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeSoundPan(string name = "pan") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "left" => 0,
            "right" => 1,
            "mono" => 2,
            "attacker" => 14,
            "defender" => 16,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "left",
            1 => "right",
            2 => "mono",
            14 => "attacker",
            16 => "defender",
            _ => GetErrorStr(value)
        };
    }
}