import java.net.*;
import java.io.*;
import java.util.Random;
public class QuoteServer
{
    public static void main(String[] args) {
        try {
	    Random randow=new Random();
	    String[] quotes = {"Every burden is a blessing",
				"To live is to think",
				"With the new day comes new strength and new thoughts",
				"Every day brings new choices",
				"Start every day off with a smile and get it over with"};
            ServerSocket sock = new ServerSocket(6017);
            /* now listen for connections */
            while (true) {
		int i = randow.nextInt(5);
                Socket client = sock.accept();
                PrintWriter pout = new
                PrintWriter(client.getOutputStream(), true);
                /* write the Date to the socket */
                pout.println(quotes[i]);
                /* close the socket and resume */
                /* listening for connections */
                client.close();
            }
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
