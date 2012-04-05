package edu.mines.cs.grad.ztillots.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Dug {

    public static void main(String[] args) {

        // Parse arguments
        String target = args[0];
        String nameServer = args[1];

        System.out.println("Asking " + nameServer + " for IP addresses of " + target);

        // Do lookup
        Dug prog = new Dug();
        List<DugResponse> responses = prog.doDugCommand(target, nameServer);

        // Print results
        if (responses == null) {
            System.err.println("Socket timeout, no response recieved");
        } else if (responses.size() == 0) {
            System.out.println("No A records");
        } else {
            for (DugResponse response : responses)
                System.out.println(response.ip + " (Authoritative? " + response.authFlag + ")");
        }

    }

    // Main command to query the name server
    List<DugResponse> doDugCommand(String target, String nameServer) {

        DatagramSocket socket = null;

        byte[] address = new byte[4];
        for (int i = 0; i < 4; i++) {
            Integer parsedInt = (Integer) Integer.parseInt(nameServer.split("\\.")[i]);
            if (parsedInt > 128)
                parsedInt = parsedInt & 0xFF;
            address[i] = parsedInt.byteValue();
        }
        try {
            socket = new DatagramSocket();
            socket.setSoTimeout(3000); // Wait 3 seconds for responses
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
        } catch (SocketTimeoutException e1) {
            return null;
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        List<DugResponse> resp = getResponseStringForm(packet);

        // Clean up
        socket.close();

        // If there are no A records, but an NS/A record exists then ask it recursively.
        boolean hasARecord = false;
        for (DugResponse dr : resp) {
            if (dr.type.compareTo("A") == 0) {
                hasARecord = true;
            }
        }

        if (!hasARecord) {

            // Get an NS record we can use
            for (DugResponse dr : resp) {
                if (dr.type.compareTo("NS") == 0 && dr.ip != null) {
                    System.out.println("\tName server " + nameServer + " doesn't know, directed to ask " + dr.ip);
                    return doDugCommand(target, dr.ip);
                }
            }

        }

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
        String[] pieces = target.split("\\.");
        int offset = 12;
        for (String piece : pieces) {
            command[offset] = ((Integer) (piece.length())).byteValue(); // Length of name
            for (int i = 0; i < piece.length(); i++) { // The name
                command[offset + 1 + i] = (byte) piece.charAt(i);
            }
            offset = offset + 1 + piece.length();
        }
        command[offset++] = ((Integer) 0).byteValue(); // A null
        command[offset++] = ((Integer) 0).byteValue(); // The type
        command[offset++] = ((Integer) 1).byteValue();
        command[offset++] = ((Integer) 0).byteValue(); // The class
        command[offset++] = ((Integer) 1).byteValue();

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
        int authoritativeFlag = Math.abs(data[2] / 4 % 2);

        int questionCount = data[5];
        int answerCount = data[7];
        int nsCount = data[9];
        int addtlCount = data[11];

        int offset = 12;

        // Go to the end of the questions
        for (int i = 0; i < questionCount; i++) {
            while (data[offset] != 0)
                offset += data[offset] + 1;
            offset += 5;
        }

        // Answers
        for (int i = 0; i < answerCount; i++) {
            int rtype = data[offset + 2] * 256 + data[offset + 3];
            int rclass = data[offset + 4] * 256 + data[offset + 5];
            int ttl = data[offset + 6] * 256 * 256 * 256 + data[offset + 7] * 256 * 256 + data[offset + 8] * 256
                    + data[offset + 9];
            int length = data[offset + 10] * 256 + data[offset + 11];
            String address = convertToUnsigned((int) data[offset + 12]) + "."
                    + convertToUnsigned((int) data[offset + 13]) + "." + convertToUnsigned((int) data[offset + 14])
                    + "." + convertToUnsigned((int) data[offset + 15]);

            offset += 12 + length;

            if (rtype == 1 || rtype == 256)
                ret.add(new DugResponse(rtype, ttl, null, address, authoritativeFlag));
        }

        // Name servers
        for (int i = 0; i < nsCount; i++) {
            int rtype = data[offset + 2] * 256 + data[offset + 3];
            int rclass = data[offset + 4] * 256 + data[offset + 5];
            int ttl = data[offset + 6] * 256 * 256 * 256 + data[offset + 7] * 256 * 256 + data[offset + 8] * 256
                    + data[offset + 9];
            int length = data[offset + 10] * 256 + data[offset + 11];
            byte[] tempArray = Arrays.copyOfRange(data, offset + 12, offset + 12 + length);
            for (int j = 0; j < tempArray.length; j += convertToUnsigned((int) data[offset + 12 + j] + 1))
                tempArray[j] = 46; // .
            String address = null;
            String name = new String(tempArray, 1, tempArray.length - 1);

            offset += 12 + length;

            if (i == 0)
                ret.add(new DugResponse(rtype, ttl, name, null, authoritativeFlag));
        }

        // Additional
        for (int i = 0; i < addtlCount; i++) {
            String name = new String(data, offset, offset + 2);
            int rtype = data[offset + 2] * 256 + data[offset + 3];
            int rclass = data[offset + 4] * 256 + data[offset + 5];
            int ttl = data[offset + 6] * 256 * 256 * 256 + data[offset + 7] * 256 * 256 + data[offset + 8] * 256
                    + data[offset + 9];
            int length = data[offset + 10] * 256 + data[offset + 11];
            String address = convertToUnsigned((int) data[offset + 12]) + "."
                    + convertToUnsigned((int) data[offset + 13]) + "." + convertToUnsigned((int) data[offset + 14])
                    + "." + convertToUnsigned((int) data[offset + 15]);

            if (rtype == 1 || rtype == 256) {
                for (DugResponse dr : ret) {
                    if (dr.type.compareTo("NS") == 0) {
                        dr.ip = address;
                    }
                }
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
