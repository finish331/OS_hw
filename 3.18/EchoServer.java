import java.net.*;
import java.util.ArrayList;
import java.io.*;
public class EchoServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(6017);
            System.out.println("Sever is connect");
            while (true) {
                Socket client = sock.accept();
		InputStream in = client.getInputStream();
                DataOutputStream out = new DataOutputStream(client.getOutputStream());
                ByteArrayOutputStream byteArrayBuffer = new ByteArrayOutputStream();
                while (true) {
                    int readData;
                    byte[] data = new byte[1024];
                    if ((readData = in.read(data,0,data.length))!= -1) {
                        byteArrayBuffer.write(data,0,readData);
                    }
                    else if((readData = in.read(data,0,data.length))== -1) {
                        break;
                    }
                    byteArrayBuffer.flush();
                    byte[] message = byteArrayBuffer.toByteArray();

                    String output =new String(message,"UTF-8");
                    System.out.println(output);
                    
                    out.write(message);
                    out.flush();
                    byteArrayBuffer.reset();
                }
		System.out.println("Sever is close");
                client.close();
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
