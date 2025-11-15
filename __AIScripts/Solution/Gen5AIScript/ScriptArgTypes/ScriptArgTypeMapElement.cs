namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMapElement(string name, ScriptArgType indexType, ScriptArgType valueType, int offset) : ScriptArgType(name)
{
    private ScriptArgType IndexType { get; } = indexType;
    private ScriptArgType ValueType { get; } = valueType;
    private int Offset { get; } = offset;


    public override uint FromString(ScriptContext context, int offset, string str)
    {
        var split = str.Split("=>", StringSplitOptions.TrimEntries);
        if (split.Length != 2)
            throw new Exception();

        return ValueType.FromString(context, Offset, split[1]);
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return $"{IndexType.FromData(context, -1, (uint)(dataOffset - Offset) / 4)} => {ValueType.FromData(context, Offset, value)}";
    }

    public override void UpdateContext(ScriptContext context, ScriptState scriptState, int offset, uint value)
    {
        base.UpdateContext(context, scriptState, offset, value);
        
        context.SetDataOffsetSectionType(offset, this);
    }
}