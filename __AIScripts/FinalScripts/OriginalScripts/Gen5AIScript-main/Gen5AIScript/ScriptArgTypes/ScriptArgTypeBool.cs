namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBool(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "false" => 0,
            "true" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "false",
            1 => "true",
            _ => GetErrorStr(value)
        };
    }
}