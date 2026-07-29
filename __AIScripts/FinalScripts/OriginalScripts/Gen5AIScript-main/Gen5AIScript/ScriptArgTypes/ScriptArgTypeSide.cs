namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeSide(string name = "side") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "player" => 0,
            "enemy" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "player",
            1 => "enemy",
            _ => GetErrorStr(value)
        };
    }
}