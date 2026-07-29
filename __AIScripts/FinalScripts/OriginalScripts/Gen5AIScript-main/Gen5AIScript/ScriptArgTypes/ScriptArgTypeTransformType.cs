namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeTransformType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "direct" => 0,
            "interpolated" => 1,
            "round_trip" => 2,
            "round_trip_2" => 3,
            "interpolated_2" => 4,
            "initial" => 5,
            "initial_direct" => 6,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "direct",
            1 => "interpolated",
            2 => "round_trip",
            3 => "round_trip_2",
            4 => "interpolated_2",
            5 => "initial",
            6 => "initial_direct",
            _ => GetErrorStr(value)
        };
    }
}