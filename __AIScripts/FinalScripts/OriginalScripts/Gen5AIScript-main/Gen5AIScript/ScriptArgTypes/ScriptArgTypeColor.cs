using System.Globalization;

namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeColor(string name = "color") : ScriptArgType(name)
{
    private static uint Expand(uint value) => (value * 510 + 31) / 62;
    private static uint Compress(uint value) => (value * 62 + 255) / 510;

    public override uint FromString(ScriptContext context, int offset, string str)
    {
        if (!str.StartsWith('#') || str.Length != 7 || !uint.TryParse(str[1..], NumberStyles.HexNumber, CultureInfo.InvariantCulture, out var value))
            throw new ArgumentException($"Failed to coerce {str} into {Name}");

        var red = Compress((value >> 16) & 0xFF);
        var green = Compress((value >> 8) & 0xFF);
        var blue = Compress(value & 0xFF);

        return red | (green << 5) | (blue << 10);
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        var red = Expand(value & 0x1F);
        var green = Expand((value >> 5) & 0x1F);
        var blue = Expand((value >> 10) & 0x1F);

        var color = (red << 16) | (green << 8) | blue;

        return $"#{color:x6}";
    }
}