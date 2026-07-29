namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMoveCategory(string name = "move_category") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "status" => 0,
            "physical" => 1,
            "special" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "status",
            1 => "physical",
            2 => "special",
            _ => GetErrorStr(value)
        };
    }
}