namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeGaugeVisibilityState(string name = "state") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "hidden" => 0,
            "visible" => 1,
            "hidden_move" => 2,
            "visible_move" => 3,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "hidden",
            1 => "visible",
            2 => "hidden_move",
            3 => "visible_move",
            _ => GetErrorStr(value)
        };
    }
}