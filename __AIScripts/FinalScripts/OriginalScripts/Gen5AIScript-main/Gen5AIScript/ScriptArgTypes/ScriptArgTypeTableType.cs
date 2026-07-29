namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeTableType(string name = "table_type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "move_effect" => 0,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "move_effect",
            _ => GetErrorStr(value)
        };
    }
}