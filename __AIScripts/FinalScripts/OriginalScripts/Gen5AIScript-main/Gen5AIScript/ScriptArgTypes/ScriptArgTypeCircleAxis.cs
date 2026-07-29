namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCircleAxis(string name = "axis") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "x_ccw" => 0,
            "x_cw" => 1,
            "y_ccw" => 2,
            "y_cw" => 3,
            "z_ccw" => 4,
            "z_cw" => 5,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "x_ccw",
            1 => "x_cw",
            2 => "y_ccw",
            3 => "y_cw",
            4 => "z_ccw",
            5 => "z_cw",
            _ => GetErrorStr(value)
        };
    }
}