namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMoveCameraType(string name = "type") : ScriptArgType(name)
{

    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "direct" => 0,
            "interpolated" => 1,
            "interpolated_relative" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "direct",
            1 => "interpolated",
            2 => "interpolated_relative",
            _ => GetErrorStr(value)
        };
    }
}