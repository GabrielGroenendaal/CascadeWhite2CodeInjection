namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBackgroundType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "platform" => 0,
            "field" => 1,
            "platform_field" => 2,
            "animations" => 3,
            "all" => 4,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "platform",
            1 => "field",
            2 => "platform_field",
            3 => "animations",
            4 => "all",
            _ => GetErrorStr(value)
        };
    }
}