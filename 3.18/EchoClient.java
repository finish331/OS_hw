import java.net.*;
import java.util.Scanner;
import java.io.*;

public class EchoClient {
    public static void main(String[] args) {
        Scanner typed = new Scanner(System.in);
        try {
            /* make connection to server socket */
            Socket sock = new Socket("127.0.0.1", 6017);
            InputStream in = sock.getInputStream();
            DataOutputStream dataOutput =new DataOutputStream(sock.getOutputStream());
            ByteArrayOutputStream byteArrayBuffer = new ByteArrayOutputStream();
            while (true) {
                String s = typed.nextLine();
                byte[] byteMessage = s.getBytes();
                String msg = new String(byteMessage ,"UTF-8");
                if (msg.equals("close")) {
                    sock.close();
                    break;
                }
                else{
                    dataOutput.write(byteMessage);
                    int nRead;
                    byte[] data = new byte[1024];
                    if ((nRead = in.read(data, 0, data.length))!= -1) {
                        byteArrayBuffer.write(data, 0, nRead);
                    }
                    byteArrayBuffer.flush();
                    String respond = new String(byteArrayBuffer.toByteArray(),"UTF-8");
                    System.out.println("Server: " + respond);
                    byteArrayBuffer.reset();
                }
            }
            
            
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
