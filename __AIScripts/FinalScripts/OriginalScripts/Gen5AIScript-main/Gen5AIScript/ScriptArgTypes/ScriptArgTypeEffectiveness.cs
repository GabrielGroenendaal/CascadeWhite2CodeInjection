namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeEffectiveness(string name = "type_effectiveness") : ScriptArgType(name)
{

    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "0x" => 0,
            "1/4x" => 1,
            "1/2x" => 2,
            "1x" => 3,
            "2x" => 4,
            "4x" => 5,
            _ => throw new ArgumentException($"Unknown Stat type \"{str}\"")
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "0x",
            1 => "1/4x",
            2 => "1/2x",
            3 => "1x",
            4 => "2x",
            5 => "4x",
            _ => throw new ArgumentException($"Could not coerce {value} into {Name}")
        };
    }
}