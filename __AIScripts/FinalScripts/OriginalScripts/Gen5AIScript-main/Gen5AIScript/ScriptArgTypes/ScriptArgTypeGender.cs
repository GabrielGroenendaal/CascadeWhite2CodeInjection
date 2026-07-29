namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeGender(string name = "gender") : ScriptArgType(name)
{

    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "male" => 0,
            "female" => 1,
            "unknown" => 2,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "male",
            1 => "female",
            2 => "unknown",
            _ => GetErrorStr(value)
        };
    }
}