namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCircleShift(string name = "shift") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "horizontal_positive" => 0,
            "horizontal_negative" => 1,
            "vertical_positive" => 2,
            "vertical_negative" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "horizontal_positive",
            1 => "horizontal_negative",
            2 => "vertical_positive",
            3 => "vertical_negative",
            _ => GetErrorStr(value)
        };
    }
}