namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBackgroundFadeType(string name = "fade_type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "none" => 0,
            "in" => 1,
            "out" => 2,
            "in_out" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "none",
            1 => "in",
            2 => "out",
            3 => "in_out",
            _ => GetErrorStr(value)
        };
    }
}