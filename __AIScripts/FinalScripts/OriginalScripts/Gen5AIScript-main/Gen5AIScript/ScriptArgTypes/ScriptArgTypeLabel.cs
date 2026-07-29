namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeLabel(string name = "address") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string? str)
    {
        if (str != null && context.TryGetLabelOffset(str[1..], out var value))
        {
            return (uint)(value - offset);
        }

        throw new ArgumentException($"Could not find label \"{str}\"");
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        var address = dataOffset + (int)value;
        var success = context.TryGetLabel(address, out var labelName);

        if (labelName == null)
            throw new Exception();

        return "&" + (success ? labelName : AddLabelToContext(context, dataOffset, value));
    }

    public override void UpdateContext(ScriptContext context, ScriptState scriptState, int argOffset, uint value)
    {
        base.UpdateContext(context, scriptState, argOffset, value);

        AddLabelToContext(context, argOffset, value);
    }

    private string AddLabelToContext(ScriptContext context, int argOffset, uint value)
    {
        var address = argOffset + (int)value;
        var labelName = $"{Name}_0x{address:X4}";
        context.AddLabel(labelName, address);

        return labelName;
    }
}