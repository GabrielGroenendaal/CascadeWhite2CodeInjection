namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBattleType(string name = "battle_type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "standard" => 0,
            "net_multi" => 1,
            "net_multi_vs_ai" => 2,
            "ai_multi" => 3,
            "ai_1v2" => 4,
            "ai_multi_vs_wild" => 5,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "standard",
            1 => "net_multi",
            2 => "net_multi_vs_ai",
            3 => "ai_multi",
            4 => "ai_1v2",
            5 => "ai_multi_vs_wild",
            _ => GetErrorStr(value)
        };
    }
}