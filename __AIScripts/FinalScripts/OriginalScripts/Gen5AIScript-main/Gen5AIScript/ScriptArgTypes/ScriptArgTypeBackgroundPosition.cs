namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBackgroundPosition(string name = "pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "front" => 0,
            "back" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "front",
            1 => "back",
            _ => GetErrorStr(value)
        };
    }
}