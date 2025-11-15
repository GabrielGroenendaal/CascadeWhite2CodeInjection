namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeInt(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        if (int.TryParse(str, out var value))
        {
            return (uint)value;
        }

        throw new ArgumentException($"Failed to coerce {str} into {Name}");
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return ((int)value).ToString();
    }
}