namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeEmitterMoveType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "static" => 0,
            "linear" => 1,
            "arc" => 2,
            "arc_2" => 3,
            "offset" => 4,
            "vertical_wave" => 5,
            "horizontal_wave" => 6,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "static",
            1 => "linear",
            2 => "arc",
            3 => "arc_2",
            4 => "offset",
            5 => "vertical_wave",
            6 => "horizontal_wave",
            _ => GetErrorStr(value)
        };
    }
}