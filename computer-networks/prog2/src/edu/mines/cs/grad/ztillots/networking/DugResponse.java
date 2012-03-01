package edu.mines.cs.grad.ztillots.networking;

public class DugResponse {
    public String type;
    public int ttl;
    public String ip;
    public boolean authFlag;

    public DugResponse(int type, int ttl, String ip, int authFlag) {
        this.type = type == 1 ? "A" : "UN";
        this.ttl = ttl;
        this.ip = ip;
        this.authFlag = authFlag == 1;
    }
}