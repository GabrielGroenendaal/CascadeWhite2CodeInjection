namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeStatStage(string name = "stat_stage") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "-6" => 0,
            "-5" => 1,
            "-4" => 2,
            "-3" => 3,
            "-2" => 4,
            "-1" => 5,
            "+0" => 6,
            "+1" => 7,
            "+2" => 8,
            "+3" => 9,
            "+4" => 10,
            "+5" => 11,
            "+6" => 12,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "-6",
            1 => "-5",
            2 => "-4",
            3 => "-3",
            4 => "-2",
            5 => "-1",
            6 => "+0",
            7 => "+1",
            8 => "+2",
            9 => "+3",
            10 => "+4",
            11 => "+5",
            12 => "+6",
            _ => GetErrorStr(value)
        };
    }
}