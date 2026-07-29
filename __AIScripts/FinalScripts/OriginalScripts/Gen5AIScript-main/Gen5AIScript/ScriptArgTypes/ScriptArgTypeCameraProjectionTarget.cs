namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCameraProjectionTarget(string name = "target") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "all" => 0,
            "move" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "all",
            1 => "move",
            _ => GetErrorStr(value)
        };
    }
}