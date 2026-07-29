namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypePokeEyeState(string name = "state") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "closed" => 0,
            "open" => 1,
            "blinking" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "closed",
            1 => "open",
            2 => "blinking",
            _ => GetErrorStr(value)
        };
    }
}