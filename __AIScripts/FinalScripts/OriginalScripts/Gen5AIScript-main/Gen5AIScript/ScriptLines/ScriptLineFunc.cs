namespace Gen5AIScript.ScriptLines;

public class ScriptLineFunc(int offset, ScriptFunc func, string[] args) : ScriptLine(offset)
{
    private ScriptFunc Func { get; } = func;
    private string[] Args { get; } = args;
    
    public override void Write(byte[] buffer, ScriptContext context)
    {
        BitConverter.TryWriteBytes(buffer.AsSpan(Offset), (ushort)Func.Id);
        
        // First pass for write
        for (var i = 0; i < Func.ArgCount; ++i)
        {
            var argType = Func.ArgTypes[i];
            var argStr = Args[i];
            var argOffset = Offset + 2 + i * 4;

            var argValue = argType.FromString(context, argOffset + 4, argStr);
            BitConverter.TryWriteBytes(buffer.AsSpan(argOffset), argValue);
        }

        Func.UpdateContext(context, buffer, Offset);
        
        // Second pass for context update
        for (var i = 0; i < Func.ArgCount; ++i)
        {
            var argType = Func.ArgTypes[i];
            var argOffset = Offset + 2 + i * 4;
            var argValue = BitConverter.ToUInt32(buffer.AsSpan(argOffset));
            
            var state = new ScriptState(Offset, context.ReturnType);
            argType.UpdateContext(context, state, argOffset + 4, argValue);
        }

        if (Func.ReturnType != null)
            context.ReturnType = Func.ReturnType;
    }
}