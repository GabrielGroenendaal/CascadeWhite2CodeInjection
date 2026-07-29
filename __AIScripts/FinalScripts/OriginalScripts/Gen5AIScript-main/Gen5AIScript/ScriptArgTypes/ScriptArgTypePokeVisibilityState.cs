namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypePokeVisibilityState(string name = "state") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "hidden" => 4,
            "visible" => 5,
            "pop_hide" => 6,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            4 => "hidden",
            5 => "visible",
            6 => "pop_hide",
            _ => GetErrorStr(value)
        };
    }
}