package edu.mines.cs.grad.ztillots.networking;

public class DugResponse {
    public String type;
    public int ttl;
    public String ip;
    public String name;
    public boolean authFlag;

    public DugResponse(int type, int ttl, String name, String ip, int authFlag) {

        this.name = name;
        this.ttl = ttl;
        this.ip = ip;
        this.authFlag = authFlag == 1;

        if (type == 1 || type == 256) {
            this.type = "A";
        } else if (type == 2) { // NS
            this.type = "NS";
        } else {
            this.type = "UN";
        }

    }
}