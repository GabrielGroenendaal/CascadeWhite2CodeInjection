using System.Globalization;
using System.Text.RegularExpressions;

namespace Gen5AIScript;

public abstract partial class ScriptArgType(string name)
{
    public string Name { get; private set; } = name;
    public abstract uint FromString(ScriptContext context, int offset, string str);
    public abstract string FromData(ScriptContext context, int funcOffset, uint value);

    protected static string GetErrorStr(uint value)
    {
        return $"ERROR [0x{value:X8}]";
    }
    
    protected static uint FromErrorStr(string str)
    {
        Console.WriteLine("the offending var is " + str);
        if (!str.StartsWith("ERROR [0x"))
            throw new Exception();

        var hexStr = str.Substring(9, 8);
        return uint.Parse(hexStr, NumberStyles.HexNumber);
    }

    protected static string SanitizeToken(string str)
    {
        return WhiteSpaceRegex().Replace(str, "");
    }

    public virtual void UpdateContext(ScriptContext context, ScriptState scriptState, int argOffset, uint value)
    {
    }

    [GeneratedRegex(@"\s+")]
    private static partial Regex WhiteSpaceRegex();
}