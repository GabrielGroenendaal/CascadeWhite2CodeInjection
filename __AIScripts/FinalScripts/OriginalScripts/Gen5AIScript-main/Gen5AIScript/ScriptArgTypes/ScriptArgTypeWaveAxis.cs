namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeWaveAxis(string name = "axis") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "x" => 0,
            "y" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "x",
            1 => "y",
            _ => GetErrorStr(value)
        };
    }
}