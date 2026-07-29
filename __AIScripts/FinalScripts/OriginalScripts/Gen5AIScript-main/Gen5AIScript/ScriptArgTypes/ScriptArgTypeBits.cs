namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeBits(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return Convert.ToUInt32(str.Replace("_", ""), 2);
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        var a = (byte)((value >> 24) & 0xFF);
        var b = (byte)((value >> 16) & 0xFF);
        var c = (byte)((value >> 8) & 0xFF);
        var d = (byte)(value & 0xFF);
        return $"{a:b8}_{b:b8}_{c:b8}_{d:b8}";
    }
}