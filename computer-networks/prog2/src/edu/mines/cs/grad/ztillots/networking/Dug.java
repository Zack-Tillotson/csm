package edu.mines.cs.grad.ztillots.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

public class Dug {

    public static void main(String[] args) {

        // Parse arguments
        String target = args[0];
        String nameServer = args[1];

        // Do lookup
        Dug prog = new Dug();
        List<DugResponse> responses = prog.doDugCommand(target, nameServer);

        // Print results
        for (DugResponse response : responses)
            System.out.println(response.type + " " + response.ip + " " + response.authFlag);

    }

    // Main command to query the name server
    List<DugResponse> doDugCommand(String target, String nameServer) {

        DatagramSocket socket = null;

        byte[] address = new byte[4];
        for (int i = 0; i < 4; i++) {
            address[i] = Byte.parseByte(nameServer.split("\\.")[i]);
        }
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            e.printStackTrace();
        }

        // Send out the command
        byte[] command = getCommandStringForm(target);
        try {
            socket.send(new DatagramPacket(command, command.length, InetAddress.getByAddress(address), 53));
        } catch (UnknownHostException e1) {
            e1.printStackTrace();
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        // Get the response from the name server
        byte[] buffer = new byte[2048];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.receive(packet);
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        List<DugResponse> resp = getResponseStringForm(packet);

        // Clean up
        socket.close();

        return resp;

    }

    // DNS Query format ////////////////////////////
    // Header //////////////////////////////////////
    // ID 2 bytes (anything)
    // QR Flag 1 bit (0 for query)
    // Op Code 4 bits (0 is what we want)
    // Authoritative flag 1 bit (response only)
    // Truncated 1 bit (response only)
    // Recursion desired 1 bit (request only)
    // Recursion available 1 bit (response only)
    // Empty 3 bits
    // Response code 4 bits (response only)
    // Question count 2 bytes
    // Answer count 2 bytes
    // Authoritative name server count 2 bytes
    // Additional count 2 bytes
    // Body - Each record //////////////////////////
    // Question name 1 byte for length, then that many bytes
    // Question type 2 bytes (1 for TYPE A, what we want)
    // Question class 2 bytes (1 for internet)

    // Formats the query into a string
    public byte[] getCommandStringForm(String target) {

        int length = 12 + 1 + target.length() + 4 + 1;

        byte[] command = new byte[length];

        command[0] = ((Integer) 0).byteValue(); // Header flags and such
        command[1] = ((Integer) 42).byteValue();
        command[2] = ((Integer) 0).byteValue();
        command[3] = ((Integer) 0).byteValue(); // End of header
        command[4] = ((Integer) 0).byteValue(); // Question count
        command[5] = ((Integer) 1).byteValue();
        command[6] = ((Integer) 0).byteValue(); // Response counts
        command[7] = ((Integer) 0).byteValue();
        command[8] = ((Integer) 0).byteValue(); // Response counts
        command[9] = ((Integer) 0).byteValue();
        command[10] = ((Integer) 0).byteValue();// Response counts
        command[11] = ((Integer) 0).byteValue();
        command[12] = ((Integer) (target.length() - 4)).byteValue(); // Length of name
        for (int i = 0; i < target.length(); i++) { // The name
            char charAt = target.charAt(i);
            if (charAt == '.')
                command[13 + i] = ((Integer) 3).byteValue();
            else
                command[13 + i] = (byte) charAt;
        }
        command[13 + target.length()] = ((Integer) 0).byteValue(); // A null
        command[14 + target.length()] = ((Integer) 0).byteValue(); // The type
        command[15 + target.length()] = ((Integer) 1).byteValue();
        command[16 + target.length()] = ((Integer) 0).byteValue(); // The class
        command[17 + target.length()] = ((Integer) 1).byteValue();

        return command;

    }

    // DNS Query format ////////////////////////////
    // Header //////////////////////////////////////
    // ID 2 bytes (anything)
    // QR Flag 1 bit (0 for query)
    // Op Code 4 bits (0 is what we want)
    // Authoritative flag 1 bit (response only)
    // Truncated 1 bit (response only)
    // Recursion desired 1 bit (request only)
    // Recursion available 1 bit (response only)
    // Empty 3 bits
    // Response code 4 bits (response only)
    // Question count 2 bytes
    // Answer count 2 bytes
    // Authoritative name server count 2 bytes
    // Additional count 2 bytes
    // Body - Each record //////////////////////////
    // Question name 1 byte for length, then that many bytes
    // Question type 2 bytes (1 for all records, what we want)
    // Question class 2 bytes (1 for internet)
    public List<DugResponse> getResponseStringForm(DatagramPacket p) {

        List<DugResponse> ret = new ArrayList<DugResponse>();

        byte[] data = p.getData();

        int responseId = data[0] * 256 + data[1];
        int responseCode = data[2] / 8 % 16;
        int authoritativeFlag = data[2] / 4 % 2;

        if (responseCode == 0) {

            int answerCount = data[7];
            int nsCount = data[9];

            int offset = 28;
            for (int i = 0; i < answerCount; i++) {
                int rtype = data[offset + 2] * 256 + data[offset + 3];
                int rclass = data[offset + 4] * 256 + data[offset + 5];
                int ttl = data[offset + 6] * 256 * 256 * 256 + data[offset + 7] * 256 * 256 + data[offset + 8] * 256
                        + data[offset + 9];
                int length = data[offset + 10] * 256 + data[offset + 11];
                String address = convertToUnsigned((int) data[offset + 12]) + "."
                        + convertToUnsigned((int) data[offset + 13]) + "." + convertToUnsigned((int) data[offset + 14])
                        + "." + convertToUnsigned((int) data[offset + 15]);

                offset += 16;

                if (rtype == 1)
                    ret.add(new DugResponse(rtype, ttl, address, authoritativeFlag));
            }

        }

        return ret;
    }

    public int convertToUnsigned(int in) {
        if (in < 0) {
            return 256 + in;
        } else {
            return in;
        }

    }
}
