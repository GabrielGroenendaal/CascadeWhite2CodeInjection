namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypePokeAnimState(string name = "state") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "idle" => 0,
            "paused" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "idle",
            1 => "paused",
            _ => GetErrorStr(value)
        };
    }
}