namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeSoundProperty(string name = "property") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "pitch" => 0,
            "volume" => 1,
            "pan" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "pitch",
            1 => "volume",
            2 => "pan",
            _ => GetErrorStr(value)
        };
    }
}