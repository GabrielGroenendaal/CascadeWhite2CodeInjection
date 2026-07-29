namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeStored(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        var returnType = context.ReturnType;
        return returnType?.FromString(context, offset, str) ?? FromErrorStr(str);
    }

    public override string FromData(ScriptContext context, int funcOffset, uint value)
    {
        if (context.ReturnType != null)
            return context.ReturnType.FromData(context, funcOffset, value);

        var intArg = new ScriptArgTypeInt(Name);
        return intArg.FromData(context, funcOffset, value);
    }
}