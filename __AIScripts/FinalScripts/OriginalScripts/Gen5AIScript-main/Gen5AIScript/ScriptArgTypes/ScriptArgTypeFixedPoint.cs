namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeFixedPoint(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        if (double.TryParse(str, out var value))
        {
            return (uint)(int)Math.Round(value * 4096.0);
        }

        throw new ArgumentException($"Failed to coerce {str} into {Name}");
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return $"{(int)value / 4096.0:N4}";
    }
}