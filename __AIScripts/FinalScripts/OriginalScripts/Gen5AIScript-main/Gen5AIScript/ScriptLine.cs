namespace Gen5AIScript;

public abstract class ScriptLine(int offset)
{
    public int Offset { get; } = offset;
    
    public abstract void Write(byte[] buffer, ScriptContext context);
}