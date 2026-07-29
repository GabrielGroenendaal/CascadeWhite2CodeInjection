namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeAICompareOperator(string name = "comp_operator") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str switch
        {
            "LT" => 0,
            "GT" => 1,
            "EQ" => 2,
            "NE" => 3,
            "AND" => 4,
            "NAND" => 5,
            "LTE" => 6,
            "GTE" => 7,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "LT",
            1 => "GT",
            2 => "EQ",
            3 => "NE",
            4 => "AND",
            5 => "NAND",
            6 => "LTE",
            7 => "GTE",
            _ => GetErrorStr(value)
        };
    }
}