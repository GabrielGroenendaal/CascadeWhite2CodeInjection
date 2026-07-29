namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeDistortBackgroundDir(string name = "dir") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "horizontal" => 0,
            "vertical" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "horizontal",
            1 => "vertical",
            _ => GetErrorStr(value)
        };
    }
}