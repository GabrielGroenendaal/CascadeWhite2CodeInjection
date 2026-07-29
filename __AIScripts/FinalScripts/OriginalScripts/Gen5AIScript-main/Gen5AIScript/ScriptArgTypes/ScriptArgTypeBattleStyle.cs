namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBattleStyle(string name = "battle_style") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "single_battle" => 0,
            "double_battle" => 1,
            "triple_battle" => 2,
            "rotation_battle" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "single_battle",
            1 => "double_battle",
            2 => "triple_battle",
            3 => "rotation_battle",
            _ => GetErrorStr(value)
        };
    }
}