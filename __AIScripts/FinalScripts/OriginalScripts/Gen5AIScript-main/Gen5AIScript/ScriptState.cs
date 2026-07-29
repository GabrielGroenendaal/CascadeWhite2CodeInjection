namespace Gen5AIScript;

public struct ScriptState
{
    public readonly int FuncOffset = 0;
    public ScriptArgType? ReturnType = null;

    public ScriptState(int funcOffset, ScriptArgType? returnType = null)
    {
        FuncOffset = funcOffset;
        ReturnType = returnType;
    }
}