package AST;

public class TokenNode extends Node {
    public final String token;
    public final Integer line;

    public TokenNode(String token, Integer line) {
        this.token = token;
        this.line = line;
    }

    @Override
    protected String nodeInfo() {
        return String.format("%s token: %s line: %d", this.getClass().getSimpleName(), this.token, this.line);
    }
}
