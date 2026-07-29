namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeWindowType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "open_vertical" => 0,
            "close_vertical" => 1,
            "open_horizontal" => 2,
            "close_horizontal" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "open_vertical",
            1 => "close_vertical",
            2 => "open_horizontal",
            3 => "close_horizontal",
            _ => GetErrorStr(value)
        };
    }
}