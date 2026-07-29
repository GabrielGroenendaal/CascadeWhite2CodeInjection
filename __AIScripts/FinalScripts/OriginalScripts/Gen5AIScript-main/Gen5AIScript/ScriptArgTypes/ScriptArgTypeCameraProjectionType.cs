namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeCameraProjectionType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "orthographic" => 0,
            "perspective" => 1,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "orthographic",
            1 => "perspective",
            _ => GetErrorStr(value)
        };
    }
}