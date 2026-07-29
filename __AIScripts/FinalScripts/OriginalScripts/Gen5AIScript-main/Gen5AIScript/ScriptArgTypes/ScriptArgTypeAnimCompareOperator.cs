namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeAnimCompareOperator(string name = "comp_operator") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str switch
        {
            "EQ" => 0,
            "NE" => 1,
            "LT" => 2,
            "GT" => 3,
            "LE" => 4,
            "GE" => 5,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "EQ",
            1 => "NE",
            2 => "LT",
            3 => "GT",
            4 => "LE",
            5 => "GE",
            _ => GetErrorStr(value)
        };
    }
}