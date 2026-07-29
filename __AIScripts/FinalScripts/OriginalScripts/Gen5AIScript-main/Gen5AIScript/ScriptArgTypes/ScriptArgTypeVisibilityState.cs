namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeVisibilityState(string name = "state") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "visible" => 0,
            "hidden" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "visible",
            1 => "hidden",
            _ => GetErrorStr(value)
        };
    }
}