namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeChangeSoundPropertyType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "interpolated" => 0,
            "round trip" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "interpolated",
            1 => "round trip",
            _ => GetErrorStr(value)
        };
    }
}